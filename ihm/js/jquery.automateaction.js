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
var _lastStatus = null;
var _lastDialog = null;
var _notificationTitle = "Information sur l'automate";
var _currentGritterId = -1;

var __AUTOMATE_STATUS__ = "AUTOMATE_STATUS";
var __AUTOMATE_DIALOG__ = "AUTOMATE_DIALOG";
var __AUTOMATE_DIALOG_RETURN__ = "AUTOMATE_DIALOG_RETURN";

$(document).one( "wesbmessenger_update", function(){
	$.wesbmessenger.singleton().regConsumSampling( __AUTOMATE_STATUS__, "string" );
	$.wesbmessenger.singleton().regConsumSampling( __AUTOMATE_DIALOG__, "string" );
	
	$(document).bind( "wesbmessenger_update", function(){
		var _status = $.wesbmessenger.consumer[__AUTOMATE_STATUS__];
		
		if ( _lastStatus != _status && $('[data-jquery-type="automateaction"][data-waiting]').size() <= 0 ){
			if (_status == "stopped") {
				if ( _lastStatus != null ){
					$.gritter.add({
						image:	"img/info.png",
						title: 	_notificationTitle,
						text:	"Arret de l'automate"
					});
				}
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="start"]').parent().parent().get(0) ).set("disabled", false);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="pause"]').parent().parent().get(0) ).set("disabled", true);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="pause"]').parent().parent().get(0) ).set("checked", false);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="stop"]').parent().parent().get(0) ).set("disabled", true);
			} else if (_status == "started"){
				if ( _lastStatus != null ){
					$.gritter.add({
						image:	"img/info.png",
						title: 	_notificationTitle,
						text:	(_lastStatus == "paused" ? "Relance de l'automate" : "Lancement de l'automate")
					});
				}
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="start"]').parent().parent().get(0) ).set("disabled", true);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="pause"]').parent().parent().get(0) ).set("disabled", false);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="pause"]').parent().parent().get(0) ).set("checked", false);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="stop"]').parent().parent().get(0) ).set("disabled", false);
			} else if (_status == "paused") {
				if ( _lastStatus != null ){
					$.gritter.add({
						image:	"img/info.png",
						title: 	_notificationTitle,
						text:	"Pause de l'automate"
					});
				}
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="start"]').parent().parent().get(0) ).set("disabled", true);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="pause"]').parent().parent().get(0) ).set("disabled", false);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="pause"]').parent().parent().get(0) ).set("checked", true);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="stop"]').parent().parent().get(0) ).set("disabled", false);
			} else {
				if ( _lastStatus != null ){
					$.gritter.add({
						image:	"img/info.png",
						title: 	_notificationTitle,
						text:	"Erreur inconnue"
					});
				}
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="start"]').parent().parent().get(0) ).set("disabled", true);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="pause"]').parent().parent().get(0) ).set("disabled", true);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="pause"]').parent().parent().get(0) ).set("checked", false);
				dijit.byNode( $('[data-jquery-type="automateaction"][data-action="stop"]').parent().parent().get(0) ).set("disabled", true);
			}
			_lastStatus = _status;
		}
		
		// automate dialogs
		var _dialog;
		if (_status == "started"){
			_dialog = $.wesbmessenger.consumer[__AUTOMATE_DIALOG__];
		}else{
			_dialog = JSON.stringify({type: "none"});
		}
		if (_lastDialog != _dialog){
			_lastDialog = _dialog;
			try {
				_dialog = JSON.parse( _dialog );
			} catch(e){
				_dialog = { type: "none" };
			}
			
			if (_dialog.type == "alert"){
				if ( $('#gritter-item-'+_currentGritterId).size() > 0 ){
					$.gritter.remove(_currentGritterId);
					_currentGritterId = -1;
				}
				
				jAlert( _dialog.text, _dialog.title, function(){
					$.wesbmessenger.singleton().trigger(__AUTOMATE_DIALOG_RETURN__, {
						"type": 	"alert"
					});
				});
			} else if (_dialog.type == "confirm"){
				if ( $('#gritter-item-'+_currentGritterId).size() > 0 ){
					$.gritter.remove(_currentGritterId);
					_currentGritterId = -1;
				}
				
				jConfirm( _dialog.text, _dialog.title, function(_r){
					$.wesbmessenger.singleton().trigger(__AUTOMATE_DIALOG_RETURN__, {
						"type": 	"confirm",
						"return": 	_r
					});
				});
			} else if (_dialog.type == "prompt"){
				if ( $('#gritter-item-'+_currentGritterId).size() > 0 ){
					$.gritter.remove(_currentGritterId);
					_currentGritterId = -1;
				}
				
				jPrompt( _dialog.text, "", _dialog.title, function(_r){
					$.wesbmessenger.singleton().trigger(__AUTOMATE_DIALOG_RETURN__, {
						"type": 	"prompt",
						"return": 	_r
					});
				});
			} else if (_dialog.type == "wait"){
				$.alerts._hide();
				
				if ( $('#gritter-item-'+_currentGritterId).size() > 0 ){
					$.gritter.remove(_currentGritterId);
				}
				_currentGritterId = $.gritter.add({
					image:	"img/waiting.png",
					sticky: true,
					title: 	"Automate en attente",
					text:	_dialog.text
				});
				$('#gritter-item-'+_currentGritterId+' .gritter-close').remove();
			}else{
				$.alerts._hide();
				if ( $('#gritter-item-'+_currentGritterId).size() > 0 ){
					$.gritter.remove(_currentGritterId);
					_currentGritterId = -1;
				}
			}
		}
	});
});
		
