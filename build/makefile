##################################################
## COMPILATION COMPLETTE DU BANC MODULAIRE CSIE ##
##################################################

help:
	@echo ''
	@echo 'all: Compile tous les composants en mode Release et Debug'
	@echo 'release: Compile tous les composants en mode Release'
	@echo 'debug: Compile tous les composants en mode Debug'
	@echo 'install: Genere un sequenceur propre (sans IHM et serveur WEB) en mode Release'
	@echo 'install_debug_lite: Genere un sequenceur propre (sans IHM et serveur WEB) en mode Debug'
	@echo 'install_release: Genere un logiciel banc complet en Release'
	@echo 'install_debug: Genere un logiciel banc complet en Debug'
	@echo 'clean: Netoie les repertoires Realease et Debug des composants'
	@echo 'clean_release: Netoie les repertoires Realease des composants'
	@echo 'clean_debug: Netoie les repertoires Debug des composants'

all: release debug

init: 
	@echo ''
	@echo '## VERIFICATION DES VARIABLES D''ENVIRONNEMENT'
ifeq (${OSPL_HOME},) 
	$(error 'OSPL_HOME not defined')
else
	@echo 'OSPL_HOME=${OSPL_HOME}'
endif
ifeq (${SIMD_INSTALL_DIR},) 
	$(error 'SIMD_INSTALL_DIR not defined')
else
	@echo 'SIMD_INSTALL_DIR=${SIMD_INSTALL_DIR}'
endif
ifeq (${SIMD_LIB},) 
	$(error 'SIMD_LIB not defined')
else
	@echo 'SIMD_LIB=${SIMD_LIB}'
endif
ifeq (${JSONCPP_ROOT},) 
	$(error 'JSONCPP_ROOT not defined')
else
	@echo 'JSONCPP_ROOT=${JSONCPP_ROOT}'
endif
ifeq (${JSONCPP_LIB},) 
	$(error 'JSONCPP_LIB not defined')
else
	@echo 'JSONCPP_LIB=${JSONCPP_LIB}'
endif
ifeq (${LUA_ROOT},) 
	$(error 'SIMD_INSTALL_DIR not defined')
else
	@echo 'SIMD_INSTALL_DIR=${SIMD_INSTALL_DIR}'
endif
ifeq (${LUA_LIB},) 
	$(error 'SIMD_INSTALL_DIR not defined')
else
	@echo 'SIMD_INSTALL_DIR=${SIMD_INSTALL_DIR}'
endif
ifeq (${CSIEMESSENGER_ROOT},) 
	$(error 'CSIEMESSENGER_ROOT not defined')
else
	@echo 'CSIEMESSENGER_ROOT=${CSIEMESSENGER_ROOT}'
endif
	@echo ''

release: init
	@echo ''
	@echo '## GENERATION DU KIT DE PRODUCTION'
	@echo ''
	@echo '#### GENERATION DE CSIEMESSENGER'
ifeq "$(WINDOWS)" "YES"
else
	-cd "../CSIEMessenger/CSIEMessenger/CSIEMessenger/Release" && make
endif
	@echo ''
	@echo '#### GENERATION DE MESSENGER POUR LUA'
	-cd "../messenger/Release" && make
	@echo ''
	@echo '#### GENERATION DE MESSENGER GATEWAY WEBSOCKETS'
ifeq "$(WINDOWS)" "YES"
else
	-cd "../messenger_gateway_websockets/Release" && make
endif
	@echo ''
	@echo '#### GENERATION DE SEQUENCER'
	-cd "../sequencer/Release" && make
#ifeq "$(WINDOWS)" "YES"
#else
#	@echo ''
#	@echo '#### GENERATION DU DRIVER NXT'
#	-cd "../nxt_driver/Release" && make
#endif

debug: init
	@echo 'GENERATION DU KIT DE DEBUG'
	@echo ''
	@echo '#### GENERATION DE CSIEMESSENGER'
ifeq "$(WINDOWS)" "YES"
#	-msbuild "../CSIEMessenger/CSIEMessenger/CSIEMessenger.sln" /p:Configuration=Debug
else
	-cd "../CSIEMessenger/CSIEMessenger/CSIEMessenger/Debug" && make
