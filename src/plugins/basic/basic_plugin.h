#ifndef SCHNITTSTELLE_BASIC_PLUGIN_H
#define SCHNITTSTELLE_BASIC_PLUGIN_H

#include "plugins.h"

namespace basic_plugin {

    void plugin_init();

    void plugin_exit();

    int load_script(const char *lua_script);

    int exec_script();

    void mouse_event(int x, int y, MouseEvent::Type type);

    void keyboard_event(char key, KeyboardEvent::Type type);
}

#endif //SCHNITTSTELLE_BASIC_PLUGIN_H
