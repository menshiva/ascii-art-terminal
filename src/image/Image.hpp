#ifndef ASCII_IMAGE_HPP
#define ASCII_IMAGE_HPP

#include <vector>
#include "../utils/Utils.hpp"
#include "../utils/Consts.hpp"

class Image {
protected:
    const std::string path;
    std::vector<std::vector<Pixel>> rawData;
    std::vector<std::string> rawAsciiData;
    mutable std::vector<std::string> resizedAsciiData;
    size_t height;
    size_t width;
    bool isContrasted;
    bool isNegatived;
    bool isSharpened;

    static unsigned char rgbToGray(const Pixel &pixel);
    static void applyContrast(Pixel &pixel, double level = AsciiConsts::DEFAULT_CONTRAST_LEVEL);
    static void applyNegative(Pixel &pixel);
    static std::vector<std::vector<Pixel>> applySharpen(const std::vector<std::vector<Pixel>> &src);
public:
    explicit Image(std::string imgPath);
    Image(const Image &) = delete;
    Image &operator=(const Image &) = delete;
    Image(Image &&) = delete;
    Image &operator=(Image &&) = delete;
    virtual ~Image() = default;

    const std::string &getPath() const;
    const std::vector<std::string> &getRawAsciiData() const;
    bool hasContrast() const;
    bool hasNegative() const;
    bool hasSharpen() const;

    void toggleContrast();
    void toggleNegative();
    void toggleSharpen();

    void convertToAscii(const std::string &grayscaleLevel);
    void computeArtSize(size_t &viewH, size_t &viewW) const;
    const std::vector<std::string> &getAsciiArt(size_t asciiH, size_t asciiW) const;

    virtual bool loadFromFile() = 0;
};

#endif