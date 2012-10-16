rem make init
msbuild "..\WESBMessenger\WESBMessenger\WESBMessenger.sln" /p:Configuration=Release
msbuild "..\messenger_gateway_websockets\win32port\win32port.sln" /p:Configuration=Release
msbuild "..\messenger\messenger.sln" /p:Configuration=Release
msbuild "..\sequencer\sequencer.sln" /p:Configuration=Release
rem make release
rem make install
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
rem xcopy "..\sequencer\conf" "sequencer\conf" /e
	
echo ''
echo '## ADD FICHIER CONFIGURATION'
copy "exemple_confs\config_win_lite.json" "sequencer\conf\config.json"
copy "exemple_confs\config_win_lite.lua" "sequencer\conf\config.lua"
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
echo '## ADD MESSENENGER FOR LUA'
copy "..\messenger\Release\wesbmessenger_c.dll" "sequencer\plugins\lua\"

echo ''
echo '## ADD LAUNCHER'
copy "startesb_dev.bat" "sequencer\"

echo '"sequencer" FOLDER BUILT'
