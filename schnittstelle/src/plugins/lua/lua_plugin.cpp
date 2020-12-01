#include <cstdlib>
#include <cstring>
#include "lua_plugin.h"
#include "lua_functions.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace lua_plugin {
    static lua_State *L;

    static void set_error_message(const char *error_message);

    static void replace_function_in_table(const char *table, const char *field, lua_CFunction function) {
        lua_getglobal(L, table);
        lua_pushstring(L, field);
        lua_pushcfunction(L, function);
        lua_settable(L, -3);
    }

    void plugin_init() {
        L = luaL_newstate();
        luaopen_base(L);
        // luaopen_package(L); // blocked
        luaopen_coroutine(L);
        luaopen_table(L);
        // luaopen_io(L); // blocked
        luaopen_os(L);
        luaopen_string(L);
        luaopen_math(L);
        luaopen_utf8(L);
        // luaopen_debug(L); // blocked

        lua_register(L, "print", lua_print);
        replace_function_in_table("os", "exit", lua_function_not_allowed);
        replace_function_in_table("io", "read", lua_function_not_allowed);
        replace_function_in_table("io", "write", lua_function_not_allowed);

        replace_function_in_table("base", "collectgarbage", lua_function_not_allowed);
        replace_function_in_table("base", "dofile", lua_function_not_allowed);
        replace_function_in_table("base", "load", lua_function_not_allowed);
        replace_function_in_table("base", "loadfile", lua_function_not_allowed);
        replace_function_in_table("base", "require", lua_function_not_allowed);
        replace_function_in_table("os", "execute", lua_function_not_allowed);
        replace_function_in_table("os", "remove", lua_function_not_allowed);
        replace_function_in_table("os", "rename", lua_function_not_allowed);
        replace_function_in_table("os", "setlocale", lua_function_not_allowed);
        replace_function_in_table("os", "tmpname", lua_function_not_allowed);
        lua_register(L,"draw", lua_draw);
        lua_register(L,"clear", lua_clear);
    }

    void plugin_exit() {
        lua_close(L);
    }

    int load_script(const char *lua_script) {
        int load_stat = luaL_loadbuffer(L, lua_script, strlen(lua_script), lua_script);

        if (load_stat != LUA_OK) {
            set_error_message(lua_tostring(L, -1));
        }
        return load_stat;
    }

    int exec_script() {
        int exec_stat = lua_pcall(L, 0, 0, 0);

        if (exec_stat != LUA_OK) {
            set_error_message(lua_tostring(L, -1));
        }
        return exec_stat;
    }

    static void set_error_message(const char *error_message) {
        char *old_error_buffer = plugins::last_error_buffer;
        plugins::last_error_buffer = nullptr;
        if (old_error_buffer != nullptr) free(old_error_buffer);
        char *new_error_buffer;

        asprintf(&new_error_buffer, "%s", error_message);
        plugins::last_error_buffer = new_error_buffer;
    }
}
