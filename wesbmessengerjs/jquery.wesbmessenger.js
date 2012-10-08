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
// node.js verification
if ( typeof(document) == "undefined" ){
	document = { 
		URL: "http://localhost:8080/"
	}
}

/*
 The MIT License: Copyright (c) 2010 LiosK.
*/
function UUID(){}UUID.generate=function(){var a=UUID._getRandomInt,b=UUID._hexAligner;return b(a(32),8)+"-"+b(a(16),4)+"-"+b(16384|a(12),4)+"-"+b(32768|a(14),4)+"-"+b(a(48),12)};UUID._getRandomInt=function(a){if(a<0)return NaN;if(a<=30)return 0|Math.random()*(1<<a);if(a<=53)return(0|Math.random()*1073741824)+(0|Math.random()*(1<<a-30))*1073741824;return NaN};UUID._getIntAligner=function(a){return function(b,f){for(var c=b.toString(a),d=f-c.length,e="0";d>0;d>>>=1,e+=e)if(d&1)c=e+c;return c}};
UUID._hexAligner=UUID._getIntAligner(16);

/**
 * Constructeur
 */
$.wesbmessenger = function() {
	this.initialized = false;
	this.m_id = this.init( "com.workesb.test", typeof(window) == "undefined" ? "NodeJS" : "IHM" );
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
 * call function
 */
$.wesbmessenger.prototype.callfunction = function( p_name, p_params, p_options ){
	if (!this.initialized) return -1;

    var _options = p_options;
    var _return = { "return": 0 };
    var _error = null;
    var _data = $.extend({}, p_params, {
		"function": p_name
	});
	
	this.ws.send(JSON.stringify( _data ) + "\n");

    return _return;
};

/**
 * WESBMessenger init
 */
$.wesbmessenger.prototype.init = function( p_domain, p_name ) {
	var _timer;

    if (typeof(window) != "undefined" && 'MozWebSocket' in window) {
      	window.WebSocket = window.MozWebSocket;
    }
	
	_timer = function(){
		//console.log("update producers");
		$.wesbmessenger.singleton().update_producers();
	};
	
	var _onopen, _onmessage, _onclose;
	_onopen = function(){
		$.wesbmessenger.singleton().initialized = true;
		$.wesbmessenger.singleton().ws.send(JSON.stringify({
			"function": "init",
			"domain": p_domain,
			"name": p_name
		}) + "\n");

		setTimeout( _timer, 1000 );
	};
	_onmessage = function(p_data){
		// console.log("update consumers: %o", p_data);
		$.wesbmessenger.singleton().update_consumers( JSON.parse( typeof(p_data.data) == "undefined" ? p_data.utf8Data : p_data.data) );
		$(document).trigger("wesbmessenger_update");
		
		setTimeout( _timer, 50 );
	};
	_onclose = function(){
		console.error("WESBMessenger connexion closed");
	};

	if ( typeof(window) != "undefined" ){
		this.ws = new window.WebSocket( 'ws://' + document.URL.substr(7).split('/')[0], 'wesbmessenger' );
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
		this._ws.connect('ws://' + document.URL.substr(7).split('/')[0], 'wesbmessenger' );
	}
	
	return -1;
};

/**
 * WESBMessenger regConsumSampling
 */
$.wesbmessenger.prototype.regConsumSampling = function( p_name, p_type ) {
	if ( $.wesbmessenger.consumercid[ p_name ] != undefined )
	{
		return $.wesbmessenger.consumercid[ p_name ];
	}
	
	var _type = $.wesbmessenger.types[p_type];
	var _cid;
	_cid = this.callfunction( "regConsumSampling", { name: p_name, type: _type })["return"];
	$.wesbmessenger.consumercid[ p_name ] = _cid;
	
	return _cid;
};

/**
 * WESBMessenger regProduceSampling
 */
$.wesbmessenger.prototype.regProduceSampling = function( p_name, p_type ) {
	return this.regProduceQueuing( p_name, p_type );
	
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
	_cid = this.callfunction( "regProduceSampling", { name: p_name, type: _type } )["return"];
	$.wesbmessenger.producercid[ p_name ] = _cid;
//	$.wesbmessenger.singleton().update_producers();
	
	return _cid;
*/
};

/**
 * WESBMessenger regConsumQueuing
 */
$.wesbmessenger.prototype.regConsumQueuing = function( p_name, p_type ) {
	if ( $.wesbmessenger.consumercid[ p_name ] != undefined )
	{
		return $.wesbmessenger.consumercid[ p_name ];
	}	
	
	var _type = $.wesbmessenger.types[p_type];
	var _cid;
	_cid = this.callfunction( "regConsumQueuing", { name: p_name, type: _type } )["return"];
	$.wesbmessenger.consumercid[ p_name ] = _cid;
	
	return _cid;
};

/**
 * WESBMessenger regProduceSampling
 */
$.wesbmessenger.prototype.regProduceQueuing = function( p_name, p_type ) {
	if ( $.wesbmessenger.producercid[ p_name ] != undefined )
	{
		return $.wesbmessenger.producercid[ p_name ];
	}
	
	var _type = $.wesbmessenger.types[p_type];
	$.wesbmessenger.producer[ p_name ] = [];

	var _cid = this.callfunction( "regProduceQueuing", { name: p_name, type: _type } )["return"];
	$.wesbmessenger.producercid[ p_name ] = _cid;
//	$.wesbmessenger.singleton().update_producers();
	
	return _cid;
};

/**
 * WESBMessenger bind
 */
$.wesbmessenger.prototype.bind = function( p_name, p_callback ) {
	var _name = $.wesbmessenger.EXTENSION_EVENT + p_name;
	this.regConsumQueuing( _name, "string" );
	
	$(document).bind( "wesbmessenger_update", function( ){
		var _params;
		var _i;
		
		if ( $.wesbmessenger.consumer[ _name ] == undefined ) return;
		for ( _i=0; _i < $.wesbmessenger.consumer[ _name ].length; _i++ ){
			_params = JSON.parse( $.wesbmessenger.consumer[ _name ][ _i ] );
			p_callback( _params._parameter );
		}
	} );
};

/**
 * WESBMessenger trigger
 */
$.wesbmessenger.prototype.trigger = function( p_name, p_params ) {
	var _name = $.wesbmessenger.EXTENSION_EVENT + p_name;
	this.regProduceQueuing( _name, "string" );

	$.wesbmessenger.producer[ _name ].push(JSON.stringify( { _parameter: p_params } ));
};

/**
 * WESBMessenger share
 */
$.wesbmessenger.prototype.share = function( p_name, p_callback ) {
	var _name = $.wesbmessenger.EXTENSION_PARAMETER + p_name;
	var _nameResponse = $.wesbmessenger.EXTENSION_RETURN_VAL + p_name;
	this.regProduceQueuing( _nameResponse, "string" );
	this.regConsumQueuing( _name, "string" );
	
	$(document).bind( "wesbmessenger_update", function( ){
		var _params;
		var _i;
		
		if ( $.wesbmessenger.consumer[ _name ] == undefined ) return;
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
};

/**
 * WESBMessenger call
 */
var currentVid = 0;
$.wesbmessenger.prototype.call = function( p_name, p_params ) {
	var _name = $.wesbmessenger.EXTENSION_PARAMETER + p_name;
	var _nameResponse = $.wesbmessenger.EXTENSION_RETURN_VAL + p_name;
	this.regProduceQueuing( _name, "string" );
	this.regConsumQueuing( _nameResponse, "string" );
	
	var _params;
	var _uuid = UUID.generate();
	var _deferred = $.Deferred();
	
	_params = {
		_parameter: p_params,
		_uuid: _uuid
	};
	$.wesbmessenger.producer[ _name ].push( JSON.stringify( _params ) );
	
	$(document).bind( "wesbmessenger_update", function(p_event) {
		try{
			if ( $.wesbmessenger.consumer[ _nameResponse ] == undefined ) return;
			
			$.each( $.wesbmessenger.consumer[ _nameResponse ], function( p_key, p_value ) {
				var _response = JSON.parse( p_value );
				
				if ( _response._uuid == _uuid ) {
					$(document).unbind( p_event );
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
 * WESBMessenger update consumers
 */
$.wesbmessenger.prototype.update_consumers = function( p_data ){
	$.wesbmessenger.consumer = p_data.consumer;
};

/**
 * WESBMessenger update producers
 */
$.wesbmessenger.prototype.update_producers = function( ){
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

$.wesbmessenger.singleton();
})(jQuery);
