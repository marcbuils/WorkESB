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
$.fn.wesbmessengerConsum = function(){
	return this.each(function(){
		var $_this = $(this);
		var _name = $_this.attr('data-variable-name');
		var _type = $_this.attr('data-variable-type');
		
		$(document).one( "wesbmessenger_update", function(){
			$.wesbmessenger.singleton().regConsumSampling( _name, _type );
			$(document).bind( "wesbmessenger_update", function(){
				var _val = ( _type == 'float' ? $.wesbmessenger.consumer[_name].toFixed(2) : $.wesbmessenger.consumer[_name] );
				
				if ($_this.is('input')) {
					$_this.val( _val );
				} else {
					$_this.text( _val );
				}
			});
		});
		
		$_this.parent().trigger('reload');
	});
};
})(jQuery);