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
$.fn.wesbmessengerProduce = function(){
	return this.each(function(){
		var $_this = $(this);
		var _name = $_this.attr('data-variable-name');
		var _type = $_this.attr('data-variable-type');
		
		// setting
		$.wesbmessenger.singleton().produceQueuing( _name, _type );
		$_this.bind('change', function(){
			var _val = $_this.val();
			
			$.wesbmessenger.producer[_name][0] = ( _type=='float' ? parseFloat(_val) : ( _type=='int' ? parseInt(_val) : _val ) );
			$_this.attr('disabled', true);			
		});
			
		// getting
		$.wesbmessenger.singleton()
			.consumSampling( _name, _type )
			.update( function(){
				var _val = $.wesbmessenger.consumer[_name];
				if ( $.isArray( _val ) ) _val = _val[ _val.length-1 ];
				_val = ( _type == 'float' ? _val.toFixed(2) : _val );
			
				if ( $_this.is(':focus') ){
					return;
				}
				
				$_this.attr('disabled', false);
				if ($_this.is('input')) {
					$_this.val( _val );
				} else {
					$_this.text( _val );
				}
			});		
	});
};
})(jQuery);