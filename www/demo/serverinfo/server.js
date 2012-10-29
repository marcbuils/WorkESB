jQuery = require('jquery')
;(function($){
	var os = require('os');
	require('../libs/jquery.wesbmessenger.js');
	
	$.wesbmessenger.singleton()
		.connect( 'com.workesb.demo', 'SERVERINFO_SERVER' )
		.produceSampling('tmpDir')
		.produceSampling('hostname')
		.produceSampling('type')
		.produceSampling('platform')
		.produceSampling('arch')
		.produceSampling('release')
		.produceSampling('uptime')
		.produceSampling('totalmem')
		.produceSampling('freemem')
		.produceSampling('loadavg')
		.update( function(){
			$.wesbmessenger.producer.tmpDir 	= os.tmpDir();
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
} )(jQuery);
