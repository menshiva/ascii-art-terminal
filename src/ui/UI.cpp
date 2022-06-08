#include "UI.hpp"

UI::UI() : View(1.0f, 1.0f, 0.0f, 0.0f) {
    raw(); // pass typed characters through our program immediately (without buffer)
    noecho(); // don't echo typed characters
    curs_set(0); // invisible cursor
    keypad(stdscr, true);
    nodelay(stdscr, true);

    // title panel
    m_Views.emplace_back(new Panel(
            this,
            UIConsts::TITLE_PANEL_HEIGHT, UIConsts::TITLE_PANEL_WIDTH,
            UIConsts::TITLE_PANEL_Y, UIConsts::TITLE_PANEL_X,
            new Text(
                    UIConsts::TITLE_TEXT_Y, UIConsts::TITLE_TEXT_X,
                    UIConsts::TITLE_TEXT, UIConsts::TITLE_TEXT_CENTERED
            )
    ));

    // menu panel
    m_Views.emplace_back(new Panel(
            this,
            UIConsts::CONTROLS_PANEL_HEIGHT, UIConsts::CONTROLS_PANEL_WIDTH,
            UIConsts::CONTROLS_PANEL_Y, UIConsts::CONTROLS_PANEL_X,
            nullptr // TODO
    ));

    // ascii art panel
    m_Views.emplace_back(new Panel(
            this,
            UIConsts::ART_PANEL_HEIGHT, UIConsts::ART_PANEL_WIDTH,
            UIConsts::ART_PANEL_Y, UIConsts::ART_PANEL_X,
            nullptr // TODO
    ));
}

UI::~UI() {
    erase();
    endwin();
}

WINDOW *UI::getWindow() const {
    return stdscr;
}

uint16_t UI::getHeight() const {
    return getmaxy(stdscr);
}

uint16_t UI::getWidth() const {
    return getmaxx(stdscr);
}

void UI::resize() {
    erase();
    for (const auto &view : m_Views)
        view->resize();
}

void UI::draw() {
    for (const auto &view : m_Views)
        view->draw();
    update_panels();
    doupdate();
}

bool UI::init() {
    return initscr() != nullptr;
}

void UI::mainLoop() {
    int pressedKey = -1;
    bool windowDirty = true;
    while (pressedKey != 27) { // ESC key
        if (pressedKey == KEY_RESIZE) {
            resize();
            windowDirty = true;
        }
        if (windowDirty) {
            draw();
            windowDirty = false;
        }
        pressedKey = wgetch(stdscr);
    }
}
