#ifndef ASCII_PIXEL_HPP
#define ASCII_PIXEL_HPP

struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Pixel(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0) : r(r), g(g), b(b) {}
};

#endif