#include "UI.hpp"

UI::UI() : m_Root({
    // title panel
    (new Panel({
        (new Text(UIConsts::TITLE_TEXT))
            ->setCenteredInParentHeight()->setCenteredInParentWidth()
    }))
        ->setRelativeParentHeight(UIConsts::TITLE_PANEL_HEIGHT_REL),
    // controls panel
    (new Panel({
        (new Menu({
             new Text(UIConsts::BTN_ADD_IMAGE),
             new Text(UIConsts::BTN_SHOW_IMAGE),
             new Text(UIConsts::BTN_GRAYSCALE_LEVEL),
             new Text(UIConsts::BTN_EDIT_IMAGE),
             new Text(UIConsts::BTN_REMOVE_IMAGE),
             new Text(UIConsts::BTN_PLAY_ANIM),
             new Text(UIConsts::BTN_PAUSE_ANIM),
             new Text(UIConsts::BTN_EXPORT_ASCII),
             new Text(UIConsts::BTN_EXIT)
        }))
            ->setCenteredInParentHeight()->setCenteredInParentWidth()
    }))
        ->setRelativeParentWidth(UIConsts::CONTROLS_PANEL_WIDTH_REL)->attachToChildInParentBelow(true, 0),
    // art panel
    (new Panel({
        // TODO
    }))
        ->attachToChildInParentBelow(true, 0)->attachToChildInParentRight(true, 1),
}) {
    raw(); // pass typed characters through our program immediately (without buffer)
    noecho(); // don't echo typed characters
    curs_set(0); // invisible cursor
    keypad(stdscr, true);
    nodelay(stdscr, true);
}

UI::~UI() {
    erase();
    endwin();
}

bool UI::init() {
    return initscr() != nullptr;
}

void UI::mainLoop() {
    int pressedKey = -1;
    bool windowDirty = true;
    while (pressedKey != 57) { // 9
        if (pressedKey == KEY_RESIZE) {
            windowDirty = true;
        }
        if (windowDirty) {
            m_Root.draw();
            windowDirty = false;
        }
        pressedKey = wgetch(stdscr);
    }
}

View *UI::assignId(int8_t id, View *view) {
    if (id != UIConsts::ViewId::UNUSED)
        m_Views.emplace(id, view);
    return view;
}

template<class T>
T *UI::getView(int8_t id) {
    return dynamic_cast<T*>(m_Views.at(id));
}
