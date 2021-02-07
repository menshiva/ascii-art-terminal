#include "ImageFactory.hpp"

ImageFactory::ImageFactory() : grayscaleLevel(AsciiConsts::DEFAULT_GRAYSCALE_LEVEL) {}

ImageFactory::~ImageFactory() {
    for (Image *img : images) delete img;
}

const std::vector<Image *> &ImageFactory::getAllImages() const {
    return images;
}

bool ImageFactory::readImage() {
    // if at least 1 image was added successfully
    bool isImageRead = false;
    while (true) {
        fs::path path;
        std::string pathStr;

        std::cout << "\n" << ConsoleConsts::TITLE_SYMBOL << ConsoleConsts::ENTER_IMAGE_PATH << "\n" << std::endl;

        while (true) {
            pathStr.clear();
            std::cin.clear();
            std::cout << ConsoleConsts::INPUT_SYMBOLS;
            // read path
            std::getline(std::cin, pathStr);

            Utils::trim(pathStr);

            if (pathStr.empty()) continue;
            else if (pathStr == "q") return isImageRead;

            // if pathStr contains leading and trailing apostrophes
            if (pathStr.front() == '\'') pathStr.erase(pathStr.begin());
            if (pathStr.back() == '\'') pathStr.erase(pathStr.end() - 1);

            path = fs::path(pathStr);

            if (!fs::exists(path)) {
                std::cout << "\n"
                          << ConsoleConsts::TITLE_SYMBOL
                          << ConsoleConsts::ERROR_FILE_NOT_FOUND
                          << " "
                          << ConsoleConsts::TRY_ANOTHER_FILE
                          << "\n" << std::endl;
                continue;
            }

            if (path.is_relative()) {
                std::cout << "\n"
                          << ConsoleConsts::TITLE_SYMBOL
                          << ConsoleConsts::ERROR_PATH_RELATIVE
                          << " "
                          << ConsoleConsts::TRY_AGAIN
                          << "\n" << std::endl;
                continue;
            }

            // check file suffix and normalize it
            if (path.extension() == ".jpg" || path.extension() == ".JPG" || path.extension() == ".JPEG")
                path.replace_extension(".jpeg");
            else if (path.extension() == ".PPM")
                path.replace_extension(".ppm");
            else if (path.extension() != ".jpeg" && path.extension() != ".ppm") {
                std::cout << "\n"
                          << ConsoleConsts::TITLE_SYMBOL
                          << ConsoleConsts::ERROR_FILE_UNSUPPORTED
                          << " "
                          << ConsoleConsts::TRY_ANOTHER_FILE
                          << "\n" << std::endl;
                continue;
            }

            // check if file can be opened
            std::ifstream imgStream(pathStr);
            if (imgStream.bad() || !imgStream.is_open()) {
                std::cout << "\n"
                          << ConsoleConsts::TITLE_SYMBOL
                          << ConsoleConsts::ERROR_FILE_READ_FAIL
                          << " "
                          << ConsoleConsts::TRY_ANOTHER_FILE
                          << "\n" << std::endl;
                continue;
            }
            imgStream.close();
            break;
        }

        // initialize image
        Image *newImg;
        if (path.extension() == ".jpeg") newImg = new JPEGImage(pathStr);
        else newImg = new PPMImage(pathStr);

        if (!newImg->loadFromFile()) {
            std::cout << "\n"
                      << ConsoleConsts::TITLE_SYMBOL
                      << ConsoleConsts::ERROR_FILE_BAD_CODING
                      << " "
                      << ConsoleConsts::TRY_ANOTHER_FILE
                      << "\n" << std::endl;
            delete newImg;
            continue;
        }

        std::cout << "\n" << ConsoleConsts::TITLE_SYMBOL << ConsoleConsts::STATUS_CONVERTING_WAIT << std::endl;
        newImg->convertToAscii(grayscaleLevel);
        images.push_back(newImg);
        std::cout << ConsoleConsts::TITLE_SYMBOL << ConsoleConsts::STATUS_CONVERTING_SUCCESS << std::endl;
        isImageRead = true;
    }
}

