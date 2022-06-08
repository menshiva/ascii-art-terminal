#include "UI.hpp"

UI::UI() :
    View(),
    m_TitleView(new Border(new Center(new Text(UIConsts::TITLE_TEXT)))),
    m_ControlsView(new Border(nullptr)), // TODO
    m_ArtView(new Border(nullptr)) // TODO
{
    raw(); // pass typed characters through our program immediately (without buffer)
    noecho(); // don't echo typed characters
    curs_set(0); // invisible cursor
    keypad(stdscr, true);
    nodelay(stdscr, true);

    m_TitleView.setParent(this);
    m_ControlsView.setParent(this);
    m_ArtView.setParent(this);
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

uint16_t UI::getY() const {
    return 0;
}

uint16_t UI::getX() const {
    return 0;
}

void UI::draw() {
    uint16_t h = getHeight(), w = getWidth();

    m_TitleView.setHeight(static_cast<uint16_t>(UIConsts::TITLE_PANEL_HEIGHT_REL * static_cast<float>(h)));
    m_TitleView.setWidth(static_cast<uint16_t>(UIConsts::TITLE_PANEL_WIDTH_REL * static_cast<float>(w)));
    m_TitleView.setY(static_cast<uint16_t>(UIConsts::TITLE_PANEL_Y_REL * static_cast<float>(h)));
    m_TitleView.setX( static_cast<uint16_t>(UIConsts::TITLE_PANEL_X_REL * static_cast<float>(w)));

    m_ControlsView.setHeight(static_cast<uint16_t>(UIConsts::CONTROLS_PANEL_HEIGHT_REL * static_cast<float>(h)));
    m_ControlsView.setWidth(static_cast<uint16_t>(UIConsts::CONTROLS_PANEL_WIDTH_REL * static_cast<float>(w)));
    m_ControlsView.setY(static_cast<uint16_t>(UIConsts::CONTROLS_PANEL_Y_REL * static_cast<float>(h)));
    m_ControlsView.setX( static_cast<uint16_t>(UIConsts::CONTROLS_PANEL_X_REL * static_cast<float>(w)));

    m_ArtView.setHeight(static_cast<uint16_t>(UIConsts::ART_PANEL_HEIGHT_REL * static_cast<float>(h)));
    m_ArtView.setWidth(static_cast<uint16_t>(UIConsts::ART_PANEL_WIDTH_REL * static_cast<float>(w)));
    m_ArtView.setY(static_cast<uint16_t>(UIConsts::ART_PANEL_Y_REL * static_cast<float>(h)));
    m_ArtView.setX( static_cast<uint16_t>(UIConsts::ART_PANEL_X_REL * static_cast<float>(w)));

    m_TitleView.draw();
    m_ControlsView.draw();
    m_ArtView.draw();

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
            erase();
            windowDirty = true;
        }
        if (windowDirty) {
            draw();
            windowDirty = false;
        }
        pressedKey = wgetch(stdscr);
    }
}
