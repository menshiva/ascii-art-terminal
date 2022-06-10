#ifndef ASCIIART_TEXT_HPP
#define ASCIIART_TEXT_HPP

#include <cstring>
#include "../base/View.hpp"

class Text final : public View {
public:
    explicit Text(const char *text) : View(), m_Text(text) {
        setAbsoluteHeight(1);
        setWidth([&]() -> uint16_t { return strlen(m_Text); });
    }

    void draw() override {
        mvwaddstr(getParentContainer()->getWindow(), getY(), getX(), m_Text);
    }
private:
    const char *m_Text;
};

#endif //ASCIIART_TEXT_HPP