void ImageFactory::removeImage(Image *image) {
    auto eraseIt = std::find(images.begin(), images.end(), image);
    if (eraseIt != images.end()) images.erase(eraseIt);
    delete image;
}

bool ImageFactory::readGrayscaleLevel() {
    std::string level;

    std::cout << "\n" << ConsoleConsts::TITLE_SYMBOL << ConsoleConsts::ENTER_GRAY_LEVEL << "\n" << std::endl;

    // input new grayscaleLevel
    while (true) {
        level.clear();
        std::cin.clear();
        std::cout << ConsoleConsts::INPUT_SYMBOLS;
        std::getline(std::cin, level);
        if (!level.empty()) break;
    }

    if (level == "q") return false;

    // check if new grayscaleLevel is not the same as the old
    bool isChanged = false;
    if (level == "d") {
        if (grayscaleLevel != AsciiConsts::DEFAULT_GRAYSCALE_LEVEL) {
            isChanged = true;
            grayscaleLevel = AsciiConsts::DEFAULT_GRAYSCALE_LEVEL;
        }
    } else {
        if (grayscaleLevel != level) {
            isChanged = true;
            grayscaleLevel = level;
        }
    }
    if (!isChanged) return false;

    // convert all images based on new grayscaleLevel
    std::cout << "\n" << ConsoleConsts::TITLE_SYMBOL << ConsoleConsts::STATUS_CONVERTING_WAIT << std::endl;
    for (Image *img : images) img->convertToAscii(grayscaleLevel);
    std::cout << ConsoleConsts::TITLE_SYMBOL
              << ConsoleConsts::STATUS_CONVERTING_SUCCESS
              << " "
              << ConsoleConsts::STATUS_CONVERTING_EXIT
              << std::endl;
    getchar();
    return true;
}

bool ImageFactory::applyEffect(Image *image) {
    size_t chosenIndex;

    std::cout << "\n" << ConsoleConsts::TITLE_SYMBOL << ConsoleConsts::PICK_EFFECT << "\n" << std::endl;

    while (true) {
        // print all supported effects
        std::cout << "1) " << ((image->hasContrast()) ? "Remove " : "Add ") << "contrast effect\n"
                  << "2) " << ((image->hasNegative()) ? "Remove " : "Add ") << "negative effect\n"
                  << "3) " << ((image->hasSharpen()) ? "Remove " : "Add ") << "sharpen effect\n" << std::endl;

        std::string str;
        std::cin.clear();
        std::cout << ConsoleConsts::INPUT_SYMBOLS;
        std::getline(std::cin, str);

        if (str.empty()) continue;
        else if (str == "q") return false;

        // read index of the chosen effect
        if (sscanf(str.c_str(), "%zu", &chosenIndex) != 1) {
            std::cout << "\n"
                      << ConsoleConsts::TITLE_SYMBOL
                      << ConsoleConsts::ERROR_IMAGE_NOT_INDEX
                      << " "
                      << ConsoleConsts::TRY_AGAIN
                      << "\n" << std::endl;
            continue;
        }

        if (chosenIndex < 1 || chosenIndex > 3) {
            std::cout << "\n"
                      << ConsoleConsts::TITLE_SYMBOL
                      << ConsoleConsts::ERROR_IMAGE_BAD_INDEX
                      << " "
                      << ConsoleConsts::TRY_AGAIN
                      << "\n" << std::endl;
            continue;
        }
        break;
    }

    switch (chosenIndex) {
        case 1:
            image->toggleContrast();
            break;
        case 2:
            image->toggleNegative();
            break;
        case 3:
            image->toggleSharpen();
            break;
        default:
            break;
    }

    std::cout << "\n" << ConsoleConsts::TITLE_SYMBOL << ConsoleConsts::STATUS_CONVERTING_WAIT << std::endl;
    image->convertToAscii(grayscaleLevel);
    std::cout << ConsoleConsts::TITLE_SYMBOL
              << ConsoleConsts::STATUS_CONVERTING_SUCCESS
              << " "
              << ConsoleConsts::STATUS_CONVERTING_EXIT
              << std::endl;
    getchar();
    return true;
}

