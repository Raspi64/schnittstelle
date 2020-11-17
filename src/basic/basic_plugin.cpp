#include <my_basic.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include "basic_plugin.h"

namespace basic_plugin {

    static const char *format_error_message();

    static int basic_print(const char *format, ...);

    static void set_error_message(const char *error_message);


    static struct mb_interpreter_t *bas = nullptr;
    static char *last_error_buffer = nullptr;

    static print_function print_function_replacement;

    void plugin_init() {
        mb_init();
        mb_open(&bas);
        mb_set_printer(bas, basic_print);
    }

    void plugin_exit() {
        mb_close(&bas);
        mb_dispose();
    }

    int load_script(const char *script) {
        mb_reset(&bas, true);
        int load_stat = mb_load_string(bas, script, false);

        if (load_stat != MB_FUNC_OK) {
            set_error_message(format_error_message());
        }
        return load_stat;
    }

    int exec_script() {
        int exec_stat = mb_run(bas, true);

        if (exec_stat != MB_FUNC_OK) {
            set_error_message(format_error_message());
        }
        return exec_stat;
    }

    const char *get_last_error() {
        return last_error_buffer;
    }

    static int basic_print(const char *format, ...) {
        va_list args;
        va_start(args, format);
        char *string = va_arg(args, char*);
        if (print_function_replacement != nullptr) {
            char *output;
            asprintf(&output, format, string);
            print_function_replacement(output);
            free(output);
        } else {
            printf(format, string);
        }
        va_end(args);
        return 0;
    }

    static const char *format_error_message() {
        const char *file;
        int pos;
        unsigned short row, col;
        mb_error_e error = mb_get_last_error(bas, &file, &pos, &row, &col);
        char *output;

        asprintf(&output, "Error: %s at line %d:%d", mb_get_error_desc(error), row, col);
        return output;
    }

    void set_error_message(const char *error_message) {
        char *old_error_buffer = last_error_buffer;
        last_error_buffer = nullptr;
        if (old_error_buffer != nullptr) free(old_error_buffer);
        char *new_error_buffer;

        asprintf(&new_error_buffer, "%s", error_message);
        last_error_buffer = new_error_buffer;
    }

    void register_print_function(print_function print_func) {
        print_function_replacement = print_func;
    }

}