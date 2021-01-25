#include "UI.hpp"

UI::UI() : View(nullptr, 1.0, 1.0, 0.0, 0.0),
           views(std::vector<View *>()), displayedImage(nullptr),
           asciiAnimationThread(nullptr), asciiAnimationThreadDriver(nullptr) {
    // we are using colors for main menu (enabled/disabled items)
    start_color();
    // we need to pass typed characters through our program immediately
    raw();
    // we dont need to echo all input characters
    noecho();
    // invisible cursor
    curs_set(0);
    refresh();

    // compute height and width of stdscr
    getmaxyx(stdscr, height, width);

    auto *upperPanel = new Panel(
            this,
            UIConsts::UPPER_PANEL_HEIGHT, UIConsts::UPPER_PANEL_WIDTH,
            UIConsts::UPPER_PANEL_OFFSET_Y, UIConsts::UPPER_PANEL_OFFSET_X,
            UIConsts::UPPER_PANEL_VISIBILITY
    );
    auto *leftPanel = new Panel(
            this,
            UIConsts::LEFT_PANEL_HEIGHT, UIConsts::LEFT_PANEL_WIDTH,
            UIConsts::LEFT_PANEL_OFFSET_Y, UIConsts::LEFT_PANEL_OFFSET_X,
            UIConsts::LEFT_PANEL_VISIBILITY
    );
    auto *rightPanel = new Panel(
            this,
            UIConsts::RIGHT_PANEL_HEIGHT, UIConsts::RIGHT_PANEL_WIDTH,
            UIConsts::RIGHT_PANEL_OFFSET_Y, UIConsts::RIGHT_PANEL_OFFSET_X,
            UIConsts::RIGHT_PANEL_VISIBILITY
    );
    auto *errorPanel = new Panel(
            this,
            UIConsts::ERROR_PANEL_HEIGHT, UIConsts::ERROR_PANEL_WIDTH,
            UIConsts::ERROR_PANEL_OFFSET_Y, UIConsts::ERROR_PANEL_OFFSET_X,
            UIConsts::ERROR_PANEL_VISIBILITY
    );
    auto *exitPanel = new Panel(
            this,
            UIConsts::EXIT_PANEL_HEIGHT, UIConsts::EXIT_PANEL_WIDTH,
            UIConsts::EXIT_PANEL_OFFSET_Y, UIConsts::EXIT_PANEL_OFFSET_X,
            UIConsts::EXIT_PANEL_VISIBILITY
    );

    auto *upperPanelText = new Text(
            upperPanel,
            UIConsts::UPPER_PANEL_TEXT,
            UIConsts::UPPER_PANEL_TEXT_OFFSET_Y, UIConsts::UPPER_PANEL_TEXT_OFFSET_X
    );
    auto *errorPanelText = new Text(
            errorPanel,
            UIConsts::ERROR_PANEL_TEXT,
            UIConsts::ERROR_PANEL_TEXT_OFFSET_Y, UIConsts::ERROR_PANEL_TEXT_OFFSET_X
    );
    auto *exitPanelText = new Text(
            exitPanel,
            UIConsts::EXIT_PANEL_TEXT,
            UIConsts::EXIT_PANEL_TEXT_OFFSET_Y, UIConsts::EXIT_PANEL_TEXT_OFFSET_X
    );

    auto *mainMenu = new Menu(
            leftPanel,
            UIConsts::MAIN_MENU_OFFSET_Y, UIConsts::MAIN_MENU_OFFSET_X,
            9u, 1u,
            new std::vector<ITEM *>{
                    new_item(UIConsts::BTN_ADD_IMAGE, ""),
                    new_item(UIConsts::BTN_SHOW_IMAGE, ""),
                    new_item(UIConsts::BTN_GRAYSCALE_LEVEL, ""),
                    new_item(UIConsts::BTN_EDIT_IMAGE, ""),
                    new_item(UIConsts::BTN_REMOVE_IMAGE, ""),
                    new_item(UIConsts::BTN_PLAY_ANIM, ""),
                    new_item(UIConsts::BTN_PAUSE_ANIM, ""),
                    new_item(UIConsts::BTN_EXPORT_ASCII, ""),
                    new_item(UIConsts::BTN_EXIT, "")
            },
            {1u, 3u, 4u, 5u, 6u, 7u}
    );
    auto *errorMenu = new Menu(
            errorPanel,
            UIConsts::ERROR_MENU_OFFSET_Y, UIConsts::ERROR_MENU_OFFSET_X,
            1u, 1u,
            new std::vector<ITEM *>{
                    new_item(UIConsts::BTN_OK, "")
            },
            {}
    );
    auto *exitMenu = new Menu(
            exitPanel,
            UIConsts::EXIT_MENU_OFFSET_Y, UIConsts::EXIT_MENU_OFFSET_X,
            1u, 2u,
            new std::vector<ITEM *>{
                    new_item(UIConsts::BTN_CANCEL, ""),
                    new_item(UIConsts::BTN_EXIT, "")
            },
            {}
    );

    views.push_back(upperPanel);
    views.push_back(leftPanel);
    views.push_back(rightPanel);
    views.push_back(errorPanel);
    views.push_back(exitPanel);

    views.push_back(upperPanelText);
    views.push_back(errorPanelText);
    views.push_back(exitPanelText);

    views.push_back(mainMenu);
    views.push_back(errorMenu);
    views.push_back(exitMenu);
}

