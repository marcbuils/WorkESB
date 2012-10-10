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
$.fn.wesbmessengerCall = function(){
	return this.each(function(){
		var $_this = $(this);
		var _name = $_this.attr('data-variable-name');
		
		$_this.bind( "click", function(){
			var _parameters = prompt('Call parameters for the function "' + _name + '"', '""' );
			if ( _parameters != null ) {
				try {
					var _result = JSON.parse( _parameters );
					$_this.parent().find('input[type="text"]').parent().parent().addClass('data_line_disabled');
					$.wesbmessenger.singleton().call( _name, _result ).done( function(p_params){
						$_this.parent().find('input[type="text"]').val( JSON.stringify(p_params) ).parent().parent().removeClass('data_line_disabled');
					});
				} catch( p_error ) {
					alert( p_error );
				}
			}
		});
	});
};
})(jQuery);