#ifndef ASCIIART_MENU_HPP
#define ASCIIART_MENU_HPP

#include <vector>
#include "../containers/Pos.hpp"
#include "Text.hpp"

class Menu : public View {
public:
    Menu(std::initializer_list<const char*> options) : View() {
        m_Options.reserve(options.size());
        for (auto &optionText : options) {
            m_Options.emplace_back(new Text(optionText));
            m_Options.back().setParent(this);
        }
    }

    WINDOW *getWindow() const override {
        return getParent()->getWindow();
    }

    uint16_t getHeight() const override {
        return m_Options.size();
    }

    uint16_t getWidth() const override {
        uint16_t w = 0;
        for (const auto &option : m_Options) {
            uint16_t textW = option.getChild()->getWidth();
            if (textW > w)
                w = textW;
        }
        return w;
    }

    uint16_t getY() const override {
        return getParent()->getY();
    }

    uint16_t getX() const override {
        return getParent()->getX();
    }

    void draw() override {
        uint16_t y = getY();
        uint16_t x = getX();
        for (auto &option : m_Options) {
            option.setY(y++);
            option.setX(x);
            option.draw();
        }
    }
private:
    std::vector<Pos> m_Options;
};

#endif //ASCIIART_MENU_HPP
