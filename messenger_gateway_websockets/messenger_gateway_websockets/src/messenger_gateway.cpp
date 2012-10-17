/*
 * This file is part of WorkESB.
 *
 *  WorkESB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  WorkESB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with WorkESB.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Created on: 25 fevr. 2011
 *      Author: Marc Buils (MATIS - http://www.matis-group.com)
 *
 * messenger_gateway.cpp: definit les fonctions exportees pour l'application DLL.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/time.h>

#include "../../lib/libwebsockets.h"

#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

#include <json/json.h>
#include <WESBMessenger.h>
#include "Log.h"

#define MAX_QUEUEING_SIZE WESBMESSENGER_MAX_QUEUEING_SIZE

#ifdef _WIN32
#define DLLAPI  __declspec(dllexport)
#else
#define DLLAPI
#endif

namespace messenger_gateway_websocket
{

string method;
Json::Value config;			// config file
int connection = 0;			// current connection (0, 1)

struct message_struct {
	union {
		int _i;
		float _f;
		char* _s;

		int* _qi;
		float* _qf;
		char** _qs;
	} value;
	int type;
	int size;
	int queuing;
	int id;
};
map<int, map<string,message_struct*> > consumer;
map<int, map<string,message_struct*> > producer;


// Used functions
#define addError( p_error ) (error[ error.isArray() ? error.size() : 0 ] = p_error)


string strreplace( string p_search, string p_replace, string p_value ){
	string _return = "";
	int _start = 0;
	int _end = 0;

	while ( (_end = p_value.find(p_search, _start)) != string::npos )
	{
		_return += p_value.substr( _start, _end-_start );
		_return += p_replace;
		_start = _end+p_search.size();
	}
	_return += p_value.substr(_start);

	return _return;
}


enum demo_protocols {
	/* always first */
	PROTOCOL_HTTP = 0,

	PROTOCOL_WESBMESSENGER,

	/* always last */
	DEMO_PROTOCOL_COUNT
};

int g_continue = false;

/* this protocol server (always the first one) just knows how to do HTTP */

static int callback_http(struct libwebsocket_context * context,
		struct libwebsocket *wsi,
		enum libwebsocket_callback_reasons reason, void *user,
							   void *in, size_t len)
{
	switch (reason) {
	case LWS_CALLBACK_HTTP:
		{
			if ( !in ){
				break;
			}
			Log::get()->add( Log::LEVEL_INFO, (string)"serving HTTP URI " + (char *)in );

			string _filename = config.get("PATH", "www").asString() + (const char*)in;
			if ( ((char*)in)[strlen((const char*)in) - 1] == '/' ){
				_filename = config.get("PATH", "www").asString() + (char*)in + "index.html";
			}
			size_t _pos = _filename.find_last_of(".");
			size_t _posend = _filename.find_first_of("?");
			if ( _posend != string::npos ){
				_filename = _filename.substr(0, _posend);
			}
			std::ifstream _file( _filename.c_str()  );
			if ( _file.fail() || _pos == string::npos || !config["CONTENT_TYPES"].isMember( _filename.substr(_pos+1) ) ) {
				char buf[512];
				char *p = buf;
				p += sprintf(p, "HTTP/1.0 404 Not Found\x0d\x0a"
					"Server: wesbmessenger\x0d\x0a"
					"Content-type: text/html\x0d\x0a"
					"Content-Length: 117\x0d\x0a"
					"\x0d\x0a"
					"<HTML>\x0d\x0a"
					"<HEAD><TITLE>File Not Found</TITLE>\x0d\x0a"
					"</HEAD>\x0d\x0a"
					"<BODY>"
					"<H1>HTTP Error 404: File Not Found</h2>\x0d\x0a"
					"</BODY></HTML>\x0d\x0a"
				);

				libwebsocket_write(wsi, (unsigned char *)buf, p - buf,
										LWS_WRITE_HTTP);
			} else {
				if (libwebsockets_serve_http_file(wsi, _filename.c_str(), config["CONTENT_TYPES"][_filename.substr(_pos+1)].asString().c_str() ))
					Log::get()->add(Log::LEVEL_ERROR, (string)"Failed to send file: " + _filename + "(" + config["CONTENT_TYPES"][_filename.substr(_pos+1)].asString() );
				break;
			}
		}
		break;

	default:
		break;
	}

	return 0;
}