void ImageFactory::exportImage(const Image *image) {
    fs::path path;
    std::string pathStr;

    std::cout << "\n" << ConsoleConsts::TITLE_SYMBOL << ConsoleConsts::ENTER_TXT_PATH << "\n" << std::endl;

    while (true) {
        pathStr.clear();
        std::cin.clear();
        std::cout << ConsoleConsts::INPUT_SYMBOLS;
        // read path
        std::getline(std::cin, pathStr);

        Utils::trim(pathStr);

        if (pathStr.empty()) continue;
        else if (pathStr == "q") return;

        // if pathStr contains leading and trailing apostrophes
        if (pathStr.front() == '\'') pathStr.erase(pathStr.begin());
        if (pathStr.back() == '\'') pathStr.erase(pathStr.end() - 1);

        path = fs::path(pathStr);

        if (fs::exists(path)) {
            std::cout << "\n"
                      << ConsoleConsts::TITLE_SYMBOL
                      << ConsoleConsts::ERROR_FILE_EXISTS
                      << " "
                      << ConsoleConsts::TRY_ANOTHER_FILE
                      << "\n" << std::endl;
            continue;
        }

        if (path.is_relative()) {
            std::cout << "\n"
                      << ConsoleConsts::TITLE_SYMBOL
                      << ConsoleConsts::ERROR_PATH_RELATIVE
                      << " "
                      << ConsoleConsts::TRY_AGAIN
                      << "\n" << std::endl;
            continue;
        }

        if (path.extension() != ".txt") {
            std::cout << "\n"
                      << ConsoleConsts::TITLE_SYMBOL
                      << ConsoleConsts::ERROR_FILE_UNSUPPORTED
                      << " "
                      << ConsoleConsts::TRY_ANOTHER_FILE
                      << "\n" << std::endl;
            continue;
        }

        // if directories in path doesn't exist, create them!
        if (!fs::exists(path.root_directory())) fs::create_directories(path);
        break;
    }

    std::cout << "\n" << ConsoleConsts::TITLE_SYMBOL << ConsoleConsts::STATUS_EXPORT_WAIT << std::endl;

    // print art to file
    auto exportData = image->getRawAsciiData();
    std::ofstream outfile(pathStr);
    for (auto &line : exportData) outfile << line << "\n";
    outfile.flush();
    outfile.close();

    std::cout << ConsoleConsts::TITLE_SYMBOL
              << ConsoleConsts::STATUS_EXPORT_SUCCESS
              << " "
              << ConsoleConsts::STATUS_CONVERTING_EXIT
              << std::endl;
    getchar();
}

Image *ImageFactory::chooseImageFromList(const char *firstMessage) const {
    size_t chosenIndex;

    std::cout << "\n" << ConsoleConsts::TITLE_SYMBOL << firstMessage << "\n" << std::endl;

    while (true) {
        // print loaded images paths
        for (size_t i = 0; i < images.size(); ++i)
            std::cout << i + 1 << ") " << images[i]->getPath() << "\n";
        std::cout << std::endl;

        std::string path;
        std::cin.clear();
        std::cout << ConsoleConsts::INPUT_SYMBOLS;
        std::getline(std::cin, path);

        if (path.empty()) continue;
        else if (path == "q") return nullptr;

        // read index of chosen path
        if (sscanf(path.c_str(), "%zu", &chosenIndex) != 1) {
            std::cout << "\n"
                      << ConsoleConsts::TITLE_SYMBOL
                      << ConsoleConsts::ERROR_IMAGE_NOT_INDEX
                      << " "
                      << ConsoleConsts::TRY_AGAIN
                      << "\n" << std::endl;
            continue;
        }

        if (chosenIndex < 1 || chosenIndex > images.size()) {
            std::cout << "\n"
                      << ConsoleConsts::TITLE_SYMBOL
                      << ConsoleConsts::ERROR_IMAGE_BAD_INDEX
                      << " "
                      << ConsoleConsts::TRY_AGAIN
                      << "\n" << std::endl;
            continue;
        }
        break;
    }
    return images[chosenIndex - 1];
}