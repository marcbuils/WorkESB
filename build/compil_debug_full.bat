rem make init
msbuild "../WESBMessenger/WESBMessenger/WESBMessenger.sln" /p:Configuration=Debug
msbuild "../messenger_gateway_websockets/win32port/win32port.sln" /p:Configuration=Debug
msbuild "../messenger/messenger.sln" /p:Configuration=Debug
msbuild "../sequencer/sequencer.sln" /p:Configuration=Debug
rem make debug
rem make install_debug
@echo off
echo ''
echo '## SEQUENCER GENERATION'
mkdir "sequencer_debug"
mkdir "sequencer_debug\automates"
xcopy "..\sequencer\automates" "sequencer_debug\automates" /e
mkdir "sequencer_debug\plugins"
xcopy "..\sequencer\plugins" "sequencer_debug\plugins" /e
mkdir "sequencer_debug\sequencers"
xcopy "..\sequencer\sequencers" "sequencer_debug\sequencers" /e
mkdir "sequencer_debug\conf"

echo ''
echo '## ADD LUA SEQUENCEURS'
copy "..\sequencers_lua\*.lua" "sequencer_debug\sequencers"
	
echo ''
echo '## ADD CONFIGURATION FILES'
copy "exemple_confs\config_win.json" "sequencer_debug\conf\config.json"
copy "exemple_confs\config_win.lua" "sequencer_debug\conf\config.lua"
copy "..\sequencer\Debug\sequencer.exe" "sequencer_debug\"

echo ''
echo '## ADD SIMD'
copy "%SIMD_LIB%\SimD.dll" "sequencer_debug\"

echo ''
echo '## ADD JSONCPP'
copy "%JSONCPP_LIB%\json.dll" "sequencer_debug\"

echo ''
echo '## ADD LUA'
copy "%LUA_LIB%\lua52.dll" "sequencer_debug\"

echo ''
echo '## ADD LUA LFS LIBRARY'
copy "libs\keplerproject-luafilesystem-149e0fb\lfs.dll" "sequencer_debug\plugins\lua\"

echo ''
echo '## ADD LUA UUID LIBRARY'
copy "libs\uuid\uuid.dll" "sequencer_debug\plugins\lua\"

echo ''
echo '## ADD WESBMESSENGER'
copy "..\WESBMessenger\WESBMessenger\Debug\WESBMessenger.dll" "sequencer_debug\"

echo ''
echo '## ADD MESSENENGER GATEWAY WEBSOCKETS'
copy "..\messenger_gateway_websockets\win32port\Debug\messenger_gateway_websockets.dll" "sequencer_debug\sequencers\"

echo ''
echo '## ADD MESSENENGER FOR LUA'
copy "..\messenger\Debug\wesbmessenger_c.dll" "sequencer_debug\plugins\lua\"

echo ''
echo '## ADD IHM'
mkdir "sequencer_debug\ihm"
xcopy "..\www" "sequencer_debug\www" /e

echo ''
echo '## ADD MESSENENGER JS FOR IHM'
copy "..\wesbmessengerjs\jquery.wesbmessenger.js" "sequencer_debug\www\admin\js\"

echo ''
echo '## ADD MESSENENGER JS FOR DEMO'
copy "..\wesbmessengerjs\jquery.wesbmessenger.js" "sequencer_debug\www\demo\libs\"

echo ''
echo '## ADD LAUNCHER'
copy "startesb_dev.bat" "sequencer_debug\"

echo '"sequencer" FOLDER BUILT'
