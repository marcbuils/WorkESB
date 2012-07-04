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

-- ifdef function
_ifndef = function( p_var, p_else )
	local _return = p_var;
	
	if ( _return == nil ) then
		_return = p_else;
	end
	
	return _return;
end

csiemessenger_c = require( "csiemessenger_c" );
local csiemessenger_c = csiemessenger_c;

json = require("json");
local json = json;

uuid = require("uuid");
local uuid = uuid;

local print = print;
local table = table;
local ipairs = ipairs;
local pairs = pairs;
local loadstring = loadstring;
local io = io;

csiemessenger_shareFunctions = {};
local csiemessenger_shareFunctions = csiemessenger_shareFunctions;
csiemessenger_callFunctions = {};
local csiemessenger_callFunctions = csiemessenger_callFunctions;
csiemessenger_events = {};
local csiemessenger_events = csiemessenger_events;

module( "csiemessenger" );

local EXTENSION_PARAMETER = "PARAMETER__";
local EXTENSION_RETURN_VAL = "RETURNVAL__";
local EXTENSION_EVENT = "EVENT__";

-- csiemessenger instance
local id = -1;

init = function( p_domain, p_name )
	id = csiemessenger_c.init( p_domain, p_name );
	return id;
end

update = function()
	local _return =  csiemessenger_c.update( id );

	-- exec shared functions
	for _i, _s in ipairs( csiemessenger_shareFunctions ) do
		_s.response = {};
        
        for _j, _w in ipairs( _s.waiting ) do
 			local _params = json.decode( _w );
			local _uuid = _params._uuid;
            
			if ( _s.event == 1 ) then
				_s.functionShared( _params._parameter );
			else
				local _response = { _response = _s.functionShared( _params._parameter ) };
				local _pos = 1 + #_s.response;

				_response._uuid = _uuid;
				_s.response[ _pos ] = json.encode( _response );
			end
		end
	end
	
	-- receive parameter
	for _i, _c in ipairs( csiemessenger_callFunctions ) do
		_c.parameter = {};
		for _j, _r in ipairs( _c.response ) do
			local _params = json.decode( _r );
			local _uuid = _params._uuid;

			if ( _c.callback[ _uuid ] ~= nil ) then
				_c.callback[ _uuid ]( _params._response );
				_c.callback[ _uuid ] = nil;
			end
		end
	end

	return _return;
end

unreg = function( )
	return csiemessenger_c.unreg( id );
end

regConsumSampling = function( p_name, p_variable, p_type )
	return csiemessenger_c.regConsumSampling( id, p_name, p_variable, p_type );
end

regProduceSampling = function( p_name, p_variable, p_type )
	return csiemessenger_c.regProduceSampling( id, p_name, p_variable, p_type );
end

regConsumQueuing = function( p_name, p_variable, p_type )
	return csiemessenger_c.regConsumQueuing( id, p_name, p_variable, p_type );
end

regProduceQueuing = function( p_name, p_variable, p_type )
	return csiemessenger_c.regProduceQueuing( id, p_name, p_variable, p_type );
end

share = function( p_name, p_function )
	local _pos = 1 + #csiemessenger_shareFunctions;

	regConsumQueuing( EXTENSION_PARAMETER .. p_name, "csiemessenger_shareFunctions[" .. _pos .. "].waiting", "string" );
	regProduceQueuing( EXTENSION_RETURN_VAL .. p_name, "csiemessenger_shareFunctions[" .. _pos .. "].response", "string" );

	csiemessenger_shareFunctions[ _pos ] = {
		waiting = {},
		response = {},
		event = 0,
		functionShared = p_function
	};

	return true;
end

regCall = function( p_name, p_variable )
	local _pos;
	
	_pos = 1 + #csiemessenger_callFunctions;
   
	regConsumQueuing( EXTENSION_RETURN_VAL .. p_name, "csiemessenger_callFunctions[" .. _pos .. "].response", "string" );
	regProduceQueuing( EXTENSION_PARAMETER .. p_name, "csiemessenger_callFunctions[" .. _pos .. "].parameter", "string" );
	
	csiemessenger_callFunctions[ _pos ] = {
		event = 0,
		parameter = {},
		response = {},
		callback = {}
	};

	loadstring(p_variable .. "=function(p_params, p_callback) return csiemessenger.callFunction(" .. _pos .. ", p_params, p_callback); end")();
    return true;
end

callFunction = function( p_idFunction, p_params, p_callback )
	local _r;
	local _params;
	local _uuid = uuid.new();
	
	_params = {
		_uuid = _uuid,
		_parameter = p_params
	};
	
	-- Save callback
	csiemessenger_callFunctions[ p_idFunction ].callback[ _uuid ] = p_callback;
	
	-- Call function
	_params._uuid = _uuid;
	_r = 1 + #csiemessenger_callFunctions[ p_idFunction ].parameter;
	csiemessenger_callFunctions[ p_idFunction ].parameter[ _r ] = json.encode( _params );
	
	return true;
end

bind = function( p_name, p_function )
	local _pos = 1 + #csiemessenger_shareFunctions;
    
	regConsumQueuing( EXTENSION_EVENT .. p_name, "csiemessenger_shareFunctions[" .. _pos .. "].waiting", "string" );
	csiemessenger_shareFunctions[ _pos ] = {
		waiting = {},
		response = {},
		event = 1,
		functionShared = p_function
	};

	return true;
end

trigger = function( p_name, p_params )
	local _pos;
	local _params = {
		_parameter = p_params
	};
	
	if ( csiemessenger_events[ p_name ] == nil ) then
		csiemessenger_events[ p_name ] = {};
		regProduceQueuing( EXTENSION_EVENT .. p_name, "csiemessenger_events[\"" .. p_name .. "\"]", "string" );
    end
	
	table.insert(csiemessenger_events[ p_name ], json.encode( _params ));

	return true;
end
