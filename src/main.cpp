#include "ui/UI.hpp"

int main() {
    if (!UI::init()) {
        puts(ConsoleConsts::ERROR_FAILED_NCURSES);
        return 1;
    }

    UI ui;
    ui.mainLoop();
    return 0;
}
