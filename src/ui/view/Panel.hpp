#ifndef ASCII_PANEL_HPP
#define ASCII_PANEL_HPP

#include <cmath>
#include <panel.h>
#include "View.hpp"

class Panel : public View {
    PANEL *panel;
    bool visible;
public:
    Panel(View *parent,
          float heightRelative, float widthRelative,
          float yRelative, float xRelative,
          bool isVisible);
    Panel(const Panel &) = delete;
    Panel &operator=(const Panel &) = delete;
    Panel(Panel &&) = delete;
    Panel &operator=(Panel &&) = delete;
    ~Panel() override;

    WINDOW *getWindow() const override;
    size_t getHeight() const override;
    size_t getWidth() const override;

    void draw() override;
    void resize() override;
    void show() override;
    void hide() override;
};

#endif