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
	$.fn.getCssPath = function(){
		var $_this = this;
		var _path = "";
		var _continue = true;
		
		while( _continue && $_this.get(0).tagName.toLowerCase() != 'html' ){
			var _selector = "";
			
			if ($_this.attr('id') != undefined) {
				_selector = '#' + $_this.attr('id');
				_continue = false;
			} else {
				_selector = $_this.get(0).tagName.toLowerCase() + ':nth-child(' + ($_this.index()+1) + ')';
			}
			
			_path = _selector + ( _path == "" ? "" : " > " + _path );
			$_this = $_this.parent();
		}
		
		return _path;
	};
})(jQuery);