void UI::printAscii(const Image *image) const {
    displayedImage = image;
    const auto *rightPanel = views[UIConsts::ViewIndex::PANEL_RIGHT];

    size_t panelHeight = rightPanel->getHeight(), panelWidth = rightPanel->getWidth();
    if (panelHeight <= 2u || panelWidth <= 2u) return;
    // substracting 2 because top, bottom, left, right panel borders are not count
    panelHeight -= 2u;
    panelWidth -= 2u;
    const size_t rows = panelHeight, cols = panelWidth;
    image->computeArtSize(panelHeight, panelWidth);
    if (panelHeight == 0u || panelWidth == 0u) return;

    const std::vector<std::string> ascii = image->getAsciiArt(panelHeight, panelWidth);

    // compute start positions for drawing art in the center of the panel
    const size_t startRowPrint = (rows > ascii.size()) ? ((rows - ascii.size()) / 2u) + 1u : 1u;
    const size_t startColPrint = (cols > ascii[0u].size()) ? ((cols - ascii[0u].size()) / 2u) + 1u : 1u;

    if (!rightPanel->isDrawn()) return;

    // draw ascii art in the center of the panel
    for (size_t y = 1u; y <= rows; ++y) {
        wmove(rightPanel->getWindow(), y, 1u);
        for (size_t x = 1u; x <= cols; ++x) {
            if (startRowPrint <= y && startColPrint <= x) {
                const size_t asciiY = y - startRowPrint, asciiX = x - startColPrint;
                if (asciiY < ascii.size() && asciiX < ascii[0u].size()) {
                    waddch(rightPanel->getWindow(), ascii[asciiY][asciiX]);
                    continue;
                }
            }
            waddch(rightPanel->getWindow(), ' ');
        }
    }

    wrefresh(rightPanel->getWindow());
}

void UI::refreshAscii() const {
    if (!displayedImage) return;
    printAscii(displayedImage);
}

void UI::clearAscii() const {
    displayedImage = nullptr;

    const auto *rightPanel = views[UIConsts::ViewIndex::PANEL_RIGHT];
    size_t panelHeight = rightPanel->getHeight(), panelWidth = rightPanel->getWidth();
    if (panelHeight <= 2u || panelWidth <= 2u) return;
    // substracting 2 because we dont want to erase top, bottom, left, right panel borders
    panelHeight -= 2u;
    panelWidth -= 2u;

    // replace all printed chars by ' '
    for (size_t y = 1u; y <= panelHeight; ++y) {
        wmove(rightPanel->getWindow(), y, 1u);
        for (size_t x = 1u; x <= panelWidth; ++x)
            waddch(rightPanel->getWindow(), ' ');
    }

    wrefresh(rightPanel->getWindow());
}

void UI::startAnimation(const std::vector<Image *> &images) {
    if (isAnimationStarted()) return;
    // disable "Start animation" button in main menu
    toggleMainMenuItem(5u, false);
    // enable "Stop animation" button in main menu
    toggleMainMenuItem(6u, true);
    asciiAnimationThreadDriver = new std::atomic<bool>{true};
    asciiAnimationThread = new std::thread(&UI::asciiAnimation, this, images, std::ref(*asciiAnimationThreadDriver));
}

void UI::stopAnimation() {
    if (!isAnimationStarted()) return;
    // enable "Start animation" button in main menu
    toggleMainMenuItem(5u, true);
    // disable "Stop animation" button in main menu
    toggleMainMenuItem(6u, false);
    *asciiAnimationThreadDriver = false;
    asciiAnimationThread->join();
    delete asciiAnimationThread;
    delete asciiAnimationThreadDriver;
    asciiAnimationThread = nullptr;
    asciiAnimationThreadDriver = nullptr;
}

