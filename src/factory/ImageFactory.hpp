// #ifndef ASCII_IMAGEFACTORY_HPP
// #define ASCII_IMAGEFACTORY_HPP
//
// #include <iostream>
// #include <experimental/filesystem>
// #include "../image/format/JPEGImage.hpp"
// #include "../image/format/PPMImage.hpp"
//
// namespace fs = std::experimental::filesystem;
//
// /**
//  * @brief Image controller.
//  *
//  * Factory class for images.\n
//  * Stores and controls all loaded images (read, remove, change etc.).\n
//  * Manages the connection between _main program_ logic and loaded image files.
//  *
//  * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
//  */
// class ImageFactory {
//     std::vector<Image *> images; /**< Loaded images. */
//     /**
//      * Range of symbols from _darkest_ to _lightest_, which will be used in ASCII conversion.
//      * @note Default value is AsciiConsts::DEFAULT_GRAYSCALE_LEVEL.
//      */
//     std::string grayscaleLevel;
// public:
//     ///Constructor.
//     ImageFactory();
//
//     ///@attention Copy constructor is forbidden.
//     ImageFactory(const ImageFactory &) = delete;
//
//     ///@attention Copy assignment operator is forbidden.
//     ImageFactory &operator=(const ImageFactory &) = delete;
//
//     ///@attention Move constructor is forbidden.
//     ImageFactory(ImageFactory &&) = delete;
//
//     ///@attention Move assignment operator is forbidden.
//     ImageFactory &operator=(ImageFactory &&) = delete;
//
//     ///Destructor. _Frees_ memory allocated for #images.
//     ~ImageFactory();
//
//     ///@return #images.
//     const std::vector<Image *> &getAllImages() const;
//
//     /**
//      * Reads image file from it's path, converts it to ASCII art and adds it to #images.\n
//      * If image file was opened and converted to ASCII art successfully, function will ask user to load another one.\n
//      * Otherwise will ask user to try again.
//      * @note Function checks file existence and image format by itself.
//      * @warning Works only in console mode. If you are using UI, you should call #UI::hide() first.
//      *
//      * @return `true` if at least _1_ image file was loaded and converted successfully, `false` otherwise.
//      */
//     bool readImage();
//
//     /**
//      * Removes given Image from #images.
//      *
//      * @param image Pointer to Image from #images to remove.
//      */
//     void removeImage(Image *image);
//
//     /**
//      * Suggests that user inputs his own #grayscaleLevel, or to use the default #grayscaleLevel.\n
//      * Reconverts #images with new #grayscaleLevel.
//      * @warning Works only in console mode. If you are using UI, you should call #UI::hide() first.
//      *
//      * @return `true` if _new_ #grayscaleLevel was successfully saved and applied to all #images, `false` otherwise.
//      */
//     bool readGrayscaleLevel();
//
//     /**
//      * Prints all supported effects in console and suggests user applying one of them to Image.
//      * @warning Works only in console mode. If you are using UI, you should call #UI::hide() first.
//      *
//      * @param[in] image Pointer to Image.
//      * @param[out] image Pointer to Image with effect applied on.
//      * @return `true` if _chosen_ effect was successfully applied to _image_, `false` otherwise.
//      */
//     bool applyEffect(Image *image);
//
//     /**
//      * Suggests that user inputs path to non-existing .txt file.\n
//      * Function creates this file and exports ASCII art of Image to it.
//      * @warning Works only in console mode. If you are using UI, you should call #UI::hide() first.
//      *
//      * @param image Pointer to Image to export.
//      */
//     static void exportImage(const Image *image);
//
//     /**
//      * Prints all #images paths as a list.\n
//      * Suggests user picking one certain Image from this list.
//      * @warning Works only in console mode. If you are using UI, you should call #UI::hide() first.
//      *
//      * @param firstMessage Title, which will be printed before the list.
//      * @return Pointer to the _chosen_ Image from #images, or `nullptr` on abort.
//      */
//     Image *chooseImageFromList(const char *firstMessage) const;
// };
//
// #endif
