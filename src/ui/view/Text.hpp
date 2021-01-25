#ifndef SEMESTR_TEXT_HPP
#define SEMESTR_TEXT_HPP

#include "View.hpp"
#include <string>

/**
 * @brief Provides text View in user interface.
 *
 * This class is derived from View and holds all data, needed for text.\n
 * Operates only with text. Other operations are implemented in View class.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class Text : public View {
    std::string text; /**< Text to draw. */
public:
    /**
     * Constructor.
     *
     * @param parent Pointer to parent view, in which current instance will be drawn.
     * @param text Text to draw.
     * @param yRelative Relative _Y_ position, based on #parent view height (_in percent_).
     * @param xRelative Relative _X_ position, based on #parent view width (_in percent_).
     */
    Text(const View *parent, std::string text, double yRelative, double xRelative);

    /**
     * @attention Copy constructor is forbidden.
     */
    Text(const Text &) = delete;

    /**
     * @attention Assignment operator is forbidden.
     */
    Text &operator=(const Text &) = delete;

    /**
     * Replaces #text.
     * @note This function calls #draw().
     *
     * @param newText New text to draw.
     */
    void changeText(const std::string &newText);

    void draw() const override;

    /**
     * @attention This function is _not_ implemented in Text because Text does not have WINDOW.
     */
    void resize() override;

    void show() const override;

    void hide() const override;

    WINDOW *getWindow() const override;

    size_t getHeight() const override;

    size_t getWidth() const override;

    /**
     * Default destructor.
     */
    ~Text() override = default;
};

#endif