endif
	@echo ''
	@echo '#### GENERATION DE MESSENGER POUR LUA'
	-cd "../messenger/Debug" && make
	@echo ''
	@echo '#### GENERATION DE MESSENGER GATEWAY WEBSOCKETS'
ifeq "$(WINDOWS)" "YES"
#	-msbuild "../messenger_gateway_websockets/win32port/win32port.sln" /p:Configuration=Debug
else
	-cd "../messenger_gateway_websockets/Debug" && make
endif
	@echo ''
	@echo '#### GENERATION DE SEQUENCER'
	-cd "../sequencer/Debug" && make
ifeq "$(WINDOWS)" "YES"
else
	@echo ''
	@echo '#### GENERATION DU DRIVER NXT'
	-cd "../nxt_driver/Debug" && make
endif

clean_debug: init
	@echo ''
	@echo '## NETTOYAGE DU MODE DEBUG'
	@echo '#### NETTOYAGE DE CSIEMESSENGER'
ifeq "$(WINDOWS)" "YES"
#	-msbuild "../CSIEMessenger/CSIEMessenger/CSIEMessenger.sln" /t:Clean /p:Configuration=Debug
else
	-cd "../CSIEMessenger/CSIEMessenger/CSIEMessenger/Debug" && make clean
endif
	@echo ''
	@echo '#### NETTOYAGE DE MESSENGER POUR LUA'
	-cd "../messenger/Debug" && make clean
	@echo ''
	@echo '#### NETTOYAGE DE MESSENGER GATEWAY WEBSOCKETS'
ifeq "$(WINDOWS)" "YES"
#	-msbuild "../messenger_gateway_websockets/win32port/win32port.sln" /t:Clean /p:Configuration=Debug
else
	-cd "../messenger_gateway_websockets/Debug" && make clean
endif
	@echo ''
	@echo '#### NETTOYAGE DE SEQUENCER'
	-cd "../sequencer/Debug" && make clean
	-rm -rf "sequencer_debug"
ifeq "$(WINDOWS)" "YES"
else
	@echo ''
	@echo '#### NOTTOYAGE DU DRIVER NXT'
	-cd "../nxt_driver/Debug" && make clean
endif

clean_release: init
	@echo ''
	@echo '## NETTOYAGE DU MODE RELEASE'
	@echo '#### NETTOYAGE DE CSIEMESSENGER'
ifeq "$(WINDOWS)" "YES"
#	-msbuild "../CSIEMessenger/CSIEMessenger/CSIEMessenger.sln" /t:Clean /p:Configuration=Release
else
	-cd "../CSIEMessenger/CSIEMessenger/CSIEMessenger/Release" && make clean
endif
	@echo ''
	@echo '#### NETTOYAGE DE MESSENGER POUR LUA'
	-cd "../messenger/Release" && make clean
	@echo ''
	@echo '#### NETTOYAGE DE MESSENGER GATEWAY WEBSOCKETS'
ifeq "$(WINDOWS)" "YES"
#	-msbuild "../messenger_gateway_websockets/win32port/win32port.sln" /t:Clean /p:Configuration=Release
else
	-cd "../messenger_gateway_websockets/Release" && make clean
endif
	@echo ''
	@echo '#### NETTOYAGE DE SEQUENCER'
	-cd "../sequencer/Release" && make clean
	-rm -rf "sequencer"
ifeq "$(WINDOWS)" "YES"
else
	@echo ''
	@echo '#### NOTTOYAGE DU DRIVER NXT'
	-cd "../nxt_driver/Release" && make clean
endif

clean: clean_release clean_debug

install_release: init
	@echo ''
	@echo '## GENERATION DU SEQUENCER'
	-mkdir "sequencer"
	-cp -rf "../sequencer/automates" "sequencer/"
	-cp -rf "../sequencer/plugins" "sequencer/"
	-cp -rf "../sequencer/sequencers" "sequencer/"
	-cp -rf "../sequencer/conf" "sequencer/"
	@echo ''
	@echo '## AJOUT DES SEQUENCEURS LUA'
	-cp -rf "../sequencers_lua/"*.lua "sequencer/sequencers"
	@echo ''
	@echo '## AJOUT DU FICHIER DE CONFIGURATION'
