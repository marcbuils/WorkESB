;(function($){
	$(document).one("csiemessenger_update", function(){
		$.csiemessenger.singleton().regProduceSampling( "HOT_COLD", "int" );
		$.csiemessenger.singleton().regConsumSampling( "TEMPERATURE", "float" );

		var hotCold = 0;
		$(document).bind("csiemessenger_update", function(){
			var _hotCold;
			
			if ($.csiemessenger.consumers.TEMPERATURE > 0) {
				_hotCold = 1;
			} else {
				_hotCold = 0;
			}
			$.csiemessenger.producers.HOT_COLD = _hotCold;
			
			if (_hotCold != hotCold) {
				$.csiemessenger.singleton().trigger( "HOT_COLD_CHANGE" );
			}
		});
	});
})(jQuery);