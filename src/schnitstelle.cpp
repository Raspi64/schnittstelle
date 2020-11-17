
#include <cstdio>
#include <cstdlib>
#include "schnitstelle.h"
#include "lua_plugin.h"
#include "basic_plugin.h"

static void replace_error_message(const char *new_message);

static struct State {
    print_function printer = nullptr;
    char *error_message = nullptr;
} state;

static void our_print(const char *string) {
    char *output;
    asprintf(&output, "%s\n", string);
    if (state.printer != nullptr) {
        state.printer(output);
    } else {
        printf("%s", output);
    }
    free(output);
}

void sc_init() {
    basic_plugin::plugin_init();
    basic_plugin::register_print_function(our_print);

    lua_plugin::plugin_init();
    lua_plugin::register_print_function(our_print);
}

Status sc_exec_script(LANG lang, const char *script) {
    int load_err = 0;
    int exec_err = 0;

    switch (lang) {
        case BASIC:
            load_err = basic_plugin::load_script(script);
            break;
        case LUA:
            load_err = lua_plugin::load_script(script);
            break;
    }

    if (load_err != 0) {
        switch (lang) {
            case BASIC:
                replace_error_message(basic_plugin::get_last_error());
                break;
            case LUA:
                replace_error_message(lua_plugin::get_last_error());
                break;
        }
        return SYNTAX_ERROR;
    }

    switch (lang) {
        case BASIC:
            exec_err = basic_plugin::exec_script();
            break;
        case LUA:
            exec_err = lua_plugin::exec_script();
            break;
    }

    if (exec_err != 0) {
        switch (lang) {
            case BASIC:
                replace_error_message(basic_plugin::get_last_error());
                break;
            case LUA:
                replace_error_message(lua_plugin::get_last_error());
                break;
        }
        return RUNTIME_ERROR;
    }
    return OK;
}


void replace_error_message(const char *new_message) {
    if (state.error_message != nullptr) {
        free(state.error_message);
        state.error_message = nullptr;
    }

    char *output;
    asprintf(&output, "%s", new_message);
    state.error_message = output;
}

const char *sc_get_last_error() {
    return state.error_message;
}

void sc_replace_print_function(print_function print) {
    state.printer = print;
}

void sc_exit() {
    basic_plugin::plugin_exit();
    lua_plugin::plugin_exit();
}