ifeq "$(WINDOWS)" "YES"
	-cp -f "exemple_confs/"config_win.json "sequencer/conf/config.json"
	-cp -f "exemple_confs/"config_win.lua "sequencer/conf/config.lua"
else
	-cp -f "exemple_confs/"config_linux.json "sequencer/conf/config.json"
	-cp -f "exemple_confs/"config_linux.lua "sequencer/conf/config.lua"
endif
ifeq "$(WINDOWS)" "YES"
	-cp -f "../sequencer/Release/"sequencer.exe "sequencer/"
else
	-cp -f "../sequencer/Release/"sequencer "sequencer/"
endif
	@echo ''
	@echo '## AJOUT DE SIMD'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${SIMD_LIB}/"SimD.dll "sequencer/"
	-cp -f "${SIMD_LIB}/"libSimD.dll "sequencer/"
else
	-cp -f "${SIMD_LIB}/"SimD.so "sequencer/"
	-cp -f "${SIMD_LIB}/"SimD.so* "sequencer/"
	-cp -f "${SIMD_LIB}/"libSimD.so "sequencer/"
	-cp -f "${SIMD_LIB}/"libSimD.so* "sequencer/"
endif
	@echo ''
	@echo '## AJOUT DE JSONCPP'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${JSONCPP_LIB}/"json.dll "sequencer/"
	-cp -f "${JSONCPP_LIB}/"libjson.dll "sequencer/"
else
	-cp -f "${JSONCPP_LIB}/"json.so "sequencer/"
	-cp -f "${JSONCPP_LIB}/"json.so* "sequencer/"
	-cp -f "${JSONCPP_LIB}/"libjson.so "sequencer/"
	-cp -f "${JSONCPP_LIB}/"libjson.so* "sequencer/"
endif
	@echo ''
	@echo '## AJOUT DE LUA'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${LUA_LIB}/"lua5.1.dll "sequencer/"
	-cp -f "${LUA_LIB}/"liblua5.1.dll "sequencer/"
else
	-cp -f "${LUA_LIB}/"lua5.1.so "sequencer/"
	-cp -f "${LUA_LIB}/"lua5.1.so* "sequencer/"
	-cp -f "${LUA_LIB}/"liblua5.1.so "sequencer/"
	-cp -f "${LUA_LIB}/"liblua5.1.so* "sequencer/"
endif
	@echo ''
	@echo '## AJOUT DU CSIEMESSENENGER'
ifeq "$(WINDOWS)" "YES"
	-cp -f "../CSIEMessenger/CSIEMessenger/Release/"CSIEMessenger.dll "sequencer/"
else
	-cp -f "../CSIEMessenger/CSIEMessenger/CSIEMessenger/Release/"libCSIEMessenger.so "sequencer/"
endif
	@echo ''
	@echo '## AJOUT DU MESSENENGER GATEWAY WEBSOCKETS'
ifeq "$(WINDOWS)" "YES"
	-cp -f "../messenger_gateway_websockets/win32port/Release/"messenger_gateway_websockets.dll "sequencer/sequencers/"
else
	-cp -f "../messenger_gateway_websockets/Release/"messenger_gateway_websockets.so "sequencer/sequencers/"
endif
	@echo ''
	@echo '## AJOUT DU MESSENENGER POUR LUA'
ifeq "$(WINDOWS)" "YES"
	-cp -f "../messenger/Release/"csiemessenger_c.dll "sequencer/plugins/lua/"
else
	-cp -f "../messenger/Release/"csiemessenger_c.so "sequencer/plugins/lua/"
endif
ifeq "$(WINDOWS)" "YES"
else
	@echo ''
	@echo '#### AJOUT DU DRIVER NXT'
	-cp -f "../nxt_driver/Release/"nxt_driver.so "sequencer/sequencers"
endif
	@echo ''
	@echo '## AJOUT DE l''IHM'
	-cp -rf "../ihm/" "sequencer/"
	@echo 'REPERTOIRE "sequencer" GENERE'

