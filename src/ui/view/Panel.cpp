#include "Panel.hpp"

Panel::Panel(View *parent,
             float heightRelative, float widthRelative,
             float yRelative, float xRelative,
             bool isVisible) : View(parent, heightRelative, widthRelative, yRelative, xRelative),
                               visible(isVisible) {
    height = static_cast<size_t>(roundf(heightRelative * parent->getHeight()));
    width = static_cast<size_t>(roundf(widthRelative * parent->getWidth()));
    auto y = static_cast<size_t>(roundf(yRelative * parent->getHeight()));
    auto x = static_cast<size_t>(roundf(xRelative * parent->getWidth()));
    panel = new_panel(newwin(height, width, y, x));
}

Panel::~Panel() {
    WINDOW *tmp = panel->win;
    del_panel(panel);
    delwin(tmp);
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