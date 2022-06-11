#ifndef ASCIIART_MENU_HPP
#define ASCIIART_MENU_HPP

#include "../views/Text.hpp"

class Menu final : public Container {
public:
    struct Callback {
        Callback(int key, std::function<void(void)> f) : key(key), f(std::move(f)) {}
        int key;
        std::function<void(void)> f;
    };

    explicit Menu(bool active) : Container(), m_IsActive(active) {
        withWrapContent();
    }

    void setActive(bool active) {
        m_IsActive = active;
    }

    WINDOW *getWindow() const override {
        return m_ParentContainer->getWindow();
    }

    Menu *withChildren(std::initializer_list<Child> children) override {
        Container::withChildren(children);
        if (!m_Children.empty()) {
            m_Children[0].view->withY([&]() -> uint16_t { return getY(); })->withX([&]() -> uint16_t { return getX(); });
            for (size_t i = 1; i < m_Children.size(); ++i)
                m_Children[i].view->withAttachedBelow(false, i - 1)->withX([&]() -> uint16_t { return getX(); });
        }
        return this;
    }

    void onChildWithId(Id id, View *child) override {
        m_ParentContainer->onChildWithId(id, child);
    }

    Menu *withCallbacks(std::initializer_list<Callback> callbacks) {
        m_Callbacks.assign(callbacks);
        return this;
    }

    void interact(int key) const override {
        if (m_IsActive) {
            for (const auto &p: m_Callbacks)
                if (p.key == key)
                    p.f();
            Container::interact(key);
        }
    }
private:
    bool m_IsActive;
    std::vector<Callback> m_Callbacks;
};

#endif //ASCIIART_MENU_HPP
