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
;( function( os, $ ){
	/**
	 * WorkESB demonstration
	 * Share server information with node.js and ProduceSampling API
	 */
	$.wesbmessenger.singleton()
		.connect( 'com.workesb.demo', 'SERVERINFO_SERVER', {
			server:	'ws://localhost:8080/'      
		} )
		.produceSampling( 'tmpDir' )
		.produceSampling( 'hostname' )
		.produceSampling( 'type' )
		.produceSampling( 'platform' )
		.produceSampling( 'arch' )
		.produceSampling( 'release' )
		.produceSampling( 'uptime' )
		.produceSampling( 'totalmem' )
		.produceSampling( 'freemem' )
		.produceSampling( 'loadavg' )
		.update( function(){
			$.wesbmessenger.producer.tmpDir 	= ( typeof(os.tmpDir) == "undefined" ? "none" : os.tmpDir() );
			$.wesbmessenger.producer.hostname 	= os.hostname();
			$.wesbmessenger.producer.type 		= os.type();
			$.wesbmessenger.producer.platform	= os.platform();
			$.wesbmessenger.producer.arch		= os.arch();
			$.wesbmessenger.producer.release	= os.release();
			$.wesbmessenger.producer.uptime		= os.uptime();
			$.wesbmessenger.producer.loadavg	= os.loadavg();
			$.wesbmessenger.producer.totalmem	= os.totalmem();
			$.wesbmessenger.producer.freemem	= os.freemem();
		} );
} )( require( 'os' ), 
	 require( 'jquery' ), 
	 require( '../libs/jquery.wesbmessenger.js' ) );
