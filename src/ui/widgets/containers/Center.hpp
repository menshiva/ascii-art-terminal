#ifndef ASCIIART_CENTER_HPP
#define ASCIIART_CENTER_HPP

#include "SingleViewContainer.hpp"

struct Center : public SingleViewContainer {
    Center() : SingleViewContainer() {}

    uint16_t getY() const override {
        return static_cast<uint16_t>(
                static_cast<float>(getHeight()) * 0.5f - static_cast<float>(getChild()->getHeight()) * 0.5f
        );
    }

    uint16_t getX() const override {
        return static_cast<uint16_t>(
                static_cast<float>(getWidth()) * 0.5f - static_cast<float>(getChild()->getWidth()) * 0.5f
        );
    }
};

#endif //ASCIIART_CENTER_HPP