install_debug: init
	@echo ''
	@echo '## GENERATION DU SEQUENCER'
	-mkdir "sequencer_debug"
	-cp -rf "../sequencer/automates" "sequencer_debug/"
	-cp -rf "../sequencer/plugins" "sequencer_debug/"
	-cp -rf "../sequencer/sequencers" "sequencer_debug/"
	-cp -rf "../sequencer/conf" "sequencer_debug/"
	@echo ''
	@echo '## AJOUT DES SEQUENCEURS LUA'
	-cp -rf "../sequencers_lua/"*.lua "sequencer/sequencers"
	@echo ''
	@echo '## AJOUT DU FICHIER DE CONFIGURATION'
ifeq "$(WINDOWS)" "YES"
	-cp -f "exemple_confs/"config_win.json "sequencer_debug/conf/config.json"
	-cp -f "exemple_confs/"config_win.lua "sequencer_debug/conf/config.lua"
else
	-cp -f "exemple_confs/"config_linux.json "sequencer_debug/conf/config.json"
	-cp -f "exemple_confs/"config_linux.lua "sequencer_debug/conf/config.lua"
endif
ifeq "$(WINDOWS)" "YES"
	-cp -f "../sequencer/Debug/"sequencer.exe "sequencer_debug/"
else
	-cp -f "../sequencer/Debug/"sequencer "sequencer_debug/"
endif
	@echo ''
	@echo '## AJOUT DE SIMD'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${SIMD_LIB}/"SimD.dll "sequencer_debug/"
	-cp -f "${SIMD_LIB}/"libSimD.dll "sequencer_debug/"
else
	-cp -f "${SIMD_LIB}/"SimD.so "sequencer_debug/"
	-cp -f "${SIMD_LIB}/"SimD.so* "sequencer_debug/"
	-cp -f "${SIMD_LIB}/"libSimD.so "sequencer_debug/"
	-cp -f "${SIMD_LIB}/"libSimD.so* "sequencer_debug/"
endif
	@echo ''
	@echo '## AJOUT DE JSONCPP'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${JSONCPP_LIB}/"json.dll "sequencer_debug/"
	-cp -f "${JSONCPP_LIB}/"libjson.dll "sequencer_debug/"
else
	-cp -f "${JSONCPP_LIB}/"json.so "sequencer_debug/"
	-cp -f "${JSONCPP_LIB}/"json.so* "sequencer_debug/"
	-cp -f "${JSONCPP_LIB}/"libjson.so "sequencer_debug/"
	-cp -f "${JSONCPP_LIB}/"libjson.so* "sequencer_debug/"
endif
	@echo ''
	@echo '## AJOUT DE LUA'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${LUA_LIB}/"lua5.1.dll "sequencer_debug/"
	-cp -f "${LUA_LIB}/"liblua5.1.dll "sequencer_debug/"
else
	-cp -f "${LUA_LIB}/"lua5.1.so "sequencer_debug/"
	-cp -f "${LUA_LIB}/"lua5.1.so* "sequencer_debug/"
	-cp -f "${LUA_LIB}/"liblua5.1.so "sequencer_debug/"
	-cp -f "${LUA_LIB}/"liblua5.1.so* "sequencer_debug/"
endif
	@echo ''
	@echo '## AJOUT DU CSIEMESSENENGER'
ifeq "$(WINDOWS)" "YES"
	-cp -f "../CSIEMessenger/CSIEMessenger/Debug/"CSIEMessenger.dll "sequencer_debug/"
else
	-cp -f "../CSIEMessenger/CSIEMessenger/CSIEMessenger/Debug/"libCSIEMessenger.so "sequencer_debug/"
endif
	@echo ''
	@echo '## AJOUT DU MESSENENGER GATEWAY WEBSOCKETS'
ifeq "$(WINDOWS)" "YES"
	-cp -f "../messenger_gateway_websockets/win32port/Debug/"messenger_gateway_websockets.dll "sequencer_debug/sequencers/"
else
	-cp -f "../messenger_gateway_websockets/Debug/"messenger_gateway_websockets.so "sequencer_debug/sequencers/"
endif
	@echo ''
	@echo '## AJOUT DU MESSENENGER POUR LUA'
ifeq "$(WINDOWS)" "YES"
	-cp -f "../messenger/Debug/"csiemessenger_c.dll "sequencer_debug/plugins/lua/"
