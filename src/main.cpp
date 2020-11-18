
#include <cstdio>
#include "schnitstelle.h"

void my_print(const char *string);

void run_and_print_error(const LANG &lang, const char *script);

int main() {
    sc_init();
    sc_replace_print_function(my_print);
    printf("\n");
    run_and_print_error(BASIC, "FABIAN\n");
    run_and_print_error(BASIC, "RND;");

    sc_exit();
}

void run_and_print_error(const LANG &lang, const char *script) {
    if (sc_exec_script(lang, script) != 0) {
        printf("%s\n\n", sc_get_last_error());
    } else {
        printf("Exec: OK!\n\n");
    }
}


void my_print(const char *string) {
    printf("%s", string);
}
