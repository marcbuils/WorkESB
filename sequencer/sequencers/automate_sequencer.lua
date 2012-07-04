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
local lfs = require('lfs');
	
-- GLOBAL VARS
g_automate = nil;
p = {};
c = {};

-- LOCAL FUCTIONS
local _lastTime = 0;
local _automateEvent;

-- Start an automate
local _startAutomate = function( p_params )
	local _return = {
		status = 1
	};
	
	if ( _status ~= "stopped" ) then
		return false;
	end

	local _file, _error;
	_file, _error = loadfile( p_params.file );
	if ( _file == nil ) then
		_return.status = 0;
		_return.error = _error;
	else
		_status = "started";
		_time = 0;
		_lastTime = os.time();
		table.insert(LOGS, "INFO: AUTOMATE START");
		csiemessenger.trigger(_automateEvent, _status);

		g_automate = coroutine.create( _file );
	end
	
	return _return;
end
	
-- Stop an automate
local _stopAutomate = function( p_params )
	if ( _status ~= "started" and _status ~= "paused" ) then
		return false;
	end

	_automateFile = "";
	_automateName = "";
	g_automate = nil;

	_status = "stopped";
	table.insert(LOGS, "INFO: AUTOMATE STOP");
	csiemessenger.trigger(_automateEvent, _status);
	
	return true;
end

-- Pause an automate
local _pauseAutomate = function( p_params )
	if ( _status ~= "started" ) then
		return false;
	end
	
	_status = "paused";
	table.insert(LOGS, "INFO: AUTOMATE PAUSED");
	csiemessenger.trigger(_automateEvent, _status);
	
	return true;
end

-- Resume an automate
local _resumeAutomate = function( p_params )
	if ( _status ~= "paused" ) then
		return false;
	end
	
	_status = "started";
	_lastTime = os.time();
	table.insert(LOGS, "INFO: AUTOMATE RESUME");
	csiemessenger.trigger(_automateEvent, _status);
	
	return true;
end

-- Get the liste of automates
local _getAutomates = function()
	local _automateFiles = {};
	local _i = 0;
	
	for file in lfs.dir('automates/') do
		if ( string.sub(file, -4) == '.lua' ) then
			_automateFiles[_i] = { 
				name = string.sub(file, 1, -5),
				file = "automates/" .. file;
			};
			
			_i = _i+1;
		end
	end

	return _automateFiles;
end

-- START
onstart = function( p_infos )
	g_config = p_infos;
	
	csiemessenger.init( g_config.domain, g_config.name );
	csiemessenger.regProduceSampling( _ifndef( g_config.variable_status, "AUTOMATE_STATUS" ), "_status", "string" );
	csiemessenger.regProduceSampling( _ifndef( g_config.variable_time, "AUTOMATE_TIME" ), "_time", "int" );
	
	-- reg functions
	csiemessenger.share( _ifndef( g_config.start, "startAutomate" ), _startAutomate );
	csiemessenger.share( _ifndef( g_config.stop, "stopAutomate" ), _stopAutomate );
	csiemessenger.share( _ifndef( g_config.pause, "pauseAutomate" ), _pauseAutomate );
	csiemessenger.share( _ifndef( g_config.resume, "resumeAutomate" ), _resumeAutomate );
	csiemessenger.share( _ifndef( g_config.get, "getAutomates" ), _getAutomates );
	_automateEvent = _ifndef( g_config.event, "AUTOMATE_EVENT" );
	
	-- Set status
	_status = "stopped";

	-- Logs
	LOGS = {};
	csiemessenger.regProduceQueuing( _ifndef( g_config.variable_logs, "LOGS" ), 'LOGS', 'string');

	-- add functions of automate
	loadfile( 'plugins/lua/automate.lua' )();
	
	-- add csiemessenger variables
	local _consumers = {};
	local _producers = {};

	csiemessenger.trigger("csiemessenger_ping");
	csiemessenger.bind("csiemessenger_pong", function(p_module)
		if ( p_module.name ~= "IHM" and p_module.name ~= g_config.name ) then
			if ( p_module.variable.com == "consumer" and p_module.variable.queuing == false ) then
				if (_producers[p_module.variable.name] == nil) then
					_producers[p_module.variable.name] = true;
					csiemessenger.regProduceQueuing( p_module.variable.name,  'p["'..p_module.variable.name..'"]',  p_module.variable.type );
				end
			elseif ( p_module.variable.com == "producer" and p_module.variable.queuing == false ) then
				if (_consumers[p_module.variable.name] == nil) then
					_consumers[p_module.variable.name] = true;
					csiemessenger.regConsumSampling( p_module.variable.name,  'c["'..p_module.variable.name..'"]',  p_module.variable.type );
				end
			elseif ( p_module.variable.com == "consumer" and p_module.variable.queuing == true ) then
				if (_producers[p_module.variable.name] == nil) then
					_producers[p_module.variable.name] = true;
					csiemessenger.regProduceQueuing( p_module.variable.name,  'p["'..p_module.variable.name..'"]',  p_module.variable.type ); 
				end
			elseif ( p_module.variable.com == "producer" and p_module.variable.queuing == true ) then
				if (_consumers[p_module.variable.name] == nil) then
					_consumers[p_module.variable.name] = true;
					csiemessenger.regConsumQueuing( p_module.variable.name,  'c["'..p_module.variable.name..'"]',  p_module.variable.type ); 
				end
			end
		end
	end);
	
	-- load a custom configuration
	loadfile( 'conf/config.lua' )();
end


-- UPDATE
onupdate = function()
	-- transform sampling producers to queuing
	for _name, _value in pairs( p ) do
		if ( type(_value) ~= "table" ) then
			p[_name] = {};
			table.insert( p[_name], _value );
		end
	end

	csiemessenger.update();
	
	if ( _status == "started" ) then
		if ( g_automate ~= nil ) then
			if ( coroutine.status( g_automate ) == "dead" ) then
				_stopAutomate();
			else
				_time = _time + os.time() - _lastTime;
				_lastTime = os.time();
				coroutine.resume( g_automate );
			end
		end
	end
	
	io.flush();
end


-- STOP
onstop = function()
	if ( g_automate ~= nil ) then
		_stopAutomate();
	end
	
	csiemessenger.unreg();
end

