/*#include "Menu.hpp"

Menu::Menu(View *parent,
           float yRelative, float xRelative,
           size_t rows, size_t cols,
           std::vector<ITEM *> newItems,
           const std::initializer_list<size_t> &disabledItems,
           std::function<void(size_t)> onClickCallback) :
        View(parent, 0.0F, 0.0F, yRelative, xRelative),
        rows(rows), items(std::move(newItems)), onClickCallback(std::move(onClickCallback)) {
    // find item with max length
    auto farthestCorner = std::max_element(items.begin(), items.end(),
                                           [](const ITEM *f, const ITEM *s) {
                                               return f->name.length < s->name.length;
                                           });
    width = cols * (*farthestCorner)->name.length;

    size_t y = static_cast<size_t>(yRelative * parent->getHeight()) - (rows >> 1);
    size_t x = static_cast<size_t>(xRelative * parent->getWidth()) - (width >> 1) - 2;

    items.push_back(nullptr);
    menu = new_menu(items.data());
    set_menu_sub(menu, derwin(parent->getWindow(), 0, 0, y, x));
    set_menu_mark(menu, "> ");
    set_menu_format(menu, rows, cols);
    set_menu_grey(menu, COLOR_PAIR(1));

    // disable "disabled" items
    for (size_t idx : disabledItems) item_opts_off(menu->items[idx], O_SELECTABLE);

    keypad(parent->getWindow(), true); // enable keypad
    nodelay(parent->getWindow(), true); // make getch to be a non-blocking call
}

Menu::~Menu() {
    unpost_menu(menu);
    free_menu(menu);
    for (ITEM *item: items) free_item(item);
}

void Menu::toggleItem(size_t idx, bool enable) {
    if (enable) item_opts_on(menu->items[idx], O_SELECTABLE);
    else item_opts_off(menu->items[idx], O_SELECTABLE);
}

void Menu::menuInteract(int key) const {
    switch (key) {
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
        case 10: // ENTER KEY
            onClickCallback(static_cast<size_t>(current_item(menu)->index));
            break;
        default:
            break;
    }
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

void Menu::draw() {
    post_menu(menu);
}

void Menu::resize() {
    unpost_menu(menu);
    size_t y = static_cast<size_t>(yRelative * parent->getHeight()) - (rows >> 1);
    size_t x = static_cast<size_t>(xRelative * parent->getWidth()) - (width >> 1) - 2;
    set_menu_sub(menu, derwin(getWindow(), 0, 0, y, x));
    keypad(parent->getWindow(), true); // enable keypad
    nodelay(parent->getWindow(), true); // make getch to be a non-blocking call
}*/
