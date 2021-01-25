#ifndef SEMESTR_PANEL_HPP
#define SEMESTR_PANEL_HPP

#include "View.hpp"
#include <panel.h>
#include <cmath>

/**
 * @brief Provides panel View in user interface.
 *
 * This class is derived from View and holds all data, needed for panel.\n
 * Operates only with panel. Other operations are implemented in View class.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class Panel : public View {
    PANEL *panel; /**< PANEL from ncurses.h. */
    mutable bool panelVisibility; /**< Flag, which indicates if Panel is shown or not. */
public:
    /**
     * Constructor.
     *
     * @param parent Pointer to parent view, in which current instance will be drawn.
     * @param heightRelative Relative height, based on #parent view height (_in percent_).
     * @param widthRelative Relative width, based on #parent view width (_in percent_).
     * @param yRelative Relative _Y_ position, based on #parent view height (_in percent_).
     * @param xRelative Relative _X_ position, based on #parent view width (_in percent_).
     * @param isVisible Flag, which indicates if #panel is shown or not.
     */
    Panel(const View *parent,
          double heightRelative, double widthRelative,
          double yRelative, double xRelative,
          bool isVisible);

    /**
     * @attention Copy constuctor is forbidden.
     */
    Panel(const Panel &) = delete;

    /**
     * @attention Assignment operator is forbidden.
     */
    Panel &operator=(const Panel &) = delete;

    void draw() const override;

    void resize() override;

    void show() const override;

    void hide() const override;

    WINDOW *getWindow() const override;

    size_t getHeight() const override;

    size_t getWidth() const override;

    /**
     * Destructor deletes #panel and its WINDOW.
     */
    ~Panel() override;
};

#endif