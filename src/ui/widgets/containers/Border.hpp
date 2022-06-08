#ifndef ASCIIART_BORDER_HPP
#define ASCIIART_BORDER_HPP

#include <panel.h>
#include "Container.hpp"

class Border : public Container {
public:
    explicit Border(View *child) : Container(child), m_Panel(new_panel(newwin(1, 1, 1, 1))) {}

    ~Border() override {
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
private:
    PANEL *m_Panel;
};

#endif //ASCIIART_BORDER_HPP
