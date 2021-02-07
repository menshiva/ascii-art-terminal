#ifndef ASCII_PIXEL_HPP
#define ASCII_PIXEL_HPP

/**
 * @brief Image pixel.
 *
 * This class holds 3 components (_RED_, _GREEN_, _BLUE_).
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
struct Pixel {
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
    explicit Pixel(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0) : r(r), g(g), b(b) {}
};

#endif