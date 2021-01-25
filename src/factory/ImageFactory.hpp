#ifndef SEMESTR_IMAGEFACTORY_HPP
#define SEMESTR_IMAGEFACTORY_HPP

#include "../image/format/JPEGImage.hpp"
#include "../image/format/PPMImage.hpp"
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

/**
 * @brief Image controller.
 *
 * This class is a general factory for images.\n
 * It stores all loaded images and can control (read, remove, change etc.) them.\n
 * Manages connection between _main program_ logic and loaded image files.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class ImageFactory {
    std::vector<Image *> images; /**< Loaded images. */
    /**
     * Range of symbols from _darkest_ to _lightest_, which will be used in ASCII convertation.
     * @note Default value is AsciiConsts::DEFAULT_GRAYSCALE_LEVEL.
     */
    std::string grayscaleLevel;
public:
    /**
     * Constructor.
     */
    ImageFactory();

    /**
     * @attention Copy constuctor is forbidden.
     */
    ImageFactory(const ImageFactory &) = delete;

    /**
     * @attention Assignment operator is forbidden.
     */
    ImageFactory &operator=(const ImageFactory &) = delete;

    /**
     * Reads image file from path, converts it to ASCII art and adds it to #images.\n
     * If image file was opened and converted to ASCII art successfully, function asks user to load another one.
     * Otherwise suggests to try again.
     * @note Function checks file existance and image format by itself.
     * @warning Works only in console mode. If you are using UI, you need to call #UI::hide() first.
     *
     * @return `true` if at least _1_ image file was loaded and converted successfully.
     * Otherwise `false`.
     */
    bool readImage();

    /**
     * Removes Image from #images.
     *
     * @param image Pointer to Image from #images to remove.
     */
    void removeImage(Image *image);

    /**
     * Suggests user to input and reconvert #images with his own #grayscaleLevel, or to use the default #grayscaleLevel.
     * @warning Works only in console mode. If you are using UI, you need to call #UI::hide() first.
     *
     * @return `true` if _new_ #grayscaleLevel was saved and applied to all #images successfully.
     * Otherwise `false`.
     */
    bool readGrayscaleLevel();

    /**
     * Prints all effects in console and suggests user to apply one of them to Image.
     * @warning Works only in console mode. If you are using UI, you need to call #UI::hide() first.
     *
     * @param[in] image Pointer to Image.
     * @param[out] image Pointer to Image with effect applied on.
     * @return `true` if _chosen_ effect was applied to _image_ succesfully.
     * Otherwise `false`.
     */
    bool applyEffect(Image *image);

    /**
     * Suggests user to input path to non-exist .txt file.\n
     * Function creates this file and exports ASCII art of Image to it.
     * @warning Works only in console mode. If you are using UI, you need to call #UI::hide() first.
     *
     * @param image Pointer to Image to export.
     * @relatesalso ImageFactory
     */
    static void exportImage(const Image *image);

    /**
     * Prints _title_ and paths of all #images as list.\n
     * Suggests user to pick one Image from this list.
     * @warning Works only in console mode. If you are using UI, you need to call #UI::hide() first.
     *
     * @param firstMessage Title, which will be printed before list.
     * @return Pointer to _chosen_ Image from #images, or `nullptr` if user cancel function.
     */
    Image *chooseImageFromList(const char *firstMessage) const;

    /**
     * @return #images.
     */
    const std::vector<Image *> &getAllImages() const;

    /**
     * Destructor. _Deletes_ all allocated #images.
     */
    ~ImageFactory();
};

#endif