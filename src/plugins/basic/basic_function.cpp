#include <stdio.h>
#include <stdlib.h>
#include "basic_function.h"


namespace basic_plugin {
    int basic_fabian(struct mb_interpreter_t *bas, void **ptr) {
        printf("Fabian ist der BESTE\n");
        return 0;
    }

    int basic_openTerminal(struct mb_interpreter_t *bas, void **ptr) {
        system("xfce4-terminal");
        return 0;
    }

    int basic_echo(struct mb_interpreter_t *bas, void **ptr) {
        printf("Echo\n");
        return 0;
    }
}
