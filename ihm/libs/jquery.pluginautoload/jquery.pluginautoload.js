require(['dojo/ready'], function(ready){
(function($){
	$.pluginautoload_options = {
		autoload:	true,
		libs_dir:	'js/',
		filename: function( p_type ){
			return this.libs_dir + 'jquery.' + p_type.toLowerCase() + '.js';
		}
	};
	
	$.fn.pluginautoload = function( p_options ){
		var _options = $.extend({}, $.pluginautoload_options, p_options);

		this.find('[data-jquery-type]:not(.jquery_pluginautoload)').each( function(){
			var $_this = $(this);
			var _params = ( $_this.attr('data-jquery-params') == undefined ? [] : JSON.parse($(this).attr('data-jquery-params')) );
			var _type = $_this.attr('data-jquery-type');
			
			if (_options.autoload && $.fn[_type] == undefined){
				$.ajax(_options.filename( _type ), {
					dataType:	'script',
					async: 		false
				}).done(function(){
					$_this[_type].apply($_this, _params);
				});
			}else{
				$_this[_type].apply($_this, _params);
			}
			$_this.addClass('jquery_pluginautoload');
		});
		
		return this;
	};

	ready(function(){
		$(document).ready(function(){
			$('body').pluginautoload();
		});
	});
})(jQuery);
});