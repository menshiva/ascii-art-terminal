#include "Panel.hpp"

Panel::Panel(const View *parent,
             double heightRelative, double widthRelative,
             double yRelative, double xRelative,
             bool isVisible) : View(parent, heightRelative, widthRelative, yRelative, xRelative),
                               panelVisibility(isVisible) {
    height = static_cast<size_t>(round(heightRelative * parent->getHeight()));
    width = static_cast<size_t>(round(widthRelative * parent->getWidth()));
    const auto y = static_cast<size_t>(round(yRelative * parent->getHeight()));
    const auto x = static_cast<size_t>(round(xRelative * parent->getWidth()));
    panel = new_panel(newwin(height, width, y, x));
}

void Panel::draw() const {
    box(getWindow(), 0, 0);
    if (!panelVisibility) hide_panel(panel);
    drawn = true;
}

void Panel::resize() {
    drawn = false;
    height = static_cast<size_t>(round(heightRelative * parent->getHeight()));
    width = static_cast<size_t>(round(widthRelative * parent->getWidth()));
    const auto newY = static_cast<size_t>(round(yRelative * parent->getHeight()));
    const auto newX = static_cast<size_t>(round(xRelative * parent->getWidth()));
    WINDOW *tmp = getWindow();
    replace_panel(panel, newwin(height, width, newY, newX));
    delwin(tmp);
}

void Panel::show() const {
    panelVisibility = true;
    show_panel(panel);
    update_panels();
    doupdate();
}

void Panel::hide() const {
    panelVisibility = false;
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

Panel::~Panel() {
    WINDOW *tmp = panel->win;
    del_panel(panel);
    delwin(tmp);
}