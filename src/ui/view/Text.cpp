#include "Text.hpp"

Text::Text(View *parent, std::string text, float yRelative, float xRelative) :
        View(parent, 0.0F, 0.0F, yRelative, xRelative),
        text(std::move(text)) {}

void Text::changeText(const std::string &newText) {
    text = newText;
    draw();
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

void Text::draw() {
    auto y = static_cast<size_t>(yRelative * parent->getHeight());
    auto x = static_cast<size_t>(xRelative * parent->getWidth()) - (text.size() >> 1);
    wmove(getWindow(), y, 1);
    for (size_t pos = 1; pos < parent->getWidth() - 1; ++pos) waddch(getWindow(), ' '); // clear old text
    mvwaddstr(getWindow(), y, x, text.c_str());
}

void Text::resize() {}