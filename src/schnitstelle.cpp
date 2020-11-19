
#include <cstdio>
#include <cstdlib>
#include <thread>
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
}


static Status exec_basic_script(const char *script) {
    basic_plugin::plugin_init();
    plugins::print_function_replacement = our_print;

    if (basic_plugin::load_script(script) != 0) {
        replace_error_message(plugins::last_error_buffer);
        return SYNTAX_ERROR;
    }

    if (basic_plugin::exec_script() != 0) {
        replace_error_message(plugins::last_error_buffer);
        return RUNTIME_ERROR;
    }

    basic_plugin::plugin_exit();
    return OK;
}

static Status exec_lua_script(const char *script) {
    lua_plugin::plugin_init();
    plugins::print_function_replacement = our_print;

    if (lua_plugin::load_script(script) != 0) {
        replace_error_message(plugins::last_error_buffer);
        return SYNTAX_ERROR;
    }

    if (lua_plugin::exec_script() != 0) {
        replace_error_message(plugins::last_error_buffer);
        return RUNTIME_ERROR;
    }

    lua_plugin::plugin_exit();
    return OK;
}

static Status exec_script(LANG lang, char *script){
    Status status;
    switch (lang) {
        case BASIC:
            status = exec_basic_script(script);
            break;
        case LUA:
        default:
            status = exec_lua_script(script);
    }
    free(script);
    return status;
}

std::future<Status> sc_exec_script(LANG lang, const char *script) {
    // copy script
    char *script_copy;
    asprintf(&script_copy, "%s", script);

    // create future
    return std::async(std::launch::async, [lang, script_copy] { return exec_script(lang, script_copy); });
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
}
