#ifndef ASCIIART_PANEL_HPP
#define ASCIIART_PANEL_HPP

#include <memory>
#include <panel.h>
#include "../View.hpp"

class Panel : public View {
public:
    Panel(View *parent, float heightRelative, float widthRelative, float yRelative, float xRelative, View *child);

    ~Panel() override;

    WINDOW *getWindow() const override;
    uint16_t getHeight() const override;
    uint16_t getWidth() const override;

    void resize() override;
    void draw() override;
private:
    PANEL *m_Panel;
    std::unique_ptr<View> m_Child;
};

#endif //ASCIIART_PANEL_HPP
