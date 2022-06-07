// #ifndef ASCII_TEXT_HPP
// #define ASCII_TEXT_HPP
//
// #include <string>
// #include "View.hpp"
//
// /**
//  * @brief Provides text View in user interface.
//  *
//  * This class is derived from View and holds all data, needed for text.\n
//  * Operates only with text.\n
//  * Other operations are implemented in View class.
//  *
//  * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
//  */
// class Text : public View {
//     std::string text; /**< Text to draw. */
// public:
//     /**
//      * Constructor.
//      *
//      * @param parent Pointer to parent view.
//      * @param text Text to draw.
//      * @param yRelative Relative _Y_ position, based on #parent view height (_in percent_).
//      * @param xRelative Relative _X_ position, based on #parent view width (_in percent_).
//      */
//     Text(View *parent, std::string text, float yRelative, float xRelative);
//
//     ///@attention Copy constructor is forbidden.
//     Text(const Text &) = delete;
//
//     ///@attention Copy assignment operator is forbidden.
//     Text &operator=(const Text &) = delete;
//
//     ///@attention Move constructor is forbidden.
//     Text(Text &&) = delete;
//
//     ///@attention Move assignment operator is forbidden.
//     Text &operator=(Text &&) = delete;
//
//     ///Destructor.
//     ~Text() override = default;
//
//     /**
//      * Print given text.
//      * @note This function calls #draw().
//      *
//      * @param newText New text to draw.
//      */
//     void changeText(const std::string &newText);
//
//     WINDOW *getWindow() const override;
//     size_t getHeight() const override;
//     size_t getWidth() const override;
//
//     void draw() override;
//
//     ///@attention This function is _not_ implemented in Text because Text does not have WINDOW.
//     void resize() override;
// };
//
// #endif
