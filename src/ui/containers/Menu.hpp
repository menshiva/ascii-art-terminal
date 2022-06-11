#ifndef ASCIIART_MENU_HPP
#define ASCIIART_MENU_HPP

#include "../views/Text.hpp"

typedef std::pair<int, std::function<void(void)>> Callback;

class Menu final : public Container {
public:
    Menu() : Container() {}

    WINDOW *getWindow() const override {
        return m_ParentContainer->getWindow();
    }

    Menu *withChildren(std::initializer_list<View*> children) override {
        Container::withChildren(children);

        uint16_t h = 0, w = 0;
        for (auto &child : children) {
            h += child->getHeight();
            uint16_t chW = child->getWidth();
            if (chW > w)
                w = chW;
        }
        withAbsoluteHeight(h);
        withAbsoluteWidth(w);

        if (!m_Children.empty()) {
            m_Children[0]->withY([&]() -> uint16_t { return getY(); })->withX([&]() -> uint16_t { return getX(); });
            for (size_t i = 1; i < m_Children.size(); ++i)
                m_Children[i]->withAttachedBelow(false, i - 1)->withX([&]() -> uint16_t { return getX(); });
        }

        return this;
    }

    Menu *withCallbacks(std::initializer_list<Callback> callbacks) {
        m_Callbacks.assign(callbacks);
        return this;
    }

    bool isActive() const override {
        return m_ParentContainer->isActive();
    }

    void interact(int key) const override {
        for (const auto &p : m_Callbacks)
            if (p.first == key)
                p.second();
        Container::interact(key);
    }
private:
    std::vector<Callback> m_Callbacks;
};

#endif //ASCIIART_MENU_HPP
