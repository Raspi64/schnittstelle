#include <stdio.h>
#include <stdlib.h>
#include "basic_function.h"


namespace basic_plugin {
    int basic_fabian(struct mb_interpreter_t * bas, void** ptr){
        printf("Fabian ist der BESTE");
    }

    int basic_openTerminal(struct mb_interpreter_t * bas, void** ptr){
        system("xfce4-terminal");
    }

    int basic_echo(struct mb_interpreter_t * bas, void** ptr){
        printf("Echo");
    }
}





