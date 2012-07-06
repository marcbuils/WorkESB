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
	$.fn.modulesList = function(){
		return this.each(function(){
			var $_this = $(this);
			var $_tmpl = $($_this.attr('data-tmpl'));
			var _pingEvent = $_this.attr('data-ping-event');
			var _pongEvent = $_this.attr('data-pong-event');
			var _stoppedEvent = $_this.attr('data-stopped-event');
			
			$_this.empty();
			$(document).one( "wesbmessenger_update", function( ){
				$.wesbmessenger.singleton().bind(_pongEvent, function(p_infos){
					if ( $_this.find('[data-sequencer-name="'+p_infos.name+'"]').size() == 0 ){
						var _loading = $('<div style="text-align: center;"></div>').loading().appendTo($_this);
						$.wesbmessenger.singleton()
							.call(p_infos.list)
							.done(function(p_modules){
								if ( $_this.find('[data-sequencer-name="'+p_infos.name+'"]').size() == 0 ){
									$_tmpl
										.tmpl({
											infos:	p_infos,
											list:	p_modules
										})
										.hide()
										.appendTo($_this)
										.fadeIn()
										.pluginautoload();
								}
								_loading.remove();
							});
					}
				});
				$.wesbmessenger.singleton().trigger(_pingEvent);
				
				// stop sequencer detection
				$.wesbmessenger.singleton().bind(_stoppedEvent, function(p_name){
					$_this
						.find('[data-sequencer-name="'+p_name+'"]')
						.fadeOut(400, function(){
							$_this
								.find('[data-sequencer-name="'+p_name+'"]')
								.remove();
						});
				});
			});
		});
	};
})(jQuery);
