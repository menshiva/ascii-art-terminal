#ifndef SEMESTR_JPEGIMAGE_HPP
#define SEMESTR_JPEGIMAGE_HPP

#include "../Image.hpp"
#include <csetjmp>

extern "C" {
#include <jpeglib.h>
}

/**
 * @brief Support for JPEG (JPG) image format.
 *
 * This class is derived from Image and holds all data, needed for JPEG format.\n
 * Operates only with reading data from image file. Other operations are implemented in Image class.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class JPEGImage : public Image {
    /**
     * @brief Error handler for JPEG decompression.
     *
     * Private extension of the standard JPEG error handler object.
     */
    struct jpegErrorManager {
        jpeg_error_mgr manager; /**< JPEG error manager. */
        jmp_buf jumpBuffer; /**< Return to caller on error recieved. */
    };
public:
    /**
     * Constructor initializes image by setting its #Image::path.
     *
     * @param imgPath _Absolute_ path to image file.
     */
    explicit JPEGImage(const std::string &imgPath);

    /**
     * @attention Copy constuctor is forbidden.
     */
    JPEGImage(const JPEGImage &) = delete;

    /**
     * @attention Assignment operator is forbidden.
     */
    JPEGImage &operator=(const JPEGImage &) = delete;

    /**
     * Opens image file from #path and reads it's metadata (such as #height, #width etc.) and #rawData.
     * @note Example of JPEG _decompression_ is referenced from:
     * https://github.com/LuaDist/libjpeg/blob/master/example.c#L210
     *
     * @return `true` if file is successfully opened and converted/decompressed to #rawData.
     * Otherwise `false`.
     */
    bool loadFromFile() override;

    /**
     * Handles errors in JPEG decompressing.\n
     * Called automatically when jpegErrorManager recieved an error from _decompressing_ used in #loadFromFile().
     * @note Replaces the standard libjpeg.h error_exit method.
     *
     * @param cinfo JPEG common struct storing all image metadata.
     * @relatesalso JPEGImage
     */
    static void jpegDecompressErrorHandler(j_common_ptr cinfo);

    /**
     * Default destructor.
     */
    ~JPEGImage() override = default;
};

#endif