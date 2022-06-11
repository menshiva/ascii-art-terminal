#ifndef ASCIIART_SPACE_HPP
#define ASCIIART_SPACE_HPP

#include "../base/View.hpp"

struct Space : public View {
    Space() : View() {}
protected:
    void draw() override {}
};

#endif //ASCIIART_SPACE_HPP
