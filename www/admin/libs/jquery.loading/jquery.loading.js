//   Copyright 2010 Marc BUILS
//
//   This file is part of Kamak.
//
//    Kamak is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Kamak is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with Kamak.  If not, see <http://www.gnu.org/licenses/>.

(function($){
    $.loading = function(){};
    $.loading.defaultOptions = {
            src: 'loading.gif',
            css: {
                textAlign:  'center',
                display:    'inline'
            }
    };
    
    // constructor
    $.fn.loading = function(p_options) {
        var _options = $.extend({}, $.loading.defaultOptions, p_options);

        return this.each(function(){
            var $_this = $(this);

    		if ( $_this.data('loading_currents') == undefined ){
    			$_this	.data('loading_currents', 1)
    					.bind('recovery', function(p_event){
    						if ( $_this.data('loading_currents') > 0 ){
	    						$_this.data( 'loading_currents', $_this.data('loading_currents')-1 );
	    						
	    						if ( $_this.data('loading_currents') == 0 ){
						        	$_this	.empty()
											.data('loading_backup').appendTo( $_this );
	    						}
    						}
							p_event.stopPropagation();
    					} );
    		}else{
    			$_this.data( 'loading_currents', $_this.data('loading_currents')+1 );
    		}

    		if ( $_this.data('loading_currents') == 1 ){
    			$_this	.data( 'loading_backup', $_this.contents().detach() );
		    }
    		$_this	.empty()
    				.append( $('<div></div>')	.css(_options.css)
    											.append( $('<img />').attr('src', _options.src) ) );
        });
    };
})(jQuery);