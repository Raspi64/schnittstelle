
#include <cstdio>
#include <cstdlib>
#include "schnitstelle.h"
#include "my_basic.h"
#include "lua_plugin.h"

static struct State {
    struct mb_interpreter_t *bas;
    print_function printer;
} state;


static void lua_print(const char *string) {
    char *output;
    asprintf(&output, "%s\n", string);
    state.printer(output);
    free(output);
}

static int basic_print(const char * format, ...) {
    va_list args;
    va_start(args, format);
    char* string = va_arg(args, char*);
    if (state.printer != nullptr) {
        char *output;
        asprintf(&output, format, string);
        state.printer(output);
        free(output);
    } else {
        printf(format, string);
    }
    va_end(args);
    return 0;
}

void sc_init() {
    mb_init();
    mb_open(&state.bas);
    mb_set_printer(state.bas, basic_print);

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

void sc_replace_print_function(print_function print) {
    state.printer = print;
}

void sc_exit() {
    mb_close(&state.bas);
    mb_dispose();
    lua_plugin::plugin_exit();
}
