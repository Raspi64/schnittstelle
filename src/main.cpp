
#include <cstdio>
#include "schnitstelle.h"
#include <unistd.h>
#include <Gui.hpp>

Gui *gui;

void my_print(const char *string);

void my_draw(int x, int y, int red, int green, int blue, int alpha, int size);

void my_clear();

void run_and_print_error(const LANG &lang, const char *script);

const char *lua_script =
        "function sleep(n)\n"
        "    os.execute(\"sleep \" .. tonumber(n))\n"
        "end\n"
        "\n"
        "function sub(r, g, b, t)\n"
        "    for i = 0, 250, 10 do\n"
        "        draw(i, i, r, g, b, 255, 10)\n"
        "        draw(i, 500 - i, r, g, b, 255, 10)\n"
        "        draw(500 - i, i, r, g, b, 255, 10)\n"
        "        draw(500 - i, 500 - i, r, g, b, 255, 10)\n"
        "        sleep(t)\n"
        "    end\n"
        "end\n"
        "\n"
        "function drawer()\n"
        "    while true do\n"
        "        sub(255, 0, 0, 0.05)\n"
        "        sub(0, 255, 0, 0.05)\n"
        "        sub(0, 0, 255, 0.05)\n"
        "    end\n"
        "end\n"
        "\n"
        "drawer()";

int main() {
    gui = new Gui();
    gui->initialize();

//    sc_register_print_function(my_print);
    sc_register_draw_function(my_draw);
    sc_register_clear_function(my_clear);
    sc_start_script(LUA, lua_script);

    gui->graphic->add_pixel(10, 10, 255, 0, 0, 128, 10);

    bool running = true;
    while (running) {
        running = gui->tick() == 0;
    }
    gui->destroy();
}

void my_draw(int x, int y, int red, int green, int blue, int alpha, int size) {
    gui->graphic->add_pixel(x, y, red, green, blue, alpha, size);
//    printf("GUI Draw!\n");
}

void my_clear() {
    gui->graphic->clear_pixels();
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
    gui->console->print(out);
    free(out);
}
