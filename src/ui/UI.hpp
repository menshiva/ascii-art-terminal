#ifndef ASCIIART_UI_HPP
#define ASCIIART_UI_HPP

#include "widgets/views/Text.hpp"
#include "widgets/containers/Size.hpp"
#include "widgets/containers/Border.hpp"
#include "widgets/containers/Center.hpp"
#include "widgets/containers/Relative.hpp"
#include "../utils/Consts.hpp"

class UI : public View {
public:
    UI();
    ~UI() override;

    WINDOW *getWindow() const override;
    uint16_t getHeight() const override;
    uint16_t getWidth() const override;
    uint16_t getY() const override;
    uint16_t getX() const override;

    void draw() override;

    static bool init();
    void mainLoop();
private:
    Relative m_TitleView, m_ControlsView, m_ArtView;
};

#endif //ASCIIART_UI_HPP
