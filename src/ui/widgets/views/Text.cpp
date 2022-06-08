#include "Text.hpp"

Text::Text(float yRelative, float xRelative,
           const char *text, bool centered
) : View(0.0f, 0.0f, yRelative, xRelative),
    m_Text(text), m_CenteredInParent(centered) {}

Text::Text(View *parent,
           float yRelative, float xRelative,
           const char *text, bool centered
) : View(parent, 0.0f, 0.0f, yRelative, xRelative),
    m_Text(text), m_CenteredInParent(centered) {}

WINDOW *Text::getWindow() const {
    return nullptr;
}

uint16_t Text::getHeight() const {
    return 1;
}

uint16_t Text::getWidth() const {
    return strlen(m_Text);
}

void Text::resize() {}

void Text::draw() {
    auto y = static_cast<uint16_t>(m_YRel * static_cast<float>(m_Parent->getHeight()));
    auto x = static_cast<uint16_t>(m_XRel * static_cast<float>(m_Parent->getWidth()));
    if (m_CenteredInParent)
        x -= getWidth() / 2;
    // wmove(m_Parent->getWindow(), y, 1);
    // // clear old text
    // for (size_t pos = 1; pos < m_Parent->getWidth() - 1; ++pos)
    //     waddch(m_Parent->getWindow(), ' ');
    mvwaddstr(m_Parent->getWindow(), y, x, m_Text);
}