const Image *UI::getDisplayedImage() const {
    return displayedImage;
}

void UI::showErrorPanel(const std::string &text) {
    dynamic_cast<Text *>(views[UIConsts::ViewIndex::TEXT_ERROR])->changeText(text);
    auto *errorMenu = dynamic_cast<Menu *>(views[UIConsts::ViewIndex::MENU_ERROR]);
    errorMenu->show();
    while (true) {
        switch (errorMenu->keyboardListener()) {
            case RuntimeCodes::RESIZE_UI: {
                resize();
                draw();
                break;
            }
            case 0u: /* BTN_OK */ {
                errorMenu->hide();
                return;
            }
            default: break;
        }
    }
}

void UI::toggleMainMenuItem(size_t itemPos, bool enabled) {
    dynamic_cast<Menu *>(views[UIConsts::ViewIndex::MENU_MAIN])->toggleItem(itemPos, enabled);
}

void UI::draw() const {
    for (const auto &view : views) view->draw();
    if (displayedImage) printAscii(displayedImage);
    update_panels();
    doupdate();
    drawn = true;
}

void UI::resize() {
    drawn = false;
    // compute height and width of stdscr
    getmaxyx(getWindow(), height, width);
    for (const auto &view : views) view->resize();
}

void UI::show() const {
    // restore saved ncurses state
    reset_prog_mode();
    refresh();
}

void UI::hide() const {
    // save ncurses state
    def_prog_mode();
    endwin();
}

WINDOW *UI::getWindow() const {
    return stdscr;
}

size_t UI::getHeight() const {
    return height;
}

size_t UI::getWidth() const {
    return width;
}

size_t UI::keyboardListener() {
    auto *mainMenu = dynamic_cast<Menu *>(views[UIConsts::ViewIndex::MENU_MAIN]);
    mainMenu->show();
    while (true) {
        switch (mainMenu->keyboardListener()) {
            case RuntimeCodes::RESIZE_UI: {
                stopAnimation();
                resize();
                draw();
                break;
            }
            case 0u: /* BTN_ADD_IMAGE */ {
                stopAnimation();
                return RuntimeCodes::ADD_IMAGE;
            }
            case 1u: /* BTN_SHOW_IMAGE */ {
                stopAnimation();
                return RuntimeCodes::SHOW_IMAGE;
            }
            case 2u: /* BTN_GRAYSCALE_LEVEL */ {
                stopAnimation();
                return RuntimeCodes::SET_LEVEL;
            }
            case 3u: /* BTN_EDIT_IMAGE */ {
                stopAnimation();
                return RuntimeCodes::EDIT_IMAGE;
            }
            case 4u: /* BTN_REMOVE_IMAGE */ {
                stopAnimation();
                return RuntimeCodes::REMOVE_IMAGE;
            }
            case 5u: /* BTN_PLAY_ANIM */ {
                return RuntimeCodes::PLAY_ANIM;
            }
            case 6u: /* BTN_PAUSE_ANIM */ {
                return RuntimeCodes::PAUSE_ANIM;
            }
            case 7u: /* BTN_EXPORT_ART */ {
                stopAnimation();
                return RuntimeCodes::EXPORT_ART;
            }
            case 8u: /* BTN_EXIT */ {
                stopAnimation();
                if (showExitPanel()) return RuntimeCodes::TERMINATE_PROGRAM;
            }
            default: break;
        }
    }
}

bool UI::isAnimationStarted() const {
    return asciiAnimationThread;
}

UI::~UI() {
    for (auto &view : views) delete view;
    erase();
    endwin();
}

void UI::asciiAnimation(const std::vector<Image *> &images, std::atomic<bool> &controller) const {
    size_t imageIndex = 0u;
    while (controller) {
        displayedImage = images[imageIndex++];
        if (isDrawn()) printAscii(displayedImage);
        std::this_thread::sleep_for(std::chrono::milliseconds(UIConsts::ANIMATION_SLEEP_TIME_MS));
        if (imageIndex >= images.size()) imageIndex = 0u;
    }
}

bool UI::showExitPanel() {
    auto *exitMenu = dynamic_cast<Menu *>(views[UIConsts::ViewIndex::MENU_EXIT]);
    exitMenu->show();
    while (true) {
        switch (exitMenu->keyboardListener()) {
            case RuntimeCodes::RESIZE_UI: {
                resize();
                draw();
                break;
            }
            case 0u: /* BTN_CANCEL */ {
                exitMenu->hide();
                return false;
            }
            case 1u: /* BTN_EXIT */
                return true;
            default: break;
        }
    }
}