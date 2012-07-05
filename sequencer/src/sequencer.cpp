/*
 * This file is part of M2Bench.
 *
 *  M2Bench is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  M2Bench is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with M2Bench.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Created on: 18 avr. 2011
 *      Author: Marc Buils (MATIS - http://www.matis-group.com)
 */
#include "../include/Log.h"
#include "../include/SequencerManager.h"
#include <WESBMessenger.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <signal.h>


#ifdef WIN32
	#include <windows.h>
	// Used to deactivate Ctrl+C event
	#include <conio.h>
    
	#define SEQUENCER_CTRL_C_KEY_EVENT 3
	#define msecSleep(msec) Sleep(msec)
#else
	#include <time.h>
	#define msecSleep(msec) usleep(1000*(msec))
#endif
using namespace std;

namespace sequencer
{

const string CONFIGURATION_FILE = "conf/config.json";

Json::Value &g_config()
{
	static Json::Value _return;
	return _return;
}

SequencerManager &_manager()
{
	static SequencerManager _return;
	return _return;
}

static std::string
readInputTestFile( const char *path )
{
   FILE *file = fopen( path, "rb" );
   if ( !file )
      return std::string("");
   fseek( file, 0, SEEK_END );
   long size = ftell( file );
   fseek( file, 0, SEEK_SET );
   std::string text;
   char *buffer = new char[size+1];
   buffer[size] = 0;
   if ( fread( buffer, 1, size, file ) == (unsigned long)size )
      text = buffer;
   fclose( file );
   delete[] buffer;
   return text;
}

const char* sequencer_add( char* p_params )
{
	Log::get()->add( Log::LEVEL_INFO, "sequencer_add");
	Log::get()->add( Log::LEVEL_DEBUG, p_params );

	static string _sreturn;
	Json::Value _return;
	Json::Reader _reader;
	Json::FastWriter _writer;
	Json::Value _value;
	Json::Value _infos;

	// parse params
	_reader.parse( p_params, _value );

	_return["status"] = 1;
	_return["error"] = "";
	try {
		// add component
		_manager().add( _value["file"].asString(), _value );

		_infos = _value;
		_infos["sequencer"] = g_config().get("name", "none");
		WESBMessenger_trigger( (char*)g_config()["share"].get("event_added", "sequencer_added").asString().c_str(), (char*)_writer.write( _infos ).c_str() );
	}
	catch(string &e)
	{
		_return["error"] = e;
		_return["status"] = 0;

		Log::get()->add( Log::LEVEL_ERROR, (string)"Error: " + e );
	}

	_sreturn = _writer.write( _return );
	return _sreturn.c_str();
}

const char* sequencer_remove( char* p_params )
{
	Log::get()->add( Log::LEVEL_INFO, "sequencer_remove");
	Log::get()->add( Log::LEVEL_DEBUG, (string)"Parameters: " + p_params );

	static string _sreturn;
	Json::Value _return;
	Json::Reader _reader;
	Json::FastWriter _writer;
	Json::Value _value;
	Json::Value _infos;

	// parse params
	_reader.parse( p_params, _value );

	_return["status"] = 1;
	_return["error"] = "";
	try {
		string _name = "none";
		if ( _manager().sequencers().find( _value.asString() ) != _manager().sequencers().end() )
		{
			_name = _manager().sequencers()[ _value.asString() ].config["name"].asString();
		}
		// remove component
		_manager().remove( _value.asString() );

		_infos["sequencer"] = g_config().get("name", "none");
		_infos["file"] = _value;
		_infos["name"] = _name;
		WESBMessenger_trigger( (char*)g_config()["share"].get("event_removed", "sequencer_removed").asString().c_str(), (char*)_writer.write( _infos ).c_str() );
	}
	catch(string &e)
	{
		_return["error"] = e;
		_return["status"] = 0;

		Log::get()->add( Log::LEVEL_ERROR, (string)"Error: " + e );
	}

	_sreturn = _writer.write( _return );
	Log::get()->add( Log::LEVEL_DEBUG, (string)"Return: " + _sreturn );
	return _sreturn.c_str();
}

const char* sequencer_reload( char* p_params )
{
	Log::get()->add( Log::LEVEL_INFO, "sequencer_reload");
	Log::get()->add( Log::LEVEL_DEBUG, (string)"Parameters: " + p_params );

	static string _sreturn;
	Json::Value _return;
	Json::Reader _reader;
	Json::FastWriter _writer;
	Json::Value _value;

	// parse params
	_reader.parse( p_params, _value );

	_return["status"] = 1;
	_return["error"] = "";
	try {
		// reload component
		_manager().reload( _value.asString() );
	}
	catch(string &e)
	{
		_return["error"] = e;
		_return["status"] = 0;

		Log::get()->add( Log::LEVEL_ERROR, (string)"Error: " + e );
	}

	_sreturn = _writer.write( _return );
	return _sreturn.c_str();
}

const char* sequencer_list( char* p_params )
{
	Log::get()->add( Log::LEVEL_INFO, "sequencer_list");
	Log::get()->add( Log::LEVEL_DEBUG, (string)"Parameters: " + p_params );

	static string _sreturn;
	Json::Value _return;
	Json::FastWriter _writer;

	try {
		_return = _manager().list( );
	}
	catch(string &e)
	{
		_return["error"] = e;
		_return["status"] = 0;

		Log::get()->add( Log::LEVEL_ERROR, (string)"Error: " + e );
	}

	_sreturn = _writer.write( _return );
	return _sreturn.c_str();
}

void sequencer_ping_event( char* p_params )
{
	Json::Value _infos;
	Json::FastWriter _writer;

	_infos["name"] = g_config().get("name", "none");
	_infos["add"] = g_config()["share"]["add"];
	_infos["remove"] = g_config()["share"]["remove"];
	_infos["reload"] = g_config()["share"]["reload"];
	_infos["list"] = g_config()["share"]["list"];
	_infos["event_added"] = g_config()["share"].get("event_added", "sequencer_added");
	_infos["event_removed"] = g_config()["share"].get("event_removed", "sequencer_removed");
	_infos["event_ping"] = g_config()["share"].get("event_ping", "sequencer_ping");
	_infos["event_pong"] = g_config()["share"].get("event_pong", "sequencer_pong");
	_infos["event_stopped"] = g_config()["share"].get("event_stopped", "sequencer_stopped");

	WESBMessenger_trigger( (char*)g_config()["share"].get("event_pong", "sequencer_pong").asString().c_str(), (char*)_writer.write( _infos ).c_str() );
}

// Boolean for update loop
bool   _stopIsRequested = false;
#ifndef WIN32
void _sigquit(int p)
{
	_stopIsRequested = true;
}
#endif


} // namespace sequencer

