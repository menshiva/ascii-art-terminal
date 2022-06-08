#ifndef ASCIIART_RELATIVE_HPP
#define ASCIIART_RELATIVE_HPP

#include "Container.hpp"
#include "Pos.hpp"
#include "Size.hpp"

struct Relative : public Container {
    explicit Relative(View *child) : Container(new Pos(new Size(child))) {}

    uint16_t getHeight() const override {
        return dynamic_cast<const Container*>(getChild())->getChild()->getHeight();
    }

    uint16_t getWidth() const override {
        return dynamic_cast<const Container*>(getChild())->getChild()->getWidth();
    }

    uint16_t getY() const override {
        return getChild()->getY();
    }

    uint16_t getX() const override {
        return getChild()->getX();
    }

    void setHeight(uint16_t h) {
        dynamic_cast<Size*>(dynamic_cast<Container*>(getChild())->getChild())->setHeight(h);
    }

    void setWidth(uint16_t w) {
        dynamic_cast<Size*>(dynamic_cast<Container*>(getChild())->getChild())->setWidth(w);
    }

    void setY(uint16_t y) {
        dynamic_cast<Pos*>(getChild())->setY(y);
    }

    void setX(uint16_t x) {
        dynamic_cast<Pos*>(getChild())->setX(x);
    }
};

#endif //ASCIIART_RELATIVE_HPP
