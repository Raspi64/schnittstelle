#ifndef SCHNITTSTELLE_SCHNITSTELLE_H
#define SCHNITTSTELLE_SCHNITSTELLE_H

#include <future>

typedef void (*print_function)(const char *);

typedef void (*draw_function)(int x, int y, int red, int green, int blue, int alpha, int size);

typedef void (*clear_function)();

enum Status {
    NOT_STARTED, // No program has been executed so far
    LOADING, // The user-program is currently loading/parsing
    LOAD_ERROR, // The user-program could not be loaded
    RUNNING, // The user-program is currently running
    RUN_ERROR, // There was an error when running the user-program
    COMPLETED_OK, // Program has exited successfully
};

enum LANG {
    BASIC,
    LUA,
};

void sc_register_print_function(print_function);

void sc_register_draw_function(draw_function);

void sc_register_clear_function(clear_function);

void sc_start_script(LANG lang, const char *script);

Status sc_get_status();

void sc_kill_current_task();

const char *sc_get_status_message();

#endif //SCHNITTSTELLE_SCHNITSTELLE_H
