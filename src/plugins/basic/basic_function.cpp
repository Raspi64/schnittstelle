#include <cstdlib>
#include <stdio.h>
#include "basic_function.h"
#include "my_basic.h"


namespace basic_plugin {
    int basic_maximum(struct mb_interpreter_t *bas, void **ptr) {
        int result = MB_FUNC_OK;
        int m = 0;
        int n = 0;

        mb_check(mb_attempt_open_bracket(bas, ptr));
        mb_check(mb_pop_int(bas, ptr, &m));
        mb_check(mb_pop_int(bas, ptr, &n));
        mb_check(mb_attempt_close_bracket(bas, ptr));

        int r = n;
        if(m > n)
            r = m;

        mb_check(mb_push_int(bas, ptr, r));

        printf("param_1 %i\n", m);
        printf("param_2 %i\n",n);

        return result;
    }

    int basic_openTerminal(struct mb_interpreter_t *bas, void **ptr) {
        system("xfce4-terminal");
        return MB_FUNC_OK;
    }

    int basic_echo(struct mb_interpreter_t *bas, void **ptr) {
        char* s;

        mb_check(mb_attempt_open_bracket(bas, ptr));
        mb_check(mb_pop_string(bas, ptr, &s));
        mb_check(mb_attempt_close_bracket(bas, ptr));

        printf("%s \n", s);

        return MB_FUNC_OK;
    }
}
