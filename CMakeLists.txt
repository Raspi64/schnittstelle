cmake_minimum_required(VERSION 3.17)
project(schnittstelle)
project(schnittstelle_test)

set(CMAKE_CXX_STANDARD 14)

# gui includes
include_directories(gui/src)
include_directories(gui/src/ui)
include_directories(gui/src/ui/window)
include_directories(gui/src/ui/window/base)
include_directories(gui/lib/imgui)
include_directories(gui/lib/imgui/backends)
include_directories(gui/lib/imgui/misc)

# Schnittstelle includes
include_directories(schnittstelle/src/)
include_directories(schnittstelle/src/plugins)
include_directories(schnittstelle/src/plugins/lua)
include_directories(schnittstelle/src/plugins/basic)
include_directories(schnittstelle/lib/lua-5.4)
include_directories(schnittstelle/lib/my_basic)

add_executable(schnittstelle
        # Schnittstelle files
        src/main.cpp
        schnittstelle/src/plugins/plugins.cpp
        schnittstelle/src/plugins/lua/lua_plugin.cpp
        schnittstelle/src/plugins/lua/lua_functions.cpp
        schnittstelle/src/plugins/basic/basic_plugin.cpp
        schnittstelle/src/plugins/basic/basic_functions.cpp
        schnittstelle/src/schnitstelle.cpp
        # my_basic files
        schnittstelle/lib/my_basic/my_basic.c
        # gui files
        gui/src/Gui.cpp
        gui/src/ui/MainMenuBar.cpp
        gui/src/ui/UiElement.cpp
        gui/src/ui/window/ConsoleWindow.cpp
        gui/src/ui/window/ConsoleWindowHandler.cpp
        gui/src/ui/window/EditorWindow.cpp
        gui/src/ui/window/EditorWindowHandler.cpp
        gui/src/ui/window/GraphicWindow.cpp
        gui/src/ui/window/GraphicWindowHandler.cpp
        gui/src/ui/window/HelpWindow.cpp
        gui/src/ui/window/HelpWindowHandler.cpp
        gui/src/ui/window/ShutdownDialogWindow.cpp
        gui/src/ui/window/base/Window.cpp
        gui/src/ui/window/base/WindowHandler.cpp
        # DearImGUI library files
        gui/lib/imgui/imgui.cpp
        gui/lib/imgui/imgui_draw.cpp
        gui/lib/imgui/imgui_demo.cpp
        gui/lib/imgui/imgui_widgets.cpp
        gui/lib/imgui/backends/imgui_impl_opengl2.cpp
        gui/lib/imgui/backends/imgui_impl_sdl.cpp
        )


add_executable(schnittstelle_test
        schnittstelle/src/main.cpp
        # Schnittstelle files
        schnittstelle/src/plugins/plugins.cpp
        schnittstelle/src/plugins/lua/lua_plugin.cpp
        schnittstelle/src/plugins/lua/lua_functions.cpp
        schnittstelle/src/plugins/basic/basic_plugin.cpp
        schnittstelle/src/plugins/basic/basic_functions.cpp
        schnittstelle/src/schnitstelle.cpp
        # my_basic files
        schnittstelle/lib/my_basic/my_basic.c
        )

# Link pthread
target_link_libraries(schnittstelle "-lpthread")
target_link_libraries(schnittstelle_test "-lpthread")

# Link SDL2
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
target_link_libraries(schnittstelle SDL2::Main)
target_link_libraries(schnittstelle "-lGL")

# Link Freetype2 font
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIR_ft2build})
target_link_libraries(schnittstelle ${FREETYPE_LIBRARIES})

# Link Lua 5.4
add_library(lualib SHARED IMPORTED)
set_property(TARGET lualib PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/schnittstelle/lib/lua-5.4/liblua54.so")
target_link_libraries(schnittstelle "-ldl" lualib)
target_link_libraries(schnittstelle_test "-ldl" lualib)

add_compile_options("-Wall -Wextra -pedantic -Werror")
