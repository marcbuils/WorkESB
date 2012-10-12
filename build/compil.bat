rem make init
msbuild "..\WESBMessenger\WESBMessenger\WESBMessenger.sln" /p:Configuration=Release
msbuild "..\messenger_gateway_websockets\win32port\win32port.sln" /p:Configuration=Release
msbuild "..\messenger\messenger.sln" /p:Configuration=Release
msbuild "..\sequencer\sequencer.sln" /p:Configuration=Release
rem make release
rem make install
@echo off
echo ''
echo '## GENERATION DU SEQUENCER'
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
echo '## AJOUT DU FICHIER DE CONFIGURATION'
copy "exemple_confs\config_win_lite.json" "sequencer\conf\config.json"
copy "exemple_confs\config_win_lite.lua" "sequencer\conf\config.lua"
copy "..\sequencer\Release\sequencer.exe" "sequencer\"

echo ''
echo '## AJOUT DE SIMD'
copy "%SIMD_LIB%\SimD.dll" "sequencer\"

echo ''
echo '## AJOUT DE JSONCPP'
copy "%JSONCPP_LIB%\json.dll" "sequencer\"

echo ''
echo '## AJOUT DE LUA'
copy "%LUA_LIB%\lua52.dll" "sequencer\"

echo ''
echo '## AJOUT DE LA LIBRAIRIE LUA LFS'
copy "libs\keplerproject-luafilesystem-149e0fb\lfs.dll" "sequencer\plugins\lua\"

echo ''
echo '## AJOUT DE LA LIBRAIRIE LUA UUID'
copy "libs\uuid\uuid.dll" "sequencer\plugins\lua\"

echo ''
echo '## AJOUT DU WESBMESSENGER'
copy "..\WESBMessenger\WESBMessenger\Release\WESBMessenger.dll" "sequencer\"

echo ''
echo '## AJOUT DU MESSENENGER POUR LUA'
copy "..\messenger\Release\wesbmessenger_c.dll" "sequencer\plugins\lua\"

echo ''
echo '## AJOUT DU LANCEUR'
copy "startesb_dev.bat" "sequencer\"

echo 'REPERTOIRE "sequencer" GENERE'
