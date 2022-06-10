#ifndef ASCIIART_MENU_HPP
#define ASCIIART_MENU_HPP

#include "../base/View.hpp"

struct Menu final : public Container {
    Menu(std::initializer_list<View*> children) : Container(children) {
        uint16_t h = 0, w = 0;
        for (const auto &child : m_Children) {
            h += child->getHeight();
            uint16_t chW = child->getWidth();
            if (chW > w)
                w = chW;
        }
        setAbsoluteHeight(h);
        setAbsoluteWidth(w);

        if (!m_Children.empty()) {
            m_Children[0]
                    ->setY([&]() -> uint16_t { return getY(); })
                    ->setX([&]() -> uint16_t { return getX(); });
            for (size_t i = 1; i < m_Children.size(); ++i)
                m_Children[i]
                    ->attachToChildInParentBelow(false, i - 1)
                    ->setX([&]() -> uint16_t { return getX(); });
        }
    }

    WINDOW *getWindow() const override {
        return getParentContainer()->getWindow();
    }
};

#endif //ASCIIART_MENU_HPP
