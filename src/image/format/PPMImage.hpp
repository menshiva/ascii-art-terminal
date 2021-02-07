#ifndef ASCII_PPMIMAGE_HPP
#define ASCII_PPMIMAGE_HPP

#include <fstream>
#include "../Image.hpp"

/**
 * @brief PPM image format.
 *
 * This class is derived from Image and holds all PPM format data.\n
 * Operates only with reading data from image file.\n
 * Other operations are implemented in Image class.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class PPMImage : public Image {
public:
    /**
     * Constructor.\n
     * Initializes image by setting its #Image::path.
     *
     * @param imgPath _Absolute_ path to image file.
     */
    explicit PPMImage(const std::string &imgPath);

    ///@attention Copy constructor is forbidden.
    PPMImage(const PPMImage &) = delete;

    ///@attention Copy assignment operator is forbidden.
    PPMImage &operator=(const PPMImage &) = delete;

    ///@attention Move constructor is forbidden.
    PPMImage(PPMImage &&) = delete;

    ///@attention Move assignment operator is forbidden.
    PPMImage &operator=(PPMImage &&) = delete;

    ///Destructor.
    ~PPMImage() override = default;

    bool loadFromFile() override;
};

#endif