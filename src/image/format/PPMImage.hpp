#ifndef ASCII_PPMIMAGE_HPP
#define ASCII_PPMIMAGE_HPP

#include <fstream>
#include "../Image.hpp"

class PPMImage : public Image {
public:
    explicit PPMImage(const std::string &imgPath);
    PPMImage(const PPMImage &) = delete;
    PPMImage &operator=(const PPMImage &) = delete;
    PPMImage(PPMImage &&) = delete;
    PPMImage &operator=(PPMImage &&) = delete;
    ~PPMImage() override = default;

    bool loadFromFile() override;
};

#endif