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

#include "../include/Log.h"
#include <json/json.h>
#include <time.h>

namespace sequencer
{

extern Json::Value &g_config();			// config file


// Log Levels
const int Log::LEVEL_DEBUG 		= 4;
const int Log::LEVEL_INFO 		= 3;
const int Log::LEVEL_WARNING	= 2;
const int Log::LEVEL_ERROR 		= 1;


Log::Log() {
	this->m_file = 0;
}

Log::~Log() {
	fclose( this->m_file );
}

Log* Log::get() {
	static Log s_instance;

	if ( s_instance.m_file == 0 )
	{
		string _file;
		_file = g_config().get("LOG_FILE", "sequencer.log").asString();

		s_instance.m_file = fopen( _file.c_str(), "w" );
		s_instance.m_level = g_config().get("LOG_LEVEL", Log::LEVEL_INFO).asInt();
	}
	return &s_instance;
}

int Log::add( int p_type, string p_message )
{
	string _message = "";

	if ( p_type > this->m_level )
	{
		return -1;
	}

	char _time[255];
    time_t _timestamp;
    struct tm * _t;
    _timestamp = time(NULL);
    _t = localtime(&_timestamp);
	sprintf( _time, "%04d-%02d-%02d %02d:%02d:%02d - ", _t->tm_year+1900, _t->tm_mon+1, _t->tm_mday, _t->tm_hour, _t->tm_min, _t->tm_sec );
	_message += _time;
	_message += p_message;
	_message += "\n";

	fprintf( this->m_file, "%s", _message.c_str() );
	fflush( this->m_file );

	return 0;
}

} // namespace sequencer
