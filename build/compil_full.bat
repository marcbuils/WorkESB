rem make init
msbuild "../WESBMessenger/WESBMessenger/WESBMessenger.sln" /p:Configuration=Release
msbuild "../messenger_gateway_websockets/win32port/win32port.sln" /p:Configuration=Release
msbuild "../messenger/messenger.sln" /p:Configuration=Release
msbuild "../sequencer/sequencer.sln" /p:Configuration=Release
rem make release
rem make install_release
@echo off
echo ''
echo '## SEQUENCER GENERATION'
mkdir "sequencer"
mkdir "sequencer\automates"
xcopy "..\sequencer\automates" "sequencer\automates" /e
mkdir "sequencer\plugins"
xcopy "..\sequencer\plugins" "sequencer\plugins" /e
mkdir "sequencer\sequencers"
xcopy "..\sequencer\sequencers" "sequencer\sequencers" /e
mkdir "sequencer\conf"

echo ''
echo '## ADD SEQUENCEURS LUA'
copy "..\sequencers_lua\*.lua" "sequencer\sequencers"
	
echo ''
echo '## ADD CONFIGURATION'
copy "exemple_confs\config_win.json" "sequencer\conf\config.json"
copy "exemple_confs\config_win.lua" "sequencer\conf\config.lua"
copy "..\sequencer\Release\sequencer.exe" "sequencer\"

echo ''
echo '## ADD SIMD'
copy "%SIMD_LIB%\SimD.dll" "sequencer\"

echo ''
echo '## ADD JSONCPP'
copy "%JSONCPP_LIB%\json.dll" "sequencer\"

echo ''
echo '## ADD LUA'
copy "%LUA_LIB%\lua52.dll" "sequencer\"

echo ''
echo '## ADD LUA LFS LIBRARY'
copy "libs\keplerproject-luafilesystem-149e0fb\lfs.dll" "sequencer\plugins\lua\"

echo ''
echo '## ADD LUA UUID LIBRARY'
copy "libs\uuid\uuid.dll" "sequencer\plugins\lua\"

echo ''
echo '## ADD WESBMESSENGER'
copy "..\WESBMessenger\WESBMessenger\Release\WESBMessenger.dll" "sequencer\"

echo ''
echo '## ADD MESSENENGER GATEWAY WEBSOCKETS'
copy "..\messenger_gateway_websockets\win32port\Release\messenger_gateway_websockets.dll" "sequencer\sequencers\"

echo ''
echo '## ADD MESSENENGER FOR LUA'
copy "..\messenger\Release\wesbmessenger_c.dll" "sequencer\plugins\lua\"

echo ''
echo '## ADD IHM'
mkdir "sequencer\ihm"
xcopy "..\www" "sequencer\www" /e

echo ''
echo '## ADD MESSENENGER JS FOR IHM'
copy "..\wesbmessengerjs\jquery.wesbmessenger.js" "sequencer\www\admin\js\"

echo ''
echo '## ADD MESSENENGER JS FOR DEMO'
copy "..\wesbmessengerjs\jquery.wesbmessenger.js" "sequencer\www\admin\js\"

echo ''
echo '## ADD LAUNCHER'
copy "startesb_dev.bat" "sequencer\"

echo '"sequencer" FOLDER BUILT'