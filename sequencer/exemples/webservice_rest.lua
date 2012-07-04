require('csiemessenger');

local SERVER_HOST = "http://localhost/www/report/";
						
local wsget = function( p_table, p_type, p_params )
	local _return = {};
		
	print( "GET: C:/Users/buils/Documents/tools/curl/curl.exe \""..SERVER_HOST.."ws/src/ws_"..p_table..".php?wsparams%5B%5D=json&wsparams%5B%5D="..p_type.."&wsparams%5B%5D="..p_params.."\" > tmp.cache" );
	os.execute( "C:/Users/buils/Documents/tools/curl/curl.exe \""..SERVER_HOST.."ws/src/ws_"..p_table..".php?wsparams%5B%5D=json&wsparams%5B%5D="..p_type.."&wsparams%5B%5D="..p_params.."\" > tmp.cache" );
	local _file = io.open("tmp.cache", "r");
	_return = json.decode( _file:read("*all") );
	_file:close();
--	os.remove("tmp.cache");
		
	return _return;
end

local wsput = function( p_table, p_type )
	local _return = {};
		
	print( "PUT: C:/Users/buils/Documents/tools/curl/curl.exe -X PUT \""..SERVER_HOST.."ws/src/ws_"..p_table..".php?wsparams%5B%5D=json&wsparams%5B%5D="..p_type.."\" > tmp.cache" );
	os.execute( "C:/Users/buils/Documents/tools/curl/curl.exe -X PUT \""..SERVER_HOST.."ws/src/ws_"..p_table..".php?wsparams%5B%5D=json&wsparams%5B%5D="..p_type.."\" > tmp.cache" );
	local _file = io.open("tmp.cache", "r");
	_return = json.decode( _file:read("*all") );
	_file:close();
--	os.remove("tmp.cache");
		
	return _return;
end

local wsdelete = function( p_table, p_type, p_params )
	local _return = {};
		
	print( "DELETE: C:/Users/buils/Documents/tools/curl/curl.exe -X DELETE \""..SERVER_HOST.."ws/src/ws_"..p_table..".php?wsparams%5B%5D=json&wsparams%5B%5D="..p_type.."&wsparams%5B%5D="..p_params.."\" > tmp.cache" );
	os.execute( "C:/Users/buils/Documents/tools/curl/curl.exe -X DELETE \""..SERVER_HOST.."ws/src/ws_"..p_table..".php?wsparams%5B%5D=json&wsparams%5B%5D="..p_type.."&wsparams%5B%5D="..p_params.."\" > tmp.cache" );
	local _file = io.open("tmp.cache", "r");
	_return = json.decode( _file:read("*all") );
	_file:close();
--	os.remove("tmp.cache");
		
	return _return;
end

local wspost = function( p_table, p_type, p_params, p_data )
--	local _return = {};
	local _data = "_=0";
	table.foreach( p_data, function( _key, _value )
		_data = _data .. "&" .. _key .. "=" .. _value;
	end );
	print( "POST: C:/Users/buils/Documents/tools/curl/curl.exe -X POST -d \"".._data.."\" \""..SERVER_HOST.."ws/src/ws_"..p_table..".php?wsparams%5B%5D=json&wsparams%5B%5D="..p_type.."&wsparams%5B%5D="..p_params.."\" > tmp.cache" );
	os.execute( "C:/Users/buils/Documents/tools/curl/curl.exe -X POST -d \"".._data.."\" \""..SERVER_HOST.."ws/src/ws_"..p_table..".php?wsparams%5B%5D=json&wsparams%5B%5D="..p_type.."&wsparams%5B%5D="..p_params.."\" > tmp.cache" );
	local _file = io.open("tmp.cache", "r");
--	_return = json.decode( _file:read("*all") );
	_file:close();
--	os.remove("tmp.cache");
		
--	return _return;
end

onstart = function( p_infos )
	csiemessenger.init( p_infos.domain, p_infos.name );
	
	csiemessenger.share( _ifndef( p_infos.reportCreate, "REPORT_CREATE" ), function( p_params )
		local _report = -1;
		local _testset = -1;
		
		_report = wsput( 'test', 'id' );
        wspost('test', 'id', _report.Test_ID, {
            Test_Procedure=31;
        } );
		
		_testset = wsput( 'testset', 'id' );
	    wspost( 'testset', 'id', _testset.TestSet_ID, {
			TestSet_Test=       _report.Test_ID,
			TestSet_Product=	111
		} );
		
		return _report.Test_ID;
	end );
	
	csiemessenger.share( _ifndef( p_infos.reportSave, "REPORT_SAVE" ), function( p_params )
		local _result = -1;
		
        _result = wsget('result', 'filter', "/.%5BResult_Test="..p_params.report.."%5D%5BResult_Action="..p_params.id.."%5D" );
		wspost('result', 'id', _result[1].Result_ID, {
			Result_Value=p_params.value;
		} );
		
		return 1;
	end );
end

onupdate = function()
	csiemessenger.update();
end

onstop = function()
	csiemessenger.unreg();
end