/* wesbmessenger protocol */

struct per_session_data__wesbmessenger {
	int id;
	int updated;
};

static int
callback_wesbmessenger(struct libwebsocket_context * context,
			struct libwebsocket *wsi,
			enum libwebsocket_callback_reasons reason,
					       void *user, void *in, size_t len)
{
//	unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 512 +
//						  LWS_SEND_BUFFER_POST_PADDING];
//	unsigned char *p = &buf[LWS_SEND_BUFFER_PRE_PADDING];
	struct per_session_data__wesbmessenger *pss = (per_session_data__wesbmessenger *)user;

	switch (reason) {

	case LWS_CALLBACK_ESTABLISHED:
		{
			Log::get()->add( Log::LEVEL_INFO, "Connexion started" );
			pss->id = -1;
			pss->updated = 0;
		}
		break;


	case LWS_CALLBACK_CLOSED:
		{
			int _i=0, _id=pss->id;
			map<string,message_struct*>::iterator _it;
			Log::get()->add( Log::LEVEL_INFO, "Connexion stopped");

			if ( pss->id >= 0 ){
				Log::get()->add( Log::LEVEL_INFO, "WESBMessenger unreg");
				WESBMessenger_unreg_full( pss->id );

	    		for ( _it = producer[ _id ].begin(); _it != producer[ _id ].end(); ++_it )
	    		{
	    			if ( _it->second->queuing != 0 )
	    			{
	    				switch ( _it->second->type )
	    				{
	    				case TYPE_INT:
	    					if ( _it->second->value._qi != 0 )
	    					{
	    						delete [] _it->second->value._qi;
	    					}
	    					break;
	    				case TYPE_FLOAT:
	    					if ( _it->second->value._qf != 0 )
	    					{
	    						delete [] _it->second->value._qf;
	    					}
	    					break;
	    				case TYPE_STRING:
	    					for ( _i=0; _i < _it->second->size; _i++ )
	    					{
	    						delete [] _it->second->value._qs[ _i ];
	    					}
	    					if ( _it->second->value._qs != 0 )
	    					{
	    						free( _it->second->value._qs );
	    					}
	    					break;
	    				}
	    			}
	    			else
	    			{
	    				switch ( _it->second->type )
	    				{
						case TYPE_STRING:
							if ( _it->second->value._s != 0 )
							{
								delete [] _it->second->value._s;
							}
							break;
						}
	    			}
					delete _it->second;
	    		}

				consumer.erase(pss->id);
				producer.erase(pss->id);
			}
		}
		break;

	/*
	 * in this protocol, we just use the broadcast action as the chance to
	 * send our own connection-specific data and ignore the broadcast info
	 * that is available in the 'in' parameter
	 */

	case LWS_CALLBACK_RECEIVE:
		{
			Json::Value _request;
			Json::Reader _reader;
			Json::Value data;			// data returned by the ws
			Json::Value error;			// error list
			static string _lastIn = "";
			string _in = _lastIn + (string)((char*)in);
			_lastIn = "";

			Log::get()->add( Log::LEVEL_INFO, "Receive data" );
			
			if ( !_reader.parse( _in.c_str(), _request ) ){
				Log::get()->add( Log::LEVEL_ERROR, (string)"Request parsing error: " + _in );	
				_lastIn =  _in;
				g_continue = true;
				break;
			}
			g_continue = false;
			Log::get()->add( Log::LEVEL_INFO, "Receive data parsed: " + _in );

			// get request params
			string _function = _request["function"].asString();
			
			// Log
			ostringstream _s;
			_s << "Function: " << _function << " - id: " << pss->id;
			Log::get()->add( Log::LEVEL_INFO, _s.str() );

			if ( _function.compare("init") == 0
				&& _request.isMember("domain") )
			{
				string _domain = _request["domain"].asString();
				string _name = _request["name"].asString();

				Log::get()->add( Log::LEVEL_INFO, "start init" );
	    		pss->id = WESBMessenger_init_full( (char*)_domain.c_str(), (char*)_name.c_str() );
				Log::get()->add( Log::LEVEL_INFO, "end init" );

				// Log
				_s.str("");
				_s << "Init: " << _function << " - id: " << pss->id << " - domain: " << _domain;
				Log::get()->add( Log::LEVEL_INFO, _s.str() );

	    		consumer[pss->id];
	    		producer[pss->id];

				data["return"] = pss->id;
			}
			else if ( _function.compare("consumSampling") == 0 
					&& _request.isMember("name")
					&& _request.isMember("type") )
			{
	    		int _id = pss->id;
				string _name = _request["name"].asString();
	    		int _type = _request["type"].asInt();

	    		if ( consumer.find( _id ) == consumer.end() )
	    		{
					ostringstream ss;
					ss << "consumSampling - MessengerManager not initialized: " << _id;
	    			addError( ss.str() );
	    		}
	    		else if ( consumer[ _id ].find( _name ) != consumer[ _id ].end() )
	    		{
	    			data["return"] = consumer[ _id ][ _name ]->id;
	    		}
	    		else
	    		{
	    			message_struct* _var = new message_struct;
	    			consumer[ _id ][_name] = _var;
	    			_var->type = _type;
	    			_var->queuing = 0;
	    			switch ( _type )
	    			{
	    			case TYPE_INT:
	    				_var->id = WESBMessenger_consumSampling_full( _id, (char*)_name.c_str(), &_var->value._i, _type );
	    				break;
	    			case TYPE_FLOAT:
	    				_var->id = WESBMessenger_consumSampling_full( _id, (char*)_name.c_str(), &_var->value._f, _type );
	    				break;
	    			case TYPE_STRING:
	    				_var->id = WESBMessenger_consumSampling_full( _id, (char*)_name.c_str(), &_var->value._s, _type );
	    				break;
	    			}

	    			data["return"] = _var->id;
	    		}
			}
			else if ( _function.compare("produceSampling") == 0
					&& _request.isMember("name")
					&& _request.isMember("type") )
			{
	    		int _id = pss->id;
				string _name = _request["name"].asString();
	    		int _type = _request["type"].asInt();

	    		if ( producer.find( _id ) == producer.end() )
	    		{
					ostringstream ss;
					ss << "produceSampling - MessengerManager not initialized: " << _id;
	    			addError( ss.str() );
	    		}
	    		else if ( producer[ _id ].find( _name ) != producer[ _id ].end() )
	    		{
	    			data["return"] = producer[ _id ][ _name ]->id;
	    		}
	    		else
	    		{
	    			message_struct* _var = new message_struct;
	    			producer[ _id ][_name] = _var;
	    			_var->type = _type;
	    			_var->queuing = 0;
	    			switch ( _type )
	    			{
	    			case TYPE_INT:
	    				_var->value._i = 0;
	    				_var->id = WESBMessenger_produceSampling_full( _id, (char*)_name.c_str(), &_var->value._i, _type );
	    				break;
	    			case TYPE_FLOAT:
	    				_var->value._f = 0;
	    				_var->id = WESBMessenger_produceSampling_full( _id, (char*)_name.c_str(), &_var->value._f, _type );
	    				break;
	    			case TYPE_STRING:
	    				_var->value._s = 0;
	    				_var->id = WESBMessenger_produceSampling_full( _id, (char*)_name.c_str(), &_var->value._s, _type );
	    				break;
	    			}
	    		}
			}
			else if ( _function.compare("consumQueuing") == 0
					&& _request.isMember("name")
					&& _request.isMember("type") )
			{
	    		int _id = pss->id;
				string _name = _request["name"].asString();
				Log::get()->add( Log::LEVEL_INFO, _request["name"].asString() );
	    		int _type = _request["type"].asInt();

	    		if ( consumer.find( _id ) == consumer.end() )
	    		{
					ostringstream ss;
					ss << "consumQueuing - MessengerManager not initialized: " << _id;
	    			addError( ss.str() );
				}
	    		else if ( consumer[ _id ].find( _name ) != consumer[ _id ].end() )
	    		{
					// Log
	    			data["return"] = consumer[ _id ][ _name ]->id;
	    		}
	    		else
	    		{
	    			message_struct* _var = new message_struct;
	    			consumer[ _id ][_name] = _var;
	    			_var->type = _type;
	    			_var->queuing = 1;
	    			_var->size = 0;
	    			switch ( _type )
	    			{
	    			case TYPE_INT:
	    				_var->id = WESBMessenger_consumQueuing_full( _id, (char*)_name.c_str(), &_var->value._qi, &_var->size, _type, MAX_QUEUEING_SIZE );
	    				break;
	    			case TYPE_FLOAT:
	    				_var->id = WESBMessenger_consumQueuing_full( _id, (char*)_name.c_str(), &_var->value._qf, &_var->size, _type, MAX_QUEUEING_SIZE );
	    				break;
	    			case TYPE_STRING:
	    				_var->id = WESBMessenger_consumQueuing_full( _id, (char*)_name.c_str(), &_var->value._qs, &_var->size, _type, MAX_QUEUEING_SIZE );
	    				break;
	    			}

	    			data["return"] = _var->id;
	    		}
			}
			else if ( _function.compare("produceQueuing") == 0
					&& _request.isMember("name")
					&& _request.isMember("type") )
			{
	    		int _id = pss->id;
				string _name = _request["name"].asString();
	    		int _type = _request["type"].asInt();

	    		if ( producer.find( _id ) == producer.end() )
	    		{
					ostringstream ss;
					ss << "produceQueuing - MessengerManager not initialized: " << _id;
	    			addError( ss.str() );
	    		}
	    		else if ( producer[ _id ].find( _name ) != producer[ _id ].end() )
	    		{
	    			data["return"] = producer[ _id ][ _name ]->id;
	    		}
	    		else
	    		{
	    			message_struct* _var = new message_struct;
	    			producer[ _id ][_name] = _var;
	    			_var->type = _type;
	    			_var->queuing = 1;
	    			_var->size = 0;
	    			switch ( _type )
	    			{
	    			case TYPE_INT:
	    				_var->value._qi = 0;
	    				_var->id = WESBMessenger_produceQueuing_full( _id, (char*)_name.c_str(), &_var->value._qi, &_var->size, _type );
	    				break;
	    			case TYPE_FLOAT:
	    				_var->value._qf = 0;
	    				_var->id = WESBMessenger_produceQueuing_full( _id, (char*)_name.c_str(), &_var->value._qf, &_var->size, _type );
	    				break;
	    			case TYPE_STRING:
	    				_var->value._qs = 0;
	    				_var->id = WESBMessenger_produceQueuing_full( _id, (char*)_name.c_str(), &_var->value._qs, &_var->size, _type );
	    				break;
	    			}

	    			data["return"] = _var->id;
	    		}
			}
			else if ( _function.compare("update") == 0 )
			{
	    		int _id = pss->id;
				Json::Value _postValues = _request["data"];
	    		Json::FastWriter _writer;
				Json::Value error;			// error list

				// log received data
	    		int _i, _j;
	    		map<string,message_struct*>::iterator _it;

	    		if ( _postValues.isMember("producer") )
	    		{
	    			for ( _it = producer[ _id ].begin(); _it != producer[ _id ].end(); ++_it )
	    			{
	    				Json::FastWriter _write;
	    				if ( _postValues["producer"].isMember( _it->first ) )
	    				{
	    					if ( _it->second->queuing != 0 )
	    					{
	    						if ( _postValues["producer"][ _it->first ].isArray() )
	    						{
									int _size = _postValues["producer"][ _it->first ].size();
									int _newSize = 0;

									switch ( _it->second->type )
									{
									case TYPE_INT:
										if ( _it->second->value._qi != 0 )
										{
											delete [] _it->second->value._qi;
										}

										// Count the new size
										for ( _i=0; _i < _size; _i++ )
										{
											if ( _postValues["producer"][ _it->first ][ _i ].isIntegral() )
											{
												_newSize++;
											}
			    							else
			    							{
			    								ostringstream ss;
			    								ss << "update - Value of a queuing producer is not an integer: " << _it->first << "[" << _i << "]";
			    				    			addError( ss.str() );
			    							}
										}

										// Allow correct buffer size
										_it->second->size = _newSize;
										_it->second->value._qi = new int[ _newSize ];

										// set data
										for ( _i=0, _j=0; _i < _size; _i++ )
										{
											if ( _postValues["producer"][ _it->first ][ _i ].isIntegral() )
											{
												_it->second->value._qi[ _j ] = _postValues["producer"][ _it->first ][ _i ].asInt();
												_j++;
											}
										}
										break;
									case TYPE_FLOAT:
										if ( _it->second->value._qf != 0 )
										{
											delete [] _it->second->value._qf;
										}

										// Count the new size
										for ( _i=0; _i < _size; _i++ )
										{
											if ( _postValues["producer"][ _it->first ][ _i ].isNumeric() )
											{
												_newSize++;
											}
			    							else
			    							{
			    								ostringstream ss;
			    								ss << "update - Value of a queuing producer is not a double: " << _it->first << "[" << _i << "]";
			    				    			addError( ss.str() );
			    							}
										}

										// Allow correct buffer size
										_it->second->size = _newSize;
										_it->second->value._qf = new float[ _newSize ];

										// set data
										for ( _i=0, _j=0; _i < _size; _i++ )
										{
											if ( _postValues["producer"][ _it->first ][ _i ].isNumeric() )
											{
												_it->second->value._qf[ _j ] = (float)_postValues["producer"][ _it->first ][ _i ].asDouble();
												_j++;
											}
										}
										break;
									case TYPE_STRING:
										for ( _i=0; _i < _it->second->size; _i++ )
										{
											delete [] _it->second->value._qs[ _i ];
										}
										if ( _it->second->value._qs != 0 )
										{
											free( _it->second->value._qs );
										}

										// Count the new size
										for ( _i=0; _i < _size; _i++ )
										{
											if ( _postValues["producer"][ _it->first ][ _i ].isString() )
											{
												_newSize++;
											}
			    							else
			    							{
			    								ostringstream ss;
			    								ss << "update - Value of a queuing producer is not a string: " << _it->first << "[" << _i << "]";
			    				    			addError( ss.str() );
			    							}
										}

										// Allow correct buffer size
										_it->second->size = _newSize;
										_it->second->value._qs = (char**)malloc( sizeof(char**) * _newSize );

										// set data
										for ( _i=0, _j=0; _i < _size; _i++ )
										{
											if ( _postValues["producer"][ _it->first ][ _i ].isString() )
											{
												_it->second->value._qs[ _j ] = new char[ 1 + _postValues["producer"][ _it->first ][ _i ].asString().size() ];
												strcpy( _it->second->value._qs[ _j ], _postValues["producer"][ _it->first ][ _i ].asCString() );
												_j++;
											}
										}
										break;
									}
	    						}
    							else
    							{
    								ostringstream ss;
    								ss << "update - Value of a queuing producer is not an array: " << _it->first;
    				    			addError( ss.str() );
    							}
	    					}
	    					else
	    					{
	    						switch ( _it->second->type )
	    						{
	    						case TYPE_INT:
	    							if ( _postValues["producer"][ _it->first ].isIntegral() )
	    							{
	    								_it->second->value._i = _postValues["producer"][ _it->first ].asInt();
	    							}
	    							else
	    							{
	    								ostringstream ss;
	    								ss << "update - Value of a sampling producer is not an integer: " << _it->first;
	    				    			addError( ss.str() );
	    							}
	    							break;
	    						case TYPE_FLOAT:
	    							if ( _postValues["producer"][ _it->first ].isNumeric() )
	    							{
	    								_it->second->value._f = (float)_postValues["producer"][ _it->first ].asDouble();
	    							}
	    							else
	    							{
	    								ostringstream ss;
	    								ss << "update - Value of a sampling producer is not a double: " << _it->first;
	    				    			addError( ss.str() );
	    							}
	    							break;
								case TYPE_STRING:
	    							if ( _postValues["producer"][ _it->first ].isString() )
	    							{
										if ( _it->second->value._s != 0 )
										{
											delete [] _it->second->value._s;
										}
										_it->second->value._s = new char[ _postValues["producer"][ _it->first ].asString().size() + 1 ];
										strcpy( _it->second->value._s, _postValues["producer"][ _it->first ].asCString() );
	    							}
	    							else
	    							{
	    								ostringstream ss;
	    								ss << "update - Value of a sampling producer is not a string: " << _it->first;
	    				    			addError( ss.str() );
	    							}
									break;
								}
	    					}
	    				}
	    			}
	    		}

				data["return"] = WESBMessenger_update_full( _id );
			
	    		// READ POST DATA
	    		Log::get()->add( Log::LEVEL_INFO, "Update Consumers");

    			for ( _it = consumer[ _id ].begin(); _it != consumer[ _id ].end(); ++_it )
    			{
   					if ( _it->second->queuing != 0 )
   					{
   						int _size = _it->second->size;
   						data["consumer"][ _it->first ] = Json::arrayValue;

   						switch ( _it->second->type )
   						{
   						case TYPE_INT:
   							for ( _i=0; _i < _size; _i++ )
							{
   								data["consumer"][ _it->first ][ _i ] = _it->second->value._qi[ _i ];
							}
   							break;
   						case TYPE_FLOAT:
   							for ( _i=0; _i < _size; _i++ )
							{
   								data["consumer"][ _it->first ][ _i ] = _it->second->value._qf[ _i ];
							}
   							break;
   						case TYPE_STRING:
    						for ( _i=0; _i < _size; _i++ )
							{
    							data["consumer"][ _it->first ][ _i ] = _it->second->value._qs[ _i ];
							}
   							break;
   						}
   					}
   					else
   					{
   						switch ( _it->second->type )
   						{
   						case TYPE_INT:
   							data["consumer"][ _it->first ] = _it->second->value._i;
   							break;
   						case TYPE_FLOAT:
   							data["consumer"][ _it->first ] = _it->second->value._f;
  							break;
						case TYPE_STRING:
							data["consumer"][ _it->first ] = _it->second->value._s;
							break;
						}
   					}
    			}

				// add error
				if ( !error.empty() )
				{
					Json::FastWriter _writer;
					Log::get()->add( Log::LEVEL_WARNING, "Request errors: " + _writer.write( error ) );

					data[ "error" ] = error;
				}

				// return the result
				data[ "function" ] = "update";
				string _json = _writer.write( data ) + "\n";
				unsigned char *buf = new unsigned char[LWS_SEND_BUFFER_PRE_PADDING + _json.size() + 1 + LWS_SEND_BUFFER_POST_PADDING];
				unsigned char *p = &buf[LWS_SEND_BUFFER_PRE_PADDING];
				sprintf((char *)p, "%s", _json.c_str());
				int n = libwebsocket_write(wsi, p, _json.size(), LWS_WRITE_TEXT);
				if (n < 0) {
					Log::get()->add( Log::LEVEL_ERROR, "ERROR writing to socket");
				}
				delete [] buf;
			}
		}
		break;

	default:
		break;
	}

	return 0;
}




