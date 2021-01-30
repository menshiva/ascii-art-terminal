#ifndef SEMESTR_PIXEL_HPP
#define SEMESTR_PIXEL_HPP

/**
 * @brief Represents Image pixel.
 *
 * This class holds 3 components (_RED_, _GREEN_, _BLUE_).
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class Pixel {
public:
    unsigned char r; /**< Red component. */
    unsigned char g; /**< Green component. */
    unsigned char b; /**< Blue component. */

    /**
     * Constructor.
     *
     * @param r Red component value.
     * @param g Green component value.
     * @param b Blue component value.
     * @note All parameters are set to `0` by default.
     */
    explicit Pixel(const unsigned char r = 0U, const unsigned char g = 0U, const unsigned char b = 0U) : r(r), g(g), b(b) {}
};

#endif