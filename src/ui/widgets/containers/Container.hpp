#ifndef ASCIIART_CONTAINER_HPP
#define ASCIIART_CONTAINER_HPP

#include <memory>
#include "../View.hpp"

class Container : public View {
public:
    explicit Container(View *child) : View(), m_Child(child) {
        if (m_Child)
            m_Child->setParent(this);
    }

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
        return getParent()->getY();
    }

    uint16_t getX() const override {
        return getParent()->getX();
    }

    void draw() override {
        if (m_Child)
            m_Child->draw();
    }

    View *getChild() const {
        return m_Child.get();
    }
private:
    std::unique_ptr<View> m_Child;
};

#endif //ASCIIART_CONTAINER_HPP
