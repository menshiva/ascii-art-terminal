#ifndef ASCIIART_VIEW_HPP
#define ASCIIART_VIEW_HPP

#include <cstdint>
#include <curses.h>

class View {
public:
    View() : m_Parent(nullptr) {}

    View(const View&) = delete;
    View &operator=(const View&) = delete;
    View(View&&) = delete;
    View &operator=(View&&) = delete;

    virtual WINDOW *getWindow() const = 0;
    virtual uint16_t getHeight() const = 0;
    virtual uint16_t getWidth() const = 0;
    virtual uint16_t getY() const = 0;
    virtual uint16_t getX() const = 0;

    const View *getParent() const {
        return m_Parent;
    }

    void setParent(View *parent) {
        m_Parent = parent;
    }

    virtual void setChild(View *child) = 0;

    virtual void draw() = 0;
private:
    View *m_Parent;
};

#endif //ASCIIART_VIEW_HPP
