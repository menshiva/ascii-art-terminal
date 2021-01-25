#include "PPMImage.hpp"

PPMImage::PPMImage(const std::string &imgPath) : Image(imgPath), firstLetter('\0'), num(0U), brightness(0U) {}

bool PPMImage::loadFromFile() {
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    // read PPM metadata
    ifs >> firstLetter >> num >> width >> height >> brightness;
    // ignore \n
    ifs.ignore(1);

    // if image is not P6 (indicates PPM format) or height == 0 or width == 0 then conversion wasn't successful
    if (firstLetter != 'P' || num != 6U || height == 0U || width == 0U) return false;

    // 3 because of RGB components
    std::vector<unsigned char> data(3U * height * width);
    ifs.read((char *) &data[0U], data.size());
    ifs.close();

    rawData.resize(height, std::vector<Pixel>(width));
    rawAsciiData.resize(height, std::string("", width));

    // convert components data to pixels data
    size_t row = 0U, col = 0U;
    for (size_t dataI = 0U; dataI < data.size(); dataI += 3U) {
        rawData[row][col].r = data[dataI];
        rawData[row][col].g = data[dataI + 1U];
        rawData[row][col].b = data[dataI + 2U];
        if (++col >= width) {
            col = 0U;
            ++row;
        }
    }

    return true;
}