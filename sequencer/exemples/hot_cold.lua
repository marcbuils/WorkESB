require('csiemessenger');

local _event;
onstart = function( p_infos )
	csiemessenger.init( p_infos.domain, p_infos.name );
	
	csiemessenger.regProduceSampling( p_infos.variable_hotcold, "HOT_COLD", "int" );
	csiemessenger.regConsumSampling( p_infos.variable_temperature, "TEMPERATURE", "float" );
	_event = p_infos.event;
	
	HOT_COLD = 0;
end

onupdate = function()
	local _HOT_COLD = HOT_COLD;
	csiemessenger.update();
	
	if (TEMPERATURE > 0) then
		HOT_COLD = 1;
	else
		HOT_COLD = 0;
	end
	
	if (_HOT_COLD ~= HOT_COLD) then 
		csiemessenger.trigger( _event );
	end
end

onstop = function()
	csiemessenger.unreg();
end
