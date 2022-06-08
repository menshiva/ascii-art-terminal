#ifndef ASCIIART_UI_HPP
#define ASCIIART_UI_HPP

#include <vector>
#include "widgets/containers/Panel.hpp"
#include "widgets/views/Text.hpp"
#include "../utils/Consts.hpp"

class UI : public View {
public:
    UI();
    ~UI() override;

    WINDOW *getWindow() const override;
    uint16_t getHeight() const override;
    uint16_t getWidth() const override;

    void resize() override;
    void draw() override;

    static bool init();
    void mainLoop();
private:
    std::vector<std::unique_ptr<View>> m_Views;
};

#endif //ASCIIART_UI_HPP
