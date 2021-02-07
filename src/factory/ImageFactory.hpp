#ifndef ASCII_IMAGEFACTORY_HPP
#define ASCII_IMAGEFACTORY_HPP

#include <iostream>
#include <experimental/filesystem>
#include "../image/format/JPEGImage.hpp"
#include "../image/format/PPMImage.hpp"

namespace fs = std::experimental::filesystem;

class ImageFactory {
    std::vector<Image *> images;
    std::string grayscaleLevel;
public:
    ImageFactory();
    ImageFactory(const ImageFactory &) = delete;
    ImageFactory &operator=(const ImageFactory &) = delete;
    ImageFactory(ImageFactory &&) = delete;
    ImageFactory &operator=(ImageFactory &&) = delete;
    ~ImageFactory();

    const std::vector<Image *> &getAllImages() const;

    bool readImage();
    void removeImage(Image *image);
    bool readGrayscaleLevel();
    bool applyEffect(Image *image);
    static void exportImage(const Image *image);
    Image *chooseImageFromList(const char *firstMessage) const;
};

#endif