$.fn.automateaction = function(){
	return this.each(function(){
		var $_this = $(this);
		var _action = $_this.attr('data-action');

		$_this.click(function(){
			if ( dijit.byNode( $_this.parent().parent().get(0) ).get('disabled') ){
				return false;
			}
			
			dijit.byNode( $('[data-jquery-type="automateaction"][data-action="start"]').parent().parent().get(0) ).set("disabled", true);
			dijit.byNode( $('[data-jquery-type="automateaction"][data-action="pause"]').parent().parent().get(0) ).set("disabled", true);
			dijit.byNode( $('[data-jquery-type="automateaction"][data-action="stop"]').parent().parent().get(0) ).set("disabled", true);
			
			if ( _action == 'start' ){
				$.wesbmessenger.singleton().call("getAutomates").done(function( _automates ){
					var $_dialog = $( $_this.attr('data-dialog') );
					
					$_dialog
						.tmpl( { automates: _automates } )
						.dialog({
							modal: true,
							title: "Executer un automate",
							buttons: { 
								"Executer": function() { 
									if ( $(this).find('li.ui-selected').size() <= 0 ){
										jAlert( "Selectionnez l'automate a executer" );
									}else if ( $(this).find('li.ui-selected').size() > 1 ){
										jAlert( "Selectionnez un seul automate" );
									}else{
										$_this.attr('data-waiting', '');
										$.wesbmessenger.singleton().call("startAutomate", {
											file: $(this).find('li.ui-selected').attr('data-file')
										}).done(function(_r){
											$_this.removeAttr('data-waiting');

											if (_r.status == 0){
												_lastStatus = null;
												jAlert(_r.error, "Erreur d'automate");
											}
										});
										$(this).dialog("destroy"); 
									}
								},
								"Annuler": function(){
									$(this).dialog("close"); 
								}
							},
							close: function(event, ui) { 
								$_this.removeAttr('data-waiting');
								_lastStatus = null;
								$(this).dialog("destroy"); 
							}
						})
						.pluginautoload();
				});
			} else if (_action == 'pause' ){
				$_this.attr('data-waiting', '');
				if ( $.wesbmessenger.consumer.AUTOMATE_STATUS != "paused" ) { 
					$.wesbmessenger.singleton().call("pauseAutomate").done(function(){
						$_this.removeAttr('data-waiting');
					}); 
				} else { 
					$.wesbmessenger.singleton().call("resumeAutomate").done(function(){
						$_this.removeAttr('data-waiting');
					});
				}
			} else if ( _action == 'stop' ){
				$_this.attr('data-waiting', '');
				$.wesbmessenger.singleton().call("stopAutomate").done(function(){
					$_this.removeAttr('data-waiting');
				}); 
			}
		}); 
	});
};
})(jQuery);