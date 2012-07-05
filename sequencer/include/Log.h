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
 *      Author: Marc Buils (MATIS - http://www.matis-group.com)
 */

#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <stdio.h>
using namespace std;

namespace sequencer
{

class Log {
protected:
	FILE 			*m_file;
	int 			m_level;

public:
	Log();
	virtual ~Log();

	static Log* get();
	int add( int p_type, string p_message );

	static const int LEVEL_DEBUG;
	static const int LEVEL_INFO;
	static const int LEVEL_WARNING;
	static const int LEVEL_ERROR;
};

}

#endif /* LOG_H_ */
