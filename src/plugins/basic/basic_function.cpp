#include <cstdio>
#include <cstdlib>
#include "basic_function.h"


namespace basic_plugin {
    int basic_fabian(struct mb_interpreter_t *bas, void **ptr) {
        printf("Fabian ist der BESTE\n");
        return MB_FUNC_OK;
    }

    int basic_openTerminal(struct mb_interpreter_t *bas, void **ptr) {
        system("xfce4-terminal");
        return MB_FUNC_OK;
    }

    int basic_echo(struct mb_interpreter_t *bas, void **ptr) {
        printf("Echo\n");
        return MB_FUNC_OK;
    }
}
