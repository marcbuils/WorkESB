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
 *  Created on: 25 fevr. 2011
 *      Author: Marc Buils (CSIE)
 */
 
#ifndef __CSIEMessenger_H__

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_STRING 2

#define CSIEMESSENGER_MAX_QUEUEING_SIZE 512

typedef const char* (*Shared_Func)( char* p_param );
typedef void (*CallBack_Func)( char* p_param );
typedef void (*Event_Func)( char* p_param );

typedef enum
{
	CONSUMER,
	PRODUCER
}typ_e_com;

int _CSIEMessengerInstance; // CSIEMessenger instance

extern "C"
{
int CSIEMessenger_init_full( char* p_domain, char* p_name );
int CSIEMessenger_regConsumSampling_full( int p_id, char* p_name, void* p_value, int p_type );
int CSIEMessenger_regProduceSampling_full( int p_id, char* p_name, void* p_value, int p_type );
int CSIEMessenger_regConsumQueuing_full( int p_id, char* p_name, void* p_values, int *p_size, int p_type, int p_maxsize );
int CSIEMessenger_regProduceQueuing_full( int p_id, char* p_name, void* p_values, int *p_size, int p_type );
int CSIEMessenger_update_full( int p_id  );
int CSIEMessenger_unreg_full( int p_id  );
int CSIEMessenger_share_full( int p_id, char* p_name, Shared_Func p_function );
int CSIEMessenger_call_full( int p_id, char* p_name, char* p_params, CallBack_Func p_function );
int CSIEMessenger_bind_full( int p_id, char* p_name, Event_Func p_function );
int CSIEMessenger_trigger_full( int p_id, char* p_name, char* p_params );
}


int CSIEMessenger_init( char* p_domain, char* p_name )
{
	_CSIEMessengerInstance = CSIEMessenger_init_full( p_domain, p_name );
	return ( _CSIEMessengerInstance >= 0 ? _CSIEMessengerInstance : -1 );
}

int CSIEMessenger_regConsumSampling( char* p_name, void* p_value, int p_type )
{
	return CSIEMessenger_regConsumSampling_full( _CSIEMessengerInstance, p_name, p_value, p_type );
}

int CSIEMessenger_regProduceSampling( char* p_name, void* p_value, int p_type )
{
	return CSIEMessenger_regProduceSampling_full( _CSIEMessengerInstance, p_name, p_value, p_type );
}

int CSIEMessenger_regConsumQueuing( char* p_name, void* p_values, int *p_size, int p_type, int p_maxsize = CSIEMESSENGER_MAX_QUEUEING_SIZE )
{
	return CSIEMessenger_regConsumQueuing_full( _CSIEMessengerInstance, p_name, p_values, p_size, p_type, p_maxsize );
}

int CSIEMessenger_regProduceQueuing( char* p_name, void* p_values, int *p_size, int p_type )
{
	return CSIEMessenger_regProduceQueuing_full( _CSIEMessengerInstance, p_name, p_values, p_size, p_type );
}

int CSIEMessenger_share( char* p_name, Shared_Func p_function )
{
	return CSIEMessenger_share_full( _CSIEMessengerInstance, p_name, p_function );
}

int CSIEMessenger_call( char* p_name, char* p_params, CallBack_Func p_function )
{
	return CSIEMessenger_call_full( _CSIEMessengerInstance, p_name, p_params, p_function );
}

int CSIEMessenger_bind( char* p_name, Event_Func p_function )
{
	return CSIEMessenger_bind_full( _CSIEMessengerInstance, p_name, p_function );
}

int CSIEMessenger_trigger( char* p_name, char* p_params )
{
	return CSIEMessenger_trigger_full( _CSIEMessengerInstance, p_name, p_params );
}

int CSIEMessenger_update( )
{
	return CSIEMessenger_update_full( _CSIEMessengerInstance );
}

int CSIEMessenger_unreg( )
{
	return CSIEMessenger_unreg_full( _CSIEMessengerInstance );
}

#endif // __CSIEMessenger_H__
