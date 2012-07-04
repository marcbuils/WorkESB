-- This file is part of M2Bench.
--
--  M2Bench is free software: you can redistribute it and/or modify
--  it under the terms of the GNU Lesser General Public License as published by
--  the Free Software Foundation, either version 3 of the License, or
--  (at your option) any later version.
--
--  M2Bench is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU Lesser General Public License for more details.
--
--  You should have received a copy of the GNU Lesser General Public License
--  along with M2Bench.  If not, see <http://www.gnu.org/licenses/>.
--
--  Created on: 18 avr. 2011
--      Author: Marc Buils (CSIE)
--

local csiemessenger = require('csiemessenger');

onstart = function( p_infos )
	csiemessenger.init( p_infos.domain, p_infos.name );
	csiemessenger.regProduceSampling( p_infos.variable_time, "TIME", "int" );
	TIME = os.time();
end

onupdate = function()
	TIME = os.time();
	csiemessenger.update();
end

onstop = function()
	csiemessenger.unreg();
end
