#ifndef ASCIIART_SCREEN_HPP
#define ASCIIART_SCREEN_HPP

#include <panel.h>
#include "../base/View.hpp"

struct Screen final : public Container {
    Screen(std::initializer_list<View*> children) : Container(children) {
        setHeight([]() -> uint16_t { return getmaxy(stdscr); });
        setWidth([]() -> uint16_t { return getmaxx(stdscr); });
        setAbsoluteY(0);
        setAbsoluteX(0);
        for (auto child : children)
            child
                ->setRelativeParentHeight(1.0f)
                ->setRelativeParentWidth(1.0f)
                ->setAbsoluteY(0)
                ->setAbsoluteX(0);
    }

    WINDOW *getWindow() const override {
        return stdscr;
    }

    void draw() override {
        Container::draw();
        update_panels();
        doupdate();
    }
};

#endif //ASCIIART_SCREEN_HPP
