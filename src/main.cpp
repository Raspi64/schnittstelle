
#include <cstdio>
#include "schnitstelle.h"

void my_print(const char * string);
int main() {
    sc_init();
    sc_replace_print_function(my_print);
    sc_exec_script(LUA,"print(\"Hello from Lua\")");
    sc_exec_script(BASIC,"print \"Hello from Basic\";");
    sc_exit();
}


void my_print(const char *string) {
    printf("From Interpreter: %s\n",string);
}
