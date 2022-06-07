// #ifndef ASCII_VIEW_HPP
// #define ASCII_VIEW_HPP
//
// extern "C" {
// #include <ncurses.h>
// }
// #include "../../utils/Consts.hpp"
//
// /**
//  * @brief Abstract base class for all supported user interface elements.
//  *
//  * Holds all data, needed for basic user interface element.\n
//  * Operates with element in common way, such as: draw, resize, getHeight, getWidth, etc.
//  *
//  * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
//  */
// class View {
// protected:
//     View *parent; /**< Pointer to parent view. */
//     size_t height; /**< Height of view, computed from #heightRelative and #parent height (_in symbols_). */
//     size_t width; /**< Width of view, computed from #widthRelative and #parent width (_in symbols_). */
//     float heightRelative; /**< Relative height, based on #parent view height (_in percent_). */
//     float widthRelative; /**< Relative width, based on #parent view width (_in percent_).  */
//     float yRelative; /**< Relative _Y_ position, based on #parent view height (_in percent_). */
//     float xRelative; /**< Relative _X_ position, based on #parent view width (_in percent_). */
// public:
//     /**
//      * Constructor.
//      *
//      * @param parent Pointer to parent view.
//      * @param heightRelative Relative height, based on #parent view height (_in percent_).
//      * @param widthRelative Relative width, based on #parent view width (_in percent_).
//      * @param yRelative Relative _Y_ position, based on #parent view height (_in percent_).
//      * @param xRelative Relative _X_ position, based on #parent view width (_in percent_).
//      */
//     View(View *parent,
//          float heightRelative, float widthRelative,
//          float yRelative, float xRelative) : parent(parent),
//                                              height(0), width(0),
//                                              heightRelative(heightRelative), widthRelative(widthRelative),
//                                              yRelative(yRelative), xRelative(xRelative) {}
//
//     ///@attention Copy constructor is forbidden.
//     View(const View &) = delete;
//
//     ///@attention Copy assignment operator is forbidden.
//     View &operator=(const View &) = delete;
//
//     ///@attention Move constructor is forbidden.
//     View(View &&) = delete;
//
//     ///@attention Move assignment operator is forbidden.
//     View &operator=(View &&) = delete;
//
//     ///Destructor.
//     virtual ~View() = default;
//
//     ///@return Current View WINDOW or #parent WINDOW if View has no WINDOW.
//     virtual WINDOW *getWindow() const = 0;
//
//     ///@return #height.
//     virtual size_t getHeight() const = 0;
//
//     ///@return #width.
//     virtual size_t getWidth() const = 0;
//
//     ///Draws View in #parent.
//     virtual void draw() = 0;
//
//     /**
//      * Computes #height and #width of View, based on #heightRelative, #widthRelative and new #parent sizes.
//      * @warning Function must be called _after_ #parent was resized.
//      * @warning Function does _not_ draw View after computing.
//      */
//     virtual void resize() = 0;
// };
//
// #endif
