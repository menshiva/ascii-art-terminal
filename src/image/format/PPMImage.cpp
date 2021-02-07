#include "PPMImage.hpp"

PPMImage::PPMImage(const std::string &imgPath) : Image(imgPath) {}

bool PPMImage::loadFromFile() {
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    // read PPM metadata
    unsigned char firstLetter = '\0';
    size_t num = 0;
    size_t brightness = 0;
    ifs >> firstLetter >> num >> width >> height >> brightness;
    // ignore \n
    ifs.ignore(1);

    // if image is not P6 (indicates PPM format) or height == 0 or width == 0 then conversion wasn't successful
    if (firstLetter != 'P' || num != 6 || height == 0 || width == 0) return false;

    // 3 because of RGB components
    std::vector<unsigned char> data(3 * height * width);
    ifs.read((char *) &data[0], data.size());
    ifs.close();

    rawData.resize(height, std::vector<Pixel>(width));
    rawAsciiData.resize(height, std::string("", width));

    // convert components data to pixels data
    size_t row = 0, col = 0;
    for (size_t dataI = 0; dataI < data.size(); dataI += 3) {
        rawData[row][col].r = data[dataI];
        rawData[row][col].g = data[dataI + 1];
        rawData[row][col].b = data[dataI + 2];
        if (++col >= width) {
            col = 0;
            ++row;
        }
    }

    return true;
}