else
	-cp -f "../messenger/Debug/"csiemessenger_c.so "sequencer_debug/plugins/lua/"
endif
ifeq "$(WINDOWS)" "YES"
else
	@echo ''
	@echo '#### AJOUT DU DRIVER NXT'
	-cp -f "../nxt_driver/Debug/"nxt_driver.so "sequencer_debug/sequencers/"
endif
	@echo ''
	@echo '## AJOUT DE l''IHM'
	-cp -rf "../ihm/" "sequencer_debug/"
	@echo 'REPERTOIRE "sequencer_debug" GENERE'

install: init
	@echo ''
	@echo '## GENERATION DU SEQUENCER'
	-mkdir "sequencer"
	-cp -rf "../sequencer/automates" "sequencer/"
	-cp -rf "../sequencer/plugins" "sequencer/"
	-cp -rf "../sequencer/sequencers" "sequencer/"
	-cp -rf "../sequencer/conf" "sequencer/"
	@echo ''
	@echo '## AJOUT DU FICHIER DE CONFIGURATION'
ifeq "$(WINDOWS)" "YES"
	-cp -f "exemple_confs/"config_win_lite.json "sequencer/conf/config.json"
	-cp -f "exemple_confs/"config_win_lite.lua "sequencer/conf/config.lua"
else
	-cp -f "exemple_confs/"config_linux_lite.json "sequencer/conf/config.json"
	-cp -f "exemple_confs/"config_linux_lite.lua "sequencer/conf/config.lua"
endif
ifeq "$(WINDOWS)" "YES"
	-cp -f "../sequencer/Release/"sequencer.exe "sequencer/"
else
	-cp -f "../sequencer/Release/"sequencer "sequencer/"
endif
	@echo ''
	@echo '## AJOUT DE SIMD'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${SIMD_LIB}/"SimD.dll "sequencer/"
	-cp -f "${SIMD_LIB}/"libSimD.dll "sequencer/"
else
	-cp -f "${SIMD_LIB}/"SimD.so "sequencer/"
	-cp -f "${SIMD_LIB}/"SimD.so* "sequencer/"
	-cp -f "${SIMD_LIB}/"libSimD.so "sequencer/"
	-cp -f "${SIMD_LIB}/"libSimD.so* "sequencer/"
endif
	@echo ''
	@echo '## AJOUT DE JSONCPP'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${JSONCPP_LIB}/"json.dll "sequencer/"
	-cp -f "${JSONCPP_LIB}/"libjson.dll "sequencer/"
else
	-cp -f "${JSONCPP_LIB}/"json.so "sequencer/"
	-cp -f "${JSONCPP_LIB}/"json.so* "sequencer/"
	-cp -f "${JSONCPP_LIB}/"libjson.so "sequencer/"
	-cp -f "${JSONCPP_LIB}/"libjson.so* "sequencer/"
endif
	@echo ''
	@echo '## AJOUT DE LUA'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${LUA_LIB}/"lua5.1.dll "sequencer/"
	-cp -f "${LUA_LIB}/"liblua5.1.dll "sequencer/"
else
	-cp -f "${LUA_LIB}/"lua5.1.so "sequencer/"
	-cp -f "${LUA_LIB}/"lua5.1.so* "sequencer/"
	-cp -f "${LUA_LIB}/"liblua5.1.so "sequencer/"
	-cp -f "${LUA_LIB}/"liblua5.1.so* "sequencer/"
endif
	@echo ''
	@echo '## AJOUT DU CSIEMESSENENGER'
ifeq "$(WINDOWS)" "YES"
	-cp -f "../CSIEMessenger/CSIEMessenger/Release/"CSIEMessenger.dll "sequencer/"
else
	-cp -f "../CSIEMessenger/CSIEMessenger/CSIEMessenger/Release/"libCSIEMessenger.so "sequencer/"
endif
	@echo ''
	@echo '## AJOUT DU MESSENENGER POUR LUA'
ifeq "$(WINDOWS)" "YES"
	-cp -f "../messenger/Release/"csiemessenger_c.dll "sequencer/plugins/lua/"
