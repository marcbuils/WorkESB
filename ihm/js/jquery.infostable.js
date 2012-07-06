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
	$.fn.infosTable = function(){
		return this.each(function(){
			var $_this = $(this);
			var _start = null;

			$(document).one( "wesbmessenger_update", function(){
				$.wesbmessenger.singleton().regConsumSampling( "AUTOMATE_STATUS", "string" );
				$.wesbmessenger.singleton().regConsumSampling( "AUTOMATE_TIME", "int" );

				$(document).bind( "wesbmessenger_update", function(){
					var _status = $.wesbmessenger.consumer.AUTOMATE_STATUS;
					
					// status
					$_this
						.find('td:contains("Status")')
						.next()
						.text( _status );
						
					// time
					var _time = $.wesbmessenger.consumer.AUTOMATE_TIME;
					var _hours = parseInt( _time / 3600 );
					var _mins = parseInt( (_time / 60) )  % 3600;
					var _secs = _time % 60;
						
					$_this
						.find('td:contains("Temps")')
						.next()
						.text( (_hours<10?'0':'')+_hours+':'+(_mins<10?'0':'')+_mins+':'+(_secs<10?'0':'')+_secs );
				});
			});
		});
	};
})(jQuery);


