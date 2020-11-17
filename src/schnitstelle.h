#ifndef SCHNITTSTELLE_SCHNITSTELLE_H
#define SCHNITTSTELLE_SCHNITSTELLE_H

typedef void (*print_function)(const char *);

enum LANG{
    BASIC,
    LUA
};

void sc_init();
void sc_exit();
void sc_replace_print_function(print_function);
int sc_exec_script(LANG lang, const char * script);

#endif //SCHNITTSTELLE_SCHNITSTELLE_H
