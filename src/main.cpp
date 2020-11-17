
#include <cstdio>
#include "schnitstelle.h"

void my_print(const char * string);
int main() {
    sc_init();
    sc_replace_print_function(my_print);
    printf("\n");
    sc_exec_script(BASIC,"print \"Hello from Basic\";");
    printf("\n");
    sc_exec_script(LUA,"print(\"Hello from Lua\")");
    printf("\n");
    sc_exit();
}


void my_print(const char *string) {
    printf("\"%s\"",string);
}
