@echo off
echo ###############################################
echo # WorkESB Environment Variable Initialisation #
echo ###############################################
echo .

set WESB_ROOT=%~dp0..
set WESBMESSENGER_ROOT=%WESB_ROOT%\WESBMessenger\WESBMessenger\WESBMessenger
set BOOST_ROOT=%WESB_ROOT%\build\libs\boost_1_48_0
set BOOST_INCLUDE_DIR=%BOOST_ROOT%\boost
set BOOST_LIB_DIR=%BOOST_ROOT%\lib
set JSONCPP_ROOT=%WESB_ROOT%\build\libs\jsoncpp-src-0.5.0
set JSONCPP_LIB=%JSONCPP_ROOT%
set LUA_ROOT=%WESB_ROOT%\build\libs\lua-5.2.1
set LUA_LIB=%LUA_ROOT%
set OSPL_HOME=%WESB_ROOT%\build\libs\HDE\x86.win32
set SIMD_INSTALL_DIR=%WESB_ROOT%\build\libs\simd-cxx
set SIMD_LIB=%SIMD_INSTALL_DIR%\build\src\dds\Release
@echo on

