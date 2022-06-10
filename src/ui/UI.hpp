#ifndef ASCIIART_UI_HPP
#define ASCIIART_UI_HPP

#include <unordered_map>
#include "containers/Screen.hpp"
#include "containers/Panel.hpp"
#include "containers/Menu.hpp"
#include "views/Text.hpp"
#include "../utils/Consts.hpp"

class UI {
public:
    UI();
    ~UI();

    static bool init();
    void mainLoop();
private:
    View *assignId(uint8_t id, View *child);

    template<class T>
    T *getView(uint8_t id);
private:
    bool m_MainLoopRunning, m_WindowDirty;
    Screen m_Root;
    std::unordered_map<uint8_t, View*> m_Views;
};

#endif //ASCIIART_UI_HPP
