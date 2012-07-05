;(function($){
	$(document).one("wesbmessenger_update", function(){
		$.wesbmessenger.singleton().regProduceSampling( "HOT_COLD", "int" );
		$.wesbmessenger.singleton().regConsumSampling( "TEMPERATURE", "float" );

		var hotCold = 0;
		$(document).bind("wesbmessenger_update", function(){
			var _hotCold;
			
			if ($.wesbmessenger.consumers.TEMPERATURE > 0) {
				_hotCold = 1;
			} else {
				_hotCold = 0;
			}
			$.wesbmessenger.producers.HOT_COLD = _hotCold;
			
			if (_hotCold != hotCold) {
				$.wesbmessenger.singleton().trigger( "HOT_COLD_CHANGE" );
			}
		});
	});
})(jQuery);