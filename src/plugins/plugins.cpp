#include "plugins.h"

namespace plugins {
    char *last_error_buffer = nullptr;
    print_function print_function_replacement;
    draw_function draw_function_value;
};