#include "Screen.hpp"

bool Screen::init() {
    return initscr() != nullptr;
}

Screen::Screen() : Container(), m_MainLoopRunning(false), m_WindowDirty(false) {
    raw(); // pass typed characters through our program immediately (without buffer)
    nonl(); // no new line
    noecho(); // don't echo typed characters
    curs_set(0); // invisible cursor
    keypad(stdscr, true);
    nodelay(stdscr, true);

    withHeight([]() -> uint16_t { return getmaxy(stdscr); });
    withWidth([]() -> uint16_t { return getmaxx(stdscr); });
    withAbsoluteY(0);
    withAbsoluteX(0);
}

Screen::~Screen() {
    erase();
    endwin();
}

void Screen::mainLoop() {
    m_MainLoopRunning = true;
    markDirty();

    while (m_MainLoopRunning) {
        int c = wgetch(stdscr);
        if (c != -1) {
            if (c == KEY_RESIZE) m_WindowDirty = true;
            else Container::interact(c);
        }

        if (m_WindowDirty) {
            draw();
            m_WindowDirty = false;
        }
    }
}

void Screen::markDirty() {
    m_WindowDirty = true;
}

void Screen::close() {
    m_MainLoopRunning = false;
}

WINDOW *Screen::getWindow() const {
    return stdscr;
}

Screen *Screen::withChildren(std::initializer_list<Child> children) {
    Container::withChildren(children);
    for (const auto &child : m_Children) {
        child.view
            ->withRelativeHeight(1.0f)->withRelativeWidth(1.0f)
            ->withAbsoluteY(0)->withAbsoluteX(0);
        if (child.id != UNUSED_ID)
            onChildWithId(child.id, child.view.get());
    }
    return this;
}

void Screen::onChildWithId(View::Id id, View *child) {
    m_Views.emplace(id, child);
}

void Screen::draw() {
    Container::draw();
    update_panels();
    doupdate();
}
