-- This file is part of WorkESB.
--
--  WorkESB is free software: you can redistribute it and/or modify
--  it under the terms of the GNU Lesser General Public License as published by
--  the Free Software Foundation, either version 3 of the License, or
--  (at your option) any later version.
--
--  WorkESB is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU Lesser General Public License for more details.
--
--  You should have received a copy of the GNU Lesser General Public License
--  along with WorkESB.  If not, see <http://www.gnu.org/licenses/>.
--
--  Created on: 18 avr. 2011
--      Author: Marc Buils (MATIS - http://www.matis-group.com)
--

local wesbmessenger = require('wesbmessenger');

_variables = {};
_add = function( p_params )
	_return = {
		status=1;
		error="";
	};
	if ( p_params.variable_in_name == nil ) then
		_return.status=0;
		_return.error="Variable IN  is not defined";
	elseif ( p_params.variable_in_type == nil ) then
		_return.status=0;
		_return.error="Type IN  is not defined";
	elseif ( p_params.variable_in_type ~= "int" 
		and p_params.variable_in_type ~= "float"
		and p_params.variable_in_type ~= "string" ) then
		_return.status=0;
		_return.error="Type IN is unknown";
	elseif ( p_params.variable_out_name == nil ) then
		_return.status=0;
		_return.error="Variable OUT unknown";
	elseif ( p_params.variable_out_type == nil ) then
		_return.status=0;
		_return.error="Type OUT is not defined";
	elseif ( p_params.variable_out_type ~= "int" 
		and p_params.variable_out_type ~= "float"
		and p_params.variable_out_type ~= "string" ) then
		_return.status=0;
		_return.error="Type OUT is unknown";
	elseif ( p_params.type == nil 
		or ( p_params.type ~= "queuing"
		and p_params.type ~= "sampling" ) ) then
		_return.status=0;
		_return.error="Type is unknow or not defined";
	else
		_variables[p_params.variable_out_name] = {};
		if ( p_params.type == "sampling" ) then
			wesbmessenger.regConsumSampling( 
				p_params.variable_in_name, 
				"_variables." .. p_params.variable_out_name .. "._in", 
				p_params.variable_in_type );
			wesbmessenger.regProduceSampling( 
				p_params.variable_out_name, 
				"_variables." .. p_params.variable_out_name .. "._out", 
				p_params.variable_out_type );
		else
			wesbmessenger.regConsumQueuing( 
				p_params.variable_in_name, 
				"_variables." .. p_params.variable_out_name .. "._in", 
				p_params.variable_in_type );
			wesbmessenger.regConsumQueuing( 
				p_params.variable_out_name, 
				"_variables." .. p_params.variable_out_name .. "._out", 
				p_params.variable_out_type );
		end
	end
	return _return;
end

_remove = function( p_params )
	_return = {
		status=1;
		error="";
	};
	
	if ( p_params == nil or _variables[p_params] == nil ) then
		_return.status=0;
		_return.error="Variable not found";
	else
		_variables[p_params] = nil;
	end
	return _return;
end
onstart = function( p_infos )
	wesbmessenger.init( p_infos.domain, p_infos.name );
	wesbmessenger.share( p_infos.add, _add );
	wesbmessenger.share( p_infos.remove, _remove );

	for _i, _v in pairs( p_infos.list ) do
		_add( _v );
	end
end

onupdate = function()
	wesbmessenger.update();
	for _i, _v in pairs( _variables ) do
		_variables[_i]._out = _variables[_i]._in;
	end
end

onstop = function()
	wesbmessenger.unreg();
end
