
#include <cstdio>
#include "schnitstelle.h"

void my_print(const char *string);

void run_and_print_error(const LANG &lang, const char *script);

int main() {
    sc_init();
    sc_replace_print_function(my_print);
    printf("\n");
    run_and_print_error(BASIC, "I = BASICMAXIMUM(2,3)\n PRINT I\n");
    run_and_print_error(BASIC, "BASICECHO(\"Hello World\")\n");

    run_and_print_error(LUA,"print('Start 4')\n"
                            "function sleep(n)\n"
                            "  os.execute(\"sleep \" .. tonumber(n))\n"
                            "end\n"
                            "sleep(4)\n"
                            "print('End 4')\n");

    run_and_print_error(LUA,"print('Start 1')\n"
                            "function sleep(n)\n"
                            "  os.execute(\"sleep \" .. tonumber(n))\n"
                            "end\n"
                            "sleep(0.5)\n"
                            "print('End 1')\n");

    sc_exit();
}

void run_and_print_error(const LANG &lang, const char *script) {
    std::future<Status> future = sc_exec_script(lang, script);

    if (!future.valid()){
        printf("Error: invalid future!\n");
        return;
    }

    switch (future.wait_for(std::chrono::seconds(1))) {
        case std::future_status::ready:
            switch (future.get()) {
                case OK:
                    printf("Exec: OK!\n\n");
                    break;
                case SYNTAX_ERROR:
                case RUNTIME_ERROR:
                    printf("%s\n\n", sc_get_last_error());
                    break;
            }
            break;
        case std::future_status::timeout:
            printf("Error: future took too long to resolve!\n");
            break;
        case std::future_status::deferred:
            printf("Error: future hasn't been started!\n");
            break;
    };

}


void my_print(const char *string) {
    printf("%s", string);
}
