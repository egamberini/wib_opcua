## ----------------------------------------------------
## Please see Documentation/quasarBuildSystem.html for
## information how to use this file.
## ----------------------------------------------------

#find_package(Protobuf REQUIRED)

set(CUSTOM_SERVER_MODULES WIBProto )
set(EXECUTABLE OpcUaServer)
set(SERVER_INCLUDE_DIRECTORIES /usr/include/protobuf3/ )
set(SERVER_LINK_LIBRARIES protobuf zmq)
set(SERVER_LINK_DIRECTORIES /usr/lib64/protobuf3 )

##
## If ON, in addition to an executable, a shared object will be created.
##
set(BUILD_SERVER_SHARED_LIB OFF)

##
## Add here any additional boost libraries needed with their canonical name
## examples: date_time atomic etc.
## Note: boost paths are resolved either from $BOOST_ROOT if defined or system paths as fallback
##
set(ADDITIONAL_BOOST_LIBS )
