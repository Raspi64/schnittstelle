#ifndef SCHNITTSTELLE_SCHNITSTELLE_H
#define SCHNITTSTELLE_SCHNITSTELLE_H

enum LANG{
    BASIC,
    LUA
};

void sc_init();
void sc_exit();
int sc_exec_script(LANG lang, const char * script);

#endif //SCHNITTSTELLE_SCHNITSTELLE_H
