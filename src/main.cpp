
#include <cstdio>
#include "schnitstelle.h"

void my_print(const char *string);

void run_and_print_error(const LANG &lang, const char *script);

int main() {
    sc_init();
    sc_replace_print_function(my_print);
    printf("\n");
    run_and_print_error(BASIC, "print \"Hello from Basic\";");
    run_and_print_error(BASIC, "print \"Wikibooks coolness quotient: , RND, \"%\n\"");
    run_and_print_error(BASIC, "print \"Hello from Basic\";");
    printf("\n");
    run_and_print_error(LUA, "print(\"Hello from Lua\")");
    run_and_print_error(LUA, "print(\"AAA)");
    run_and_print_error(LUA, "print(\"Hello from Lua\")");
    printf("\n");
    sc_exit();
}

void run_and_print_error(const LANG &lang, const char *script) {
    if (sc_exec_script(lang, script) != 0)
        printf("%s\n", sc_get_last_error());
}


void my_print(const char *string) {
    printf("%s", string);
}
