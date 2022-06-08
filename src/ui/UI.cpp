#include "UI.hpp"

UI::UI() :
    View(),
    m_TitleView(
            new Border(
                    new Center(
                            new Text(UIConsts::TITLE_TEXT)
                    )
            )
    ),
    m_ControlsView(
            new Border(
                    new Center(
                            new Menu({
                                UIConsts::BTN_ADD_IMAGE,
                                UIConsts::BTN_SHOW_IMAGE,
                                UIConsts::BTN_GRAYSCALE_LEVEL,
                                UIConsts::BTN_EDIT_IMAGE,
                                UIConsts::BTN_REMOVE_IMAGE,
                                UIConsts::BTN_PLAY_ANIM,
                                UIConsts::BTN_PAUSE_ANIM,
                                UIConsts::BTN_EXPORT_ASCII,
                                UIConsts::BTN_EXIT
                            })
                    )
            )
    ),
    m_ArtView(
            new Border(
                    nullptr // TODO
            )
    )
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

    auto titleH = static_cast<uint16_t>(UIConsts::TITLE_PANEL_HEIGHT_REL * static_cast<float>(h));
    m_TitleView.setHeight(titleH);
    m_TitleView.setWidth(w);
    m_TitleView.setY(0);
    m_TitleView.setX(0);

    auto controlsW = static_cast<uint16_t>(UIConsts::CONTROLS_PANEL_WIDTH_REL * static_cast<float>(w));
    m_ControlsView.setHeight(h - titleH);
    m_ControlsView.setWidth(controlsW);
    m_ControlsView.setY(titleH);
    m_ControlsView.setX(0);

    m_ArtView.setHeight(h - titleH);
    m_ArtView.setWidth(w - controlsW);
    m_ArtView.setY(titleH);
    m_ArtView.setX(controlsW);

    m_TitleView.draw();
    m_ControlsView.draw();
    m_ArtView.draw();

    update_panels();
    refresh();
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
            draw();
            windowDirty = false;
        }
        pressedKey = wgetch(stdscr);
    }
}
