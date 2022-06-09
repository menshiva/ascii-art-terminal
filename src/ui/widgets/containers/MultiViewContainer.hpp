#ifndef ASCIIART_MULTIVIEWCONTAINER_HPP
#define ASCIIART_MULTIVIEWCONTAINER_HPP

#include <vector>
#include "../View.hpp"

class MultiViewContainer : public View {
public:
    MultiViewContainer() : View() {}

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
        for (auto &child : m_Children)
            child->draw();
    }

    void setChild(View *child) override {
        child->setParent(this);
        m_Children.emplace_back(child);
    }
private:
    std::vector<View*> m_Children;
};

#endif //ASCIIART_MULTIVIEWCONTAINER_HPP
