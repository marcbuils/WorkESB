require('wesbmessenger');

local _event;
onstart = function( p_infos )
	wesbmessenger.init( p_infos.domain, p_infos.name );
	
	wesbmessenger.regProduceSampling( p_infos.variable_hotcold, "HOT_COLD", "int" );
	wesbmessenger.regConsumSampling( p_infos.variable_temperature, "TEMPERATURE", "float" );
	_event = p_infos.event;
	
	HOT_COLD = 0;
end

onupdate = function()
	local _HOT_COLD = HOT_COLD;
	wesbmessenger.update();
	
	if (TEMPERATURE > 0) then
		HOT_COLD = 1;
	else
		HOT_COLD = 0;
	end
	
	if (_HOT_COLD ~= HOT_COLD) then 
		wesbmessenger.trigger( _event );
	end
end

onstop = function()
	wesbmessenger.unreg();
end
