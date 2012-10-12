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
(function($){
$.fn.logsTable = function(){
	return this.each(function(){
		var $_this = $(this);
		var _name = $_this.attr('data-variable-name');
		var _type = $_this.attr('data-variable-type');
		var $_tmpl = $($_this.attr('data-tmpl'));
		var _logs = [];
		
		$.wesbmessenger.singleton().regConsumQueuing( _name, _type );
		$_this.bind('refresh', function(){
			$_tmpl.tmpl( {logs: _logs} ).appendTo($_this.empty())
			$_this.pluginautoload();
			return false;
		}).trigger('refresh');
		$.wesbmessenger.singleton().update( function(){
			var _vals = $.wesbmessenger.consumer[_name];
				
			if (_vals.length > 0) {
				_logs = $.merge( _logs, _vals );
				$_this.trigger('refresh');
			}
		});
		
		log = function( p_value ){
			_logs = $.merge( _logs, [p_value] );
			$_this.trigger('refresh');
			return '';
		};
	});
};
})(jQuery);