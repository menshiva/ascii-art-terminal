#ifndef ASCIIART_SCREEN_HPP
#define ASCIIART_SCREEN_HPP

#include <panel.h>
#include "containers/Panel.hpp"
#include "containers/Menu.hpp"
#include "views/Text.hpp"

class Screen final : public Container {
public:
    static bool init();

    Screen();
    ~Screen() override;

    void mainLoop();
    void markDirty();
    void close();

    WINDOW *getWindow() const override;
    Screen *withChildren(std::initializer_list<View*> children) override;
protected:
    void draw() override;
    bool isActive() const override;
private:
    bool m_MainLoopRunning, m_WindowDirty;
};

#endif //ASCIIART_SCREEN_HPP
