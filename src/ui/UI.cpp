#include "UI.hpp"

UI::UI() : MultiViewContainer() {
    raw(); // pass typed characters through our program immediately (without buffer)
    noecho(); // don't echo typed characters
    curs_set(0); // invisible cursor
    keypad(stdscr, true);
    nodelay(stdscr, true);

    addChildren(this, {
            {UIConsts::ViewId::TITLE_ABSOLUTE, stackViews(new Absolute(), {
                    {-1, new Border()},
                    {-1, new Center()},
                    {-1, new Text(UIConsts::TITLE_TEXT)}
            })},
            {UIConsts::ViewId::CONTROLS_ABSOLUTE, stackViews(new Absolute(), {
                    {-1, new Border()},
                    {-1, new Center()},
                    {UIConsts::ViewId::MAIN_MENU, addChildren(new Menu(9, 1, 0, 0), {
                            {-1, new Text(UIConsts::BTN_ADD_IMAGE)},
                            {-1, new Text(UIConsts::BTN_SHOW_IMAGE)},
                            {-1, new Text(UIConsts::BTN_GRAYSCALE_LEVEL)},
                            {-1, new Text(UIConsts::BTN_EDIT_IMAGE)},
                            {-1, new Text(UIConsts::BTN_REMOVE_IMAGE)},
                            {-1, new Text(UIConsts::BTN_PLAY_ANIM)},
                            {-1, new Text(UIConsts::BTN_PAUSE_ANIM)},
                            {-1, new Text(UIConsts::BTN_EXPORT_ASCII)},
                            {-1, new Text(UIConsts::BTN_EXIT)}
                    })}
            })},
            // TODO
            {UIConsts::ViewId::ART_ABSOLUTE, stackViews(new Absolute(), {
                    {-1, new Border()},
                    {-1, new Text(UIConsts::TITLE_TEXT)}
            })}
    });
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

    const auto titlePanel = getView<Absolute>(UIConsts::ViewId::TITLE_ABSOLUTE);
    auto titleH = static_cast<uint16_t>(UIConsts::TITLE_PANEL_HEIGHT_REL * static_cast<float>(h));
    titlePanel->setHeight(titleH);
    titlePanel->setWidth(w);
    titlePanel->setY(0);
    titlePanel->setX(0);

    const auto controlsPanel = getView<Absolute>(UIConsts::ViewId::CONTROLS_ABSOLUTE);
    auto controlsW = static_cast<uint16_t>(UIConsts::CONTROLS_PANEL_WIDTH_REL * static_cast<float>(w));
    controlsPanel->setHeight(h - titleH);
    controlsPanel->setWidth(controlsW);
    controlsPanel->setY(titleH);
    controlsPanel->setX(0);

    const auto artPanel = getView<Absolute>(UIConsts::ViewId::ART_ABSOLUTE);
    artPanel->setHeight(h - titleH);
    artPanel->setWidth(w - controlsW);
    artPanel->setY(titleH);
    artPanel->setX(controlsW);

    MultiViewContainer::draw();
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

View *UI::addChildren(View *parent, std::initializer_list<std::pair<int8_t, View *>> views) {
    for (const auto &p : views) {
        m_Views.emplace(p.first, p.second);
        parent->setChild(p.second);
    }
    return parent;
}

View *UI::stackViews(View *parent, std::initializer_list<std::pair<int8_t, View *>> views) {
    auto tmpParent = parent;
    for (const auto &p : views) {
        m_Views.emplace(p.first, p.second);
        tmpParent->setChild(p.second);
        tmpParent = p.second;
    }
    return parent;
}

template<class T>
T *UI::getView(int8_t id) {
    return dynamic_cast<T*>(m_Views.find(id)->second.get());
}
