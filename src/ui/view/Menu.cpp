#include "Menu.hpp"

Menu::Menu(const View *parent,
           double yRelative, double xRelative,
           size_t rows, size_t cols,
           std::vector<ITEM *> *newItems,
           const std::initializer_list<size_t> &disabledItems) :
        View(parent, 0.0, 0.0, yRelative, xRelative),
        rows(rows), items(newItems) {
    // first color = disabled item
    // second color = disabled item with hover
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);

    // find item with max length
    size_t max = 0U;
    for (const auto i : *items)
        if (static_cast<size_t>(i->name.length) > max)
            max = static_cast<size_t>(i->name.length);
    width = cols * max;

    const size_t y = static_cast<size_t>(yRelative * parent->getHeight()) - (rows >> 1U);
    const size_t x = static_cast<size_t>(xRelative * parent->getWidth()) - (width >> 1U) - 2U;

    items->push_back(nullptr);
    menu = new_menu(items->data());
    set_menu_sub(menu, derwin(parent->getWindow(), 0, 0, y, x));
    set_menu_mark(menu, "> ");
    set_menu_format(menu, rows, cols);
    set_menu_grey(menu, COLOR_PAIR(1));

    // disable disabled items
    for (const auto pos : disabledItems)
        item_opts_off(menu->items[pos], O_SELECTABLE);
}

void Menu::toggleItem(size_t pos, bool enable) {
    if (enable) item_opts_on(menu->items[pos], O_SELECTABLE);
    else item_opts_off(menu->items[pos], O_SELECTABLE);
}

void Menu::draw() const {
    post_menu(menu);
    drawn = true;
}

void Menu::resize() {
    drawn = false;
    unpost_menu(menu);
    const size_t y = static_cast<size_t>(yRelative * parent->getHeight()) - (rows >> 1U);
    const size_t x = static_cast<size_t>(xRelative * parent->getWidth()) - (width >> 1U) - 2U;
    set_menu_sub(menu, derwin(getWindow(), 0, 0, y, x));
}

void Menu::show() const {
    parent->show();
}

void Menu::hide() const {
    parent->hide();
}

WINDOW *Menu::getWindow() const {
    return parent->getWindow();
}

size_t Menu::getHeight() const {
    return parent->getHeight();
}

size_t Menu::getWidth() const {
    return parent->getWidth();
}

size_t Menu::keyboardListener() const {
    keypad(getWindow(), true);
    while (true) {
        switch (wgetch(getWindow())) {
            case KEY_RESIZE: /* RESIZE TERMINAL */
                return RuntimeCodes::RESIZE_UI;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(menu, REQ_LEFT_ITEM);
                break;
            case KEY_RIGHT:
                menu_driver(menu, REQ_RIGHT_ITEM);
                break;
            case 10: /* ENTER KEY */
                keypad(getWindow(), false);
                return (size_t) current_item(menu)->index;
            default: break;
        }
    }
}

Menu::~Menu() {
    unpost_menu(menu);
    free_menu(menu);
    for (auto item: *items) free_item(item);
    delete items;
}