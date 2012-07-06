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

uuid = require("uuid");

__AUTOMATE_CALL_LIST__ = {};

automate = {
	-- FUNCTIONS
	-- Sleep (s)
	sleep = function ( p_time )
		local _endTime = os.time() + p_time;
		
		if (__AUTOMATE_DIALOG__ == nil) then
			__AUTOMATE_DIALOG__ = "";
			wesbmessenger.regProduceSampling( _ifndef( g_config.variable_dialog, "AUTOMATE_DIALOG" ), "__AUTOMATE_DIALOG__", "string" );
		end
		
		table.insert(LOGS, "INFO: START SLEEP " .. p_time);
		__AUTOMATE_DIALOG__ = json.encode({
			type = "wait",
			text = "Sleep "..p_time.."s"
		});
		
		while ( os.time() <= _endTime ) do
			coroutine.yield( g_automate );
		end
		
		__AUTOMATE_DIALOG__ = json.encode({
			type = "none"
		});
		table.insert(LOGS, "INFO: END SLEEP " .. p_time);
		coroutine.yield( g_automate );
	end,
	
	-- Wait (condition)
	wait = function ( p_condition )
		if (__AUTOMATE_DIALOG__ == nil) then
			__AUTOMATE_DIALOG__ = "";
			wesbmessenger.regProduceSampling( _ifndef( g_config.variable_dialog, "AUTOMATE_DIALOG" ), "__AUTOMATE_DIALOG__", "string" );
		end
		
		table.insert(LOGS, "INFO: START WAIT " .. p_condition);
		__AUTOMATE_DIALOG__ = json.encode({
			type = "wait",
			text = p_condition
		});
		
		while ( loadstring('return '..p_condition)() == false ) do
			coroutine.yield( g_automate );
		end
		
		__AUTOMATE_DIALOG__ = json.encode({
			type = "none"
		});
		table.insert(LOGS, "INFO: END WAIT " .. p_condition);
		coroutine.yield( g_automate );
	end,
	
	assert = function ( p_condition )
		if ( loadstring('return '..p_condition)() == true ) then
			table.insert(LOGS, "INFO: TEST OK - "..p_condition);
		else
			table.insert(LOGS, "ERROR: TEST KO - "..p_condition);
		end
	end,
	
	logs = function ( p_line )
		table.insert( LOGS, "AUTOMATE: " .. p_line );
	end,
	
	call = function ( p_name, p_params )
		local _return = nil;

		if ( __AUTOMATE_CALL_LIST__[p_name] == nil ) then
			wesbmessenger.regCall( p_name, '__AUTOMATE_CALL_LIST__["'..p_name..'"]' );
		end

		__AUTOMATE_CALL_LIST__[p_name](p_params, function( p_return )
			_return = p_return;
		end );

		while ( _return == nil ) do
			coroutine.yield( g_automate );
		end
		
		return _return;
	end,
	
	trigger = function( p_name, p_params )
		wesbmessenger.trigger( p_name, p_params );
		coroutine.yield( g_automate );
	end,
	
	alert = function( p_text, p_title )
		-- Send trigger
		if (__AUTOMATE_DIALOG__ == nil) then
			__AUTOMATE_DIALOG__ = "";
			wesbmessenger.regProduceSampling( _ifndef( g_config.variable_dialog, "AUTOMATE_DIALOG" ), "__AUTOMATE_DIALOG__", "string" );
		end
		__AUTOMATE_DIALOG__ = json.encode({
			type = "alert",
			text = p_text,
			title = p_title
		});
		coroutine.yield( g_automate );
		
		-- Receive return
		if ( __AUTOMATE_EVENT_DIALOG_RETURN__ == nil ) then
			__AUTOMATE_EVENT_DIALOG_RETURN__ = {};
			wesbmessenger.regConsumQueuing( "EVENT__".._ifndef(g_config.event_dialog_return, "AUTOMATE_DIALOG_RETURN"), "__AUTOMATE_EVENT_DIALOG_RETURN__", "string");
		end
		
		local _end = false;
		while ( _end == false ) do	
			for _i, _v in ipairs( __AUTOMATE_EVENT_DIALOG_RETURN__ ) do
				local _value = json.decode(_v);
				if (_value._parameter.type == "alert") then
					_end = true;
					__AUTOMATE_DIALOG__ = json.encode({
						type = "none"
					});
				end
			end
			coroutine.yield( g_automate );
		end
	end,

	confirm = function( p_text, p_title )
		local _return;
		
		-- Send trigger
		if (__AUTOMATE_DIALOG__ == nil) then
			__AUTOMATE_DIALOG__ = "";
			wesbmessenger.regProduceSampling( _ifndef( g_config.variable_dialog, "AUTOMATE_DIALOG" ), "__AUTOMATE_DIALOG__", "string" );
		end
		__AUTOMATE_DIALOG__ = json.encode({
			type = "confirm",
			text = p_text,
			title = p_title
		});
		coroutine.yield( g_automate );
		
		-- Receive return
		if ( __AUTOMATE_EVENT_DIALOG_RETURN__ == nil ) then
			__AUTOMATE_EVENT_DIALOG_RETURN__ = {};
			wesbmessenger.regConsumQueuing( "EVENT__".._ifndef(g_config.event_dialog_return, "AUTOMATE_DIALOG_RETURN"), "__AUTOMATE_EVENT_DIALOG_RETURN__", "string");
		end
		
		local _end = false;
		while ( _end == false ) do
			for _i, _v in ipairs( __AUTOMATE_EVENT_DIALOG_RETURN__ ) do
				local _value = json.decode(_v);
				if (_value._parameter.type == "confirm") then
					_end = true;
					_return = _value._parameter["return"];
					__AUTOMATE_DIALOG__ = json.encode({
						type = "none"
					});
				end
			end
			coroutine.yield( g_automate );
		end
		
		return _return;
	end,
	
	prompt = function( p_text, p_title )
		local _return;
		
		-- Send trigger
		if (__AUTOMATE_DIALOG__ == nil) then
			__AUTOMATE_DIALOG__ = "";
			wesbmessenger.regProduceSampling( _ifndef( g_config.variable_dialog, "AUTOMATE_DIALOG" ), "__AUTOMATE_DIALOG__", "string" );
		end
		__AUTOMATE_DIALOG__ = json.encode({
			type = "prompt",
			text = p_text,
			title = p_title
		});
		coroutine.yield( g_automate );
		
		-- Receive return
		if ( __AUTOMATE_EVENT_DIALOG_RETURN__ == nil ) then
			__AUTOMATE_EVENT_DIALOG_RETURN__ = {};
			wesbmessenger.regConsumQueuing( "EVENT__".._ifndef(g_config.event_dialog_return, "AUTOMATE_DIALOG_RETURN"), "__AUTOMATE_EVENT_DIALOG_RETURN__", "string");
		end
		
		local _end = false;
		while ( _end == false ) do
			for _i, _v in ipairs( __AUTOMATE_EVENT_DIALOG_RETURN__ ) do
				local _value = json.decode(_v);
				if (_value._parameter.type == "prompt") then
					_end = true;
					_return = _value._parameter["return"];
					__AUTOMATE_DIALOG__ = json.encode({
						type = "none"
					});
				end
			end
			coroutine.yield( g_automate );
		end
		
		return _return;
	end
};
