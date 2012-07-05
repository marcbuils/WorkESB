rem make init
msbuild "../WESBMessenger/WESBMessenger/WESBMessenger.sln" /p:Configuration=Release
msbuild "../messenger_gateway_websockets/win32port/win32port.sln" /p:Configuration=Release
msbuild "../messenger/messenger.sln" /p:Configuration=Release
msbuild "../sequencer/sequencer.sln" /p:Configuration=Release
rem make release
rem make install_release
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
echo '## AJOUT DES SEQUENCEURS LUA'
copy "..\sequencers_lua\*.lua" "sequencer\sequencers"
	
echo ''
echo '## AJOUT DU FICHIER DE CONFIGURATION'
copy "exemple_confs\config_win.json" "sequencer\conf\config.json"
copy "exemple_confs\config_win.lua" "sequencer\conf\config.lua"
copy "..\sequencer\Release\sequencer.exe" "sequencer\"

echo ''
echo '## AJOUT DE SIMD'
copy "%SIMD_LIB%\SimD.dll" "sequencer\"

echo ''
echo '## AJOUT DE JSONCPP'
copy "%JSONCPP_LIB%\json.dll" "sequencer\"

echo ''
echo '## AJOUT DE LUA'
copy "%LUA_LIB%\lua5.1.dll" "sequencer\"

echo ''
echo '## AJOUT DU WESBMESSENGER'
copy "..\WESBMessenger\WESBMessenger\Release\WESBMessenger.dll" "sequencer\"

echo ''
echo '## AJOUT DU MESSENENGER GATEWAY WEBSOCKETS'
copy "..\messenger_gateway_websockets\win32port\Release\messenger_gateway_websockets.dll" "sequencer\sequencers\"

echo ''
echo '## AJOUT DU MESSENENGER POUR LUA'
copy "..\messenger\Release\wesbmessenger_c.dll" "sequencer\plugins\lua\"


echo ''
echo '#### AJOUT DU DRIVER NXT'
copy "..\nxt_driver\Release\nxt_driver.dll" "sequencer\sequencers"

echo ''
echo '## AJOUT DE l''IHM'
mkdir "sequencer\ihm"
xcopy "..\ihm" "sequencer\ihm" /e

echo 'REPERTOIRE "sequencer" GENERE'