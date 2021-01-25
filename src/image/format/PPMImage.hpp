#ifndef SEMESTR_PPMIMAGE_HPP
#define SEMESTR_PPMIMAGE_HPP

#include "../Image.hpp"
#include <fstream>

/**
 * @brief Support for PPM image format.
 *
 * This class is derived from Image and holds all data, needed for PPM format.\n
 * Operates only with reading data from image file. Other operations are implemented in Image class.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class PPMImage : public Image {
    unsigned char firstLetter; /**< First part of magic number, indicating _Portable pixmap_ format. */
    size_t num; /**< Second part of magic number, indicating _Portable pixmap_ format type. */
    size_t brightness; /**< _Portable pixmap_ image brightness. */
public:
    /**
     * Constructor initializes image by setting its #Image::path.
     * @note Sets #firstLetter to `\0` and #num and #brightness to `0`.
     *
     * @param imgPath _Absolute_ path to image file.
     */
    explicit PPMImage(const std::string &imgPath);

    /**
     * @attention Copy constuctor is forbidden.
     */
    PPMImage(const PPMImage &) = delete;

    /**
     * @attention Assignment operator is forbidden.
     */
    PPMImage &operator=(const PPMImage &) = delete;

    bool loadFromFile() override;

    /**
     * Default destructor.
     */
    ~PPMImage() override = default;
};

#endif