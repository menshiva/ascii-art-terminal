#include "Panel.hpp"

Panel::Panel(
        View *parent,
        float heightRelative, float widthRelative,
        float yRelative, float xRelative,
        View *child
) : View(parent, heightRelative, widthRelative, yRelative, xRelative), m_Child(child) {
    auto h = static_cast<uint16_t>(m_HeightRel * static_cast<float>(m_Parent->getHeight()));
    auto w = static_cast<uint16_t>(m_WidthRel * static_cast<float>(m_Parent->getWidth()));
    auto y = static_cast<uint16_t>(m_YRel * static_cast<float>(m_Parent->getHeight()));
    auto x = static_cast<uint16_t>(m_XRel * static_cast<float>(m_Parent->getWidth()));
    m_Panel = new_panel(newwin(h, w, y, x));
    if (m_Child)
        m_Child->setParent(this);
}

Panel::~Panel() {
    WINDOW *tmp = m_Panel->win;
    del_panel(m_Panel);
    delwin(tmp);
}

WINDOW *Panel::getWindow() const {
    return m_Panel->win;
}

uint16_t Panel::getHeight() const {
    return static_cast<uint16_t>(m_HeightRel * static_cast<float>(m_Parent->getHeight()));
}

uint16_t Panel::getWidth() const {
    return static_cast<uint16_t>(m_WidthRel * static_cast<float>(m_Parent->getWidth()));
}

void Panel::resize() {
    auto newY = static_cast<uint16_t>(m_YRel * static_cast<float>(m_Parent->getHeight()));
    auto newX = static_cast<uint16_t>(m_XRel * static_cast<float>(m_Parent->getWidth()));
    WINDOW *oldWin = getWindow();
    replace_panel(m_Panel, newwin(getHeight(), getWidth(), newY, newX));
    delwin(oldWin);
    if (m_Child)
        m_Child->resize();
}

void Panel::draw() {
    box(getWindow(), 0, 0);
    if (m_Child)
        m_Child->draw();
}
