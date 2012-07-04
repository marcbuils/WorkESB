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
	var _notificationTitle = "Gestion des profils";
	var _profils = null;
	
	// local storage init
	if ( localStorage.getItem( 'jquery.configurationtable' ) != null ){
		_profils = JSON.parse( localStorage.getItem( 'jquery.configurationtable' ) );
	}
	
	// version verification
	if ( localStorage.getItem( 'jquery.configurationtable' ) == null || _profils.version != $('body').attr('data-version') ){
		_profils = {
			version: 	$('body').attr('data-version'),
			list:		{}
		};
		
		localStorage.setItem( 'jquery.configurationtable', JSON.stringify( _profils ) );
	}
	

	$.fn.configurationTable = function(){
		return this.each(function(){
			var $_this = $(this);
			var $_dlgConfiguration = $($_this.attr('data-dialog-configuration'));
			var $_dlgLoad = $($_this.attr('data-dialog-load'));
			var $_dlgChange = $($_this.attr('data-dialog-change'));
			var $_dlgModules = $($_this.attr('data-dialog-modules'));
			
			$_this
				.find( 'input[data-type="modules_configuration"]' )
				.live('click', function(){
					$_dlgModules
						.tmpl()
						.dialog({
							modal: true,
							title: "Configuration des modules",
							width: 550,
							height:500,
							close: function(event, ui) { 
								$(this)
									.dialog("destroy")
									.remove(); 
							}
						})
						.pluginautoload();
				})
				.end()
				.find( 'input[data-type="profils_configuration"]' )
				.live('click', function(){
					$_dlgConfiguration
						.tmpl()
						.dialog({
							modal: true,
							title: "Configuration des profils",
							buttons: { 
								"Charger un profil existant": function() { 
									var $_dlg = $(this);
console.log(_profils);
									$_dlgLoad
										.tmpl( _profils )
										.dialog({
											modal: true,
											title: "Chargement d'un profil",
											buttons: { 
												"Charger": function() { 
													if ( $(this).find('li.ui-selected').size() <= 0 ){
														jAlert( "Selectionnez le profil a charger" );
													}else if ( $(this).find('li.ui-selected').size() > 1 ){
														jAlert( "Selectionnez un seul profil" );
													}else{
														var _name = $(this).find('li.ui-selected').text();
														
														localStorage.setItem( 'jquery.sortablevariable', _profils.list[ _name ].profil );
														$('[data-jquery-type="sortableVariable"]').trigger('reload');

														$.gritter.add({
															image:	"img/info.png",
															title: 	_notificationTitle,
															text:	"Profil '" + _name + "' charge"
														});
														$(this).dialog("close"); 
														$_dlg.dialog("close");
													}
												},
												"Fermer": function(){
													$(this).dialog("close");
												}
											},
											close: function(event, ui) { 
												$(this)
													.dialog("destroy")
													.remove(); 
											}
										})
										.pluginautoload();
								},
								"Modifier un profil existant": function(){
									var $_dlg = $(this);

									$_dlgChange
										.tmpl( _profils )
										.dialog({
											modal: true,
											title: "Modification d'un profil",
											buttons: { 
												"Modifier": function() { 
													if ( $(this).find('li.ui-selected').size() <= 0 ){
														jAlert( "Selectionnez le profil a modifier" );
													}else if ( $(this).find('li.ui-selected').size() > 1 ){
														jAlert( "Selectionnez un seul profil" );
													}else{
														var _name = $(this).find('li.ui-selected').text();

														_profils.list[_name].profil = localStorage.getItem( 'jquery.sortablevariable' );
														localStorage.setItem( 'jquery.configurationtable', JSON.stringify( _profils ) );
									
														$.gritter.add({
															image:	"img/info.png",
															title: 	_notificationTitle,
															text:	"Profil '" + _name + "' modifie"
														});
														$(this).dialog("close"); 
														$_dlg.dialog("close");
													}
												},
												"Fermer": function(){
													$(this).dialog("close");
												}
											},
											close: function(event, ui) { 
												$(this)
													.dialog("destroy")
													.remove(); 
											}
										})
										.pluginautoload()
										.find('[data-type="delete"]')
										.bind('click', function(){
											var _name = $(this).parent().text();
											
											if ( confirm("Supprimer le profil '" + _name + "' ?") ) {
												delete _profils.list[_name];
												localStorage.setItem( 'jquery.configurationtable', JSON.stringify( _profils ) );
												$(this).parent().remove();
											}
										});
								},
								"Ajouter un nouveau profil": function(){
									var $_dlg = $(this);
									var _name = null;
									
									// error
									while ( (_name = prompt("Entrez le nom du nouveau profil")) == "" 
											|| _profils.list[_name] != undefined ) {
										if (_name == ""){
											jAlert("Le nom saisi est vide");
										}else{
											jAlert("Le nom saisi est deja utilise pour un autre profil");
										}
									}
									
									// cancel
									if (_name == null){
										return;
									}
									
									_profils.list[_name] = {
										profil: localStorage.getItem( 'jquery.sortablevariable' )
									};
									localStorage.setItem( 'jquery.configurationtable', JSON.stringify( _profils ) );
									
									$.gritter.add({
										image:	"img/info.png",
										title: 	_notificationTitle,
										text:	"Profil '" + _name + "' ajoute"
									});
									$(this).dialog("close"); 
									$_dlg.dialog("close");
								}
							},
							close: function(event, ui) { 
								$(this)
									.dialog("destroy")
									.remove(); 
							}
						})
						.pluginautoload();
				});
		});
	};
})(jQuery);