#ifndef ASCII_PANEL_HPP
#define ASCII_PANEL_HPP

#include <cmath>
#include <panel.h>
#include "Text.hpp"
#include "Menu.hpp"

/**
 * @brief Provides panel View in user interface.
 *
 * This class is derived from View and holds all data, needed for panel.\n
 * Operates only with panel.\n
 * Other operations are implemented in View class.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class Panel : public View {
    PANEL *panel; /**< PANEL from ncurses.h. */
    Text *panelText; /**< Child text. */
    Menu *panelMenu; /**< Child menu. */
    bool visible; /**< Visibility flag. */
public:
    /**
     * Constructor.
     *
     * @param parent Pointer to parent view.
     * @param heightRelative Relative height, based on #parent view height (_in percent_).
     * @param widthRelative Relative width, based on #parent view width (_in percent_).
     * @param yRelative Relative _Y_ position, based on #parent view height (_in percent_).
     * @param xRelative Relative _X_ position, based on #parent view width (_in percent_).
     * @param isVisible Flag, which indicates if #panel is visible or not.
     */
    Panel(View *parent,
          float heightRelative, float widthRelative,
          float yRelative, float xRelative,
          bool isVisible);

    ///@attention Copy constructor is forbidden.
    Panel(const Panel &) = delete;

    ///@attention Copy assignment operator is forbidden.
    Panel &operator=(const Panel &) = delete;

    ///@attention Move constructor is forbidden.
    Panel(Panel &&) = delete;

    ///@attention Move assignment operator is forbidden.
    Panel &operator=(Panel &&) = delete;

    /**
     * Destructor.\n
     * _Frees_ memory allocated for #panel its WINDOW.
     * @attention Calls #panelText and #panelMenu destructors.
     */
    ~Panel() override;

    ///@return #panelText.
    Text *getPanelText() const;

    ///@return #panelMenu.
    Menu *getPanelMenu() const;

    /**
     * Sets #panelText.
     *
     * @param text New text in Panel.
     */
    void setPanelText(Text *text);

    /**
     * Sets #panelMenu.
     *
     * @param menu New menu in Panel.
     */
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