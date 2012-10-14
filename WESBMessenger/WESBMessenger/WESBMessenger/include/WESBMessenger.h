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
 
#ifndef __WESBMessenger_H__

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_STRING 2

#define WESBMESSENGER_MAX_QUEUEING_SIZE 512

typedef const char* (*Shared_Func)( char* p_param );
typedef void (*CallBack_Func)( char* p_param );
typedef void (*Event_Func)( char* p_param );

typedef enum
{
	CONSUMER,
	PRODUCER
}typ_e_com;

int _WESBMessengerInstance; // WESBMessenger instance

extern "C"
{
int WESBMessenger_init_full( char* p_domain, char* p_name );
int WESBMessenger_consumSampling_full( int p_id, char* p_name, void* p_value, int p_type );
int WESBMessenger_produceSampling_full( int p_id, char* p_name, void* p_value, int p_type );
int WESBMessenger_consumQueuing_full( int p_id, char* p_name, void* p_values, int *p_size, int p_type, int p_maxsize );
int WESBMessenger_produceQueuing_full( int p_id, char* p_name, void* p_values, int *p_size, int p_type );
int WESBMessenger_update_full( int p_id  );
int WESBMessenger_unreg_full( int p_id  );
int WESBMessenger_share_full( int p_id, char* p_name, Shared_Func p_function );
int WESBMessenger_call_full( int p_id, char* p_name, char* p_params, CallBack_Func p_function );
int WESBMessenger_bind_full( int p_id, char* p_name, Event_Func p_function );
int WESBMessenger_trigger_full( int p_id, char* p_name, char* p_params );
}


int WESBMessenger_init( char* p_domain, char* p_name )
{
	_WESBMessengerInstance = WESBMessenger_init_full( p_domain, p_name );
	return ( _WESBMessengerInstance >= 0 ? _WESBMessengerInstance : -1 );
}

int WESBMessenger_consumSampling( char* p_name, void* p_value, int p_type )
{
	return WESBMessenger_consumSampling_full( _WESBMessengerInstance, p_name, p_value, p_type );
}

int WESBMessenger_produceSampling( char* p_name, void* p_value, int p_type )
{
	return WESBMessenger_produceSampling_full( _WESBMessengerInstance, p_name, p_value, p_type );
}

int WESBMessenger_consumQueuing( char* p_name, void* p_values, int *p_size, int p_type, int p_maxsize = WESBMESSENGER_MAX_QUEUEING_SIZE )
{
	return WESBMessenger_consumQueuing_full( _WESBMessengerInstance, p_name, p_values, p_size, p_type, p_maxsize );
}

int WESBMessenger_produceQueuing( char* p_name, void* p_values, int *p_size, int p_type )
{
	return WESBMessenger_produceQueuing_full( _WESBMessengerInstance, p_name, p_values, p_size, p_type );
}

int WESBMessenger_share( char* p_name, Shared_Func p_function )
{
	return WESBMessenger_share_full( _WESBMessengerInstance, p_name, p_function );
}

int WESBMessenger_call( char* p_name, char* p_params, CallBack_Func p_function )
{
	return WESBMessenger_call_full( _WESBMessengerInstance, p_name, p_params, p_function );
}

int WESBMessenger_bind( char* p_name, Event_Func p_function )
{
	return WESBMessenger_bind_full( _WESBMessengerInstance, p_name, p_function );
}

int WESBMessenger_trigger( char* p_name, char* p_params )
{
	return WESBMessenger_trigger_full( _WESBMessengerInstance, p_name, p_params );
}

int WESBMessenger_update( )
{
	return WESBMessenger_update_full( _WESBMessengerInstance );
}

int WESBMessenger_unreg( )
{
	return WESBMessenger_unreg_full( _WESBMessengerInstance );
}

#endif // __WESBMessenger_H__
