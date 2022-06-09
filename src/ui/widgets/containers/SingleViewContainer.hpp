#ifndef ASCIIART_SINGLEVIEWCONTAINER_HPP
#define ASCIIART_SINGLEVIEWCONTAINER_HPP

#include "../View.hpp"

class SingleViewContainer : public View {
public:
    SingleViewContainer() : View(), m_Child(nullptr) {}

    WINDOW *getWindow() const override {
        return getParent()->getWindow();
    }

    uint16_t getHeight() const override {
        return getParent()->getHeight();
    }

    uint16_t getWidth() const override {
        return getParent()->getWidth();
    }

    uint16_t getY() const override {
        return 0;
    }

    uint16_t getX() const override {
        return 0;
    }

    void draw() override {
        m_Child->draw();
    }

    View *getChild() const {
        return m_Child;
    }

    void setChild(View *child) override {
        m_Child = child;
        m_Child->setParent(this);
    }
private:
    View *m_Child;
};

#endif //ASCIIART_SINGLEVIEWCONTAINER_HPP
