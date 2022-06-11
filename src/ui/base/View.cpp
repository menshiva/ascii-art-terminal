#include "View.hpp"

uint16_t View::getHeight() const {
    return m_GetHeight();
}

uint16_t View::getWidth() const {
    return m_GetWidth();
}

uint16_t View::getY() const {
    return m_GetY();
}

uint16_t View::getX() const {
    return m_GetX();
}

View *View::withHeight(const std::function<uint16_t()> &f) {
    if (!m_GetHeight)
        m_GetHeight = f;
    return this;
}

View *View::withWidth(const std::function<uint16_t()> &f) {
    if (!m_GetWidth)
        m_GetWidth = f;
    return this;
}

View *View::withAbsoluteHeight(uint16_t h) {
    if (!m_GetHeight)
        m_GetHeight = [h]() -> uint16_t { return h; };
    return this;
}

View *View::withAbsoluteWidth(uint16_t w) {
    if (!m_GetWidth)
        m_GetWidth = [w]() -> uint16_t { return w; };
    return this;
}

View *View::withRelativeHeight(float hRel) {
    if (!m_GetHeight) {
        m_GetHeight = [&, hRel]() -> uint16_t {
            return static_cast<uint16_t>(hRel * static_cast<float>(m_ParentContainer->m_GetHeight()));
        };
    }
    return this;
}

View *View::withRelativeWidth(float wRel) {
    if (!m_GetWidth) {
        m_GetWidth = [&, wRel]() -> uint16_t {
            return static_cast<uint16_t>(wRel * static_cast<float>(m_ParentContainer->m_GetWidth()));
        };
    }
    return this;
}

View *View::withY(const std::function<uint16_t()> &f) {
    if (!m_GetY)
        m_GetY = f;
    return this;
}

View *View::withX(const std::function<uint16_t()> &f) {
    if (!m_GetX)
        m_GetX = f;
    return this;
}

View *View::withAbsoluteY(uint16_t y) {
    if (!m_GetY)
        m_GetY = [y]() -> uint16_t { return y; };
    return this;
}

View *View::withAbsoluteX(uint16_t x) {
    if (!m_GetX)
        m_GetX = [x]() -> uint16_t { return x; };
    return this;
}

View *View::withCenteredInParentHeight() {
    if (!m_GetY) {
        m_GetY = [&]() -> uint16_t {
            return static_cast<uint16_t>(static_cast<float>(m_ParentContainer->m_GetHeight() - m_GetHeight()) * 0.5f);
        };
    }
    return this;
}

View *View::withCenteredInParentWidth() {
    if (!m_GetX) {
        m_GetX = [&]() -> uint16_t {
            return static_cast<uint16_t>(static_cast<float>(m_ParentContainer->m_GetWidth() - m_GetWidth()) * 0.5f);
        };
    }
    return this;
}

View *View::withAttachedBelow(bool fillSize, size_t childIdx) {
    if (!m_GetY) {
        if (fillSize) {
            m_GetHeight = [&, childIdx]() -> uint16_t {
                const auto toAttachTo = m_ParentContainer->m_Children[childIdx].get();
                return m_ParentContainer->getHeight() - toAttachTo->getHeight();
            };
        }
        m_GetY = [&, childIdx]() -> uint16_t {
            const auto toAttachTo = m_ParentContainer->m_Children[childIdx].get();
            return toAttachTo->getY() + toAttachTo->getHeight();
        };
    }
    return this;
}

View *View::withAttachedRight(bool fillSize, size_t childIdx) {
    if (!m_GetX) {
        if (fillSize) {
            m_GetWidth = [&, childIdx]() -> uint16_t {
                const auto toAttachTo = m_ParentContainer->m_Children[childIdx].get();
                return m_ParentContainer->getWidth() - toAttachTo->getWidth();
            };
        }
        m_GetX = [&, childIdx]() -> uint16_t {
            const auto toAttachTo = m_ParentContainer->m_Children[childIdx].get();
            return toAttachTo->getX() + toAttachTo->getWidth();
        };
    }
    return this;
}

bool View::isActive() const {
    return true;
}

void View::interact(int key) const {}

View::View() : m_ParentContainer(nullptr) {}

Container *Container::withChildren(std::initializer_list<View *> children) {
    for (auto child : children)
        addChild(child);
    return this;
}

void Container::interact(int key) const {
    if (isActive())
        for (const auto &child : m_Children)
            if (child->isActive())
                child->interact(key);
}

Container::Container() : View() {}

void Container::addChild(View *child) {
    child->m_ParentContainer = this;
    m_Children.emplace_back(child);
}

void Container::draw() {
    for (auto &child : m_Children)
        child->draw();
}
