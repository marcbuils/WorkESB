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
 *      Author: Marc Buils (MATIS - http://www.matis-group.com)
 */
;(function($){
var _id = 1;

$.fn.wesbmessengerTerminal = function(){
	return this.each(function(){
		var $_this = $(this);
		var _term;
		
		if ( $_this.attr('id') == undefined ){
			$_this.attr('id', 'wesbmessengerterminal_' + _id );
			_id = _id+1;
		}

		TermGlobals.keylock = true;
		_term = new Terminal({
			handler: function(){
				this.newLine();
				var line = this.lineBuffer;
				if (line != "") {
					try {
						this.write(window.eval(line));
					}catch(e){
						this.write(e);
					}
				}
				this.prompt();
			},
			ctrlHandler: function(){
				if (this.inputChar == termKey.SYN) {
					try {
						TermGlobals.insertText("test");
					}catch(e){
						this.write(e);
					}
				}
			},
			termDiv: $_this.attr('id'),
			rows: 18,
			ps: ">",
			greeting: [
				"*** WESBMessenger Shell ***",
				"Write \"help()\" for more informations"
			]
		});
		_term.crsrBlinkMode = true;
		_term.open();
		
		var _node = dijit.byNode($_this.parent().get(0));
		_node.connect(_node, "onShow", function(){
			TermGlobals.keylock = false;
		});
		_node.connect(_node, "onHide", function(){
			TermGlobals.keylock = true;
		});
		
		// fixed input text and textarea problem
		$('input:text,textarea')
			.live( 'focus', function(){
				TermGlobals.keylock = true;
			})
			.live( 'blur', function(){
				if ($_this.is(":visible")){
					TermGlobals.keylock = false;
				}
			});		
		
		$_this
			.append( $('<div><textarea></textarea><input type="button" value="insert" /></div>') )
			.find( 'div > input[type="button"]' )
			.bind( 'click', function(){
				TermGlobals.insertText( $(this).parent().children('textarea').val() );
				$(this).parent().children('textarea').val( '' );
			} );
			
			// WESBMessenger functions
			regConsumSampling = function( p_name, p_type ){ return $.wesbmessenger.singleton().regConsumSampling( p_name, p_type ); };
			regProduceSampling = function( p_name, p_type ){ return $.wesbmessenger.singleton().regProduceSampling( p_name, p_type ); };
			regConsumQueuing = function( p_name, p_type ){ return $.wesbmessenger.singleton().regConsumQueuing( p_name, p_type ); };
			regProduceQueuing = function( p_name, p_type ){ return $.wesbmessenger.singleton().regProduceQueuing( p_name, p_type ); };
			bind = function( p_name, p_callback ){ return $.wesbmessenger.singleton().bind( p_name, p_callback ); };
			trigger = function( p_name, p_params ){ return $.wesbmessenger.singleton().trigger( p_name, p_params ); };
			share = function( p_name, p_callback ){ return $.wesbmessenger.singleton().share( p_name, p_callback ); };
			call = function( p_name, p_params ){ return $.wesbmessenger.singleton().call( p_name, p_params ); };
			echo = function(p_value){_term.write(p_value); _term.newLine(); return '';};
			clear = function() { _term.clear(); return ''; };
			c = {};
			$(document).bind('wesbmessenger_update', function(){c = $.wesbmessenger.consumer;});
			p = $.wesbmessenger.producer;
			help = function(){
				_term.write([
					"Write a Javascript or a following WESBMessenger command:",
					"- regConsumSampling( name, type )",
					"- regProduceSampling( name, type )",
					"- regConsumQueuing( name, type )",
					"- regProduceQueuing( name, type )",
					"- bind( name, callback )",
					"- trigger( name, params )",
					"- share( name, callback )",
					"- call( name, params )[.done( callback )]",
					"- echo( text )",
					"- log( text )",
					"- clear( )",
					"- help( )",
					"- c [[consumers]]",
					"- p [[producers]]",
					"( with type=\"int\" or \"float\" or \"string\" )"
				]);
				return '';
			};
	});
};
})(jQuery);