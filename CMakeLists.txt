cmake_minimum_required(VERSION 3.17)
project(schnittstelle)
project(schnittstelle_test)

set(CMAKE_CXX_STANDARD 14)

add_library(lualib SHARED IMPORTED)
set_property(TARGET lualib PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/lua-5.4/liblua54.so")


include_directories(src/plugins)
include_directories(src/plugins/lua)
include_directories(src/plugins/basic)
include_directories(lib/my_basic)
include_directories(lib/lua-5.4/include)
include_directories(src)

add_library(schnittstelle
        src/schnitstelle.h
        src/schnitstelle.cpp
        src/plugins/plugins.cpp
        src/plugins/lua/lua_plugin.cpp
        src/plugins/lua/lua_functions.cpp
        src/plugins/basic/basic_plugin.cpp
        src/plugins/basic/basic_functions.cpp
        lib/my_basic/my_basic.c
        )

add_executable(schnittstelle_test
        src/main.cpp
        src/plugins/plugins.cpp
        src/plugins/lua/lua_plugin.cpp
        src/plugins/lua/lua_functions.cpp
        src/plugins/basic/basic_plugin.cpp
        src/plugins/basic/basic_functions.cpp
        src/schnitstelle.cpp
        lib/my_basic/my_basic.c
        )

target_link_libraries(schnittstelle lualib "-ldl" "-lpthread")
target_link_libraries(schnittstelle_test lualib "-ldl" "-lpthread")
