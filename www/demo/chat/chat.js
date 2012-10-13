;(function( $ ){
	/*
	 * Get login
	 */
	var _login = prompt( "What's your username ?" );

	/*
	 * Connect WorkESB and listen 'talk' event
	 */
	$.wesbmessenger.singleton()
		.connect( 'com.worbesb.demo.chat', 'CHAT' )
		.bind( 'talk', function( p_text ){
			$( '#conversation' ).append( $( '<li />' ).text( p_text ) );
		});
	
	$(function(){
		/*
		 * Send a talk event
		 */
		$( '#send_button' ).click( function(){
			$.wesbmessenger.singleton().trigger( 'talk', _login + ': ' + $( '#send_text' ).val() );
		});
	});
})( jQuery );
