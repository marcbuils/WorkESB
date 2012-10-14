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
 */

// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

// -- SIMD Include
#include <dds/runtime.hpp>
#include <dds/topic.hpp>
#include <dds/writer.hpp>
#include <dds/reader.hpp>
#include <dds/traits.hpp>

// -- Shared Data Include
#include "gen/ccpp_Shared_Data.h"

// Logs
#include "Log.h"

// JSON
#include <json/json.h>


#ifdef WIN32
#include "Windows.h"
#define msecSleep(msec) Sleep(msec)
#else
#define msecSleep(msec) usleep(1000*(msec))
#endif



#ifdef _WIN32
#define DLL_API __declspec(dllexport)
#else
#define DLL_API
#endif

#include <stdio.h>
#include <vector>
using namespace std;

// BOOST
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time/local_time/local_time.hpp>

typedef const char* (*Shared_Func)(char* p_param);
typedef void (*CallBack_Func)(char* p_param);
typedef void (*Event_Func)(char* p_param);

#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_STRING 2

#define TYPE_SAMPLING 0
#define TYPE_QUEUING 1

#define EXTENSION_PARAMETER "PARAMETER__"
#define EXTENSION_RETURN_VAL "RETURNVAL__"
#define EXTENSION_EVENT "EVENT__"

typedef enum
{
	CONSUMER,
	PRODUCER,
	FUNCTION,
	CALL,
	EVENT,
	EVENT_INT		// Intern event
}type_com;

// functions declaration
extern "C" DLL_API int WESBMessenger_trigger_full( int p_id, char* p_name, char* p_params );

namespace wesbmessenger
{
struct data_struct {
	union {
		int *i;
		float *f;
		char **s;
		int **qi;
		float **qf;
		char ***qs;
		Shared_Func fsf;		// Function Shared Function
		data_struct *fsp;		// Function Structure Producer
		Event_Func fef;			// Function Event Function
	} value;
	int* size;
	int type;
	type_com com;
	int typeData;

	dds::TopicQos *tqos;
	union {
		dds::Topic<Shared_Data::DDS_int> *i;
		dds::Topic<Shared_Data::DDS_float> *f;
		dds::Topic<Shared_Data::DDS_string> *s;
		dds::Topic<Shared_Data::DDS_int> *qi;
		dds::Topic<Shared_Data::DDS_float> *qf;
		dds::Topic<Shared_Data::DDS_string> *qs;
	} topic;
	union {
		dds::DataReaderQos *reader;
		dds::DataWriterQos *writer;
	} dqos;
	union {
		dds::DataReader<Shared_Data::DDS_int> *ireader;
		dds::DataReader<Shared_Data::DDS_float> *freader;
		dds::DataReader<Shared_Data::DDS_string> *sreader;
		dds::DataReader<Shared_Data::DDS_int> *qireader;
		dds::DataReader<Shared_Data::DDS_float> *qfreader;
		dds::DataReader<Shared_Data::DDS_string> *qsreader;

		dds::DataWriter<Shared_Data::DDS_int> *iwriter;
		dds::DataWriter<Shared_Data::DDS_float> *fwriter;
		dds::DataWriter<Shared_Data::DDS_string> *swriter;
		dds::DataWriter<Shared_Data::DDS_int> *qiwriter;
		dds::DataWriter<Shared_Data::DDS_float> *qfwriter;
		dds::DataWriter<Shared_Data::DDS_string> *qswriter;
	} player;
};
struct struct_instance {
	struct_instance() { };
	struct_instance(string p_domain, string p_name) { this->m_domain = p_domain; this->name = p_name; };

