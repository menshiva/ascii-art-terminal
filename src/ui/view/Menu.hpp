// #ifndef ASCII_MENU_HPP
// #define ASCII_MENU_HPP
//
// #include <algorithm>
// #include <menu.h>
// #include "View.hpp"
//
// /**
//  * @brief Provides menu View in user interface.
//  *
//  * This class is derived from View and holds all data, needed for menu.\n
//  * Operates only with menu.\n
//  * Other operations are implemented in View class.
//  *
//  * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
//  */
// class Menu : public View {
//     MENU *menu; /**< MENU from ncurses.h. */
//     size_t rows; /**< Rows count in #menu. */
//     std::vector<ITEM *> items; /**< #menu items. */
//
//     std::function<void(size_t)> onClickCallback; /**< On item click event listener. */
// public:
//     /**
//      * Constructor.
//      *
//      * @param parent Pointer to parent view.
//      * @param yRelative Relative _Y_ position, based on #parent view height (_in percent_).
//      * @param xRelative Relative _X_ position, based on #parent view width (_in percent_).
//      * @param rows Rows count in #menu.
//      * @param cols Columns count in #menu.
//      * @param newItems #menu items.
//      * @param disabledItems Disabled #items indexes.
//      * @param onClickCallback Item click event listener.
//      */
//     Menu(View *parent,
//          float yRelative, float xRelative,
//          size_t rows, size_t cols,
//          std::vector<ITEM *> newItems,
//          const std::initializer_list<size_t> &disabledItems,
//          std::function<void(size_t)> onClickCallback);
//
//     ///@attention Copy constructor is forbidden.
//     Menu(const Menu &) = delete;
//
//     ///@attention Copy assignment operator is forbidden.
//     Menu &operator=(const Menu &) = delete;
//
//     ///@attention Move constructor is forbidden.
//     Menu(Menu &&) = delete;
//
//     ///@attention Move assignment operator is forbidden.
//     Menu &operator=(Menu &&) = delete;
//
//     /**
//      * Destructor.\n
//      * _Frees_ memory allocated for #menu, its WINDOW and its #items.
//      */
//     ~Menu() override;
//
//     /**
//      * Toggles specific item from #items by given index.
//      *
//      * @param idx Item index from #items.
//      * @param enable Enable/disable item.
//      */
//     void toggleItem(size_t idx, bool enable);
//
//     /**
//      * Update menu selection.
//      * @note Invokes #onClickCallback with currently selected item on ENTER key.
//      *
//      * @param key Pressed key.
//      */
//     void menuInteract(int key) const;
//
//     WINDOW *getWindow() const override;
//     size_t getHeight() const override;
//     size_t getWidth() const override;
//
//     void draw() override;
//     void resize() override;
// };
//
// #endif
