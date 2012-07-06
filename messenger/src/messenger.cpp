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
 *  Created on: 31 janv. 2012
 *      Author: Marc Buils (MATIS - http://www.matis-group.com)
 *
 *
 *  Created on: 18 avr. 2011
 *      Author: marc
 */
// Librairies LUA
#ifdef WIN32
#define LUA_BUILD_AS_DLL
#endif // #ifdef WIN32
#define LUA_LIB
#define wesbmessenger_c
extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}
#include <WESBMessenger.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <string.h>
#include <stdlib.h>
using namespace std;
#include <json/json.h>

namespace messenger
{

struct struct_var
{
	int type;
	union {
		int _i;
		float _f;
		char* _s;
		int* _qi;
		float* _qf;
		char** _qs;
	} value;
	string var;
	int com;
	int queuing;
	int size;
};
map< int, vector<struct_var*> > &vars()
{
	static map< int, vector<struct_var*> > _return;
	return _return;
}


/*
 * Fonctions génériques
 */
string str_replace( string p_from, string p_to, string p_context )
{
	string _buffer = "";
	int _end;
	int _start = 0;
	int _size = p_from.size();

    while( ( _end = p_context.find( p_from, _start ) ) != string::npos)
    {
    	_buffer += p_context.substr( _start, _end-_start );
    	_buffer += p_to;
    	_start = _end + _size;
    }
    _buffer += p_context.substr( _start );

    return _buffer;
}


/*
 * Fonctions partagées avec le LUA
 */
static int init (lua_State *p_L)
{
	string _domain;
	string _name;
	int _id;

	_domain = luaL_checkstring( p_L, 1 );
	_name = luaL_checkstring( p_L, 2 );
	_id = WESBMessenger_init_full( (char*)_domain.c_str(), (char*)_name.c_str() );
	lua_pushnumber( p_L, _id );

	return 1;
}


static int regConsumSampling (lua_State *p_L)
{
	int _return;
	string _name;
	string _var;
	string _type;
	int _id;

	_id = luaL_checkint( p_L, 1 );
	_name = luaL_checkstring( p_L, 2 );
	_var = luaL_checkstring( p_L, 3 );
	_type = luaL_checkstring( p_L, 4 );

	void* _value = 0;
	struct_var* _s = new struct_var;
	_s->var = _var;
	_s->com = CONSUMER;
	_s->queuing = 0;
	if ( _type == "int" )
	{
		_s->type = TYPE_INT;
		_value = &(_s->value._i);
	}
	else if ( _type == "float" )
	{
		_s->type = TYPE_FLOAT;
		_value = &(_s->value._f);
	}
	else if ( _type == "string" )
	{
		_s->type = TYPE_STRING;
		_value = &(_s->value._s);
	}
	vars()[_id].push_back( _s );

	_return = WESBMessenger_regConsumSampling_full( _id, (char*)_name.c_str(), _value, _s->type );
	lua_pushnumber( p_L, _return );
	return 1;
}

static int regProduceSampling (lua_State *p_L)
{
	int _return;
	int _id;
	string _name;
	string _var;
	string _type;

	_id = luaL_checkint( p_L, 1 );
	_name = luaL_checkstring( p_L, 2 );
	_var = luaL_checkstring( p_L, 3 );
	_type = luaL_checkstring( p_L, 4 );

	void* _value = 0;
	struct_var* _s = new struct_var;
	_s->var = _var;
	_s->com = PRODUCER;
	_s->queuing = 0;
	if ( _type == "int" )
	{
		_s->type = TYPE_INT;
		_value = &(_s->value._i);
		_s->value._i = 0;
	}
	else if ( _type == "float" )
	{
		_s->type = TYPE_FLOAT;
		_value = &(_s->value._f);
		_s->value._f = 0;
	}
	else if ( _type == "string" )
	{
		_s->type = TYPE_STRING;
		_value = &(_s->value._s);
		_s->value._s = 0;
	}
	vars()[_id].push_back( _s );

	_return = WESBMessenger_regProduceSampling_full( _id, (char*)_name.c_str(), _value, _s->type );
	lua_pushnumber( p_L, _return );
	return 1;
}

static int regConsumQueuing (lua_State *p_L)
{
	int _return;
	string _name;
	string _var;
	string _type;
	int _id;

	_id = luaL_checkint( p_L, 1 );
	_name = luaL_checkstring( p_L, 2 );
	_var = luaL_checkstring( p_L, 3 );
	_type = luaL_checkstring( p_L, 4 );

	void* _value = 0;
	struct_var* _s = new struct_var;
	_s->var = _var;
	_s->com = CONSUMER;
	_s->queuing = 1;
	_s->size = 0;
	if ( _type == "int" )
	{
		_s->type = TYPE_INT;
		_value = &(_s->value._qi);
	}
	else if ( _type == "float" )
	{
		_s->type = TYPE_FLOAT;
		_value = &(_s->value._qf);
	}
	else if ( _type == "string" )
	{
		_s->type = TYPE_STRING;
		_value = &(_s->value._qs);
	}
	vars()[_id].push_back( _s );

	_return = WESBMessenger_regConsumQueuing_full( _id, (char*)_name.c_str(), _value, &_s->size, _s->type, WESBMESSENGER_MAX_QUEUEING_SIZE );
	lua_pushnumber( p_L, _return );
	return 1;
}


static int regProduceQueuing (lua_State *p_L)
{
	int _return;
	string _name;
	string _var;
	string _type;
	int _id;

	_id = luaL_checkint( p_L, 1 );
	_name = luaL_checkstring( p_L, 2 );
	_var = luaL_checkstring( p_L, 3 );
	_type = luaL_checkstring( p_L, 4 );

	void* _value = 0;
	struct_var* _s = new struct_var;
	_s->var = _var;
	_s->com = PRODUCER;
	_s->queuing = 1;
	_s->size = 0;
	if ( _type == "int" )
	{
		_s->type = TYPE_INT;
		_value = &(_s->value._qi);
		_s->value._qi = 0;
	}
	else if ( _type == "float" )
	{
		_s->type = TYPE_FLOAT;
		_value = &(_s->value._qf);
		_s->value._qf = 0;
	}
	else if ( _type == "string" )
	{
		_s->type = TYPE_STRING;
		_value = &(_s->value._qs);
		_s->value._qs = 0;
	}
	vars()[_id].push_back( _s );

	_return = WESBMessenger_regProduceQueuing_full( _id, (char*)_name.c_str(), _value, &_s->size, _s->type );
	lua_pushnumber( p_L, _return );
	return 1;
}

static int update (lua_State *p_L)
{
	int _return;
	int _i,_j;
	int _id;

	_id = luaL_checkint( p_L, 1 );

	// set producer vars()[_id]
	for ( _i=0; _i<(int)vars()[_id].size(); _i++ )
	{
		if ( vars()[_id][_i]->com == PRODUCER )
		{
			lua_settop( p_L, 0 );
			ostringstream _oss;
			_oss << "return " << vars()[_id][_i]->var << ";";
			luaL_dostring( p_L, _oss.str().c_str() );

			if ( vars()[_id][_i]->queuing == 0 )
			{
				switch ( vars()[_id][_i]->type )
				{
				case TYPE_INT:
					if ( lua_isnumber( p_L, -1 ) ) {
						vars()[_id][_i]->value._i = (int)lua_tonumber( p_L, -1 );
					}
					break;
				case TYPE_FLOAT:
					if ( lua_isnumber( p_L, -1 ) ) {
						vars()[_id][_i]->value._f = (float)lua_tonumber( p_L, -1 );
					}
					break;
				case TYPE_STRING:
					if ( lua_isstring( p_L, -1 ) ) {
						if ( vars()[_id][_i]->value._s != 0 )
						{
							delete [] vars()[_id][_i]->value._s;
						}

						string _value = lua_tostring( p_L, -1 );
						vars()[_id][_i]->value._s = new char[ _value.length() + 1 ];
						strcpy( vars()[_id][_i]->value._s, _value.c_str() );
					}
					break;
				}
			}
			else if ( lua_istable( p_L, -1 ) ) 	// queuing producer
			{
				int _oldSize = vars()[_id][_i]->size;
				vars()[_id][_i]->size = lua_rawlen( p_L, -1 );
				switch ( vars()[_id][_i]->type )
				{
				case TYPE_INT:
					if ( vars()[_id][_i]->value._qi != 0 )
					{
						delete [] vars()[_id][_i]->value._qi;
					}
					vars()[_id][_i]->value._qi = new int[ vars()[_id][_i]->size ];
					for ( _j=0; _j<vars()[_id][_i]->size; _j++ )
					{
						lua_pushnumber( p_L, _j+1 );
						lua_gettable( p_L, -2 );
						if ( lua_isnumber( p_L, -1 ) )
						{
							vars()[_id][_i]->value._qi[ _j ] = (int)lua_tonumber( p_L, -1 );
						}
						lua_pop( p_L, 1 );
					}
					break;
				case TYPE_FLOAT:
					if ( vars()[_id][_i]->value._qf != 0 )
					{
						delete [] vars()[_id][_i]->value._qf;
					}
					vars()[_id][_i]->value._qf = new float[ vars()[_id][_i]->size ];
					for ( _j=0; _j<vars()[_id][_i]->size; _j++ )
					{
						lua_pushnumber( p_L, _j+1 );
						lua_gettable( p_L, -2 );
						if ( lua_isnumber( p_L, -1 ) )
						{
							vars()[_id][_i]->value._qf[ _j ] = (float)lua_tonumber( p_L, -1 );
						}
						lua_pop( p_L, 1 );
					}
					break;
				case TYPE_STRING:
					if ( vars()[_id][_i]->value._qs != 0 )
					{
						for ( _j=0; _j<_oldSize; _j++ )
						{
							delete [] vars()[_id][_i]->value._qs[ _j ];
						}
						free( vars()[_id][_i]->value._qs );
					}
					vars()[_id][_i]->value._qs = (char**)malloc( sizeof(char*) * vars()[_id][_i]->size );
					for ( _j=0; _j<vars()[_id][_i]->size; _j++ )
					{
						lua_pushnumber( p_L, _j+1 );
						lua_gettable( p_L, -2 );
						if ( lua_isstring( p_L, -1 ) )
						{
							string _value = lua_tostring( p_L, -1 );
							vars()[_id][_i]->value._qs[ _j ] = new char[ _value.size() + 1 ];
							strcpy( vars()[_id][_i]->value._qs[ _j ], _value.c_str() );
						}
						lua_pop( p_L, 1 );
					}
					break;
				}

				ostringstream _emptyLuaVar;
				_emptyLuaVar << vars()[_id][_i]->var << "={};";
				luaL_dostring( p_L, _emptyLuaVar.str().c_str() );
			}
			lua_pop( p_L, 1 );
		}
	}

	_return = WESBMessenger_update_full( _id );
	lua_pushnumber( p_L, _return );

	// get consummer vars()[_id]
	for ( _i=0; _i<(int)vars()[_id].size(); _i++ )
	{
		if ( vars()[_id][_i]->com == CONSUMER )
		{
			ostringstream _oss;
			_oss << vars()[_id][_i]->var << "=";

			if ( vars()[_id][_i]->queuing == 0 )
			{
				switch ( vars()[_id][_i]->type )
				{
				case TYPE_INT:
					_oss << vars()[_id][_i]->value._i;
					break;
				case TYPE_FLOAT:
					_oss << vars()[_id][_i]->value._f;
					break;
				case TYPE_STRING:
					_oss << "\"" << str_replace("\n", "", str_replace( "\"", "\\\"", vars()[_id][_i]->value._s )) << "\"";
					break;
				}
			}
			else
			{
				_oss << "{";
				switch ( vars()[_id][_i]->type )
				{
				case TYPE_INT:
					for ( _j=0; _j<vars()[_id][_i]->size; _j++)
					{
						if ( _j > 0 )
						{
							_oss << ",";
						}
						_oss << ((int*)vars()[_id][_i]->value._qi)[_j];
					}
					break;
				case TYPE_FLOAT:
					for ( _j=0; _j<vars()[_id][_i]->size; _j++)
					{
						if ( _j > 0 )
						{
							_oss << ",";
						}
						_oss << ((float*)vars()[_id][_i]->value._qf)[_j];
					}
					break;
				case TYPE_STRING:
					for ( _j=0; _j<vars()[_id][_i]->size; _j++)
					{
						if ( _j > 0 )
						{
							_oss << ",";
						}

						string _tmp = ((char**)vars()[_id][_i]->value._qs)[_j];
						_tmp = str_replace( "\"", "\\\"", _tmp );
						_tmp = str_replace("\n", "", _tmp);
						_oss << "\"" << _tmp.c_str() << "\"";
					}
					break;
				}
				_oss << "}";
			}

			_oss << ";";
			luaL_dostring( p_L,_oss.str().c_str() );
		}
	}

	return 1;
}

static int unreg (lua_State *p_L)
{
	int _return;
	int _i, _j;

	int _id;

	_id = luaL_checkint( p_L, 1 );

	_return = WESBMessenger_unreg_full( _id );
	lua_pushnumber( p_L, _return );

	for ( _i=0; _i<(int)vars()[_id].size(); _i++ )
	{
		if ( vars()[_id][_i]->com == PRODUCER )
		{
			if ( vars()[_id][_i]->queuing == 0 )
			{
				switch ( vars()[_id][_i]->type )
				{
				case TYPE_STRING:
					if ( vars()[_id][_i]->value._s != 0 )
					{
						delete [] vars()[_id][_i]->value._s;
					}
					break;
				}
			}
			else
			{
				switch ( vars()[_id][_i]->type )
				{
				case TYPE_INT:
					if ( vars()[_id][_i]->value._qi != 0 )
					{
						delete [] vars()[_id][_i]->value._qi;
					}
					break;
				case TYPE_FLOAT:
					if ( vars()[_id][_i]->value._qf != 0 )
					{
						delete [] vars()[_id][_i]->value._qf;
					}
					break;
				case TYPE_STRING:
					if ( vars()[_id][_i]->value._qs != 0 )
					{
						for ( _j=0; _j<vars()[_id][_i]->size; _j++ )
						{
							delete [] vars()[_id][_i]->value._qs[ _j ];
						}
						free( vars()[_id][_i]->value._qs );
					}
					break;
				}
			}
		}
		delete vars()[_id][_i];
	}
	if ( vars().find(_id) != vars().end() )
	{
		vars().erase(_id);
	}

	return 1;
}

} // namespace messenger

using namespace messenger;

static const luaL_Reg messengerlib[] = {
{"init",   					init},
{"regConsumSampling",   	regConsumSampling},
{"regProduceSampling",   	regProduceSampling},
{"regConsumQueuing",   		regConsumQueuing},
{"regProduceQueuing",   	regProduceQueuing},
{"update",   				update},
{"unreg",					unreg},
{NULL, NULL}
};

extern "C" {
	/*
	** Open messenger library
	*/
	int LUA_API luaopen_wesbmessenger_c (lua_State *L) {
	  luaL_newlib(L, messengerlib);
	  return 1;
	}
}
