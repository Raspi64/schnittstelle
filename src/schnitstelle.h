#ifndef SCHNITTSTELLE_SCHNITSTELLE_H
#define SCHNITTSTELLE_SCHNITSTELLE_H

#include <future>

typedef void (*print_function)(const char *);

enum Status {
    OK,
    SYNTAX_ERROR,
    RUNTIME_ERROR,
};

enum LANG {
    BASIC,
    LUA,
};

void sc_init();

void sc_exit();

void sc_replace_print_function(print_function);

std::future<Status> sc_exec_script(LANG lang, const char *script);

bool is_running();

void kill_current_task();

const char *sc_get_last_error();

#endif //SCHNITTSTELLE_SCHNITSTELLE_H
