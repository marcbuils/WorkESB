rem make init
msbuild "../WESBMessenger/WESBMessenger/WESBMessenger.sln" /p:Configuration=Debug
msbuild "../messenger_gateway_websockets/win32port/win32port.sln" /p:Configuration=Debug
msbuild "../messenger/messenger.sln" /p:Configuration=Debug
msbuild "../sequencer/sequencer.sln" /p:Configuration=Debug
rem make debug
rem make install_debug_lite
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
rem xcopy "..\sequencer\conf" "sequencer_debug\conf" /e
	
echo ''
echo '## ADD FICHIER CONFIGURATION'
copy "exemple_confs\config_win_lite.json" "sequencer_debug\conf\config.json"
copy "exemple_confs\config_win_lite.lua" "sequencer_debug\conf\config.lua"
copy "..\sequencer\Debug\sequencer.exe" "sequencer_debug\"

echo ''
echo '## ADD SIMD'
copy "%SIMD_LIB%\SimD.dll" "sequencer_debug\"

echo ''
echo '## ADD JSONCPP'
copy "%JSONCPP_LIB%\json.dll" "sequencer_debug\"

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
copy "..\WESBMessenger\WESBMessenger\Debug\WESBMessenger.dll" "sequencer_debug\"

echo ''
echo '## ADD MESSENENGER FOR LUA'
copy "..\messenger\Debug\wesbmessenger_c.dll" "sequencer_debug\plugins\lua\"

echo ''
echo '## ADD LAUNCHER'
copy "startesb_dev.bat" "sequencer_debug\"

echo '"sequencer" FOLDER BUILT'
