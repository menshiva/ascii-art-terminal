#ifndef ASCIIART_PANEL_HPP
#define ASCIIART_PANEL_HPP

#include <panel.h>
#include "../base/View.hpp"

class Panel final : public Container {
public:
    explicit Panel(bool visible) : Container(), m_IsVisible(visible), m_Panel(new_panel(newwin(1, 1, 1, 1))) {}

    ~Panel() override {
        WINDOW *tmp = m_Panel->win;
        del_panel(m_Panel);
        delwin(tmp);
    }

    WINDOW *getWindow() const override {
        return m_Panel->win;
    }

    Panel *withChildren(std::initializer_list<View*> children) override {
        Container::withChildren(children);
        for (auto child : children) {
            child
                ->withRelativeHeight(1.0f)->withRelativeWidth(1.0f)
                ->withAbsoluteY(0)->withAbsoluteX(0);
        }
        return this;
    }

    bool isActive() const override {
        return m_IsVisible;
    }
protected:
    void draw() override {
        WINDOW *oldWin = m_Panel->win;
        replace_panel(m_Panel, newwin(getHeight(), getWidth(), getY(), getX()));
        delwin(oldWin);
        box(m_Panel->win, 0, 0);
        Container::draw();
    }
private:
    bool m_IsVisible;
    PANEL *m_Panel;
};

#endif //ASCIIART_PANEL_HPP
