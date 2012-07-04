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
(function($){
$.fn.logsTable = function(){
	return this.each(function(){
		var $_this = $(this);
		var _name = $_this.attr('data-variable-name');
		var _type = $_this.attr('data-variable-type');
		var $_tmpl = $($_this.attr('data-tmpl'));
		var _logs = [];
		
		$(document).one( "csiemessenger_update", function(){
			$.csiemessenger.singleton().regConsumQueuing( _name, _type );
			$_this.bind('refresh', function(){
				$_tmpl.tmpl( {logs: _logs} ).appendTo($_this.empty())
				$_this.pluginautoload();
				return false;
			}).trigger('refresh');
			$(document).bind( "csiemessenger_update", function(){
				var _vals = $.csiemessenger.consumer[_name];
				
				if (_vals.length > 0) {
					_logs = $.merge( _logs, _vals );
					$_this.trigger('refresh');
				}
			});
		});
		log = function( p_value ){
			_logs = $.merge( _logs, [p_value] );
			$_this.trigger('refresh');
			return '';
		};
	});
};
})(jQuery);