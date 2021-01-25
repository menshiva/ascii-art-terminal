#ifndef SEMESTR_MENU_HPP
#define SEMESTR_MENU_HPP

#include "View.hpp"
#include <menu.h>
#include <vector>

/**
 * @brief Provides menu View in user interface.
 *
 * This class is derived from View and holds all data, needed for menu.\n
 * Operates only with menu. Other operations are implemented in View class.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class Menu : public View {
    MENU *menu; /**< MENU from ncurses.h. */
    size_t rows; /**< Rows count in #menu. */
    size_t cols; /**< Columns count in #menu. */
    std::vector<ITEM *> *items; /**< Items in #menu. */
public:
    /**
     * Constructor.
     *
     * @param parent Pointer to parent view, in which current instance will be drawn.
     * @param yRelative Relative _Y_ position, based on #parent view height (_in percent_).
     * @param xRelative Relative _X_ position, based on #parent view width (_in percent_).
     * @param rows Rows count in #menu.
     * @param cols Columns count in #menu.
     * @param newItems Items in #menu.
     * @param disabledItems Indexes of disabled #items.
     */
    Menu(const View *parent,
         double yRelative, double xRelative,
         size_t rows, size_t cols,
         std::vector<ITEM *> *newItems,
         const std::initializer_list<size_t> &disabledItems);

    /**
     * @attention Copy constuctor is forbidden.
     */
    Menu(const Menu &) = delete;

    /**
     * @attention Assignment operator is forbidden.
     */
    Menu &operator=(const Menu &) = delete;

    /**
     * Toggles item from #items by _pos_ index.
     *
     * @param pos Item index from #items.
     * @param enable Enable/disable item.
     */
    void toggleItem(size_t pos, bool enable);

    void draw() const override;

    void resize() override;

    void show() const override;

    void hide() const override;

    WINDOW *getWindow() const override;

    size_t getHeight() const override;

    size_t getWidth() const override;

    /**
     * Handles keyboard actions and updates #menu, basing on this actions.
     *
     * @return Index of chosen item from #menu.
     */
    size_t keyboardListener() const;

    /**
     * Destructor deletes #menu, its WINDOW and its #items.
     */
    ~Menu() override;
};

#endif