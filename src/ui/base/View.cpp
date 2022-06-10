#include "View.hpp"

View::View() : m_ParentContainer(nullptr) {}

const Container *View::getParentContainer() const {
    return m_ParentContainer;
}

void View::setParentContainer(Container *container) {
    m_ParentContainer = container;
}

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

View *View::setHeight(const std::function<uint16_t()> &f) {
    if (!m_GetHeight)
        m_GetHeight = f;
    return this;
}

View *View::setWidth(const std::function<uint16_t()> &f) {
    if (!m_GetWidth)
        m_GetWidth = f;
    return this;
}

View *View::setAbsoluteHeight(uint16_t h) {
    if (!m_GetHeight)
        m_GetHeight = [h]() -> uint16_t { return h; };
    return this;
}

View *View::setAbsoluteWidth(uint16_t w) {
    if (!m_GetWidth)
        m_GetWidth = [w]() -> uint16_t { return w; };
    return this;
}

View *View::setRelativeParentHeight(float hRel) {
    if (!m_GetHeight) {
        m_GetHeight = [&, hRel]() -> uint16_t {
            return static_cast<uint16_t>(hRel * static_cast<float>(m_ParentContainer->m_GetHeight()));
        };
    }
    return this;
}

View *View::setRelativeParentWidth(float wRel) {
    if (!m_GetWidth) {
        m_GetWidth = [&, wRel]() -> uint16_t {
            return static_cast<uint16_t>(wRel * static_cast<float>(m_ParentContainer->m_GetWidth()));
        };
    }
    return this;
}

View *View::setY(const std::function<uint16_t()> &f) {
    if (!m_GetY)
        m_GetY = f;
    return this;
}

View *View::setX(const std::function<uint16_t()> &f) {
    if (!m_GetX)
        m_GetX = f;
    return this;
}

View *View::setAbsoluteY(uint16_t y) {
    if (!m_GetY)
        m_GetY = [y]() -> uint16_t { return y; };
    return this;
}

View *View::setAbsoluteX(uint16_t x) {
    if (!m_GetX)
        m_GetX = [x]() -> uint16_t { return x; };
    return this;
}

View *View::setCenteredInParentHeight() {
    if (!m_GetY) {
        m_GetY = [&]() -> uint16_t {
            return static_cast<uint16_t>(static_cast<float>(m_ParentContainer->m_GetHeight() - m_GetHeight()) * 0.5f);
        };
    }
    return this;
}

View *View::setCenteredInParentWidth() {
    if (!m_GetX) {
        m_GetX = [&]() -> uint16_t {
            return static_cast<uint16_t>(static_cast<float>(m_ParentContainer->m_GetWidth() - m_GetWidth()) * 0.5f);
        };
    }
    return this;
}

View *View::attachToChildInParentBelow(bool fillSize, size_t childIdx) {
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

View *View::attachToChildInParentRight(bool fillSize, size_t childIdx) {
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

void View::interact(int c) const {}

bool View::isActive() const {
    return true;
}

Container::Container(std::initializer_list<View *> children) {
    m_Children.reserve(children.size());
    for (auto child : children) {
        child->setParentContainer(this);
        m_Children.emplace_back(child);
    }
}

void Container::draw() {
    for (auto &child : m_Children)
        child->draw();
}

void Container::interact(int c) const {
    for (const auto &child : m_Children)
        child->interact(c);
}
