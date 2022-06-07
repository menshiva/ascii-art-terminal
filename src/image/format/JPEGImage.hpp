// #ifndef ASCII_JPEGIMAGE_HPP
// #define ASCII_JPEGIMAGE_HPP
//
// #include <csetjmp>
// #include "../Image.hpp"
//
// extern "C" {
// #include <jpeglib.h>
// }
//
// /**
//  * @brief JPEG (JPG) image format.
//  *
//  * This class is derived from Image and holds all JPEG format data.\n
//  * Operates only with reading data from image file.\n
//  * Other operations are implemented in Image class.
//  *
//  * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
//  */
// class JPEGImage : public Image {
//     /**
//      * @brief Error handler for JPEG decompression.
//      *
//      * Private extension for the JPEG error handler object.
//      */
//     struct jpegErrorManager {
//         jpeg_error_mgr manager; /**< JPEG error manager. */
//         jmp_buf jumpBuffer; /**< Return to caller on error received. */
//     };
// public:
//     /**
//      * Constructor.\n
//      * Initializes image by setting its #Image::path.
//      *
//      * @param imgPath _Absolute_ path to image file.
//      */
//     explicit JPEGImage(const std::string &imgPath);
//
//     ///@attention Copy constructor is forbidden.
//     JPEGImage(const JPEGImage &) = delete;
//
//     ///@attention Copy assignment operator is forbidden.
//     JPEGImage &operator=(const JPEGImage &) = delete;
//
//     ///@attention Move constructor is forbidden.
//     JPEGImage(JPEGImage &&) = delete;
//
//     ///@attention Move assignment operator is forbidden.
//     JPEGImage &operator=(JPEGImage &&) = delete;
//
//     ///Destructor.
//     ~JPEGImage() override = default;
//
//     /**
//      * Opens image file from #path and reads it's metadata (such as #height, #width etc.) and #rawData.
//      * @note JPEG _decompression_ example is referenced from:
//      * https://github.com/LuaDist/libjpeg/blob/master/example.c#L210
//      *
//      * @return `true` if file is successfully opened and converted/decompressed to #rawData, `false` otherwise.
//      */
//     bool loadFromFile() override;
//
//     /**
//      * Handles errors in JPEG decompressing.\n
//      * Called automatically when jpegErrorManager received an error from _decompressing_ used in #loadFromFile().
//      * @note Replaces the standard libjpeg.h error_exit method.
//      *
//      * @param cinfo JPEG common struct storing image metadata.
//      */
//     static void jpegDecompressErrorHandler(j_common_ptr cinfo);
// };
//
// #endif
