#ifndef SEMESTR_VIEW_HPP
#define SEMESTR_VIEW_HPP

#include "../../utils/Consts.hpp"

extern "C" {
#include <ncurses.h>
}

/**
 * @brief Abstract base class for all supported user interface elements.
 *
 * This class holds all data, needed for basic user interface element.\n
 * Operates with element in common way, such as: draw, refresh, hide, show, etc.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class View {
protected:
    const View *parent; /**< Pointer to parent view, in which current instance is drawn. */
    size_t height; /**< Height of view, computed from #heightRelative and #parent height (_in symbols_). */
    size_t width; /**< Width of view, computed from #widthRelative and #parent width (_in symbols_). */
    const double heightRelative; /**< Relative height, based on #parent view height (_in percent_). */
    const double widthRelative; /**< Relative width, based on #parent view width (_in percent_).  */
    const double yRelative; /**< Relative _Y_ position, based on #parent view height (_in percent_). */
    const double xRelative; /**< Relative _X_ position, based on #parent view width (_in percent_). */
    mutable bool drawn; /**< Flag, which indicates if view is drawn, or initialized only. */
public:
    /**
     * Constructor.
     *
     * @param parent Pointer to parent view, in which current instance will be drawn.
     * @param heightRelative Relative height, based on #parent view height (_in percent_).
     * @param widthRelative Relative width, based on #parent view width (_in percent_).
     * @param yRelative Relative _Y_ position, based on #parent view height (_in percent_).
     * @param xRelative Relative _X_ position, based on #parent view width (_in percent_).
     */
    View(const View *parent,
         double heightRelative, double widthRelative,
         double yRelative, double xRelative) : parent(parent),
                                               height(0U), width(0U),
                                               heightRelative(heightRelative), widthRelative(widthRelative),
                                               yRelative(yRelative), xRelative(xRelative),
                                               drawn(false) {}

    /**
     * @attention Copy constructor is forbidden.
     */
    View(const View &) = delete;

    /**
     * @attention Assignment operator is forbidden.
     */
    View &operator=(const View &) = delete;

    /**
     * Draws View in #parent.
     * @note Sets #drawn flag to `true`.
     */
    virtual void draw() const = 0;

    /**
     * Computes #height and #width of View, based on #heightRelative, #widthRelative and new sizes of #parent.
     * @note Sets #drawn flag to `false`.
     * @warning Function must be called _after_ #resize() of #parent was called.
     * @warning Function does _not_ draw View after computing.
     */
    virtual void resize() = 0;

    /**
     * Shows View in #parent.
     * @warning Shows #parent if View has no WINDOW.
     */
    virtual void show() const = 0;

    /**
     * Hides View in #parent.
     * @warning Hides #parent if View has no WINDOW.
     */
    virtual void hide() const = 0;

    /**
     * @return Current View WINDOW or #parent WINDOW if View has no WINDOW.
     */
    virtual WINDOW *getWindow() const = 0;

    /**
     * @return #height.
     */
    virtual size_t getHeight() const = 0;

    /**
     * @return #width.
     */
    virtual size_t getWidth() const = 0;

    /**
     * @return #drawn flag.
     */
    bool isDrawn() const {
        return drawn;
    }

    /**
     * Default destructor.
     */
    virtual ~View() = default;
};

#endif