/*#include "Panel.hpp"

Panel::Panel(View *parent,
             float heightRelative, float widthRelative,
             float yRelative, float xRelative,
             bool isVisible) : View(parent, heightRelative, widthRelative, yRelative, xRelative),
                               panelText(nullptr), panelMenu(nullptr), visible(isVisible) {
    height = static_cast<size_t>(roundf(heightRelative * parent->getHeight()));
    width = static_cast<size_t>(roundf(widthRelative * parent->getWidth()));
    auto y = static_cast<size_t>(roundf(yRelative * parent->getHeight()));
    auto x = static_cast<size_t>(roundf(xRelative * parent->getWidth()));
    panel = new_panel(newwin(height, width, y, x));
}

Panel::~Panel() {
    delete panelText;
    delete panelMenu;
    WINDOW *tmp = panel->win;
    del_panel(panel);
    delwin(tmp);
}

Text *Panel::getPanelText() const {
    return panelText;
}

Menu *Panel::getPanelMenu() const {
    return panelMenu;
}

void Panel::setPanelText(Text *text) {
    panelText = text;
}

void Panel::setPanelMenu(Menu *menu) {
    panelMenu = menu;
}

void Panel::show() {
    visible = true;
    show_panel(panel);
    update_panels();
    doupdate();
}

void Panel::hide() {
    visible = false;
    hide_panel(panel);
    update_panels();
    doupdate();
}

WINDOW *Panel::getWindow() const {
    return panel->win;
}

size_t Panel::getHeight() const {
    return height;
}

size_t Panel::getWidth() const {
    return width;
}

void Panel::draw() {
    box(panel->win, 0, 0);
    if (panelText) panelText->draw();
    if (panelMenu) panelMenu->draw();
    if (!visible) hide_panel(panel);
}

void Panel::resize() {
    height = static_cast<size_t>(roundf(heightRelative * parent->getHeight()));
    width = static_cast<size_t>(roundf(widthRelative * parent->getWidth()));
    auto newY = static_cast<size_t>(roundf(yRelative * parent->getHeight()));
    auto newX = static_cast<size_t>(roundf(xRelative * parent->getWidth()));
    WINDOW *oldWin = getWindow();
    replace_panel(panel, newwin(height, width, newY, newX));
    delwin(oldWin);
    if (panelMenu) panelMenu->resize();
}*/
