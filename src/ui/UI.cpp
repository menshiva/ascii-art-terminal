#include "UI.hpp"

UI::UI() : m_Root({
    // title panel
    (new Panel(true, {
        (new Text(UIConsts::TITLE_TEXT))
            ->setCenteredInParentHeight()->setCenteredInParentWidth()
    }))
        ->setRelativeParentHeight(UIConsts::TITLE_PANEL_HEIGHT_REL),
    // controls panel
    (new Panel(true, {
        (new Menu(
        {
             new Text(UIConsts::BTN_ADD_IMAGE),
             new Text(UIConsts::BTN_SHOW_IMAGE),
             new Text(UIConsts::BTN_GRAYSCALE_LEVEL),
             new Text(UIConsts::BTN_EDIT_IMAGE),
             new Text(UIConsts::BTN_REMOVE_IMAGE),
             new Text(UIConsts::BTN_PLAY_ANIM),
             new Text(UIConsts::BTN_PAUSE_ANIM),
             new Text(UIConsts::BTN_EXPORT_ASCII),
             new Text(UIConsts::BTN_EXIT)
        },
        {
            {57, [&]() -> void { m_MainLoopRunning = false; }}
        }))
            ->setCenteredInParentHeight()->setCenteredInParentWidth()
    }))
        ->setRelativeParentWidth(UIConsts::CONTROLS_PANEL_WIDTH_REL)->attachToChildInParentBelow(true, 0),
    // art panel
    (new Panel(true, {
        // TODO
    }))
        ->attachToChildInParentBelow(true, 0)->attachToChildInParentRight(true, 1),
}), m_MainLoopRunning(true), m_WindowDirty(true) {
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
    while (m_MainLoopRunning) {
        int c = wgetch(stdscr);
        if (c == KEY_RESIZE) {
            m_WindowDirty = true;
        }
        else {
            m_Root.interact(c);
        }

        if (m_WindowDirty) {
            m_Root.draw();
            m_WindowDirty = false;
        }
    }
}

View *UI::assignId(uint8_t id, View *view) {
    m_Views.emplace(id, view);
    return view;
}

template<class T>
T *UI::getView(uint8_t id) {
    return dynamic_cast<T*>(m_Views.at(id));
}
