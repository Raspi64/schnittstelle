
#include <cstdio>
#include <cstdlib>
#include "lua_plugin.h"
#include "lua_functions.h"

namespace lua_plugin {
    int lua_print(lua_State *state) {
        char *return_string;
        asprintf(&return_string, "");

        int top = lua_gettop(state);
        for (int i = 1; i <= top; i++) {  /* repeat for each level */
            int t = lua_type(state, i);

            char *string_value;
            switch (t) {
                case LUA_TSTRING:  /* strings */
                    asprintf(&string_value, "%s", lua_tostring(state, i));
                    break;

                case LUA_TBOOLEAN:  /* booleans */
                    asprintf(&string_value, lua_toboolean(state, i) ? "true" : "false");
                    break;

                case LUA_TNUMBER:  /* numbers */
                    asprintf(&string_value, "%g", lua_tonumber(state, i));
                    break;

                default:  /* other values */
                    asprintf(&string_value, "%s", lua_typename(state, t));
                    break;

            }

            char *temp;
            if (i < top) {
                asprintf(&temp, "%s%s\t", return_string, string_value);
            } else {
                asprintf(&temp, "%s%s", return_string, string_value);
            }
            free(return_string);
            free(string_value);
            return_string = temp;
        }

        if (plugins::print_function_replacement != nullptr) {
            plugins::print_function_replacement(return_string);
        }
        return 0;
    }
};