else
	-cp -f "../messenger/Release/"csiemessenger_c.so "sequencer/plugins/lua/"
endif
	@echo 'REPERTOIRE "sequencer" GENERE'
	
install_debug_lite: init
	@echo ''
	@echo '## GENERATION DU SEQUENCER'
	-mkdir "sequencer_debug"
	-cp -rf "../sequencer/automates" "sequencer_debug/"
	-cp -rf "../sequencer/plugins" "sequencer_debug/"
	-cp -rf "../sequencer/sequencers" "sequencer_debug/"
	-cp -rf "../sequencer/conf" "sequencer_debug/"
	@echo ''
	@echo '## AJOUT DU FICHIER DE CONFIGURATION'
ifeq "$(WINDOWS)" "YES"
	-cp -f "exemple_confs/"config_win_lite.json "sequencer_debug/conf/config.json"
	-cp -f "exemple_confs/"config_win_lite.lua "sequencer_debug/conf/config.lua"
else
	-cp -f "exemple_confs/"config_linux_lite.json "sequencer_debug/conf/config.json"
	-cp -f "exemple_confs/"config_linux_lite.lua "sequencer_debug/conf/config.lua"
endif
ifeq "$(WINDOWS)" "YES"
	-cp -f "../sequencer/Debug/"sequencer.exe "sequencer_debug/"
else
	-cp -f "../sequencer/Debug/"sequencer "sequencer_debug/"
endif
	@echo ''
	@echo '## AJOUT DE SIMD'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${SIMD_LIB}/"SimD.dll "sequencer_debug/"
	-cp -f "${SIMD_LIB}/"libSimD.dll "sequencer_debug/"
else
	-cp -f "${SIMD_LIB}/"SimD.so "sequencer_debug/"
	-cp -f "${SIMD_LIB}/"SimD.so* "sequencer_debug/"
	-cp -f "${SIMD_LIB}/"libSimD.so "sequencer_debug/"
	-cp -f "${SIMD_LIB}/"libSimD.so* "sequencer_debug/"
endif
	@echo ''
	@echo '## AJOUT DE JSONCPP'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${JSONCPP_LIB}/"json.dll "sequencer_debug/"
	-cp -f "${JSONCPP_LIB}/"libjson.dll "sequencer_debug/"
else
	-cp -f "${JSONCPP_LIB}/"json.so "sequencer_debug/"
	-cp -f "${JSONCPP_LIB}/"json.so* "sequencer_debug/"
	-cp -f "${JSONCPP_LIB}/"libjson.so "sequencer_debug/"
	-cp -f "${JSONCPP_LIB}/"libjson.so* "sequencer_debug/"
endif
	@echo ''
	@echo '## AJOUT DE LUA'
ifeq "$(WINDOWS)" "YES"
	-cp -f "${LUA_LIB}/"lua5.1.dll "sequencer_debug/"
	-cp -f "${LUA_LIB}/"liblua5.1.dll "sequencer_debug/"
else
	-cp -f "${LUA_LIB}/"lua5.1.so "sequencer_debug/"
	-cp -f "${LUA_LIB}/"lua5.1.so* "sequencer_debug/"
	-cp -f "${LUA_LIB}/"liblua5.1.so "sequencer_debug/"
	-cp -f "${LUA_LIB}/"liblua5.1.so* "sequencer_debug/"
endif
	@echo ''
	@echo '## AJOUT DU CSIEMESSENENGER'
ifeq "$(WINDOWS)" "YES"
	-cp -f "../CSIEMessenger/CSIEMessenger/Debug/"CSIEMessenger.dll "sequencer_debug/"
else
	-cp -f "../CSIEMessenger/CSIEMessenger/CSIEMessenger/Debug/"libCSIEMessenger.so "sequencer_debug/"
endif
	@echo ''
	@echo '## AJOUT DU MESSENENGER POUR LUA'
ifeq "$(WINDOWS)" "YES"
	-cp -f "../messenger/Debug/"csiemessenger_c.dll "sequencer_debug/plugins/lua/"
else
	-cp -f "../messenger/Debug/"csiemessenger_c.so "sequencer_debug/plugins/lua/"
endif
	@echo 'REPERTOIRE "sequencer_debug" GENERE'
