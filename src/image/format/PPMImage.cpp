#include "PPMImage.hpp"

PPMImage::PPMImage(const std::string &imgPath) : Image(imgPath), firstLetter('\0'), num(0u), brightness(0u) {}

bool PPMImage::loadFromFile() {
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    // read PPM metadata
    ifs >> firstLetter >> num >> width >> height >> brightness;
    // ignore \n
    ifs.ignore(1);

    // if image is not P6 (indicates PPM format) or height == 0 or width == 0 then convertation wasn't successfull
    if (firstLetter != 'P' || num != 6u || height == 0u || width == 0u) return false;

    // 3 because of RGB components
    std::vector<unsigned char> data(3u * height * width);
    ifs.read((char *) &data[0u], data.size());
    ifs.close();

    rawData.resize(height, std::vector<Pixel>(width));
    rawAsciiData.resize(height, std::string("", width));

    // convert components data to pixels data
    size_t row = 0u, col = 0u;
    for (size_t dataI = 0u; dataI < data.size(); dataI += 3u) {
        rawData[row][col].r = data[dataI];
        rawData[row][col].g = data[dataI + 1u];
        rawData[row][col].b = data[dataI + 2u];
        if (++col >= width) {
            col = 0u;
            ++row;
        }
    }

    return true;
}