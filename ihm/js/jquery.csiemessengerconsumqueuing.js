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
$.fn.csiemessengerConsumQueuing = function(){
	return this.each(function(){
		var $_this = $(this);
		var _name = $_this.attr('data-variable-name');
		var _type = $_this.attr('data-variable-type');
		
		$.csiemessenger.singleton().regConsumQueuing( _name, _type );
		$(document).bind( "csiemessenger_update", function(){
			if ( $.csiemessenger.consumer[_name].length > 0 ){
				var _val = ( _type == 'float' ? $.csiemessenger.consumer[_name][$.csiemessenger.consumer[_name].length-1].toFixed(2) : $.csiemessenger.consumer[_name][$.csiemessenger.consumer[_name].length-1] );
				
				if ($_this.is('input')) {
					$_this.val( _val );
				} else {
					$_this.text( _val );
				}
			}
		});
	});
};
})(jQuery);