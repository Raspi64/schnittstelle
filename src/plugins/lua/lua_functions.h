#ifndef SCHNITTSTELLE_LUA_FUNCTIONS_H
#define SCHNITTSTELLE_LUA_FUNCTIONS_H

extern "C" {
#include "lua.h"
}

namespace lua_plugin {
    int lua_print(lua_State *state);
}

#endif //SCHNITTSTELLE_LUA_FUNCTIONS_H
