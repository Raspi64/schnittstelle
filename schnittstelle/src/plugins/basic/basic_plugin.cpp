#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <my_basic.h>
#include "basic_plugin.h"
#include "basic_functions.h"

namespace basic_plugin {

    static struct mb_interpreter_t *bas = nullptr;

    static int basic_print(const char *format, ...);

    static void update_error_message();

    void plugin_init() {
        mb_init();
        mb_open(&bas);
        mb_set_printer(bas, basic_print);
        basic_register_command();

    }

    void plugin_exit() {
        mb_close(&bas);
        mb_dispose();
    }

    int load_script(const char *script) {
        int load_stat = mb_load_string(bas, script, true);

        if (load_stat != MB_FUNC_OK) {
            update_error_message();
        }
        return load_stat;
    }

    int exec_script() {
        int exec_stat = mb_run(bas, true);

        if (exec_stat != MB_FUNC_OK) {
            update_error_message();
        }
        return exec_stat;
    }

    static int basic_print(const char *format, ...) {
        va_list args;
        va_start(args, format);
        char *string = va_arg(args, char*);
        if (plugins::print_function_replacement != nullptr) {
            char *output;
            asprintf(&output, format, string);
            plugins::print_function_replacement(output);
            free(output);
        } else {
            printf(format, string);
        }
        va_end(args);
        return 0;
    }

    void update_error_message() {
        const char *file;
        int pos;
        unsigned short row, col;
        mb_error_e error = mb_get_last_error(bas, &file, &pos, &row, &col);
        char *new_error_buffer;

        asprintf(&new_error_buffer, "Error: %s at line %d:%d", mb_get_error_desc(error), row, col);

        char *old_error_buffer = plugins::last_error_buffer;
        plugins::last_error_buffer = nullptr;
        if (old_error_buffer != nullptr) free(old_error_buffer);

        plugins::last_error_buffer = new_error_buffer;
    }

    void basic_register_command() {
        mb_register_func(bas, "BASICMAXIMUM", basic_maximum);
        mb_register_func(bas, "OPENTERMINAL", basic_openTerminal);
        mb_register_func(bas, "BASICECHO", basic_echo);
    }
}
