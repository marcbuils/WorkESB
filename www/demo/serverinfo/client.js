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
 *  Created on: 28 octo. 2012
 *      Author: Marc Buils (http://www.marcbuils.fr)
 */
;( function( $ ){
	/**
	 * WorkESB demonstration
	 * Display server information on client site with ConsumSampling API
	 */
	$.wesbmessenger.singleton()
		.connect( 'com.workesb.demo', 'SERVERINFO_CLIENT' )
		.consumSampling( 'tmpDir' )
		.consumSampling( 'hostname' )
		.consumSampling( 'type' )
		.consumSampling( 'platform' )
		.consumSampling( 'arch' )
		.consumSampling( 'release' )
		.consumSampling( 'uptime' )
		.consumSampling( 'totalmem' )
		.consumSampling( 'freemem' )
		.consumSampling( 'loadavg' )
		.update( function(){
			$( '#tmpDir' ).text( $.wesbmessenger.consumer.tmpDir );
			$( '#hostname' ).text( $.wesbmessenger.consumer.hostname );
			$( '#type' ).text( $.wesbmessenger.consumer.type );
			$( '#platform' ).text( $.wesbmessenger.consumer.platform );
			$( '#arch' ).text( $.wesbmessenger.consumer.arch );
			$( '#release' ).text( $.wesbmessenger.consumer.release );
			$( '#uptime' ).text( $.wesbmessenger.consumer.uptime );
			$( '#loadavg' ).text( $.wesbmessenger.consumer.loadavg.toString() );
			$( '#totalmem' ).text( $.wesbmessenger.consumer.totalmem );
			$( '#freemem' ).text( $.wesbmessenger.consumer.freemem );
		} );
})( jQuery );