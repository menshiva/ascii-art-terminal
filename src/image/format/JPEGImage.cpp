#include "JPEGImage.hpp"

JPEGImage::JPEGImage(const std::string &imgPath) : Image(imgPath) {}

bool JPEGImage::loadFromFile() {
    /* This struct contains the JPEG decompression parameters and pointers to
     * working space (which is allocated as needed by the JPEG library).
     */
    jpeg_decompress_struct decompressInfo{};
    /* We use our private extension JPEG error handler.
     * Note that this struct must live as long as the main JPEG parameter
     * struct, to avoid dangling-pointer problems.
     */
    jpegErrorManager errorManager{};

    FILE *file = fopen(path.c_str(), "rb");

    decompressInfo.err = jpeg_std_error(&errorManager.manager);
    errorManager.manager.error_exit = jpegDecompressErrorHandler;
    // if decompress traces an error, then jpegDecompressErrorHandler calls this part of code
    if (setjmp(errorManager.jumpBuffer)) {
        /* If we get here, the JPEG code has signaled an error.
         * We need to clean up the JPEG object, close the input file, and return.
         */
        jpeg_destroy_decompress(&decompressInfo);
        fclose(file);
        return false;
    }

    jpeg_create_decompress(&decompressInfo);
    jpeg_stdio_src(&decompressInfo, file);
    // read metadata
    jpeg_read_header(&decompressInfo, true);
    jpeg_start_decompress(&decompressInfo);

    // color components (RGB, YCbCr, CMYK, etc.)
    auto components = static_cast<size_t>(decompressInfo.num_components);
    height = decompressInfo.output_height;
    width = decompressInfo.output_width;

    if (height == 0U || width == 0U || components == 0U || components > 3U) return false;

    const size_t lineWidth = components * width;
    std::vector<unsigned char> data(height * lineWidth);
    while (decompressInfo.output_scanline < decompressInfo.output_height) {
        // pointer to data + current line * lineWidth
        unsigned char *rowptr = data.data() + decompressInfo.output_scanline * lineWidth;
        // read 1 line to rowptr
        jpeg_read_scanlines(&decompressInfo, &rowptr, 1);
    }
    jpeg_finish_decompress(&decompressInfo);
    jpeg_destroy_decompress(&decompressInfo);
    fclose(file);

    rawData.resize(height, std::vector<Pixel>(width));
    rawAsciiData.resize(height, std::string("", width));

    // convert components data to pixels data
    size_t row = 0U, col = 0U;
    for (size_t dataI = 0U; dataI < data.size(); dataI += components) {
        rawData[row][col].r = data[dataI];
        if (components == 1U) {
            // if jpeg is grayscaled then all color components should be the same
            rawData[row][col].g = data[dataI];
            rawData[row][col].b = data[dataI];
        } else {
            rawData[row][col].g = data[dataI + 1U];
            rawData[row][col].b = data[dataI + 2U];
        }
        if (++col >= width) {
            col = 0U;
            ++row;
        }
    }
    return true;
}

void JPEGImage::jpegDecompressErrorHandler(j_common_ptr cinfo) {
    // jump to setjmp in loadFromFile (return control to the setjmp point)
    longjmp(((jpegErrorManager *) cinfo->err)->jumpBuffer, 1);
}