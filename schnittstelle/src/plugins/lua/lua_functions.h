#ifndef SCHNITTSTELLE_LUA_FUNCTIONS_H
#define SCHNITTSTELLE_LUA_FUNCTIONS_H

extern "C" {
#include "lua.h"
}

namespace lua_plugin {
    int lua_os_exit(lua_State *state);

    int lua_io_read(lua_State *state);

    int lua_io_write(lua_State *state);

    int lua_print(lua_State *state);

    int lua_draw(lua_State *state);

    int lua_clear(lua_State *state);
}

#endif //SCHNITTSTELLE_LUA_FUNCTIONS_H
