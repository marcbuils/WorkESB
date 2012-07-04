/**
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
 *  Created on: 31 janv. 2012
 *      Author: Marc Buils (CSIE)
 */
;(function($){
/*
 The MIT License: Copyright (c) 2010 LiosK.
*/
function UUID(){}UUID.generate=function(){var a=UUID._getRandomInt,b=UUID._hexAligner;return b(a(32),8)+"-"+b(a(16),4)+"-"+b(16384|a(12),4)+"-"+b(32768|a(14),4)+"-"+b(a(48),12)};UUID._getRandomInt=function(a){if(a<0)return NaN;if(a<=30)return 0|Math.random()*(1<<a);if(a<=53)return(0|Math.random()*1073741824)+(0|Math.random()*(1<<a-30))*1073741824;return NaN};UUID._getIntAligner=function(a){return function(b,f){for(var c=b.toString(a),d=f-c.length,e="0";d>0;d>>>=1,e+=e)if(d&1)c=e+c;return c}};
UUID._hexAligner=UUID._getIntAligner(16);

/**
 * Constructeur
 */
$.csiemessenger = function() {
	this.initialized = false;
	this.m_id = this.init( "fr.csie.benches.test", "IHM" );
};

/*
 * Static vars
 */
$.csiemessenger.EXTENSION_PARAMETER = "PARAMETER__";
$.csiemessenger.EXTENSION_RETURN_VAL = "RETURNVAL__";
$.csiemessenger.EXTENSION_EVENT = "EVENT__";
$.csiemessenger.producer = {};
$.csiemessenger.consumer = {};
$.csiemessenger.consumercid = {};
$.csiemessenger.producercid = {};
$.csiemessenger.s_instance = null;
$.csiemessenger.types = {
	"int":		0,
	"float":	1,
	"string":	2
};

/**
 * Singleton
 */
$.csiemessenger.singleton = function(){
	if ( $.csiemessenger.s_instance == null ) {
		$.csiemessenger.s_instance = new $.csiemessenger();
	}
	return $.csiemessenger.s_instance;
};

/**
 * call function
 */
$.csiemessenger.prototype.callfunction = function( p_name, p_params, p_options ){
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
 * CSIEMessenger init
 */
$.csiemessenger.prototype.init = function( p_domain, p_name ) {
	var _timer;

    if ('MozWebSocket' in window) {
      	window.WebSocket = window.MozWebSocket;
    }
	
	_timer = function(){
		//console.log("update producers");
		$.csiemessenger.singleton().update_producers();
	};
	this.ws = new window.WebSocket( 'ws://' + document.URL.substr(7).split('/')[0], 'csiemessenger' );
	this.ws.onopen = function(){
		$.csiemessenger.singleton().initialized = true;
		$.csiemessenger.singleton().ws.send(JSON.stringify({
			"function": "init",
			"domain": p_domain,
			"name": p_name
		}) + "\n");

		setTimeout( _timer, 1000 );
	};
	this.ws.onmessage = function(p_data){
		//console.log("update consumers: %s", p_data.data);
		$.csiemessenger.singleton().update_consumers(JSON.parse(p_data.data));
		$(document).trigger("csiemessenger_update");
		
		setTimeout( _timer, 250 );
	};
	this.ws.onclose = function(){
		console.error("CSIEMessenger connexion closed");
	};
	
	return -1;
};

/**
 * CSIEMessenger regConsumSampling
 */
$.csiemessenger.prototype.regConsumSampling = function( p_name, p_type ) {
	if ( $.csiemessenger.consumercid[ p_name ] != undefined )
	{
		return $.csiemessenger.consumercid[ p_name ];
	}
	
	var _type = $.csiemessenger.types[p_type];
	var _cid;
	_cid = this.callfunction( "regConsumSampling", { name: p_name, type: _type })["return"];
	$.csiemessenger.consumercid[ p_name ] = _cid;
	
	return _cid;
};

/**
 * CSIEMessenger regProduceSampling
 */
$.csiemessenger.prototype.regProduceSampling = function( p_name, p_type ) {
	return this.regProduceQueuing( p_name, p_type );
	
/*	NO PRODUCE SAMPLING - TOO DANGEROUS
	if ( $.inArray( p_name, $.csiemessenger.producercid ) != -1 )
	{
		return $.csiemessenger.producercid[ p_name ];
	}
	
	var _type = $.csiemessenger.types[p_type];
	
	if ( p_type == "string" ) {
		$.csiemessenger.producer[ p_name ] = "";
	}
	else
	{
		$.csiemessenger.producer[ p_name ] = 0;
	}
	
	var _cid;
	_cid = this.callfunction( "regProduceSampling", { name: p_name, type: _type } )["return"];
	$.csiemessenger.producercid[ p_name ] = _cid;
//	$.csiemessenger.singleton().update_producers();
	
	return _cid;
*/
};

/**
 * CSIEMessenger regConsumQueuing
 */
$.csiemessenger.prototype.regConsumQueuing = function( p_name, p_type ) {
	if ( $.csiemessenger.consumercid[ p_name ] != undefined )
	{
		return $.csiemessenger.consumercid[ p_name ];
	}	
	
	var _type = $.csiemessenger.types[p_type];
	var _cid;
	_cid = this.callfunction( "regConsumQueuing", { name: p_name, type: _type } )["return"];
	$.csiemessenger.consumercid[ p_name ] = _cid;
	
	return _cid;
};

/**
 * CSIEMessenger regProduceSampling
 */
$.csiemessenger.prototype.regProduceQueuing = function( p_name, p_type ) {
	if ( $.csiemessenger.producercid[ p_name ] != undefined )
	{
		return $.csiemessenger.producercid[ p_name ];
	}
	
	var _type = $.csiemessenger.types[p_type];
	$.csiemessenger.producer[ p_name ] = [];

	var _cid = this.callfunction( "regProduceQueuing", { name: p_name, type: _type } )["return"];
	$.csiemessenger.producercid[ p_name ] = _cid;
//	$.csiemessenger.singleton().update_producers();
	
	return _cid;
};

/**
 * CSIEMessenger bind
 */
$.csiemessenger.prototype.bind = function( p_name, p_callback ) {
	var _name = $.csiemessenger.EXTENSION_EVENT + p_name;
	this.regConsumQueuing( _name, "string" );
	
	$(document).bind( "csiemessenger_update", function( ){
		var _params;
		var _i;
		
		if ( $.csiemessenger.consumer[ _name ] == undefined ) return;
		for ( _i=0; _i < $.csiemessenger.consumer[ _name ].length; _i++ ){
			_params = JSON.parse( $.csiemessenger.consumer[ _name ][ _i ] );
			p_callback( _params._parameter );
		}
	} );
};

/**
 * CSIEMessenger trigger
 */
$.csiemessenger.prototype.trigger = function( p_name, p_params ) {
	var _name = $.csiemessenger.EXTENSION_EVENT + p_name;
	this.regProduceQueuing( _name, "string" );

	$.csiemessenger.producer[ _name ].push(JSON.stringify( { _parameter: p_params } ));
};

/**
 * CSIEMessenger share
 */
$.csiemessenger.prototype.share = function( p_name, p_callback ) {
	var _name = $.csiemessenger.EXTENSION_PARAMETER + p_name;
	var _nameResponse = $.csiemessenger.EXTENSION_RETURN_VAL + p_name;
	this.regProduceQueuing( _nameResponse, "string" );
	this.regConsumQueuing( _name, "string" );
	
	$(document).bind( "csiemessenger_update", function( ){
		var _params;
		var _i;
		
		if ( $.csiemessenger.consumer[ _name ] == undefined ) return;
		for ( _i=0; _i < $.csiemessenger.consumer[ _name ].length; _i++ ){
			var _return;
			var _pos;

			_params = JSON.parse( $.csiemessenger.consumer[ _name ][ _i ] );
			_return = {
				_uuid: 		_params._uuid,
				_response:	p_callback( _params._parameter )
			};

			$.csiemessenger.producer[ _nameResponse ].push( JSON.stringify( _return ) );
		}
	} );
};

/**
 * CSIEMessenger call
 */
var currentVid = 0;
$.csiemessenger.prototype.call = function( p_name, p_params ) {
	var _name = $.csiemessenger.EXTENSION_PARAMETER + p_name;
	var _nameResponse = $.csiemessenger.EXTENSION_RETURN_VAL + p_name;
	this.regProduceQueuing( _name, "string" );
	this.regConsumQueuing( _nameResponse, "string" );
	
	var _params;
	var _uuid = UUID.generate();
	var _deferred = $.Deferred();
	
	_params = {
		_parameter: p_params,
		_uuid: _uuid
	};
	$.csiemessenger.producer[ _name ].push( JSON.stringify( _params ) );
	
	$(document).bind( "csiemessenger_update", function(p_event) {
		try{
			if ( $.csiemessenger.consumer[ _nameResponse ] == undefined ) return;
			
			$.each( $.csiemessenger.consumer[ _nameResponse ], function( p_key, p_value ) {
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
 * CSIEMessenger update consumers
 */
$.csiemessenger.prototype.update_consumers = function( p_data ){
	$.csiemessenger.consumer = p_data.consumer;
};

/**
 * CSIEMessenger update producers
 */
$.csiemessenger.prototype.update_producers = function( ){
	// CONVERT SAMPLING TO QUEUING
	$.each( $.csiemessenger.producer, function (p_key, p_value){
		if ( !$.isArray( p_value ) ) {
			$.csiemessenger.producer[ p_key ] = [p_value];
		}
	});
	
	$.csiemessenger.singleton().ws.send(JSON.stringify({
		"function": "update",
		"data": { 
			producer: 	$.csiemessenger.producer
		}
	}) + "\n");
	$.each( $.csiemessenger.producer, function( p_key, p_value ){
		if ( $.isArray( p_value ) ) {
			$.csiemessenger.producer[ p_key ] = [];
		}
	} );
};

$.csiemessenger.singleton();
})(jQuery);
