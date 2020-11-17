
#include <cstdio>
#include <cstdlib>
#include "schnitstelle.h"
#include "my_basic.h"
#include "lua_plugin.h"

static struct State {
    struct mb_interpreter_t *bas;
    print_function printer;
} state;


static void default_lua_print(const char *string) {
    printf("%s\n", string);
}

static int print(const char *__restrict format, ...) {
    va_list args;
    if (state.printer != nullptr) {
        char *output;
        asprintf(&output, format, args);
        state.printer(output);
        free(output);
    } else {
        printf(format, args);
    }
    return 0;
}

void sc_init() {
    mb_init();
    mb_open(&state.bas);
    mb_set_printer(state.bas, printf);

    lua_plugin::plugin_init();
    lua_plugin::register_print_function(default_lua_print);
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

void sc_replace_print_function(print_function print) {
    state.printer = print;
    lua_plugin::register_print_function(print);
}

void sc_exit() {
    mb_close(&state.bas);
    mb_dispose();
    lua_plugin::plugin_exit();
}
