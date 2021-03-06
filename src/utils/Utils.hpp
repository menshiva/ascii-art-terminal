#ifndef ASCII_UTILS_HPP
#define ASCII_UTILS_HPP

#include <algorithm>
#include <string>
#include <cmath>
#include "../image/Pixel.hpp"

/**
 * @brief Utilities.
 *
 * Utility functions.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
namespace Utils {
    /**
     * Eliminates leading and trailing spaces from string.
     *
     * @param[in] s string.
     * @param[out] s Omitted string without spaces.
     */
    static inline void trim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {
            return !std::isspace(c);
        }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {
            return !std::isspace(c);
        }).base(), s.end());
    }

    /**
     * Truncates variable to unsigned char value.
     *
     * @tparam T Type of variable which you want to truncate.
     * @param toTrunc Variable to truncate.
     * @return _toTrunc_ truncated to unsigned char.
     */
    template<class T>
    static inline unsigned char truncateToUnsignedChar(T toTrunc) {
        return (toTrunc > static_cast<T>(255)) ? 255 : ((toTrunc < static_cast<T>(0))
                                                        ? 0
                                                        : static_cast<unsigned char>(toTrunc));
    }
}

#endif