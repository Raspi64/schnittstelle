
#include <cstdio>
#include "schnitstelle.h"
#include "my_basic.h"
#include "lua_plugin.h"

static struct State {
    struct mb_interpreter_t *bas;
} state;


static void lua_print(const char *string) {
    printf("%s\n", string);
}

void sc_init(){
    mb_init();
    mb_open(&state.bas);
    mb_set_printer(state.bas, printf);

    lua_plugin::plugin_init();
    lua_plugin::register_print_function(lua_print);
}


int sc_exec_script(LANG lang, const char *script) {
    switch (lang) {
        case BASIC:
            mb_load_string(state.bas, script, true);
            return mb_run(state.bas, true);
        case LUA:
            return lua_plugin::exec_script(script);
    }
}


void sc_exit() {
    mb_close(&state.bas);
    mb_dispose();
    lua_plugin::plugin_exit();
}
