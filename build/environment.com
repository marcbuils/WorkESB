echo "###############################################"
echo "# WorkESB Environment Variable Initialisation #"
echo "###############################################"
echo "."
WESB_ROOT=$PWD/..
WESBMESSENGER_ROOT=$WESB_ROOT/WESBMessenger/WESBMessenger/WESBMessenger
BOOST_ROOT=$WESB_ROOT/build/libs/boost_1_48_0
BOOST_INCLUDE_DIR=$BOOST_ROOT/boost
BOOST_LIB_DIR=$BOOST_ROOT/lib
JSONCPP_ROOT=$WESB_ROOT/build/libs/jsoncpp-src-0.5.0
JSONCPP_LIB=$JSONCPP_ROOT
LUA_ROOT=$WESB_ROOT/build/libs/lua52
LUA_LIB=$LUA_ROOT
OSPL_HOME=$WESB_ROOT/build/libs/HDE/arm9.linux2.6
SIMD_INSTALL_DIR=$WESB_ROOT/build/libs/simd-cxx
SIMD_LIB=$SIMD_INSTALL_DIR/build/src/dds/Release
export WESB_ROOT WESBMESSENGER_ROOT BOOST_ROOT BOOST_INCLUDE_DIR BOOST_LIB_DIR JSONCPP_ROOT JSONCPP_LIB LUA_ROOT LUA_LIB OSPL_HOME SIMD_INSTALL_DIR SIMD_LIB 
