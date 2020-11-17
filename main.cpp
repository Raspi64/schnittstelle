#include <lua_plugin.h>
#include "my_basic.h"

void lua_print(const char *string);

int main() {
    struct mb_interpreter_t *bas = nullptr;

    mb_init();
    mb_open(&bas);
    mb_set_printer(bas, printf);
    mb_load_string(bas, "print \"Hello from Basic\";", true);
    mb_run(bas, true);
    mb_close(&bas);
    mb_dispose();

    lua_plugin::plugin_init();
    lua_plugin::register_print_function(print);

    lua_plugin::exec_script("print('Hello from Lua')");

    lua_plugin::plugin_exit();

    return 0;
}

void print(const char *string) {
    printf("%s\n", string);
}
