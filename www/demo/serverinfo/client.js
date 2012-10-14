;(function($){
	$.wesbmessenger.singleton()
		.connect('com.workesb.demo.serverinfo', 'SERVERINFO_CLIENT')
		.consumSampling('tmpDir', 'string')
		.consumSampling('hostname', 'string')
		.consumSampling('type', 'string')
		.consumSampling('platform', 'string')
		.consumSampling('arch', 'string')
		.consumSampling('release', 'string')
		.consumSampling('uptime', 'string')
		.consumSampling('totalmem', 'string')
		.consumSampling('freemem', 'string')
		.consumSampling('tmpDir', 'string')
		.update(function(){
			$('#tmpDir').val($.wesbmessenger.consumer.tmpDir);
			$('#hostname').val($.wesbmessenger.consumer.hostname);
			$('#type').val($.wesbmessenger.consumer.type);
			$('#platform').val($.wesbmessenger.consumer.platform);
			$('#arch').val($.wesbmessenger.consumer.arch);
			$('#release').val($.wesbmessenger.consumer.release);
			$('#uptime').val($.wesbmessenger.consumer.uptime);
			$('#loadavg').val($.wesbmessenger.consumer.loadavg);
			$('#totalmem').val($.wesbmessenger.consumer.totalmem);
			$('#freemem').val($.wesbmessenger.consumer.freemem);
		});
})(jQuery);