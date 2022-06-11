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

    void setVisibility(bool visible) {
        m_IsVisible = visible;
        if (visible) show_panel(m_Panel);
        else hide_panel(m_Panel);
    }

    WINDOW *getWindow() const override {
        return m_Panel->win;
    }

    Panel *withChildren(std::initializer_list<Child> children) override {
        Container::withChildren(children);
        for (const auto &child : m_Children) {
            child.view
                ->withRelativeHeight(1.0f)->withRelativeWidth(1.0f)
                ->withAbsoluteY(0)->withAbsoluteX(0);
        }
        return this;
    }

    void onChildWithId(Id id, View *child) override {
        m_ParentContainer->onChildWithId(id, child);
    }
protected:
    void draw() override {
        if (m_IsVisible) {
            WINDOW *oldWin = m_Panel->win;
            replace_panel(m_Panel, newwin(getHeight(), getWidth(), getY(), getX()));
            delwin(oldWin);
            box(m_Panel->win, 0, 0);
            Container::draw();
        }
    }
private:
    bool m_IsVisible;
    PANEL *m_Panel;
};

#endif //ASCIIART_PANEL_HPP
