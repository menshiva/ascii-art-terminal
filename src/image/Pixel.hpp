#ifndef SEMESTR_PIXEL_HPP
#define SEMESTR_PIXEL_HPP

/**
 * @brief Represents Image pixel.
 *
 * This class holds 3 components (_RED_, _GREEN_, _BLUE_) of each pixel in Image.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class Pixel {
public:
    unsigned char r; /**< Red component. */
    unsigned char g; /**< Green component. */
    unsigned char b; /**< Blue component. */

    /**
     * Constuctor.
     *
     * @param r Red component value.
     * @param g Green component value.
     * @param b Blue component value.
     * @note All parameters have default values set to `0`.
     */
    explicit Pixel(const unsigned char r = 0u, const unsigned char g = 0u, const unsigned char b = 0u) : r(r), g(g), b(b) {}
};

#endif