	string name;
	dds::Subscriber &sub(){
		static  dds::Subscriber _return(this->m_domain);
		return _return;
	};
	dds::Publisher &pub(){
		static  dds::Publisher _return(this->m_domain);
		return _return;
	};
	vector<data_struct> datas;

private:
	string m_domain;
};
map<int, struct_instance> &instances() {
	static map<int, struct_instance> _return;
	return _return;
}
map< int, map<string,data_struct> > &triggers()
{
	static map< int, map<string,data_struct> > _return;
	return _return;
}
map< int, map<string,data_struct> > &calls()
{
	static map< int, map<string,data_struct> > _return;
	return _return;
}
map< int, map<string,CallBack_Func> > &responses()
{
	static map< int, map<string,CallBack_Func> > _return;
	return _return;
}

// Max queue size for functions or events
#define MAX_QUEUE_SIZE 50


dds::Runtime &runtime()
{
	static dds::Runtime _return;
	return _return;
}

// ping event
void event_ping_var( int p_id, int p_pos )
{
	Json::Value _infos;
	Json::FastWriter _writer;
	int _id = p_id;
	int _i = p_pos;

	_infos["name"] = instances()[_id].name;
	switch ( instances()[_id].datas[_i].com ) 
	{
		case CONSUMER:
		case PRODUCER:
		{
			_infos["variable"]["com"] = ( instances()[_id].datas[_i].com == PRODUCER ? "producer" : "consumer" );
			_infos["variable"]["queuing"] = ( instances()[_id].datas[_i].typeData == TYPE_SAMPLING ? false : true );
		
			switch ( instances()[_id].datas[_i].type ) {
				case TYPE_INT:
					_infos["variable"]["type"] = "int";
					_infos["variable"]["name"] = ( instances()[_id].datas[_i].typeData == TYPE_SAMPLING ? instances()[_id].datas[_i].topic.i->get_name() : instances()[_id].datas[_i].topic.qi->get_name() );
					break;
				case TYPE_FLOAT:
					_infos["variable"]["type"] = "float";
					_infos["variable"]["name"] = ( instances()[_id].datas[_i].typeData == TYPE_SAMPLING ? instances()[_id].datas[_i].topic.f->get_name() : instances()[_id].datas[_i].topic.qf->get_name() );
					break;
				case TYPE_STRING:
					_infos["variable"]["type"] = "string";
					_infos["variable"]["name"] = ( instances()[_id].datas[_i].typeData == TYPE_SAMPLING ? instances()[_id].datas[_i].topic.s->get_name() : instances()[_id].datas[_i].topic.qs->get_name() );
					break;
			}
		}
		break;
		case EVENT:
		{
			_infos["variable"]["com"] = "event";
			_infos["variable"]["name"] = instances()[_id].datas[_i].topic.qs->get_name().substr(std::strlen(EXTENSION_EVENT), -1);
		}
		break;
		case FUNCTION:
		{
			_infos["variable"]["com"] = "share";
			_infos["variable"]["name"] = instances()[_id].datas[_i].topic.qs->get_name().substr(std::strlen(EXTENSION_RETURN_VAL), -1);
		}
		break;
		default:
			return;
		}

		// others function vars
		if ( instances()[_id].datas[_i].typeData != TYPE_SAMPLING
			 && ( ( instances()[_id].datas[_i].com == CONSUMER  && std::strncmp( EXTENSION_RETURN_VAL, _infos["variable"]["name"].asString().c_str(), std::strlen(EXTENSION_RETURN_VAL) ) == 0 )
				|| ( instances()[_id].datas[_i].com == PRODUCER  && std::strncmp( EXTENSION_PARAMETER, _infos["variable"]["name"].asString().c_str(), std::strlen(EXTENSION_PARAMETER) ) == 0 )
				|| ( instances()[_id].datas[_i].com == CONSUMER  && std::strncmp( EXTENSION_PARAMETER, _infos["variable"]["name"].asString().c_str(), std::strlen(EXTENSION_PARAMETER) ) == 0 ) ) ) {
			return;
		}

		// shared function
		if ( instances()[_id].datas[_i].com == PRODUCER 
			 && instances()[_id].datas[_i].typeData != TYPE_SAMPLING
			 && std::strncmp( EXTENSION_RETURN_VAL, _infos["variable"]["name"].asString().c_str(), std::strlen(EXTENSION_RETURN_VAL) ) == 0 ) {
			_infos["variable"]["name"] = _infos["variable"]["name"].asString().substr(std::strlen(EXTENSION_RETURN_VAL), -1);
			_infos["variable"]["com"] = "share";
			_infos["variable"].removeMember("queuing");
		}

		// bind
		if ( instances()[_id].datas[_i].com == CONSUMER
			 && instances()[_id].datas[_i].typeData != TYPE_SAMPLING
			 && std::strncmp( EXTENSION_EVENT, _infos["variable"]["name"].asString().c_str(), std::strlen(EXTENSION_EVENT) ) == 0 ) {
			_infos["variable"]["name"] = _infos["variable"]["name"].asString().substr(std::strlen(EXTENSION_EVENT), -1);
			_infos["variable"]["com"] = "bind";
			_infos["variable"].removeMember("queuing");
		}

		// trigger
		if ( instances()[_id].datas[_i].com == PRODUCER
			 && instances()[_id].datas[_i].typeData != TYPE_SAMPLING
			 && std::strncmp( EXTENSION_EVENT, _infos["variable"]["name"].asString().c_str(), std::strlen(EXTENSION_EVENT) ) == 0 ) {
			_infos["variable"]["name"] = _infos["variable"]["name"].asString().substr(std::strlen(EXTENSION_EVENT), -1);
			_infos["variable"]["com"] = "trigger";
			_infos["variable"].removeMember("queuing");
		}

		WESBMessenger_trigger_full(_id, "wesbmessenger_pong", (char*)_writer.write(_infos).c_str());
}
// ping event trigger
void event_ping_trigger( int p_id, string p_name )
{
	Json::Value _infos;
	Json::FastWriter _writer;
	int _id = p_id;

	_infos["name"] = instances()[_id].name;
	_infos["variable"]["name"] = p_name;
	_infos["variable"]["com"] = "trigger";

	WESBMessenger_trigger_full(_id, "wesbmessenger_pong", (char*)_writer.write(_infos).c_str());
}
void event_ping(char* p_params)
{
	Json::Value _params;
	Json::Reader _reader;
	int _i;
	int _id;

	_reader.parse(p_params, _params);
	_id = _params.asInt();

	// vars and functions list
	for ( _i=0; _i < (int)instances()[_id].datas.size(); _i++ )
	{
		event_ping_var( _id, _i );
	}

	// tiggers list
	map<string, data_struct>::const_iterator _itr;
	for ( _itr=triggers()[_id].begin(); _itr != triggers()[_id].end(); ++_itr ){
		event_ping_trigger( _id, _itr->first );
	}
}

} // namespace wesbmessenger

REGISTER_TOPIC_TRAITS(Shared_Data::DDS_int)
REGISTER_TOPIC_TRAITS(Shared_Data::DDS_float)
REGISTER_TOPIC_TRAITS(Shared_Data::DDS_string)

using namespace wesbmessenger;

