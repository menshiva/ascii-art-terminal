#ifndef ASCII_JPEGIMAGE_HPP
#define ASCII_JPEGIMAGE_HPP

#include <csetjmp>
#include "../Image.hpp"

extern "C" {
#include <jpeglib.h>
}

class JPEGImage : public Image {
    struct jpegErrorManager {
        jpeg_error_mgr manager;
        jmp_buf jumpBuffer;
    };
public:
    explicit JPEGImage(const std::string &imgPath);
    JPEGImage(const JPEGImage &) = delete;
    JPEGImage &operator=(const JPEGImage &) = delete;
    JPEGImage(JPEGImage &&) = delete;
    JPEGImage &operator=(JPEGImage &&) = delete;
    ~JPEGImage() override = default;

    bool loadFromFile() override;
    static void jpegDecompressErrorHandler(j_common_ptr cinfo);
};

#endif