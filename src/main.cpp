#include "ui/Screen.hpp"
#include "utils/Consts.hpp"

int main() {
    if (!Screen::init()) {
        puts(ConsoleConsts::ERROR_FAILED_NCURSES);
        return 1;
    }

    Screen screen;
    screen.withChildren({
        (new Panel(true))->withChildren({
            (new Text(UIConsts::TITLE_TEXT))->withCenteredInParentHeight()->withCenteredInParentWidth()
        })->withRelativeHeight(UIConsts::TITLE_PANEL_HEIGHT_REL),
        (new Panel(true))->withChildren({
            (new Menu())->withCallbacks({
                {UIConsts::KEYS::EXIT, [&]() -> void { screen.close(); }}
            })->withChildren({
                new Text(UIConsts::BTN_ADD_IMAGE),
                new Text(UIConsts::BTN_SHOW_IMAGE),
                new Text(UIConsts::BTN_GRAYSCALE_LEVEL),
                new Text(UIConsts::BTN_EDIT_IMAGE),
                new Text(UIConsts::BTN_REMOVE_IMAGE),
                new Text(UIConsts::BTN_PLAY_ANIM),
                new Text(UIConsts::BTN_PAUSE_ANIM),
                new Text(UIConsts::BTN_EXPORT_ASCII),
                new Text(UIConsts::BTN_EXIT)
            })->withCenteredInParentHeight()->withCenteredInParentWidth()
        })->withRelativeWidth(UIConsts::CONTROLS_PANEL_WIDTH_REL)->withAttachedBelow(true, 0),
        (new Panel(true))->withChildren({
            // TODO
        })->withAttachedBelow(true, 0)->withAttachedRight(true, 1)
    });
    screen.mainLoop();
    return 0;
}
