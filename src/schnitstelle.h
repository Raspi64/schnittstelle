#ifndef SCHNITTSTELLE_SCHNITSTELLE_H
#define SCHNITTSTELLE_SCHNITSTELLE_H

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

Status sc_exec_script(LANG lang, const char *script);

const char *sc_get_last_error();

#endif //SCHNITTSTELLE_SCHNITSTELLE_H
