#ifndef LUATEST_LUA_PLUGIN_H
#define LUATEST_LUA_PLUGIN_H

#include "plugins.h"

namespace lua_plugin {

    void plugin_init();

    void plugin_exit();

    int load_script(const char *lua_script);

    int exec_script();

    void mouse_event(int x, int y, MouseEvent::Type type);

    void keyboard_event(char key, KeyboardEvent::Type type);
}

#endif //LUATEST_LUA_PLUGIN_H
