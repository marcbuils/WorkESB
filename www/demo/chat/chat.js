;(function( $ ){
	/*
	 * Get login
	 */
	var _login = prompt( "What's your username ?" );

	/*
	 * Connect WorkESB and listen 'talk' event
	 */
	$.wesbmessenger.singleton()
		.connect( 'com.worbesb.demo', 'CHAT' )
		.bind( 'talk', function( p_text ){
			$( '#conversation' ).prepend( $( '<li />' ).text( p_text ) );
		})
		.trigger( 'talk', '>>> ' + _login + ' is now connected' );
	
	$(function(){
		/*
		 * Send a talk event
		 */
		$( '#send_button' ).click( function(){
			$.wesbmessenger.singleton().trigger( 'talk', _login + ': ' + $( '#send_text' ).val() );
		});
	});
})( jQuery );
