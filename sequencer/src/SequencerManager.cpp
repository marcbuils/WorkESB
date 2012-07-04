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
 *      Author: Marc Buils (CSIE)
 */

#include "../include/SequencerManager.h"
#include "../include/Log.h"

namespace sequencer
{

extern Json::Value &g_config();

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

SequencerManager::SequencerManager() {
	this->m_running = 0;
}

SequencerManager::~SequencerManager() {
}

void SequencerManager::add( string p_file, Json::Value p_config )
{
	Json::Value _config = p_config;

	if ( this->m_sequencers.find(p_file) != this->m_sequencers.end() )
	{
		throw (string)"Add component error: " + p_file + " already loaded";
	}

	if ( !_config.isObject() )
	{
		throw (string)"Add component error: " + p_file + " - bad parameters";
	}

	// set default configuration if necessary
	if ( _config.isMember("default") && _config["default"].asBool() == true )
	{
		if ( !g_config()["list"].isMember(p_file) )
		{
			throw (string)"Add component error: " + p_file + " - default parameters not set";
		}
		else
		{
			_config = g_config()["list"][p_file];
		}
	}

	// Add dds partition
	if ( !_config.isMember("domain") )
	{
		_config["domain"] = g_config()["share"]["domain"].asString();
	}

	// Add name
	if ( !_config.isMember("name") )
	{
		_config["name"] = g_config()["list"][p_file].get("name", "none").asString();
	}

	try {
		if ( _config["type"] == "lua" )
		{
			this->addLua( p_file, _config );
		}
		else if ( _config["type"] == "dll" )
		{
			this->addDll( p_file, _config );
		}
	}
	catch( string &e )
	{
		try
		{
			this->remove( p_file );
		}
		catch(string &_e){}

		throw e;
	}
}

void SequencerManager::addLua( string p_file, Json::Value p_config )
{
	string _file = p_file;
    lua_State *_L;
    Json::FastWriter _writer;

    // Instance de l'interface LUA
    _L = luaL_newstate();
    luaL_openlibs( _L ); // Chargement des libraries standard
    luaL_dostring( _L, ("package.path = package.path .. ';" + g_config()["lua_path"].asString() + "'").c_str() );
    luaL_dostring( _L, ("package.cpath = package.cpath .. ';" + g_config()["lua_cpath"].asString() + "'").c_str() );
    luaL_dostring( _L, ((string)"json = require(\"json\");").c_str() );
    if ( luaL_dofile( _L, _file.c_str() ) )
    {  // Chargement du fichier
    	string _error = lua_tostring(_L, -1);

    	lua_close( _L );
        throw (string)"Loading LUA file error: " + _error;
    }

    sequencer_struct _lua;
    _lua.infos.lua.L = _L;
    _lua.config = p_config;
    _lua.type = SequencerManager::LUA;
	this->m_sequencers[ _file ] = _lua;


	if ( this->m_running )
	{
		// Execute la fonction d'init
		string _cmd = "onstart(json.decode(\"" + strreplace("\n", "", strreplace("\"", "\\\"", _writer.write( _lua.config )) + "\"));");
		if ( luaL_dostring( _lua.infos.lua.L, (char*)_cmd.c_str() ) != 0 )
		{
			throw (string)"Function onstart error: " + lua_tostring( _lua.infos.lua.L,-1);
		}
	}
}

void SequencerManager::addDll( string p_file, Json::Value p_config )
{
	string _file = p_file;
	sequencer_struct _dll;
	Json::FastWriter _writer;

#ifdef WIN32
	_dll.infos.dll.hDll = LoadLibrary( _file.c_str() );
	if ( !_dll.infos.dll.hDll ){
		throw (string)"Loading DLL error: " + _file;
	}

	_dll.infos.dll.onstart = (DLL_ONSTART)GetProcAddress( _dll.infos.dll.hDll, "onstart" );
	if ( !_dll.infos.dll.onstart ){
		throw (string)"Loading onstart function in DLL: " + _file;
	}

	_dll.infos.dll.onupdate = (DLL_ONUPDATE)GetProcAddress( _dll.infos.dll.hDll, "onupdate" );
	if ( !_dll.infos.dll.onupdate ){
		throw (string)"Loading onupdate function in DLL: " + _file;
	}

	_dll.infos.dll.onstop = (DLL_ONSTOP)GetProcAddress( _dll.infos.dll.hDll, "onstop" );
	if ( !_dll.infos.dll.onstop ){
		throw (string)"Loading onstop function in DLL: " + _file;
	}
#else
	_dll.infos.dll.hDll = dlopen( _file.c_str(), RTLD_LAZY );
	if ( !_dll.infos.dll.hDll ){
		throw (string)"Loading DLL error: " + _file + " (" + dlerror() + ")";
	}

	_dll.infos.dll.onstart = (DLL_ONSTART)dlsym( _dll.infos.dll.hDll, "onstart" );
	if ( !_dll.infos.dll.onstart ){
		throw (string)"Loading onstart function in DLL: " + _file;
	}

	_dll.infos.dll.onupdate = (DLL_ONUPDATE)dlsym( _dll.infos.dll.hDll, "onupdate" );
	if ( !_dll.infos.dll.onupdate ){
		throw (string)"Loading onupdate function in DLL: " + _file;
	}

	_dll.infos.dll.onstop = (DLL_ONSTOP)dlsym( _dll.infos.dll.hDll, "onstop" );
	if ( !_dll.infos.dll.onstop ){
		throw (string)"Loading onstop function in DLL: " + _file;
	}
#endif

	_dll.config = p_config;
	_dll.type = SequencerManager::DLL;
	this->m_sequencers[ _file ] = _dll;

	if ( this->m_running )
	{
		// Execute la fonction d'init
		if ( _dll.infos.dll.onstart( (char*)_writer.write( _dll.config ).c_str() ) < 0 )
		{
			throw (string)"Function onstart error";
		}
	}
}

void SequencerManager::remove( string p_file )
{
	if ( this->m_sequencers.find(p_file) == this->m_sequencers.end() )
	{
		throw (string)"Remove component error: " + p_file + " not found";
	}

	try
	{
		if ( this->m_sequencers[ p_file ].type == SequencerManager::LUA )
		{
			this->removeLua( p_file );
		}
		else if ( this->m_sequencers[ p_file ].type == SequencerManager::DLL )
		{
			this->removeDll( p_file );
		}
	}
	catch(string &e)
	{
		this->m_sequencers.erase( p_file );
		throw e;
	}
	this->m_sequencers.erase( p_file );
}

void SequencerManager::removeLua( string p_file )
{
	lua_State *_L = this->m_sequencers[ p_file ].infos.lua.L;

	// Execute la fonction
	lua_getglobal( _L, "onstop" );
	if ( lua_pcall( _L, 0, LUA_MULTRET, 0) != 0 )
	{
		throw (string)"Function onstop error: " + lua_tostring( _L,-1);
	}

	lua_close( _L );
}

void SequencerManager::removeDll( string p_file )
{
	// Execute la fonction
	if ( this->m_sequencers[ p_file ].infos.dll.onstop() != 0 )
	{
		throw (string)"Function onstop error";
	}

#ifdef WIN32
	if ( this->m_sequencers[ p_file ].infos.dll.hDll )
	{
		FreeLibrary( this->m_sequencers[ p_file ].infos.dll.hDll );
	}
#else
	if ( this->m_sequencers[ p_file ].infos.dll.hDll )
	{
		dlclose( this->m_sequencers[ p_file ].infos.dll.hDll );
	}
#endif
}

void SequencerManager::reload( string p_file )
{
	if ( this->m_sequencers.find(p_file) == this->m_sequencers.end() )
	{
		throw (string)"Reload component error: " + p_file + " not found";
	}

	Json::Value _config = this->m_sequencers[ p_file ].config;

	this->remove( p_file );
	this->add( p_file, _config );
}

Json::Value SequencerManager::list()
{
	Json::Value _return;
	map<string,sequencer_struct>::iterator _it;
	unsigned int _i = 0;

	// set default enable value to false
	for ( _i=0; _i < g_config()["list"].getMemberNames().size(); _i++ )
	{
		_return[ g_config()["list"].getMemberNames()[_i] ][ "name" ] = g_config()["list"][ g_config()["list"].getMemberNames()[_i] ].get("name", "none");
		_return[ g_config()["list"].getMemberNames()[_i] ][ "enable" ] = false;
	}
	for ( _it = this->m_sequencers.begin(); _it != this->m_sequencers.end(); ++_it )
	{
		_return[ _it->first ][ "enable" ] = true;
	}

	return _return;
}

void SequencerManager::run()
{
	Json::FastWriter _writer;
	map<string,sequencer_struct>::iterator _it;

	for ( _it = this->m_sequencers.begin(); _it != this->m_sequencers.end(); ++_it )
	{
		switch( _it->second.type )
		{
		case SequencerManager::DLL:
			{
				// Execute la fonction d'init
				if ( _it->second.infos.dll.onstart( (char*)_writer.write( _it->second.config ).c_str() ) < 0 )
				{
					throw (string)"Function onstart error";
				}
			}
			break;
		case SequencerManager::LUA:
			{
				// Execute la fonction d'init
				string _cmd = "onstart(json.decode(\"" + strreplace("\n", "", strreplace("\"", "\\\"", _writer.write( _it->second.config )) + "\"));");
				if ( luaL_dostring( _it->second.infos.lua.L, (char*)_cmd.c_str() ) != 0 )
				{
					throw (string)"Function onstart error: " + lua_tostring( _it->second.infos.lua.L,-1);
				}
			}
			break;
		default:
			break;
		}
	}

	this->m_running = 1;
}

void SequencerManager::update()
{
	map<string,sequencer_struct>::iterator _it;

	// update only if running
	if ( !this->m_running )
	{
		return;
	}

	for ( _it = this->m_sequencers.begin(); _it != this->m_sequencers.end(); ++_it )
	{
		switch( _it->second.type )
		{
		case SequencerManager::DLL:
			{
				// Execute la fonction
				if ( _it->second.infos.dll.onupdate() != 0 )
				{
					throw (string)"Function onupdate error";
				}
			}
			break;
		case SequencerManager::LUA:
			{
				// Execute la fonction
				lua_getglobal( _it->second.infos.lua.L, "onupdate" );
				if ( lua_pcall( _it->second.infos.lua.L, 0, LUA_MULTRET, 0) != 0 )
				{
					throw (string)"Function onupdate error: " + lua_tostring( _it->second.infos.lua.L,-1);
				}
			}
			break;
		default:
			break;
		}
	}
}

void SequencerManager::stop()
{
	map<string,sequencer_struct>::iterator _it;

	while ( (_it = this->m_sequencers.begin()) != this->m_sequencers.end() )
	{
		try {
			this->remove( _it->first );
		}
		catch(string &e)
		{
			Log::get()->add( Log::LEVEL_ERROR, "Error during stop: " + e );
		}
	}

	this->m_running = 0;
}

int SequencerManager::isRunning()
{
	return this->m_running;
}

} // namespace sequencer
