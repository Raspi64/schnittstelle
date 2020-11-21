
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include "schnitstelle.h"
#include "plugins.h"
#include "lua_plugin.h"
#include "basic_plugin.h"

static void replace_status(Status new_status, const char *new_message);


static print_function printer = nullptr;
static char *status_message = nullptr;
static Status status = NOT_STARTED;
static pthread_t exec_thread;
static bool is_running = false;

static void our_print(const char *string) {
    char *output;
    asprintf(&output, "%s\n", string);
    if (printer != nullptr) {
        printer(output);
    } else {
        printf("%s", output);
    }
    free(output);
}

static void exec_basic_script(const char *script) {
    replace_status(LOADING, "Loading...");
    basic_plugin::plugin_init();
    plugins::print_function_replacement = our_print;

    if (basic_plugin::load_script(script) != 0) {
        replace_status(LOAD_ERROR, plugins::last_error_buffer);
    }

    replace_status(RUNNING, "Running...");
    if (basic_plugin::exec_script() != 0) {
        replace_status(RUN_ERROR, plugins::last_error_buffer);
    }

    basic_plugin::plugin_exit();
    replace_status(COMPLETED_OK, "Done!");
}

static void exec_lua_script(const char *script) {
    replace_status(LOADING, "Loading...");
    lua_plugin::plugin_init();
    plugins::print_function_replacement = our_print;

    if (lua_plugin::load_script(script) != 0) {
        replace_status(LOAD_ERROR, plugins::last_error_buffer);
    }

    replace_status(RUNNING, "Running...");
    if (lua_plugin::exec_script() == 0) {
        replace_status(COMPLETED_OK, "Done!");
    } else {
        replace_status(RUN_ERROR, plugins::last_error_buffer);
    }

    lua_plugin::plugin_exit();
}

struct StartParams {
    LANG lang;
    char *script;
};

void *exec_script(void *params_void) {
    auto *params = (StartParams *) params_void;

    switch (params->lang) {
        case BASIC:
            exec_basic_script(params->script);
            break;
        case LUA:
        default:
            exec_lua_script(params->script);
            break;
    }
    free(params->script);
    is_running = false;
    return nullptr;
}

void sc_start_script(LANG lang, const char *script) {
    sc_kill_current_task();

    // copy params
    char *script_copy;
    asprintf(&script_copy, "%s", script);

    auto *params = (StartParams *) malloc(sizeof(StartParams));
    params->lang = lang;
    params->script = script_copy;

    is_running = true;
    // create and start thread
    pthread_create(&exec_thread, nullptr, exec_script, params);
}

static void replace_status(Status new_status, const char *message) {
    // save old message
    char *old_message = nullptr;
    if (status_message != nullptr) {
        old_message = status_message;
    }

    // copy new message
    char *new_message;
    asprintf(&new_message, "%s", message);

    // replace
    status = new_status;
    status_message = new_message;

    // free old message
    if (old_message != nullptr) {
        free(old_message);
    }
}

const char *sc_get_status_message() {
    return status_message;
}

void sc_register_print_function(print_function func) {
    printer = func;
}

void sc_register_draw_function(draw_function func) {
    plugins::draw_function_value = func;
}

void sc_register_clear_function(clear_function func) {
    plugins::clear_function_value = func;
}

Status sc_get_status() {
    return status;
}

void sc_kill_current_task() {
    if (is_running) {
        printf("Killing...");
        pthread_cancel(exec_thread);
        pthread_join(exec_thread, nullptr);
        is_running = false;
        printf("Killed!\n");
    }
}
