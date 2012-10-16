;(function($){
	$.wesbmessenger.singleton()
		.connect('com.workesb.demo', 'SERVERINFO_CLIENT')
		.consumSampling('tmpDir', 'string')
		.consumSampling('hostname', 'string')
		.consumSampling('type', 'string')
		.consumSampling('platform', 'string')
		.consumSampling('arch', 'string')
		.consumSampling('release', 'string')
		.consumSampling('uptime', 'string')
		.consumSampling('totalmem', 'string')
		.consumSampling('freemem', 'string')
		.consumSampling('loadavg', 'string')
		.update(function(){
			$('#tmpDir').text($.wesbmessenger.consumer.tmpDir);
			$('#hostname').text($.wesbmessenger.consumer.hostname);
			$('#type').text($.wesbmessenger.consumer.type);
			$('#platform').text($.wesbmessenger.consumer.platform);
			$('#arch').text($.wesbmessenger.consumer.arch);
			$('#release').text($.wesbmessenger.consumer.release);
			$('#uptime').text($.wesbmessenger.consumer.uptime);
			$('#loadavg').text($.wesbmessenger.consumer.loadavg);
			$('#totalmem').text($.wesbmessenger.consumer.totalmem);
			$('#freemem').text($.wesbmessenger.consumer.freemem);
		});
})(jQuery);