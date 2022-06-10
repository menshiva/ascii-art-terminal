#ifndef ASCIIART_PANEL_HPP
#define ASCIIART_PANEL_HPP

#include <panel.h>
#include "../base/View.hpp"

class Panel final : public Container {
public:
    Panel(bool visible, std::initializer_list<View*> children) :
        Container(children),
        m_IsVisible(visible),
        m_Panel(new_panel(newwin(1, 1, 1, 1)))
    {
        for (auto child : children)
            child
                    ->setRelativeParentHeight(1.0f)
                    ->setRelativeParentWidth(1.0f)
                    ->setAbsoluteY(0)
                    ->setAbsoluteX(0);
    }

    ~Panel() override {
        WINDOW *tmp = m_Panel->win;
        del_panel(m_Panel);
        delwin(tmp);
    }

    WINDOW *getWindow() const override {
        return m_Panel->win;
    }

    void draw() override {
        WINDOW *oldWin = m_Panel->win;
        replace_panel(m_Panel, newwin(getHeight(), getWidth(), getY(), getX()));
        delwin(oldWin);
        box(m_Panel->win, 0, 0);
        Container::draw();
    }

    bool isActive() const override {
        return m_IsVisible;
    }
private:
    bool m_IsVisible;
    PANEL *m_Panel;
};

#endif //ASCIIART_PANEL_HPP
