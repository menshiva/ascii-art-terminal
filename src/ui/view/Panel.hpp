#ifndef ASCII_PANEL_HPP
#define ASCII_PANEL_HPP

#include <cmath>
#include <panel.h>
#include "Text.hpp"
#include "Menu.hpp"

class Panel : public View {
    PANEL *panel;
    Text *panelText;
    Menu *panelMenu;
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

    Text *getPanelText() const;
    Menu *getPanelMenu() const;

    void setPanelText(Text *text);
    void setPanelMenu(Menu *menu);

    void show();
    void hide();

    WINDOW *getWindow() const override;
    size_t getHeight() const override;
    size_t getWidth() const override;

    void draw() override;
    void resize() override;
};

#endif