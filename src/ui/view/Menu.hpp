#ifndef ASCII_MENU_HPP
#define ASCII_MENU_HPP

#include <algorithm>
#include <menu.h>
#include "View.hpp"

class Menu : public View {
    MENU *menu;
    size_t rows;
    std::vector<ITEM *> items;

    std::function<void(size_t)> onClickCallback;
public:
    Menu(View *parent,
         float yRelative, float xRelative,
         size_t rows, size_t cols,
         std::vector<ITEM *> newItems,
         const std::initializer_list<size_t> &disabledItems,
         std::function<void(size_t)> onClickCallback);
    Menu(const Menu &) = delete;
    Menu &operator=(const Menu &) = delete;
    Menu(Menu &&) = delete;
    Menu &operator=(Menu &&) = delete;
    ~Menu() override;

    void toggleItem(size_t idx, bool enable);
    void menuInteract(int key) const;

    WINDOW *getWindow() const override;
    size_t getHeight() const override;
    size_t getWidth() const override;

    void draw() override;
    void resize() override;
};

#endif