extern "C"
{

DLL_API int WESBMessenger_init_full( char* p_domain, char* p_name )
{
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_init_full: " + (string)p_domain + (string)" - " + p_name );

	static bool _isInit = false;
	if ( !_isInit )
	{
		runtime(); // DDS Runtime Init
	}
	_isInit = true;

	int _pos;
	for (_pos=0; instances().find(_pos) != instances().end(); _pos++)
	{
		if (_pos < 0) {
			return -1;
		}
	}
	instances()[_pos] = struct_instance(p_domain, p_name);

	// Register ping event
	data_struct _sc;
	_sc.value.fef = event_ping;
	_sc.tqos = new dds::TopicQos();
	_sc.topic.qs = new dds::Topic<Shared_Data::DDS_string>( (string)EXTENSION_EVENT + "wesbmessenger_ping", *(_sc.tqos) );
	_sc.dqos.reader = new dds::DataReaderQos( *(_sc.tqos) );
	_sc.dqos.reader->set_keep_last( MAX_QUEUE_SIZE );
	_sc.dqos.reader->set_reliable();
	_sc.player.qsreader = new dds::DataReader<Shared_Data::DDS_string>( *(_sc.topic.qs), *(_sc.dqos.reader), instances()[_pos].sub() );
	_sc.com = EVENT_INT;
	instances()[_pos].datas.push_back( _sc );

	return _pos;
}


DLL_API int WESBMessenger_consumSampling_full( int p_id, char* p_name, void* p_value, int p_type )
{
	Log::get()->add( Log::LEVEL_INFO,  (string)"WESBMessenger_consumSampling_full: " + p_name );
	int _return = -1;

	switch ( p_type )
	{
		case TYPE_INT:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.i = (int*)p_value;

			_s.tqos = new dds::TopicQos();

			_s.topic.i = new dds::Topic<Shared_Data::DDS_int>( p_name, *(_s.tqos) );

			_s.dqos.reader = new dds::DataReaderQos( *(_s.tqos) );
			_s.dqos.reader->set_keep_last(1);

			_s.player.ireader = new dds::DataReader<Shared_Data::DDS_int>( *(_s.topic.i), *(_s.dqos.reader), instances()[p_id].sub() );

			_s.typeData = TYPE_SAMPLING;
			_s.size = 0;
			_s.com = CONSUMER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
		case TYPE_FLOAT:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.f = (float*)p_value;

			_s.tqos = new dds::TopicQos();

			_s.topic.f = new dds::Topic<Shared_Data::DDS_float>( p_name, *(_s.tqos) );

			_s.dqos.reader = new dds::DataReaderQos( *(_s.tqos) );
			_s.dqos.reader->set_keep_last(1);

			_s.player.freader = new dds::DataReader<Shared_Data::DDS_float>( *(_s.topic.f), *(_s.dqos.reader), instances()[p_id].sub() );

			_s.typeData = TYPE_SAMPLING;
			_s.size = 0;
			_s.com = CONSUMER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
		case TYPE_STRING:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.s = (char**)p_value;
			*(_s.value.s) = new char[1];
			(*(_s.value.s))[0] = '\0';

			_s.tqos = new dds::TopicQos();

			_s.topic.s = new dds::Topic<Shared_Data::DDS_string>( p_name, *(_s.tqos) );

			_s.dqos.reader = new dds::DataReaderQos( *(_s.tqos) );
			_s.dqos.reader->set_keep_last(1);

			_s.player.sreader = new dds::DataReader<Shared_Data::DDS_string>( *(_s.topic.s), *(_s.dqos.reader), instances()[p_id].sub() );

			_s.typeData = TYPE_SAMPLING;
			_s.size = 0;
			_s.com = CONSUMER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
	}

	// call event
	event_ping_var( p_id, instances()[p_id].datas.size()-1 );

	return _return;
}

DLL_API int WESBMessenger_produceSampling_full( int p_id, char* p_name, void* p_value, int p_type )
{
	Log::get()->add( Log::LEVEL_INFO,  (string)"WESBMessenger_produceSampling_full: " + p_name );

	int _return = -1;

	switch ( p_type )
	{
		case TYPE_INT:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.i = (int*)p_value;

			_s.tqos = new dds::TopicQos();

			_s.topic.i = new dds::Topic<Shared_Data::DDS_int>( p_name, *(_s.tqos) );

			_s.dqos.writer = new dds::DataWriterQos( *(_s.tqos) );

			_s.player.iwriter = new dds::DataWriter<Shared_Data::DDS_int>( *(_s.topic.i), *(_s.dqos.writer), instances()[p_id].pub() );

			_s.typeData = TYPE_SAMPLING;
			_s.size = 0;
			_s.com = PRODUCER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
		case TYPE_FLOAT:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.f = (float*)p_value;

			_s.tqos = new dds::TopicQos();

			_s.topic.f = new dds::Topic<Shared_Data::DDS_float>( p_name, *(_s.tqos) );

			_s.dqos.writer = new dds::DataWriterQos( *(_s.tqos) );

			_s.player.fwriter = new dds::DataWriter<Shared_Data::DDS_float>( *(_s.topic.f), *(_s.dqos.writer), instances()[p_id].pub() );

			_s.typeData = TYPE_SAMPLING;
			_s.size = 0;
			_s.com = PRODUCER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
		case TYPE_STRING:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.s = (char**)p_value;

			_s.tqos = new dds::TopicQos();

			_s.topic.s = new dds::Topic<Shared_Data::DDS_string>( p_name, *(_s.tqos) );

			_s.dqos.writer = new dds::DataWriterQos( *(_s.tqos) );

			_s.player.swriter = new dds::DataWriter<Shared_Data::DDS_string>( *(_s.topic.s), *(_s.dqos.writer), instances()[p_id].pub() );

			_s.typeData = TYPE_SAMPLING;
			_s.size = 0;
			_s.com = PRODUCER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
	}

	// call event
	event_ping_var( p_id, instances()[p_id].datas.size()-1 );

	return _return;
}


DLL_API int WESBMessenger_consumQueuing_full( int p_id, char* p_name, void* p_values, int* p_size, int p_type, int p_maxsize )
{
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_consumQueuing_full" );

	int _return = -1;

	switch ( p_type )
	{
		case TYPE_INT:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.qi = (int**)p_values;
			*(_s.value.qi) = 0;

			_s.tqos = new dds::TopicQos();

			_s.topic.qi = new dds::Topic<Shared_Data::DDS_int>( p_name, *(_s.tqos) );

			_s.dqos.reader = new dds::DataReaderQos( *(_s.tqos) );
			_s.dqos.reader->set_keep_last( p_maxsize );
			_s.dqos.reader->set_reliable();

			_s.player.qireader = new dds::DataReader<Shared_Data::DDS_int>( *(_s.topic.qi), *(_s.dqos.reader), instances()[p_id].sub() );

			_s.typeData = TYPE_QUEUING;
			_s.size = p_size;
			*(_s.size) = 0;
			_s.com = CONSUMER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
		case TYPE_FLOAT:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.qf = (float**)p_values;
			*(_s.value.qf) = 0;

			_s.tqos = new dds::TopicQos();

			_s.topic.qf = new dds::Topic<Shared_Data::DDS_float>( p_name, *(_s.tqos) );

			_s.dqos.reader = new dds::DataReaderQos( *(_s.tqos) );
			_s.dqos.reader->set_keep_last( p_maxsize );
			_s.dqos.reader->set_reliable();

			_s.player.qfreader = new dds::DataReader<Shared_Data::DDS_float>( *(_s.topic.qf), *(_s.dqos.reader), instances()[p_id].sub() );

			_s.typeData = TYPE_QUEUING;
			_s.size = p_size;
			*(_s.size) = 0;
			_s.com = CONSUMER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
		case TYPE_STRING:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.qs = (char***)p_values;
			*(_s.value.qs) = 0;

			_s.tqos = new dds::TopicQos();

			_s.topic.qs = new dds::Topic<Shared_Data::DDS_string>( p_name, *(_s.tqos) );

			_s.dqos.reader = new dds::DataReaderQos( *(_s.tqos) );
			_s.dqos.reader->set_keep_last( p_maxsize );
			_s.dqos.reader->set_reliable();

			_s.player.qsreader = new dds::DataReader<Shared_Data::DDS_string>( *(_s.topic.qs), *(_s.dqos.reader), instances()[p_id].sub() );

			_s.typeData = TYPE_QUEUING;
			_s.size = p_size;
			*(_s.size) = 0;
			_s.com = CONSUMER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
	}

	// call event
	event_ping_var( p_id, instances()[p_id].datas.size()-1 );

	return _return;
}


DLL_API int WESBMessenger_produceQueuing_full( int p_id, char* p_name, void* p_values, int* p_size, int p_type )
{
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_produceQueuing_full" );

	int _return = -1;

	switch ( p_type )
	{
		case TYPE_INT:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.qi = (int**)p_values;

			_s.tqos = new dds::TopicQos();

			_s.topic.qi = new dds::Topic<Shared_Data::DDS_int>( p_name, *(_s.tqos) );

			_s.dqos.writer = new dds::DataWriterQos( *(_s.tqos) );
			_s.dqos.writer->set_reliable();

			_s.player.qiwriter = new dds::DataWriter<Shared_Data::DDS_int>( *(_s.topic.qi), *(_s.dqos.writer), instances()[p_id].pub() );

			_s.typeData = TYPE_QUEUING;
			_s.size = p_size;
			_s.com = PRODUCER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
		case TYPE_FLOAT:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.qf = (float**)p_values;

			_s.tqos = new dds::TopicQos();

			_s.topic.qf = new dds::Topic<Shared_Data::DDS_float>( p_name, *(_s.tqos) );

			_s.dqos.writer = new dds::DataWriterQos( *(_s.tqos) );
			_s.dqos.writer->set_reliable();

			_s.player.qfwriter = new dds::DataWriter<Shared_Data::DDS_float>( *(_s.topic.qf), *(_s.dqos.writer), instances()[p_id].pub() );

			_s.typeData = TYPE_QUEUING;
			_s.size = p_size;
			_s.com = PRODUCER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
		case TYPE_STRING:
		{
			data_struct _s;

			_s.type = p_type;
			_s.value.qs = (char***)p_values;

			_s.tqos = new dds::TopicQos();

			_s.topic.qs = new dds::Topic<Shared_Data::DDS_string>( p_name, *(_s.tqos) );

			_s.dqos.writer = new dds::DataWriterQos( *(_s.tqos) );
			_s.dqos.writer->set_reliable();

			_s.player.qswriter = new dds::DataWriter<Shared_Data::DDS_string>( *(_s.topic.qs), *(_s.dqos.writer), instances()[p_id].pub() );

			_s.typeData = TYPE_QUEUING;
			_s.size = p_size;
			_s.com = PRODUCER;

			instances()[p_id].datas.push_back( _s );

			_return = (int)(&(instances()[p_id].datas.back()));
			break;
		}
	}

	// call event
	event_ping_var( p_id, instances()[p_id].datas.size()-1 );

	return _return;
}

DLL_API int WESBMessenger_unreg_full( int p_id )
{
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_unreg_full: " + instances()[p_id].name );

	int _i=0;
/*	Json::FastWriter _writer;
	Json::Value _infos;
	
	// send unreg event
	_infos["name"] = instances()[p_id].name;
	for ( _i = instances()[p_id].datas.size()-1; _i >= 0; _i-- )
	{
		switch ( instances()[p_id].datas[_i].type ) {
			case TYPE_INT:
				_infos["variable"]["type"] = "int";
				_infos["variable"]["name"] = ( instances()[p_id].datas[_i].typeData == TYPE_SAMPLING ? instances()[p_id].datas[_i].topic.i->get_name() : instances()[p_id].datas[_i].topic.qi->get_name() );
				break;
			case TYPE_FLOAT:
				_infos["variable"]["type"] = "float";
				_infos["variable"]["name"] = ( instances()[p_id].datas[_i].typeData == TYPE_SAMPLING ? instances()[p_id].datas[_i].topic.f->get_name() : instances()[p_id].datas[_i].topic.qf->get_name() );
				break;
			case TYPE_STRING:
				_infos["variable"]["type"] = "string";
				_infos["variable"]["name"] = ( instances()[p_id].datas[_i].typeData == TYPE_SAMPLING ? instances()[p_id].datas[_i].topic.s->get_name() : instances()[p_id].datas[_i].topic.qs->get_name() );
				break;
		}
		WESBMessenger_trigger_full(p_id, "wesbmessenger_unreg", (char*)_writer.write(_infos).c_str());
	}
*/

	// free memory
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_unreg_full: Free memory" );
	for ( _i = instances()[p_id].datas.size()-1; _i >= 0; _i-- )
	{
		if ( instances()[p_id].datas[_i].com == CONSUMER )
		{
			if( instances()[p_id].datas[_i].typeData == TYPE_SAMPLING )
			{
				switch ( instances()[p_id].datas[_i].type )
				{
				case TYPE_STRING:
					delete [] (*(instances()[p_id].datas[_i].value.s));
					break;
				default:
					break;
				}
			}
			else if ( instances()[p_id].datas[_i].typeData == TYPE_QUEUING )
			{
				DDS::ULong _j;

				switch ( instances()[p_id].datas[_i].type )
				{
				case TYPE_INT:
				{
					if ( *(instances()[p_id].datas[_i].value.qi) != 0 )
					{
						delete [] *((int**)instances()[p_id].datas[_i].value.qi);
					}
				}
				break;
				case TYPE_FLOAT:
				{
					if ( *(instances()[p_id].datas[_i].value.qf) != 0 )
					{
						delete [] *(instances()[p_id].datas[_i].value.qf);
					}
				}
				break;
				case TYPE_STRING:
				{
					for ( _j=0; _j<(DDS::ULong)*(instances()[p_id].datas[_i].size); _j++){
						delete [] (*(instances()[p_id].datas[_i].value.qs))[_j];
					}
					if ( *(instances()[p_id].datas[_i].value.qs) != 0 )
					{
						free( *(instances()[p_id].datas[_i].value.qs) );
					}
				}
				break;
				}
			}
		}
	}

	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_unreg_full: Free DDS vars" );
	for (_i=instances()[p_id].datas.size()-1; _i>=0; _i--)
	{
		switch (instances()[p_id].datas[_i].com)
		{
		case CONSUMER:
			switch (instances()[p_id].datas[_i].typeData)
			{
			case TYPE_SAMPLING:
				switch (instances()[p_id].datas[_i].type)
				{
				case TYPE_INT:
					delete instances()[p_id].datas[_i].player.ireader;
					delete instances()[p_id].datas[_i].dqos.reader;
					delete instances()[p_id].datas[_i].topic.i;
					delete instances()[p_id].datas[_i].tqos;
					break;
				case TYPE_FLOAT:
					delete instances()[p_id].datas[_i].player.freader;
					delete instances()[p_id].datas[_i].dqos.reader;
					delete instances()[p_id].datas[_i].topic.f;
					delete instances()[p_id].datas[_i].tqos;
					break;
				case TYPE_STRING:
					delete instances()[p_id].datas[_i].player.sreader;
					delete instances()[p_id].datas[_i].dqos.reader;
					delete instances()[p_id].datas[_i].topic.s;
					delete instances()[p_id].datas[_i].tqos;
					break;
				}
				break;

			case TYPE_QUEUING:
				switch (instances()[p_id].datas[_i].type)
				{
				case TYPE_INT:
					delete instances()[p_id].datas[_i].player.qireader;
					delete instances()[p_id].datas[_i].dqos.reader;
					delete instances()[p_id].datas[_i].topic.qi;
					delete instances()[p_id].datas[_i].tqos;
					break;
				case TYPE_FLOAT:
					delete instances()[p_id].datas[_i].player.qfreader;
					delete instances()[p_id].datas[_i].dqos.reader;
					delete instances()[p_id].datas[_i].topic.qf;
					delete instances()[p_id].datas[_i].tqos;
					break;
				case TYPE_STRING:
					delete instances()[p_id].datas[_i].player.qsreader;
					delete instances()[p_id].datas[_i].dqos.reader;
					delete instances()[p_id].datas[_i].topic.qs;
					delete instances()[p_id].datas[_i].tqos;
					break;
				}
				break;
			}
			break;

		case PRODUCER:
			switch (instances()[p_id].datas[_i].typeData)
			{
			case TYPE_SAMPLING:
				switch (instances()[p_id].datas[_i].type)
				{
				case TYPE_INT:
					delete instances()[p_id].datas[_i].player.iwriter;
					delete instances()[p_id].datas[_i].dqos.writer;
					delete instances()[p_id].datas[_i].topic.i;
					delete instances()[p_id].datas[_i].tqos;
					break;
				case TYPE_FLOAT:
					delete instances()[p_id].datas[_i].player.fwriter;
					delete instances()[p_id].datas[_i].dqos.writer;
					delete instances()[p_id].datas[_i].topic.f;
					delete instances()[p_id].datas[_i].tqos;
					break;
				case TYPE_STRING:
					delete instances()[p_id].datas[_i].player.swriter;
					delete instances()[p_id].datas[_i].dqos.writer;
					delete instances()[p_id].datas[_i].topic.s;
					delete instances()[p_id].datas[_i].tqos;
					break;
				}
				break;

			case TYPE_QUEUING:
				switch (instances()[p_id].datas[_i].type)
				{
				case TYPE_INT:
					delete instances()[p_id].datas[_i].player.qiwriter;
					delete instances()[p_id].datas[_i].dqos.writer;
					delete instances()[p_id].datas[_i].topic.qi;
					delete instances()[p_id].datas[_i].tqos;
					break;
				case TYPE_FLOAT:
					delete instances()[p_id].datas[_i].player.qfwriter;
					delete instances()[p_id].datas[_i].dqos.writer;
					delete instances()[p_id].datas[_i].topic.qf;
					delete instances()[p_id].datas[_i].tqos;
					break;
				case TYPE_STRING:
					delete instances()[p_id].datas[_i].player.qswriter;
					delete instances()[p_id].datas[_i].dqos.writer;
					delete instances()[p_id].datas[_i].topic.qs;
					delete instances()[p_id].datas[_i].tqos;
					break;
				}
				break;
			}
			break;

		case FUNCTION:
			{
				delete instances()[p_id].datas[_i].value.fsp->player.qswriter;
				delete instances()[p_id].datas[_i].value.fsp->dqos.writer;
				delete instances()[p_id].datas[_i].value.fsp->topic.qs;
				delete instances()[p_id].datas[_i].value.fsp->tqos;
				delete instances()[p_id].datas[_i].value.fsp;

				delete instances()[p_id].datas[_i].player.qsreader;
				delete instances()[p_id].datas[_i].dqos.reader;
				delete instances()[p_id].datas[_i].topic.qs;
				delete instances()[p_id].datas[_i].tqos;
			}
			break;
		case CALL:
			{
				delete instances()[p_id].datas[_i].player.qsreader;
				delete instances()[p_id].datas[_i].dqos.reader;
				delete instances()[p_id].datas[_i].topic.qs;
				delete instances()[p_id].datas[_i].tqos;
			}
			break;
		case EVENT_INT:
		case EVENT:
			{
				delete instances()[p_id].datas[_i].player.qsreader;
				delete instances()[p_id].datas[_i].dqos.reader;
				delete instances()[p_id].datas[_i].topic.qs;
				delete instances()[p_id].datas[_i].tqos;
			}
			break;
		}
		instances()[p_id].datas.pop_back();
	}

	// Remove triggers
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_unreg_full: Free triggers" );
	if ( triggers().find(p_id) != triggers().end() )
	{
		map<string,data_struct>::iterator _it;
		for ( _it = triggers()[p_id].begin(); _it != triggers()[p_id].end(); ++_it )
		{
			delete _it->second.player.qswriter;
			delete _it->second.dqos.writer;
			delete _it->second.topic.qs;
			delete _it->second.tqos;
		}
		triggers().erase(p_id);
	}

	// remove calls
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_unreg_full: Free calls" );
	if ( calls().find(p_id) != calls().end() )
	{
		map<string,data_struct>::iterator _it;
		for ( _it = calls()[p_id].begin(); _it != calls()[p_id].end(); ++_it )
		{
			delete _it->second.player.qswriter;
			delete _it->second.dqos.writer;
			delete _it->second.topic.qs;
			delete _it->second.tqos;
		}
		calls().erase(p_id);
	}

	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_unreg_full: Free responses" );
	if ( responses().find(p_id) != responses().end() )
	{
		responses().erase(p_id);
	}

	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_unreg_full: Free DDS tools" );
	instances().erase(p_id);
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_unreg_full: End" );

	return 0;
}

DLL_API int WESBMessenger_share_full( int p_id, char* p_name, Shared_Func p_function )
{
	int _return = -1;
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_share_full" );

	// Produce queuing string
	data_struct *_sp = new data_struct;
	_sp->value.fsf = p_function;
	_sp->tqos = new dds::TopicQos();
	_sp->topic.qs = new dds::Topic<Shared_Data::DDS_string>( (char*)((string)EXTENSION_RETURN_VAL + (string)p_name).c_str(), *(_sp->tqos) );
	_sp->dqos.writer = new dds::DataWriterQos( *(_sp->tqos) );
	_sp->dqos.writer->set_reliable();
	_sp->player.qswriter = new dds::DataWriter<Shared_Data::DDS_string>( *(_sp->topic.qs), *(_sp->dqos.writer), instances()[p_id].pub() );
	
	// Consum queuing string
	data_struct _sc;
	_sc.value.fsp = _sp;
	_sc.tqos = new dds::TopicQos();
	_sc.topic.qs = new dds::Topic<Shared_Data::DDS_string>( (char*)((string)EXTENSION_PARAMETER + (string)p_name).c_str(), *(_sc.tqos) );
	_sc.dqos.reader = new dds::DataReaderQos( *(_sc.tqos) );
	_sc.dqos.reader->set_reliable();
	_sc.dqos.reader->set_keep_last( MAX_QUEUE_SIZE );
	_sc.player.qsreader = new dds::DataReader<Shared_Data::DDS_string>( *(_sc.topic.qs), *(_sc.dqos.reader), instances()[p_id].sub() );
	_sc.com = FUNCTION;
	instances()[p_id].datas.push_back( _sc );

	// call event
	event_ping_var( p_id, instances()[p_id].datas.size()-1 );

	// set return value
	_return = (int)(&(instances()[p_id].datas.back()));
	return _return;
}

DLL_API int WESBMessenger_call_full( int p_id, char* p_name, char* p_params, CallBack_Func p_function )
{
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_call_full" );

	int _return = -1;
	data_struct _sp;
	boost::posix_time::ptime _curtime = boost::posix_time::microsec_clock::universal_time();
	long	_time	= (_curtime - (boost::posix_time::ptime)boost::gregorian::date(1970,1,1)).total_seconds(),
			_timems	= _curtime.time_of_day().total_milliseconds() % 1000;

	if ( calls()[p_id].find(p_name) == calls()[p_id].end() )
	{
		// Consum queuing string
		data_struct _sc;
		_sc.tqos = new dds::TopicQos();
		_sc.topic.qs = new dds::Topic<Shared_Data::DDS_string>( (char*)((string)EXTENSION_RETURN_VAL + (string)p_name).c_str(), *(_sc.tqos) );
		_sc.dqos.reader = new dds::DataReaderQos( *(_sc.tqos) );
		_sc.dqos.reader->set_keep_last( MAX_QUEUE_SIZE );
		_sc.dqos.reader->set_reliable();
		_sc.player.qsreader = new dds::DataReader<Shared_Data::DDS_string>( *(_sc.topic.qs), *(_sc.dqos.reader), instances()[p_id].sub() );
		_sc.com = CALL;
		_sc.value.fsp = &_sp;
		instances()[p_id].datas.push_back( _sc );

		// set return value
		_return = (int)(&(instances()[p_id].datas.back()));


		// Produce queuing string
		_sp.tqos = new dds::TopicQos();
		_sp.topic.qs = new dds::Topic<Shared_Data::DDS_string>( (char*)((string)EXTENSION_PARAMETER + (string)p_name).c_str(), *(_sp.tqos) );
		_sp.dqos.writer = new dds::DataWriterQos( *(_sp.tqos) );
		_sp.dqos.writer->set_reliable();
		_sp.player.qswriter = new dds::DataWriter<Shared_Data::DDS_string>( *(_sp.topic.qs), *(_sp.dqos.writer), instances()[p_id].pub() );
		_sp.value.fsp = &_sc;
		calls()[p_id][p_name] = _sp;
	}
	else
	{
		_sp = calls()[p_id][p_name];
		_return = (int)_sp.value.fsp;
	}

	Shared_Data::DDS_string _vs;
	Json::Reader _reader;
	Json::FastWriter _writer;
	Json::Value _parameter;
	string _val = p_params;
	stringstream _uuid;
	_uuid << boost::uuids::random_generator()();

	responses()[p_id][_uuid.str()] = p_function;
	_parameter["_uuid"] = _uuid.str();
	if ( !_reader.parse( _val, _parameter["_parameter"] ) )
	{
		Log::get()->add( Log::LEVEL_ERROR,  "Failed to parse call params: " + _val + "(" + _reader.getFormatedErrorMessages() + ")" );
	}
	_vs.data = DDS::string_dup( _writer.write( _parameter ).c_str() );
	_vs.valid = 1;
	_vs.time = _time;
	_vs.timems = _timems;
	_sp.player.qswriter->write( _vs );

	return _return;
}

DLL_API int WESBMessenger_bind_full( int p_id, char* p_name, Event_Func p_function )
{
	int _return = -1;
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_bind_full" );

	// Consum queuing string
	data_struct _sc;
	_sc.value.fef = p_function;
	_sc.tqos = new dds::TopicQos();
	_sc.topic.qs = new dds::Topic<Shared_Data::DDS_string>( (char*)((string)EXTENSION_EVENT + (string)p_name).c_str(), *(_sc.tqos) );
	_sc.dqos.reader = new dds::DataReaderQos( *(_sc.tqos) );
	_sc.dqos.reader->set_keep_last( MAX_QUEUE_SIZE );
	_sc.dqos.reader->set_reliable();
	_sc.player.qsreader = new dds::DataReader<Shared_Data::DDS_string>( *(_sc.topic.qs), *(_sc.dqos.reader), instances()[p_id].sub() );
	_sc.com = EVENT;
	instances()[p_id].datas.push_back( _sc );

	// call event
	event_ping_var( p_id, instances()[p_id].datas.size()-1 );

	// set return value
	_return = (int)(&(instances()[p_id].datas.back()));
	return _return;
}

DLL_API int WESBMessenger_trigger_full( int p_id, char* p_name, char* p_params )
{
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_trigger_full: " + (string)p_name + " " + p_params );
	data_struct _sp;
	boost::posix_time::ptime _curtime = boost::posix_time::microsec_clock::universal_time();
	long	_time	= (_curtime - (boost::posix_time::ptime)boost::gregorian::date(1970,1,1)).total_seconds(),
			_timems	= _curtime.time_of_day().total_milliseconds() % 1000;
	
	// Produce queuing string
	if ( triggers()[p_id].find(p_name) == triggers()[p_id].end() )
	{
		_sp.tqos = new dds::TopicQos();
		_sp.topic.qs = new dds::Topic<Shared_Data::DDS_string>( (string)EXTENSION_EVENT + (string)p_name, *(_sp.tqos) );
		_sp.dqos.writer = new dds::DataWriterQos( *(_sp.tqos) );
		_sp.dqos.writer->set_reliable();
		_sp.player.qswriter = new dds::DataWriter<Shared_Data::DDS_string>( *(_sp.topic.qs), *(_sp.dqos.writer), instances()[p_id].pub() );
		triggers()[p_id][p_name] = _sp;

		event_ping_trigger( p_id, p_name );
	}
	else
	{
		_sp = triggers()[p_id][p_name];
	}

	Shared_Data::DDS_string _vs;
	Json::Reader _reader;
	Json::FastWriter _writer;
	Json::Value _parameter;
	string _val = p_params;

	if ( !_reader.parse( _val, _parameter["_parameter"] ) )
	{
		Log::get()->add( Log::LEVEL_ERROR,  "Failed to parse the trigger params: " + _val + "(" + _reader.getFormatedErrorMessages() + ")" );
	}
	_vs.data = DDS::string_dup( _writer.write( _parameter ).c_str() );
	_vs.valid = 1;
	_vs.time = _time;
	_vs.timems = _timems;
	_sp.player.qswriter->write( _vs );

	return 0;
}

DLL_API int WESBMessenger_update_full( int p_id )
{
	Log::get()->add( Log::LEVEL_INFO,  "WESBMessenger_update_full: " + instances()[p_id].name );

	int _i;
	boost::posix_time::ptime _curtime = boost::posix_time::microsec_clock::universal_time();
	long	_time	= (_curtime - (boost::posix_time::ptime)boost::gregorian::date(1970,1,1)).total_seconds(),
			_timems	= _curtime.time_of_day().total_milliseconds() % 1000;


	for ( _i = 0; _i < (int)instances()[p_id].datas.size(); _i++ )
	{
		if ( instances()[p_id].datas[_i].com == PRODUCER )
		{
			if ( instances()[p_id].datas[_i].typeData == TYPE_SAMPLING )
			{
				switch ( instances()[p_id].datas[_i].type )
				{
				case TYPE_INT:
					Shared_Data::DDS_int _vi;
					_vi.data = *(instances()[p_id].datas[_i].value.i);
					_vi.valid = 1;
					_vi.time = _time;
					_vi.timems = _timems;
					instances()[p_id].datas[_i].player.iwriter->write( _vi );
					break;
				case TYPE_FLOAT:
					Shared_Data::DDS_float _vf;
					_vf.data = *(instances()[p_id].datas[_i].value.f);
					_vf.valid = 1;
					_vf.time = _time;
					_vf.timems = _timems;
					instances()[p_id].datas[_i].player.fwriter->write( _vf );
					break;
				case TYPE_STRING:
					Shared_Data::DDS_string _vs;
					_vs.data = DDS::string_dup(*(instances()[p_id].datas[_i].value.s));
					_vs.valid = 1;
					_vs.time = _time;
					_vs.timems = _timems;
					instances()[p_id].datas[_i].player.swriter->write( _vs );
					break;
				}
			}
			else if ( instances()[p_id].datas[_i].typeData == TYPE_QUEUING ) // queuing
			{
				int _j;

				switch ( instances()[p_id].datas[_i].type )
				{
				case TYPE_INT:
					Shared_Data::DDS_int _vi;
					for ( _j=0; _j < *(instances()[p_id].datas[_i].size); _j++ )
					{
						_vi.data = (*(instances()[p_id].datas[_i].value.qi))[_j];
						_vi.valid = 1;
						_vi.time = _time;
						_vi.timems = _timems;
						instances()[p_id].datas[_i].player.qiwriter->write( _vi );
					}
					break;
				case TYPE_FLOAT:
					Shared_Data::DDS_float _vf;
					for ( _j=0; _j < *(instances()[p_id].datas[_i].size); _j++ )
					{
						_vf.data = (*(instances()[p_id].datas[_i].value.qf))[_j];
						_vf.valid = 1;
						_vf.time = _time;
						_vf.timems = _timems;
						instances()[p_id].datas[_i].player.qfwriter->write( _vf );
					}
					break;
				case TYPE_STRING:
					Shared_Data::DDS_string _vs;
					for ( _j=0; _j < *(instances()[p_id].datas[_i].size); _j++ )
					{
						_vs.data = DDS::string_dup((*(instances()[p_id].datas[_i].value.qs))[_j]);
						_vs.valid = 1;
						_vs.time = _time;
						_vs.timems = _timems;
						instances()[p_id].datas[_i].player.qswriter->write( _vs );
					}
					break;
				}
			}
		}
	}

	// consumer
	for ( _i = 0; _i < (int)instances()[p_id].datas.size(); _i++ )
	{
		if ( instances()[p_id].datas[_i].com == CONSUMER )
		{
			if ( instances()[p_id].datas[_i].typeData == TYPE_SAMPLING )
			{
				switch ( instances()[p_id].datas[_i].type )
				{
				case TYPE_INT:
				{
					Shared_Data::DDS_intSeq _si;
					DDS::SampleInfoSeq infos;

					instances()[p_id].datas[_i].player.ireader->take(_si, infos);
					if ( _si.length() > 0 && _si[0].valid ){
						*(instances()[p_id].datas[_i].value.i) = _si[0].data;
					}
					instances()[p_id].datas[_i].player.ireader->return_loan(_si, infos);
				}
				break;
				case TYPE_FLOAT:
				{
					Shared_Data::DDS_floatSeq _sf;
					DDS::SampleInfoSeq infos;

					instances()[p_id].datas[_i].player.freader->take(_sf, infos);
					if ( _sf.length() > 0 && _sf[0].valid ){
						*(instances()[p_id].datas[_i].value.f) = _sf[0].data;
					}
					instances()[p_id].datas[_i].player.freader->return_loan(_sf, infos);
				}
				break;
				case TYPE_STRING:
				{
					Shared_Data::DDS_stringSeq _ss;
					DDS::SampleInfoSeq infos;

					instances()[p_id].datas[_i].player.sreader->take(_ss, infos);
					if ( _ss.length() > 0 && _ss[0].valid ){
						delete [] (*(instances()[p_id].datas[_i].value.s));
						(*(instances()[p_id].datas[_i].value.s)) = new char[strlen(_ss[0].data)+1];
						strcpy( (*(instances()[p_id].datas[_i].value.s)), _ss[0].data );
					}
					instances()[p_id].datas[_i].player.sreader->return_loan(_ss, infos);
				}
				break;
				}
			}
			else if ( instances()[p_id].datas[_i].typeData == TYPE_QUEUING )
			{
				DDS::ULong _j;

				switch ( instances()[p_id].datas[_i].type )
				{
				case TYPE_INT:
				{
					Shared_Data::DDS_intSeq _si;
					DDS::SampleInfoSeq infos;

					if ( *(instances()[p_id].datas[_i].value.qi) != 0 )
					{
						delete [] *((int**)instances()[p_id].datas[_i].value.qi);
					}

					instances()[p_id].datas[_i].player.qireader->take(_si, infos);
					*(instances()[p_id].datas[_i].size) = _si.length();
					*(instances()[p_id].datas[_i].value.qi) = new int[ *(instances()[p_id].datas[_i].size) ];

					int _pos = 0;
					for ( _j=0; _j <_si.length(); _j++ )
					{
						if ( _si[_j].valid )
						{
							(*(instances()[p_id].datas[_i].value.qi))[_j] = _si[_j].data;
							_pos++;
						}
						else
						{
							*(instances()[p_id].datas[_i].size) = *(instances()[p_id].datas[_i].size)-1;
						}
					}
					instances()[p_id].datas[_i].player.qireader->return_loan(_si, infos);
				}
				break;
				case TYPE_FLOAT:
				{
					Shared_Data::DDS_floatSeq _sf;
					DDS::SampleInfoSeq infos;

					if ( *(instances()[p_id].datas[_i].value.qf) != 0 )
					{
						delete [] *(instances()[p_id].datas[_i].value.qf);
					}

					instances()[p_id].datas[_i].player.qfreader->take(_sf, infos);
					*(instances()[p_id].datas[_i].size) = _sf.length();
					*(instances()[p_id].datas[_i].value.qf) = new float[ *(instances()[p_id].datas[_i].size) ];

					int _pos = 0;
					for ( _j=0; _j <_sf.length(); _j++ )
					{
						if ( _sf[_j].valid )
						{
							(*(instances()[p_id].datas[_i].value.qf))[_j] = _sf[_j].data;
							_pos++;
						}
						else
						{
							*(instances()[p_id].datas[_i].size) = *(instances()[p_id].datas[_i].size)-1;
						}
					}
					instances()[p_id].datas[_i].player.qfreader->return_loan(_sf, infos);
				}
				break;
				case TYPE_STRING:
				{
					Shared_Data::DDS_stringSeq _ss;
					DDS::SampleInfoSeq infos;

					for ( _j=0; _j<(DDS::ULong)*(instances()[p_id].datas[_i].size); _j++){
						delete [] (*(instances()[p_id].datas[_i].value.qs))[_j];
					}
					if ( *(instances()[p_id].datas[_i].value.qs) != 0 )
					{
						free( *(instances()[p_id].datas[_i].value.qs) );
					}
					
					instances()[p_id].datas[_i].player.qsreader->take(_ss, infos);
					*(instances()[p_id].datas[_i].size) = _ss.length();
					*(instances()[p_id].datas[_i].value.qs) = (char**)malloc( sizeof(char*) * (*(instances()[p_id].datas[_i].size)) );

					int _pos = 0;
					for ( _j=0; _j <_ss.length(); _j++ )
					{
						if ( _ss[_j].valid )
						{
							(*(instances()[p_id].datas[_i].value.qs))[_j] = new char[strlen(_ss[_j].data)+1];
							strcpy( (*(instances()[p_id].datas[_i].value.qs))[_j], _ss[_j].data );
						}
						else
						{
							*(instances()[p_id].datas[_i].size) = *(instances()[p_id].datas[_i].size)-1;
						}
					}
					instances()[p_id].datas[_i].player.qsreader->return_loan(_ss, infos);
				}
				break;
				}
			}
		}
		else if ( instances()[p_id].datas[_i].com == FUNCTION )
		{
			int _j;
			Shared_Data::DDS_stringSeq _ss;
			DDS::SampleInfoSeq _infos;
			Shared_Data::DDS_string _vs;
			Json::Reader _reader;
			Json::FastWriter _writer;
			Json::Value _parameter;
			Json::Value _returnValue;

			instances()[p_id].datas[_i].player.qsreader->take(_ss, _infos);

			for ( _j=0; _j < (int)_ss.length(); _j++ )
			{
				if ( _ss[_j].valid )
				{
					string _val;

					_reader.parse( (const char*)_ss[_j].data, _parameter );
					_returnValue["_uuid"] = _parameter["_uuid"];

					_val = instances()[p_id].datas[_i].value.fsp->value.fsf( (char*)_writer.write( _parameter.get("_parameter", "") ).c_str() );
					if ( !_reader.parse( _val, _returnValue["_response"] ) )
					{
						Log::get()->add( Log::LEVEL_ERROR,  "Failed to parse the function result: " + _val + "(" + _reader.getFormatedErrorMessages() + ")" );
					}
					_vs.data = DDS::string_dup( _writer.write( _returnValue ).c_str() );
					_vs.valid = 1;
					_vs.time = _time;
					_vs.timems = _timems;
					instances()[p_id].datas[_i].value.fsp->player.qswriter->write( _vs );
				}
			}
			instances()[p_id].datas[_i].player.qsreader->return_loan(_ss, _infos);
		}
		else if ( instances()[p_id].datas[_i].com == CALL )
		{
			int _j;
			Shared_Data::DDS_stringSeq _ss;
			DDS::SampleInfoSeq _infos;
			Json::Reader _reader;
			Json::FastWriter _writer;
			Json::Value _response;

			instances()[p_id].datas[_i].player.qsreader->take(_ss, _infos);

 			for ( _j=0; _j < (int)_ss.length(); _j++ )
			{
				if ( _ss[_j].valid )
				{
					string _uuid;
					_reader.parse( (const char*)_ss[_j].data, _response );

					if ( _response.isMember("_uuid") )
					{
						_uuid = _response["_uuid"].asString();

						if ( responses()[p_id].find( _uuid ) != responses()[p_id].end() )
						{
							responses()[p_id][ _uuid ]( (char*)_writer.write( _response.get("_response", "") ).c_str() );
							responses()[p_id].erase( _uuid );
						}
					}
					else
					{
						Log::get()->add( Log::LEVEL_ERROR, "Error during response receive, uuid not found" );
					}
				}
			}
			instances()[p_id].datas[_i].player.qsreader->return_loan(_ss, _infos);
		}
		else if ( instances()[p_id].datas[_i].com == EVENT )
		{
			int _j;
			Shared_Data::DDS_stringSeq _ss;
			DDS::SampleInfoSeq _infos;
			Json::Reader _reader;
			Json::FastWriter _writer;
			Json::Value _parameter;

			instances()[p_id].datas[_i].player.qsreader->take(_ss, _infos);

			for ( _j=0; _j < (int)_ss.length(); _j++ )
			{
				if ( _ss[_j].valid )
				{
					_reader.parse( (const char*)_ss[_j].data, _parameter );
					instances()[p_id].datas[_i].value.fef( (char*)_writer.write( _parameter.get("_parameter", "") ).c_str() );
				}
			}
			instances()[p_id].datas[_i].player.qsreader->return_loan(_ss, _infos);
		}
		else if ( instances()[p_id].datas[_i].com == EVENT_INT )
		{
			int _j;
			Shared_Data::DDS_stringSeq _ss;
			DDS::SampleInfoSeq _infos;
			Json::FastWriter _writer;
			Json::Value _parameter = p_id;

			instances()[p_id].datas[_i].player.qsreader->take(_ss, _infos);

			for ( _j=0; _j < (int)_ss.length(); _j++ )
			{
				if ( _ss[_j].valid )
				{
					instances()[p_id].datas[_i].value.fef( (char*)_writer.write( _parameter ).c_str() );
				}
			}
			instances()[p_id].datas[_i].player.qsreader->return_loan(_ss, _infos);
		}
	}

	return 0;
}

} // extern "C"
