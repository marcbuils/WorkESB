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
	var _getIdByName = function(p_name){
		var _return = "";
		
		$.each(p_name, function(_i,_v){
			if ( _v == ' ' ){
				_return += '_';
			} else if ( (_v >= 'a' && _v <= 'z')
						|| (_v >= 'A' && _v <= 'Z')
						|| (_v >= '0' && _v <= '9' ) ){
				_return += _v;
			}
		});
		
		return _return;
	};
	
	$.fn.variableList = function(){
		return this.each(function(){
			var $_this = $(this);
			var _list = $($_this.attr('data-tmpl-list'));
			var _removed = $_this.attr('data-sequencer-removed');
			var _consumText = $($_this.attr('data-tmpl-consum-text'));
			var _produceText = $($_this.attr('data-tmpl-produce-text'));
			var _consumQueuingText = $($_this.attr('data-tmpl-consum-queuing-text'));
			var _produceQueuingText = $($_this.attr('data-tmpl-produce-queuing-text'));
			var _call = $($_this.attr('data-tmpl-call'));
			var _bind = $($_this.attr('data-tmpl-bind'));
			var _trigger = $($_this.attr('data-tmpl-trigger'));
			var _eventlist = {};
			
			$.wesbmessenger.singleton().bind('wesbmessenger_pong', function(p_module){
				if ( p_module.name == "IHM" || p_module.name == "SEQUENCEUR D'AUTOMATE"
					|| p_module.variable.name == "wesbmessenger_pong" ){
					return;
				}
					
				// add id
				p_module.id = _getIdByName( p_module.name );
				p_module.variable.id = _getIdByName( p_module.variable.name );					
					
				var _block = $_this.find('ul[data-jquery-type="sortableVariable"][data-name="' + p_module.name + '"]');
				if ( _block.size() <= 0
					&& ( p_module.variable.com == "consumer" || p_module.variable.com == "producer"
						|| p_module.variable.com == "share" || p_module.variable.com == "bind") ){
					_block = _list
								.tmpl({
									name: 	p_module.name,
									id:		p_module.id
								})
								.appendTo( $_this );
				}
						
				if ( $('ul[data-jquery-type="sortableVariable"] li[data-module="'+p_module.name+'"][data-name="'+p_module.variable.name+'"]').size() <= 0 ){
					if ( p_module.variable.com == "producer" && !p_module.variable.queuing ) {
						_consumText
							.tmpl(p_module)
							.appendTo( _block );
					} else if ( p_module.variable.com == "consumer" && !p_module.variable.queuing ) {
						_produceText
							.tmpl(p_module)
							.appendTo( _block );
					} else if ( p_module.variable.com == "producer" && p_module.variable.queuing ) {
						_consumQueuingText
							.tmpl(p_module)
							.appendTo( _block );
					} else if ( p_module.variable.com == "consumer" && p_module.variable.queuing ) {
						_produceQueuingText
							.tmpl(p_module)
							.appendTo( _block );
					} else if ( p_module.variable.com == "share" ) {
						_call
							.tmpl(p_module)
							.appendTo( _block );
					} else if ( p_module.variable.com == "bind" ) {
						_trigger
							.tmpl(p_module)
							.appendTo( _block );
					}
				}
				
				if ( p_module.variable.com == "trigger" ) {
					if ( typeof( _eventlist[p_module.variable.name] ) == 'undefined' ){
						_eventlist[p_module.variable.name] = true;
							
						$.wesbmessenger.singleton().bind( p_module.variable.name, function(p){
							log( 'trigger "'+p_module.variable.name+'": '+JSON.stringify(p) );
						});
					}
				}
				
				_block
					.parent()
					.pluginautoload();
			});
			
			$.wesbmessenger.singleton().bind(_removed, function(p_module){
				$('ul[data-jquery-type="sortableVariable"] li[data-module="'+p_module.name+'"]').remove();
				$_this.find('ul[data-jquery-type="sortableVariable"][data-name="' + p_module.name + '"]').remove();
			});
			$.wesbmessenger.singleton().trigger('wesbmessenger_ping');
		});
	};
})(jQuery);