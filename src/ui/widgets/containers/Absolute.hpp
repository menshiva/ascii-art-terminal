#ifndef ASCIIART_ABSOLUTE_HPP
#define ASCIIART_ABSOLUTE_HPP

#include <memory>
#include "Pos.hpp"
#include "Size.hpp"

class Absolute : public SingleViewContainer {
public:
    Absolute() : SingleViewContainer(), m_Pos(new Pos()), m_Size(new Size()) {
        m_Pos->setChild(m_Size.get());
        m_Size->setParent(m_Pos.get());
        SingleViewContainer::setChild(m_Pos.get());
    }

    uint16_t getHeight() const override {
        return m_Size->getHeight();
    }

    uint16_t getWidth() const override {
        return m_Size->getWidth();
    }

    uint16_t getY() const override {
        return m_Pos->getY();
    }

    uint16_t getX() const override {
        return m_Pos->getX();
    }

    void setHeight(uint16_t h) {
        m_Size->setHeight(h);
    }

    void setWidth(uint16_t w) {
        m_Size->setWidth(w);
    }

    void setY(uint16_t y) {
        m_Pos->setY(y);
    }

    void setX(uint16_t x) {
        m_Pos->setX(x);
    }

    void setChild(View *child) override {
        m_Size->setChild(child);
        child->setParent(this);
    }
private:
    std::unique_ptr<Pos> m_Pos;
    std::unique_ptr<Size> m_Size;
};

#endif //ASCIIART_ABSOLUTE_HPP
