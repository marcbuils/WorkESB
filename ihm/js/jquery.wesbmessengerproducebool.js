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
$.fn.wesbmessengerProduceBool = function(){
	return this.each(function(){
		var $_this = $(this);
		var _name = $_this.attr('data-variable-name');
		var _type = $_this.attr('data-variable-type');
		
		// setting
		$.wesbmessenger.singleton().regProduceQueuing( _name, _type );
		$_this.bind('click', function(){
			if ( dijit.byNode( $_this.parent().parent().get(0) ).get('disabled') ){
				return false;
			}
		
			$.wesbmessenger.producer[_name][0] = ( dijit.byNode( $_this.parent().parent().get(0) ).get('checked') ? 0 : 1);
			dijit.byNode( $_this.parent().parent().get(0) ).set('disabled', true);
		});

		// getting
		$.wesbmessenger.singleton().regConsumSampling( _name, _type );
		$(document).bind( "wesbmessenger_update", function(){
			try{
				var _val = $.wesbmessenger.consumer[_name];

				dijit.byNode( $_this.parent().parent().get(0) ).set('disabled', false);
				if ( _val == 0) {
					dijit.byNode( $_this.parent().parent().get(0) ).set('checked', false);
					dijit.byNode( $_this.parent().parent().get(0) ).set('label', 'OFF');
				} else {
					dijit.byNode( $_this.parent().parent().get(0) ).set('checked', true);
					dijit.byNode( $_this.parent().parent().get(0) ).set('label', 'ON');
				}
			}catch(e){
				console.error("%s - %s", e, new Error().stack);
			}
		});
	});
};
})(jQuery);