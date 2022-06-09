#ifndef ASCIIART_POS_HPP
#define ASCIIART_POS_HPP

#include "SingleViewContainer.hpp"

class Pos : public SingleViewContainer {
public:
    Pos() : SingleViewContainer(), m_Y(0), m_X(0) {}

    uint16_t getY() const override {
        return m_Y;
    }

    uint16_t getX() const override {
        return m_X;
    }

    void setY(uint16_t y) {
        m_Y = y;
    }

    void setX(uint16_t x) {
        m_X = x;
    }
private:
    uint16_t m_Y, m_X;
};

#endif //ASCIIART_POS_HPP
