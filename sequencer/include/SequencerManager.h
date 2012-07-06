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
 *  Created on: 18 avr. 2011
 *      Author: Marc Buils (MATIS - http://www.matis-group.com)
 */

#ifndef SEQUENCERMANAGER_H_
#define SEQUENCERMANAGER_H_

// Librairies LUA
extern "C" {
	#include <lauxlib.h>
	#include <lualib.h>
}
#include <string>
#include <map>
using namespace std;

#include <json/json.h>

#ifdef WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

typedef int ( *DLL_ONSTART )( char* p_configuration );
typedef int ( *DLL_ONUPDATE )( void );
typedef int ( *DLL_ONSTOP )( void );

namespace sequencer
{

class SequencerManager {
public:
	enum SEQUENCER_TYPE {
		DLL,
		LUA
	};

private:
	struct sequencer_struct {
		string file;
		SEQUENCER_TYPE type;
		Json::Value config;
		union {
			struct {
#ifdef WIN32
				HINSTANCE hDll;
#else
				void* hDll;
#endif
				DLL_ONSTART onstart;
				DLL_ONUPDATE onupdate;
				DLL_ONSTOP onstop;
				int conf;
			} dll;
			struct {
				lua_State* L;
				int conf;
			} lua;
		} infos;
	};

	map<string, sequencer_struct> m_sequencers;
	int m_running;

public:
	SequencerManager();
	virtual ~SequencerManager();

	void add( string p_file, Json::Value p_config );
	void addLua( string p_file, Json::Value p_config );
	void addDll( string p_file, Json::Value p_config );

	void remove( string p_file );
	void removeLua( string p_file );
	void removeDll( string p_file );

	Json::Value list();

	void reload( string p_file );

	void run();
	void update();
	void stop();

	int isRunning();

	map<string, sequencer_struct> &sequencers(){ return this->m_sequencers; }
};

} // namespace sequencer

#endif /* SEQUENCERMANAGER_H_ */
