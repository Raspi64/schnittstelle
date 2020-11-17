
#include "schnitstelle.h"

int main() {
    sc_init();
    sc_exec_script(LUA,"print(\"Hello from Lua\")");
    sc_exec_script(BASIC,"print \"Hello from Basic\";");
    sc_exit();
}
