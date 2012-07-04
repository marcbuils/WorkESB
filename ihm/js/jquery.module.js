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
	$.fn.module = function(){
		return this.each(function(){
			var $_this = $(this);
			var _add = $_this.attr('data-sequencer-add');
			var _remove = $_this.attr('data-sequencer-remove');
			var _added = $_this.attr('data-sequencer-added');
			var _removed = $_this.attr('data-sequencer-removed');
			var _file = $_this.attr('data-file');
			var _sequencer = $_this.attr('data-sequencer');
			
			$_this.bind('click', function(){
				$_this.attr('disabled', 'disabled');
				if ($_this.is(':checked')){
					$_this.removeAttr('checked');
					$.csiemessenger.singleton().call(_add, {
						file: _file,
						default: true
					}).done(function(p_data){
						if (p_data.status == 0){
							jAlert(p_data.error);
							$_this.removeAttr('disabled');
						}
					});
				}else{
					$_this.attr('checked', 'checked');
					$.csiemessenger.singleton()
						.call(_remove, _file)
						.done(function(p_data){
							if (p_data.status == 0){
								jAlert(p_data.error);
								$_this.removeAttr('disabled');
							}
						});
				}
			});
			
			$.csiemessenger.singleton().bind(_added, function(p_infos){
				if (p_infos.sequencer == _sequencer && p_infos.file == _file){
					$_this.attr('checked', 'checked');
					$_this.removeAttr('disabled');
				}
			});
			$.csiemessenger.singleton().bind(_removed, function(p_infos){
				if (p_infos.sequencer == _sequencer && p_infos.file == _file){
					$_this.removeAttr('checked');
					$_this.removeAttr('disabled');
				}
			});
		});
	};
})(jQuery);