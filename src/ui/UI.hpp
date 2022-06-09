#ifndef ASCIIART_UI_HPP
#define ASCIIART_UI_HPP

#include <unordered_map>
#include "widgets/containers/Absolute.hpp"
#include "widgets/containers/Border.hpp"
#include "widgets/containers/Center.hpp"
#include "widgets/views/Menu.hpp"
#include "widgets/views/Text.hpp"
#include "../utils/Consts.hpp"

class UI : public MultiViewContainer {
public:
    UI();
    ~UI();

    WINDOW *getWindow() const override;
    uint16_t getHeight() const override;
    uint16_t getWidth() const override;
    uint16_t getY() const override;
    uint16_t getX() const override;

    void draw() override;

    static bool init();
    void mainLoop();
private:
    View *addChildren(View *parent, std::initializer_list<std::pair<int8_t, View*>> views);

    View *stackViews(View *parent, std::initializer_list<std::pair<int8_t, View*>> views);

    template<class T>
    T *getView(int8_t id);
private:
    std::unordered_multimap<int8_t, std::unique_ptr<View>> m_Views;
};

#endif //ASCIIART_UI_HPP