/* list of supported protocols and callbacks */

static struct libwebsocket_protocols protocols[] = {
	/* first protocol must always be HTTP handler */

	{
		"http-only",		/* name */
		callback_http,		/* callback */
		0			/* per_session_data_size */
	},
	{
		"wesbmessenger",
		callback_wesbmessenger,
		sizeof(struct per_session_data__wesbmessenger),
	},
	{
		NULL, NULL, 0		/* End of list */
	}
};


struct libwebsocket_context *context;

} // namespace messenger_gateway_websocket

using namespace messenger_gateway_websocket;
// lib websocket
//static int close_testing;

extern "C" {
// FCGI initialisation
int DLLAPI onstart( char* p_configuration )
{
	int port;
	const char * interface = NULL;

	// config file reading
	Json::Reader _reader;
	bool _parsingSuccessful = _reader.parse( p_configuration, config );
	if ( !_parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		printf( "Failed to parse configuration\n%s", _reader.getFormatedErrorMessages().c_str());

		return -1;
	}

	// WebSockets Initialisation
	port = config.get("PORT", 80).asInt();
	context = libwebsocket_create_context(port, interface, protocols,
				libwebsocket_internal_extensions,
				NULL, NULL, -1, -1, 0);
	if (context == NULL) {
		Log::get()->add( Log::LEVEL_ERROR, "libwebsocket init failed");
		return -1;
	}

    Log::get()->add( Log::LEVEL_INFO, "Initialization");
	return 0;
}


/**
 * onupdate
 * Function called for each cycle
 *
 * @return sequencer_calling Messages to return
 */
int DLLAPI onupdate( )
{
	Log::get()->add( Log::LEVEL_INFO, "calling start" );

	do {
		libwebsocket_service(context, 50);
	} while ( g_continue );

	Log::get()->add( Log::LEVEL_INFO, "calling end" );
	return 0;
}

/*
 * Response
 */
int DLLAPI onstop( )
{
	libwebsocket_context_destroy(context);

	return 0;
}

} // extern "C"
