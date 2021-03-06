
#include <cstdio>
#include "schnitstelle.h"
#include <unistd.h>
#include <Gui.hpp>

Gui *gui;

void my_print(const char *string);

void my_draw(int x, int y, int red, int green, int blue, int alpha, int size);

void my_clear();

void run_and_print_error(const LANG &lang, const char *script);

char *loadfile(char *file) {
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen(file, "rb");
    if (!fp) perror(file), exit(1);

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    /* allocate memory for entire content */
    buffer = (char *) calloc(1, lSize + 1);
    if (!buffer) fclose(fp), fputs("memory alloc fails", stderr), exit(1);

    /* copy the file into the buffer */
    if (1 != fread(buffer, lSize, 1, fp))
        fclose(fp), free(buffer), fputs("entire read fails", stderr), exit(1);

    /* do your work here, buffer is a string contains the whole text */

    fclose(fp);
    return buffer;
}


int main() {
    gui = new Gui();
    gui->initialize();

//    sc_register_print_function(my_print);
    sc_register_draw_function(my_draw);
    sc_register_clear_function(my_clear);
    char *lua_script = loadfile("../src/drawer.lua");
    sc_start_script(LUA, lua_script);
    free(lua_script);

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
