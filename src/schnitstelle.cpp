
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include "schnitstelle.h"
#include "my_basic.h"
#include "lua_plugin.h"

static void replace_error_message(const char *new_message);


const char *format_error_message();

static struct State {
    struct mb_interpreter_t *bas = nullptr;
    print_function printer = nullptr;
    char *error_message = nullptr;
} state;

static void lua_print(const char *string) {
    char *output;
    asprintf(&output, "%s\n", string);
    state.printer(output);
    free(output);
}

static int basic_print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *string = va_arg(args, char*);
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
}

Status sc_exec_script(LANG lang, const char *script) {
    int load_err = 0;
    int exec_err = 0;

    switch (lang) {
        case BASIC:
            mb_reset(&state.bas, true);
            load_err = mb_load_string(state.bas, script, false);
            break;
        case LUA:
            lua_plugin::plugin_init();
            lua_plugin::register_print_function(lua_print);
            load_err = lua_plugin::load_script(script);
            break;
    }

    if (load_err != 0) {
        const char *error;
        switch (lang) {
            case BASIC:
                error = format_error_message();
                replace_error_message(error);
                free((void *) error);
                break;
            case LUA:
                replace_error_message(lua_plugin::get_last_error());
                break;
        }
        return SYNTAX_ERROR;
    }

    switch (lang) {
        case BASIC:
            exec_err = mb_run(state.bas, true);
            break;
        case LUA:
            exec_err = lua_plugin::exec_script();
            lua_plugin::plugin_exit();
            break;
    }

    if (exec_err != 0) {
        const char *error;
        switch (lang) {
            case BASIC:
                error = format_error_message();
                replace_error_message(error);
                free((void *) error);
                break;
            case LUA:
                replace_error_message(lua_plugin::get_last_error());
                break;
        }
        return RUNTIME_ERROR;
    }
    return OK;
}

const char *format_error_message() {
    const char *file;
    int pos;
    unsigned short row, col;
    mb_error_e error = mb_get_last_error(state.bas, &file, &pos, &row, &col);
    char *output;

    asprintf(&output, "Error: %s at line %d:%d", mb_get_error_desc(error), row, col);
    return output;
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
    mb_close(&state.bas);
    mb_dispose();
}
