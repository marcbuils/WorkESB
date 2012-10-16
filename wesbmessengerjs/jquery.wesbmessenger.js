/**
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
 *  Created on: 31 janv. 2012
 *      Author: Marc Buils (MATIS - http://www.matis-group.com)
 */
;(function($){
/*
 UUID
 The MIT License: Copyright (c) 2010 LiosK.
*/
function UUID(){}UUID.generate=function(){var a=UUID._getRandomInt,b=UUID._hexAligner;return b(a(32),8)+"-"+b(a(16),4)+"-"+b(16384|a(12),4)+"-"+b(32768|a(14),4)+"-"+b(a(48),12)};UUID._getRandomInt=function(a){if(a<0)return NaN;if(a<=30)return 0|Math.random()*(1<<a);if(a<=53)return(0|Math.random()*1073741824)+(0|Math.random()*(1<<a-30))*1073741824;return NaN};UUID._getIntAligner=function(a){return function(b,f){for(var c=b.toString(a),d=f-c.length,e="0";d>0;d>>>=1,e+=e)if(d&1)c=e+c;return c}};
UUID._hexAligner=UUID._getIntAligner(16);

/**
 * Constructeur
 */
$.wesbmessenger = function() {
	this.initialized = false;
	this._oninit = new $.Deferred();
	this.options = {};
};

/**
 * Default options
 */
$.wesbmessenger.options = {
	server: 	( typeof(document) == "undefined" ? 'ws://localhost:8080' : 'ws://' + document.URL.substr(7).split('/')[0] ),
	frequency: 	50,					// ms
	inittime:	1000
};

/*
 * Static vars
 */
$.wesbmessenger.EXTENSION_PARAMETER = "PARAMETER__";
$.wesbmessenger.EXTENSION_RETURN_VAL = "RETURNVAL__";
$.wesbmessenger.EXTENSION_EVENT = "EVENT__";
$.wesbmessenger.producer = {};
$.wesbmessenger.consumer = {};
$.wesbmessenger.consumercid = {};
$.wesbmessenger.producercid = {};
$.wesbmessenger.s_instance = null;
$.wesbmessenger.types = {
	"int":		0,
	"float":	1,
	"string":	2
};

/**
 * Singleton
 */
$.wesbmessenger.singleton = function(){
	if ( $.wesbmessenger.s_instance == null ) {
		$.wesbmessenger.s_instance = new $.wesbmessenger();
	}
	return $.wesbmessenger.s_instance;
};

/**
 * init event
 */
$.wesbmessenger.prototype.init = function(){
	return this._oninit.promise();
}

/**
 * WESBMessenger connect
 */
$.wesbmessenger.prototype.connect = function( p_domain, p_name, p_options ) {
	var _this = this;
	var _timer;
	this.options = $.extend({}, p_options, $.wesbmessenger.options);
	
    if (typeof(window) != "undefined" && 'MozWebSocket' in window) {
      	window.WebSocket = window.MozWebSocket;
    }
	
	_timer = function(){
		_this._update_producers();
	};
	
	var _onopen, _onmessage, _onclose;
	_onopen = function(){
		_this.initialized = true;
		_this.ws.send(JSON.stringify({
			"function": "init",
			"domain": p_domain,
			"name": p_name
		}) + "\n");
		_this._oninit.resolve();
		
		setTimeout( _timer, _this.options.inittime );
	};
	_onmessage = function(p_data){
		var _data = JSON.parse( typeof(p_data.data) == "undefined" ? p_data.utf8Data : p_data.data);
		if ( typeof( _data.error ) != 'undefined' ){
			$.each( _data.error, function( _index, _value ){
				console.error( _value );
			} );
		}
		_this._update_consumers( _data );
		$($.wesbmessenger).trigger("wesbmessenger_update");
		
		setTimeout( _timer, _this.options.frequency );
	};
	_onclose = function(){
		console.error("WESBMessenger connexion closed");
		_this._oninit.reject("WESBMessenger connexion closed");
	};

	if ( typeof(document) != "undefined" ){
		this.ws = new window.WebSocket( this.options.server, 'wesbmessenger' );
		this.ws.onopen = _onopen;
		this.ws.onmessage = _onmessage;
		this.ws.onclose = _onclose;
	} else {
		var _websocket = require('websocket').client;
		this._ws = new _websocket();
		this._ws.on('connect', function( p_connection ){
			$.wesbmessenger.singleton().ws = p_connection;
			$.wesbmessenger.singleton().ws.on('message', _onmessage);
			$.wesbmessenger.singleton().ws.on('close', _onclose);
			_onopen();
		});
		this._ws.connect( this.options.server, 'wesbmessenger' );
	}
	
	return this;
};

/**
 * WESBMessenger consumSampling
 */
$.wesbmessenger.prototype.consumSampling = function( p_name, p_type ) {
	if ( typeof($.wesbmessenger.consumercid[ p_name ]) != "undefined" )
	{
		return this;
	}
	
	var _type = $.wesbmessenger.types[p_type];
	var _cid;
	_cid = this._callfunction( "consumSampling", { name: p_name, type: _type })["return"];
	$.wesbmessenger.consumercid[ p_name ] = _cid;
	
	return this;
};

/**
 * WESBMessenger produceSampling
 */
$.wesbmessenger.prototype.produceSampling = function( p_name, p_type ) {
	return this.produceQueuing( p_name, p_type );
	
/*	NO PRODUCE SAMPLING - TOO DANGEROUS
	if ( $.inArray( p_name, $.wesbmessenger.producercid ) != -1 )
	{
		return $.wesbmessenger.producercid[ p_name ];
	}
	
	var _type = $.wesbmessenger.types[p_type];
	
	if ( p_type == "string" ) {
		$.wesbmessenger.producer[ p_name ] = "";
	}
	else
	{
		$.wesbmessenger.producer[ p_name ] = 0;
	}
	
	var _cid;
	_cid = this.callfunction( "produceSampling", { name: p_name, type: _type } )["return"];
	$.wesbmessenger.producercid[ p_name ] = _cid;
//	$.wesbmessenger.singleton()._update_producers();
	
	return _cid;
*/
};

/**
 * WESBMessenger consumQueuing
 */
$.wesbmessenger.prototype.consumQueuing = function( p_name, p_type ) {
	if (typeof($.wesbmessenger.consumercid[ p_name ]) != "undefined" )
	{
		return this;
	}	
	
	var _type = $.wesbmessenger.types[p_type];
	var _cid;
	_cid = this._callfunction( "consumQueuing", { name: p_name, type: _type } )["return"];
	$.wesbmessenger.consumercid[ p_name ] = _cid;
	
	return this;
};

/**
 * WESBMessenger produceSampling
 */
$.wesbmessenger.prototype.produceQueuing = function( p_name, p_type ) {
	if ( typeof($.wesbmessenger.producercid[ p_name ]) != "undefined" )
	{
		return this;
	}
	
	var _type = $.wesbmessenger.types[p_type];
	$.wesbmessenger.producer[ p_name ] = [];

	var _cid = this._callfunction( "produceQueuing", { name: p_name, type: _type } )["return"];
	$.wesbmessenger.producercid[ p_name ] = _cid;
//	$.wesbmessenger.singleton()._update_producers();
	
	return this;
};

/**
 * WESBMessenger bind
 */
$.wesbmessenger.prototype.bind = function( p_name, p_callback ) {
	var _name = $.wesbmessenger.EXTENSION_EVENT + p_name;
	this.consumQueuing( _name, "string" );
	
	this.update( function( ){
		var _params;
		var _i;
		
		if ( typeof($.wesbmessenger.consumer[ _name ]) == "undefined" ) return;
		for ( _i=0; _i < $.wesbmessenger.consumer[ _name ].length; _i++ ){
			_params = JSON.parse( $.wesbmessenger.consumer[ _name ][ _i ] );
			p_callback( _params._parameter );
		}
	} );
	
	return this;
};

/**
 * WESBMessenger trigger
 */
$.wesbmessenger.prototype.trigger = function( p_name, p_params ) {
	var _name = $.wesbmessenger.EXTENSION_EVENT + p_name;
	this.produceQueuing( _name, "string" );

	$.wesbmessenger.producer[ _name ].push( JSON.stringify( { _parameter: p_params } ) );
	
	return this;
};

/**
 * WESBMessenger share
 */
$.wesbmessenger.prototype.share = function( p_name, p_callback ) {
	var _name = $.wesbmessenger.EXTENSION_PARAMETER + p_name;
	var _nameResponse = $.wesbmessenger.EXTENSION_RETURN_VAL + p_name;
	this.produceQueuing( _nameResponse, "string" );
	this.consumQueuing( _name, "string" );
	
	this.update( function( ){
		var _params;
		var _i;
		
		if ( typeof($.wesbmessenger.consumer[ _name ]) == "undefined" ) return;
		for ( _i=0; _i < $.wesbmessenger.consumer[ _name ].length; _i++ ){
			var _return;
			var _pos;

			_params = JSON.parse( $.wesbmessenger.consumer[ _name ][ _i ] );
			_return = {
				_uuid: 		_params._uuid,
				_response:	p_callback( _params._parameter )
			};

			$.wesbmessenger.producer[ _nameResponse ].push( JSON.stringify( _return ) );
		}
	} );
	
	return this;
};

/**
 * WESBMessenger call
 */
var currentVid = 0;
$.wesbmessenger.prototype.call = function( p_name, p_params ) {
	var _name = $.wesbmessenger.EXTENSION_PARAMETER + p_name;
	var _nameResponse = $.wesbmessenger.EXTENSION_RETURN_VAL + p_name;
	this.produceQueuing( _name, "string" );
	this.consumQueuing( _nameResponse, "string" );
	
	var _params;
	var _uuid = UUID.generate();
	var _deferred = $.Deferred();
	
	_params = {
		_parameter: p_params,
		_uuid: _uuid
	};
	$.wesbmessenger.producer[ _name ].push( JSON.stringify( _params ) );
	
	this.update( function(p_event) {
		try{
			if ( typeof($.wesbmessenger.consumer[ _nameResponse ]) == "undefined" ) return;
			
			$.each( $.wesbmessenger.consumer[ _nameResponse ], function( p_key, p_value ) {
				var _response = JSON.parse( p_value );
				
				if ( _response._uuid == _uuid ) {
					$($.wesbmessenger).unbind( p_event );
					_deferred.resolveWith( _deferred, [_response._response] );
				}
			} );
		}catch(e){
			console.error(e);
		}
	} );
	
	return _deferred.promise();
};

/**
 * Update callback
 */
$.wesbmessenger.prototype.update = function( p_callback ){
	$($.wesbmessenger).bind( "wesbmessenger_update", p_callback );
};

/**
 * WESBMessenger update consumers
 */
$.wesbmessenger.prototype._update_consumers = function( p_data ){
	$.wesbmessenger.consumer = ( typeof(p_data.consumer) == "undefined" ? {} : p_data.consumer );
};

/**
 * WESBMessenger update producers
 */
$.wesbmessenger.prototype._update_producers = function( ){
	// CONVERT SAMPLING TO QUEUING
	var _producers = {};
	$.each( $.wesbmessenger.producer, function (p_key, p_value){
		if ( !$.isArray( p_value ) ) {
			_producers[ p_key ] = [p_value];
		} else {
			_producers[ p_key ] = p_value;
		}
	});
	
	$.wesbmessenger.singleton().ws.send(JSON.stringify({
		"function": "update",
		"data": { 
			producer: 	_producers
		}
	}) + "\n");
	$.each( $.wesbmessenger.producer, function( p_key, p_value ){
		if ( $.isArray( p_value ) ) {
			$.wesbmessenger.producer[ p_key ] = [];
		}
	} );
};

/**
 * call function
 */
$.wesbmessenger.prototype._callfunction = function( p_name, p_params, p_options ){
	var _this = this;
    var _options = p_options;
    var _return = { "return": 0 };
    var _error = null;
    var _data = $.extend({}, p_params, {
		"function": p_name
	});
	
	this.init().done( function(){
		_this.ws.send( JSON.stringify( _data ) + "\n" );
	} );
    return _return;
};
})(jQuery);