using namespace sequencer;

int main(void)
{
#ifdef WIN32
    // Handle of the keyboard
    HANDLE _hStdin;
    // New mode to set to console
    DWORD  _fdwMode;
    
    // Used to catch the Ctrl+C command and quit properly
    _hStdin = GetStdHandle( STD_INPUT_HANDLE );
    _fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    // Set the new mode to the console
    SetConsoleMode( _hStdin, _fdwMode );
#else
    signal(SIGINT, _sigquit);
#endif

	try
	{
		string _config_doc = readInputTestFile( CONFIGURATION_FILE.c_str() );
		Json::Reader _reader;
		unsigned int _i;

		// Lecture du fichier de configuration
		if ( !_reader.parse( _config_doc, g_config(), false ) )
		{
			// report to the user the failure and their locations in the document.
			cout  << "Failed to parse configuration\n" << _reader.getFormatedErrorMessages();
			return -1;
		}

		Log::get()->add( Log::LEVEL_INFO, "Initialization");

		// WESBMessenger share functions
		WESBMessenger_init( (char*)g_config()["share"]["domain"].asString().c_str(), (char*)g_config()["name"].asString().c_str() );
		WESBMessenger_share( (char*)g_config()["share"]["add"].asString().c_str(), sequencer_add );
		WESBMessenger_share( (char*)g_config()["share"]["remove"].asString().c_str(), sequencer_remove );
		WESBMessenger_share( (char*)g_config()["share"]["reload"].asString().c_str(), sequencer_reload );
		WESBMessenger_share( (char*)g_config()["share"]["list"].asString().c_str(), sequencer_list );
		WESBMessenger_bind( (char*)g_config()["share"].get("event_ping", "sequencer_ping").asString().c_str(), sequencer_ping_event );

		// chargement des fichiers - sequencer
		for ( _i=0; _i < g_config()["list"].getMemberNames().size(); _i++ )
		{
			if ( g_config()["list"][ g_config()["list"].getMemberNames()[_i] ].get( "enable", true ).asBool() )
			{
				_manager().add( g_config()["list"].getMemberNames()[_i], g_config()["list"][ g_config()["list"].getMemberNames()[_i] ] );
			}
		}

		// Launch manager run
        _manager().run();

		// trigger presence 
		sequencer_ping_event("");

        // While the user does not request to quit (Ctrl+C)
		do
		{
#ifdef WIN32
			if( _kbhit() )
            {
            	// CTRL + C = 3
                if( getchar( ) == SEQUENCER_CTRL_C_KEY_EVENT )
                {
                    _stopIsRequested = true;
                }
            }
            else
            {
            	WESBMessenger_update();
                _manager().update();
            }
#else
        	WESBMessenger_update();
            _manager().update();
#endif
			msecSleep( g_config()["time"].asInt() );
		} while( !_stopIsRequested );

	}
	catch ( string &p_error )
	{
		Log::get()->add( Log::LEVEL_ERROR, (string)"Error: " + p_error );
	}

	Log::get()->add( Log::LEVEL_DEBUG, "Start stop");
	_manager().stop();

	string _stoppedParams = "\"" + g_config().get("name", "none").asString() + "\"";
	WESBMessenger_trigger( (char*)g_config()["share"].get("event_stopped", "sequencer_stopped").asString().c_str(), (char*)_stoppedParams.c_str() );
	msecSleep( 1000 );

	Log::get()->add( Log::LEVEL_DEBUG, "Manager stopped");
	WESBMessenger_unreg();
	Log::get()->add( Log::LEVEL_DEBUG, "WESBMessenger unreg");

	return 0;
}
