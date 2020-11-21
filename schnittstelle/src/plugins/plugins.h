#ifndef SCHNITTSTELLE_PLUGINS_H
#define SCHNITTSTELLE_PLUGINS_H


namespace MouseEvent {
    enum Type {
        Press,
        Release,
        Move
    };
}

namespace KeyboardEvent {
    enum Type {
        Press,
        Release
    };
}

namespace plugins {
    typedef void (*print_function)(const char *);

    typedef void (*draw_function)(int x, int y, int r, int g, int b, int alpha, int size);

    typedef void (*clear_function)();

    extern char *last_error_buffer;
    extern print_function print_function_replacement;
    extern draw_function draw_function_value;
    extern clear_function clear_function_value;
}

#endif //SCHNITTSTELLE_PLUGINS_H
