
#include <cstdio>
#include "schnitstelle.h"
#include <unistd.h>

void my_print(const char *string);

void run_and_print_error(const LANG &lang, const char *script);

int main() {
    sc_register_print_function(my_print);
    printf("\n\nBasic 1:\n");
    run_and_print_error(BASIC, "I = BASICMAXIMUM(2,3)\n PRINT I\n");
    usleep(100000); // 100 ms
    printf("\n\nBasic 2:\n");
    run_and_print_error(BASIC, "BASICECHO(\"Hello World\")\n");
    usleep(100000); // 100 ms

    printf("\n\nLua 1:\n");
    run_and_print_error(
            LUA,
            "print('Start 2')\n"
            "function sleep(n)\n"
            "  os.execute(\"sleep \" .. tonumber(n))\n"
            "end\n"
            "sleep(2)\n"
            "print('End 2')\n"
    );
    usleep(100000); // 100 ms

    printf("\n\nLua 2:\n");
    sc_start_script(LUA, "os.execute(\"sleep \" .. 2)\n");
    usleep(100000); // 100 ms
    sc_start_script(LUA, "os.execute(\"sleep \" .. 2)\n");
    usleep(100000); // 100 ms

    printf("\n\nLua 3:\n");
    run_and_print_error(
            LUA,
            "function sleep(n)\nos.execute(\"sleep \" .. tonumber(n))\nend\n"
            "print('Start 1')\n"
            "sleep(0.2)\n"
            "print('End 1')\n"
    );
    usleep(100000); // 100 ms
}

void run_and_print_error(const LANG &lang, const char *script) {
    sc_start_script(lang, script);

    int i = 0;
    // wait for 1 second to finish
    for (; i < 1000 && (sc_get_status() == NOT_STARTED || sc_get_status() == LOADING || sc_get_status() == RUNNING); ++i) {
        usleep(1000); // 1 ms
    }
    if (sc_get_status_message() != nullptr)printf("Status: %s\n", sc_get_status_message());

    switch (sc_get_status()) {
        case COMPLETED_OK:
            printf("Exec: OK!\n");
            break;
        case LOAD_ERROR:
            printf("Load: Error!\n");
            break;
        case RUN_ERROR:
            printf("Exec: Error!\n");
            printf("Status: %s\n", sc_get_status_message());
            break;
        case NOT_STARTED:
        case LOADING:
        case RUNNING:
            printf("Timeout: ");
            sc_kill_current_task();
            break;
    }
    printf("Running took %d ms.\n", i);
}


void my_print(const char *string) {
    char *out;
    asprintf(&out, "%s", string);

    for (int i = 0; out[i] != '\0'; i++) {
        if (out[i] == '\n') {
            out[i] = '\t';
        }
    }
    printf("Print: \"%s\"\n", out);
    free(out);
}
