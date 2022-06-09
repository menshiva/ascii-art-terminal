#ifndef ASCIIART_SIZE_HPP
#define ASCIIART_SIZE_HPP

#include "SingleViewContainer.hpp"

class Size : public SingleViewContainer {
public:
    Size() : SingleViewContainer(), m_Height(0), m_Width(0) {}

    uint16_t getHeight() const override {
        return m_Height;
    }

    uint16_t getWidth() const override {
        return m_Width;
    }

    void setHeight(uint16_t h) {
        m_Height = h;
    }

    void setWidth(uint16_t w) {
        m_Width = w;
    }
private:
    uint16_t m_Height, m_Width;
};

#endif //ASCIIART_SIZE_HPP
