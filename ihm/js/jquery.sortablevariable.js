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
	var _getIdByName = function(p_name){
		var _return = "";
		
		$.each(p_name, function(_i,_v){
			if ( _v == ' ' ){
				_return += '_';
			} else if ( (_v >= 'a' && _v <= 'z')
						|| (_v >= 'A' && _v <= 'Z')
						|| (_v >= '0' && _v <= '9' ) ){
				_return += _v;
			}
		});
		
		return _return;
	};
	var _infos = null;
	
	// local storage init
	if ( localStorage.getItem( 'jquery.sortablevariable' ) != null ){
		_infos = JSON.parse( localStorage.getItem( 'jquery.sortablevariable' ) );
	}
	
	// version verification
	if ( localStorage.getItem( 'jquery.sortablevariable' ) == null || _infos.version != $('body').attr('data-version') ){
		_infos = {
			version: 	$('body').attr('data-version'),
			list:		{}
		};
		
		localStorage.setItem( 'jquery.sortablevariable', JSON.stringify( _infos ) );
	}
	
	$.fn.sortableVariable = function(){
		return this.each(function(){
			var $_this = $(this);

			$_this
				.sortable({
					connectWith: "ul.data",
					start: function(){
						$_this.parent().addClass('sortable');
					},
					stop: function(event, ui){
						$_this.parent().removeClass('sortable');

						ui.item.parent().children('li').each(function(){
							_infos.list[ $(this).attr('data-sortablevariable-id') ] = {
								path: 	$(this).parent().getCssPath(),
								pos:	$(this).index()
							};
						});
						$_this.children('li').each(function(){
							_infos.list[ $(this).attr('data-sortablevariable-id') ] = {
								path: 	$(this).parent().getCssPath(),
								pos:	$(this).index()
							};
						});
						localStorage.setItem( 'jquery.sortablevariable', JSON.stringify( _infos ) );
					}
				})
				.bind('reload', function(){
					var _toReload = [];
					_infos = JSON.parse( localStorage.getItem( 'jquery.sortablevariable') );
				
					$_this
						.children('li')
						.each(function(){
							var _itemId = $(this).attr( 'data-sortablevariable-id');
							
							if (_itemId == undefined) {
								_itemId = ( $(this).attr('id') != undefined ? $(this).attr('id') : _getIdByName($(this).attr('data-module')+'_'+$(this).attr('data-name')) );
								$(this).attr( 'data-sortablevariable-id', _itemId );
							}
						})
						.each(function(){
							if ( _infos.list[ $(this).attr('data-sortablevariable-id') ] == undefined ){
								_infos.list[ $(this).attr('data-sortablevariable-id') ] = {
									path: 	$(this).parent().getCssPath(),
									pos:	$(this).index()
								};
								localStorage.setItem( 'jquery.sortablevariable', JSON.stringify( _infos ) );
							}
						})
						.each(function(){
							var _itemId = $(this).attr( 'data-sortablevariable-id');
							$( _infos.list[ _itemId ].path ).append( $(this) ); 
							if ($(this).parent().getCssPath() != _infos.list[ _itemId ].path){
								_toReload[_infos.list[ _itemId ].path] = true;
							}
						})
						.end();
						
					var _list = [];
					$_this.children('li').each(function(){
						_list.push({
							pos: 	_infos.list[ $(this).attr('data-sortablevariable-id') ].pos,
							id: 	$(this).attr('data-sortablevariable-id')
						});
					});
					_list.sort(function(a,b){return a.pos - b.pos});
					$.each( _list, function( _i, _item ){
						$_this.append( $_this.find('li[data-sortablevariable-id="'+_item.id+'"]') ); 
					});
					
					$_this.children('li').each(function(){
						_infos.list[ $(this).attr('data-sortablevariable-id') ] = {
							path: 	$(this).parent().getCssPath(),
							pos:	$(this).index()
						};
					});
					localStorage.setItem( 'jquery.sortablevariable', JSON.stringify( _infos ) );

					$.each(_toReload, function(_i, _v){
						$(_v).trigger('reload');
					});
				});
						
			$_this.trigger('reload');
		});
	}
})(jQuery);