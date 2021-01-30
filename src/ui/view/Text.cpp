#include "Text.hpp"

#include <utility>

Text::Text(const View *parent, std::string text, double yRelative, double xRelative) :
        View(parent, 0.0, 0.0, yRelative, xRelative), text(std::move(text)) {}

void Text::changeText(const std::string &newText) {
    drawn = false;
    text = newText;
    draw();
}

void Text::draw() const {
    const auto y = static_cast<size_t>(yRelative * parent->getHeight());
    const auto x = static_cast<size_t>(xRelative * parent->getWidth()) - (text.size() >> 1U);
    wmove(getWindow(), y, 1U);
    // clear old text
    for (size_t pos = 1U; pos < parent->getWidth() - 1U; ++pos) waddch(getWindow(), ' ');
    mvwaddstr(getWindow(), y, x, text.c_str());
    drawn = true;
}

void Text::resize() {}

void Text::show() const {
    parent->show();
}

void Text::hide() const {
    parent->hide();
}

WINDOW *Text::getWindow() const {
    return parent->getWindow();
}

size_t Text::getHeight() const {
    return parent->getHeight();
}

size_t Text::getWidth() const {
    return parent->getWidth();
}