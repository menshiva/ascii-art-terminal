#ifndef ASCII_VIEW_HPP
#define ASCII_VIEW_HPP

extern "C" {
#include <ncurses.h>
}
#include "../../utils/Consts.hpp"

class View {
protected:
    View *parent;
    size_t height, width;
    const float heightRelative, widthRelative;
    const float yRelative, xRelative;
public:
    View(View *parent,
         float heightRelative, float widthRelative,
         float yRelative, float xRelative) : parent(parent),
                                             height(0), width(0),
                                             heightRelative(heightRelative), widthRelative(widthRelative),
                                             yRelative(yRelative), xRelative(xRelative) {}
    View(const View &) = delete;
    View &operator=(const View &) = delete;
    View(View &&) = delete;
    View &operator=(View &&) = delete;
    virtual ~View() = default;

    virtual WINDOW *getWindow() const = 0;
    virtual size_t getHeight() const = 0;
    virtual size_t getWidth() const = 0;

    virtual void draw() = 0;
    virtual void resize() = 0;
};

#endif