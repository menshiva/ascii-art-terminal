#ifndef ASCIIART_TEXT_HPP
#define ASCIIART_TEXT_HPP

#include <cstring>
#include "../View.hpp"

class Text : public View {
public:
    explicit Text(const char *text) : View(), m_Text(text) {}

    WINDOW *getWindow() const override {
        return getParent()->getWindow();
    }

    uint16_t getHeight() const override {
        return 1;
    }

    uint16_t getWidth() const override {
        return strlen(m_Text);
    }

    uint16_t getY() const override {
        return getParent()->getY();
    }

    uint16_t getX() const override {
        return getParent()->getX();
    }

    void setChild(View *child) override {}

    void draw() override {
        mvwaddstr(getWindow(), getY(), getX(), m_Text);
    }
private:
    const char *m_Text;
};

#endif //ASCIIART_TEXT_HPP
