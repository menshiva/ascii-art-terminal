#include "Image.hpp"

unsigned char Image::rgbToGray(const Pixel &pixel) {
    // get gamma compressed components
    double gammaCompressedR = pixel.r / 255.0,
            gammaCompressedG = pixel.g / 255.0,
            gammaCompressedB = pixel.b / 255.0;
    // convert to linear components
    double Rlin = (gammaCompressedR <= 0.04045)
                  ? gammaCompressedR / 12.92
                  : pow((gammaCompressedR + 0.055) / 1.055, 2.4);
    double Glin = (gammaCompressedG <= 0.04045)
                  ? gammaCompressedG / 12.92
                  : pow((gammaCompressedG + 0.055) / 1.055, 2.4);
    double Blin = (gammaCompressedB <= 0.04045)
                  ? gammaCompressedB / 12.92
                  : pow((gammaCompressedB + 0.055) / 1.055, 2.4);
    // get basic linear luminance
    double linearLuminance = Rlin * 0.2126 + Glin * 0.7152 + Blin * 0.0722;
    // convert to gamma compressed luminance
    double gammaCompressedLuminance = (linearLuminance <= 0.0031308)
                                      ? linearLuminance * 12.92
                                      : 1.055 * pow(linearLuminance, 1.0 / 2.4) - 0.055;
    // return gamma compressed luminance normalized to gray color value
    return static_cast<unsigned char>(gammaCompressedLuminance * 255.0);
}

void Image::applyContrast(Pixel &pixel, double level) {
    double factor = (259.0 * (level + 255.0)) / (255.0 * (259.0 - level));
    double nonTruncContrastedR = factor * (static_cast<double>(pixel.r) - 128.0) + 128.0;
    double nonTruncContrastedG = factor * (static_cast<double>(pixel.g) - 128.0) + 128.0;
    double nonTruncContrastedB = factor * (static_cast<double>(pixel.b) - 128.0) + 128.0;
    pixel.r = Utils::truncateToUnsignedChar<double>(nonTruncContrastedR);
    pixel.g = Utils::truncateToUnsignedChar<double>(nonTruncContrastedG);
    pixel.b = Utils::truncateToUnsignedChar<double>(nonTruncContrastedB);
}

void Image::applyNegative(Pixel &pixel) {
    pixel.r = 255 - pixel.r;
    pixel.g = 255 - pixel.g;
    pixel.b = 255 - pixel.b;
}

std::vector<std::vector<Pixel>> Image::applySharpen(const std::vector<std::vector<Pixel>> &src) {
    std::vector<std::vector<Pixel>> convoluted(src);
    for (size_t row = 1; row < convoluted.size() - 1; ++row) {
        for (size_t col = 1; col < convoluted[row].size() - 1; ++col) {
            // 5 * center pixel - left pixel - right pixel - pixel below - pixel above
            const int convolutedR = 5 * static_cast<int>(src[row][col].r)
                                    - static_cast<int>(src[row][col - 1].r)
                                    - static_cast<int>(src[row][col + 1].r)
                                    - static_cast<int>(src[row - 1][col].r)
                                    - static_cast<int>(src[row + 1][col].r);
            const int convolutedG = 5 * static_cast<int>(src[row][col].g)
                                    - static_cast<int>(src[row][col - 1].g)
                                    - static_cast<int>(src[row][col + 1].g)
                                    - static_cast<int>(src[row - 1][col].g)
                                    - static_cast<int>(src[row + 1][col].g);
            const int convolutedB = 5 * static_cast<int>(src[row][col].b)
                                    - static_cast<int>(src[row][col - 1].b)
                                    - static_cast<int>(src[row][col + 1].b)
                                    - static_cast<int>(src[row - 1][col].b)
                                    - static_cast<int>(src[row + 1][col].b);

            convoluted[row][col].r = Utils::truncateToUnsignedChar<int>(convolutedR);
            convoluted[row][col].g = Utils::truncateToUnsignedChar<int>(convolutedG);
            convoluted[row][col].b = Utils::truncateToUnsignedChar<int>(convolutedB);
        }
    }
    return convoluted;
}

Image::Image(std::string imgPath) : path(std::move(imgPath)),
                                    height(0), width(0),
                                    isContrasted(false), isNegatived(false), isSharpened(false) {}

const std::string &Image::getPath() const {
    return path;
}

const std::vector<std::string> &Image::getRawAsciiData() const {
    return rawAsciiData;
}

bool Image::hasContrast() const {
    return isContrasted;
}

bool Image::hasNegative() const {
    return isNegatived;
}

bool Image::hasSharpen() const {
    return isSharpened;
}

void Image::toggleContrast() {
    isContrasted ^= 1;
}

void Image::toggleNegative() {
    isNegatived ^= 1;
}

void Image::toggleSharpen() {
    isSharpened ^= 1;
}

void Image::convertToAscii(const std::string &grayscaleLevel) {
    resizedAsciiData.clear();
    auto data = hasSharpen() ? applySharpen(rawData) : rawData;
    for (size_t row = 0; row < height; ++row) {
        for (size_t col = 0; col < width; ++col) {
            Pixel pixel = data[row][col];
            if (hasNegative()) applyNegative(pixel);
            if (hasContrast()) applyContrast(pixel);
            rawAsciiData[row][col] = grayscaleLevel[static_cast<size_t>(rgbToGray(pixel) / 255.0 * grayscaleLevel.size())];
        }
    }
}

void Image::computeArtSize(size_t &viewH, size_t &viewW) const {
    size_t asciiH, asciiW;
    if (height >= width) {
        // if height of image >= width of image, then compute new width first
        asciiW = static_cast<size_t>(width * (viewH / (height / 2.0)));
        // if viewW < new width, then compute new height and base new width on viewW
        // otherwise base new height on viewH
        if (viewW < asciiW) {
            asciiH = static_cast<size_t>(viewH * (static_cast<double>(viewW) / asciiW));
            asciiW = viewW;
        } else asciiH = viewH;
    } else {
        // if height of image < width of image, then compute new height first
        asciiH = static_cast<size_t>((height / 2.0) * (static_cast<double>(viewW) / width));
        // if viewH < new height, then compute new width and base new height on viewH
        // otherwise base new width on viewW
        if (viewH < asciiH) {
            asciiW = static_cast<size_t>(viewW * (static_cast<double>(viewH) / asciiH));
            asciiH = viewH;
        } else asciiW = viewW;
    }
    viewH = asciiH;
    viewW = asciiW;
}

const std::vector<std::string> &Image::getAsciiArt(size_t asciiH, size_t asciiW) const {
    // if resizedAsciiData wasn't changed and has the same size as asciiH and asciiW
    // then return resizedAsciiData (optimization for animation)
    if (!resizedAsciiData.empty() && resizedAsciiData.size() == asciiH && resizedAsciiData[0].size() == asciiW)
        return resizedAsciiData;

    resizedAsciiData.clear();
    resizedAsciiData.resize(asciiH, std::string("", asciiW));

    double scaleHeight = static_cast<double>(asciiH) / height;
    double scaleWidth = static_cast<double>(asciiW) / width;

    // art scaling based on asciiH, asciiW and image size
    for (size_t row = 0; row < asciiH; ++row)
        for (size_t col = 0; col < asciiW; ++col)
            resizedAsciiData[row][col] = rawAsciiData[row / scaleHeight][col / scaleWidth];

    return resizedAsciiData;
}