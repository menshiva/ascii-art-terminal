#include "UI.hpp"

void UI::updateSizeNormalized() {
    int tmpH, tmpW;
    getmaxyx(stdscr, tmpH, tmpW);
    height = tmpH > 0 ? tmpH : 0;
    width = tmpW > 0 ? tmpW : 0;
}

void UI::asciiAnimation(const std::vector<Image *> &images, std::atomic<bool> &controller) {
    size_t imageIndex = 0;
    while (controller) {
        displayedImage = images[imageIndex++];
        printAscii(displayedImage);
        std::this_thread::sleep_for(std::chrono::milliseconds(UIConsts::ANIMATION_SLEEP_TIME_MS));
        if (imageIndex >= images.size()) imageIndex = 0;
    }
}

UI::UI() : View(nullptr, 1.0F, 1.0F, 0.0F, 0.0F),
           mainLoopRunning(false), displayedImage(nullptr),
           asciiAnimationThread(nullptr), asciiAnimationThreadDriver(nullptr) {
    start_color(); // use colors
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK); // disabled item, disabled item with hover
    raw(); // we need to pass typed characters through our program immediately (without buffer)
    noecho(); // we don't need to echo typed characters
    curs_set(0); // invisible cursor
    ESCDELAY = 0; // remove delay for escape character
    updateSizeNormalized();

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
            9, 1,
            std::vector<ITEM *>{
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
            {
                    UIConsts::ViewIndex::BTN_SHOW_IMAGE,
                    UIConsts::ViewIndex::BTN_EDIT_IMAGE,
                    UIConsts::ViewIndex::BTN_REMOVE_IMAGE,
                    UIConsts::ViewIndex::BTN_PLAY_ANIM,
                    UIConsts::ViewIndex::BTN_PAUSE_ANIM,
                    UIConsts::ViewIndex::BTN_EXPORT_ASCII
            },
            [this](size_t idx) -> void {
                if (idx != 5 && idx != 6) stopAnimation();
                switch (idx) {
                    case UIConsts::ViewIndex::BTN_ADD_IMAGE:
                        addImageCallback(*this);
                        break;
                    case UIConsts::ViewIndex::BTN_SHOW_IMAGE:
                        showImageCallback(*this);
                        break;
                    case UIConsts::ViewIndex::BTN_GRAYSCALE_LEVEL:
                        setLevelCallback(*this);
                        break;
                    case UIConsts::ViewIndex::BTN_EDIT_IMAGE:
                        editImageCallback(*this);
                        break;
                    case UIConsts::ViewIndex::BTN_REMOVE_IMAGE:
                        removeImageCallback(*this);
                        break;
                    case UIConsts::ViewIndex::BTN_PLAY_ANIM:
                        playAnimCallback(*this);
                        break;
                    case UIConsts::ViewIndex::BTN_PAUSE_ANIM:
                        stopAnimCallback(*this);
                        break;
                    case UIConsts::ViewIndex::BTN_EXPORT_ASCII:
                        exportArtCallback(*this);
                        break;
                    case UIConsts::ViewIndex::BTN_EXIT:
                        showExitPanel();
                        break;
                    default:
                        break;
                }
            }
    );
    auto *errorMenu = new Menu(
            errorPanel,
            UIConsts::ERROR_MENU_OFFSET_Y, UIConsts::ERROR_MENU_OFFSET_X,
            1, 1,
            std::vector<ITEM *>{
                    new_item(UIConsts::BTN_OK, "")
            },
            {}, [this](size_t) -> void {
                activeMenu.top()->hide();
                activeMenu.pop();
            }
    );
    auto *exitMenu = new Menu(
            exitPanel,
            UIConsts::EXIT_MENU_OFFSET_Y, UIConsts::EXIT_MENU_OFFSET_X,
            1, 2,
            std::vector<ITEM *>{
                    new_item(UIConsts::BTN_CANCEL, ""),
                    new_item(UIConsts::BTN_EXIT, "")
            },
            {}, [this](size_t idx) -> void {
                if (idx == 0) {
                    activeMenu.top()->hide();
                    activeMenu.pop();
                }
                else mainLoopRunning = false;
            }
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

    activeMenu.push(mainMenu);
}

UI::~UI() {
    for (View *view : views) delete view;
    erase();
    endwin();
}

const Image *UI::getDisplayedImage() const {
    return displayedImage;
}

bool UI::isAnimationStarted() const {
    return asciiAnimationThread != nullptr;
}

void UI::setOnAddImageCallback(const std::function<void(UI &)> &onAddImage) {
    addImageCallback = onAddImage;
}

void UI::setOnShowImageCallback(const std::function<void(UI &)> &onShowImage) {
    showImageCallback = onShowImage;
}

void UI::setOnSetLevelCallback(const std::function<void(UI &)> &onSetLevel) {
    setLevelCallback = onSetLevel;
}

void UI::setOnEditImageCallback(const std::function<void(UI &)> &onEditImage) {
    editImageCallback = onEditImage;
}

void UI::setOnRemoveImageCallback(const std::function<void(UI &)> &onRemoveImage) {
    removeImageCallback = onRemoveImage;
}

void UI::setOnPlayAnimCallback(const std::function<void(UI &)> &onPlayAnim) {
    playAnimCallback = onPlayAnim;
}

void UI::setOnStopAnimCallback(const std::function<void(UI &)> &onStopAnim) {
    stopAnimCallback = onStopAnim;
}

void UI::setOnExportArtCallback(const std::function<void(UI &)> &onExportArt) {
    exportArtCallback = onExportArt;
}

void UI::callUpdates() {
    mainLoopRunning = true;
    int pressedKey;
    while (mainLoopRunning) {
        pressedKey = wgetch(activeMenu.top()->getWindow());
        activeMenu.top()->menuInteract(pressedKey);
        if (pressedKey == KEY_RESIZE) {
            stopAnimation();
            resize();
            draw();
        }
    }
}

void UI::showExitPanel() {
    auto exitMenu = dynamic_cast<Menu *>(views[UIConsts::ViewIndex::MENU_EXIT]);
    exitMenu->show();
    activeMenu.push(exitMenu);
}

void UI::showErrorPanel(const std::string &text) {
    dynamic_cast<Text *>(views[UIConsts::ViewIndex::TEXT_ERROR])->changeText(text);
    auto errorMenu = dynamic_cast<Menu *>(views[UIConsts::ViewIndex::MENU_ERROR]);
    errorMenu->show();
    activeMenu.push(errorMenu);
}

void UI::toggleMainMenuItem(size_t itemPos, bool enabled) {
    dynamic_cast<Menu *>(views[UIConsts::ViewIndex::MENU_MAIN])->toggleItem(itemPos, enabled);
}

void UI::printAscii(const Image *image) {
    displayedImage = image;
    auto rightPanel = views[UIConsts::ViewIndex::PANEL_RIGHT];

    size_t panelHeight = rightPanel->getHeight(), panelWidth = rightPanel->getWidth();
    if (panelHeight <= 2 || panelWidth <= 2) return;
    // subtract 2 because top, bottom, left, right panel borders are not count
    panelHeight -= 2;
    panelWidth -= 2;
    size_t rows = panelHeight, cols = panelWidth;
    image->computeArtSize(panelHeight, panelWidth);
    if (panelHeight == 0 || panelWidth == 0) return;

    const std::vector<std::string> ascii = image->getAsciiArt(panelHeight, panelWidth);

    // compute start positions for drawing art in the center of the panel
    size_t startRowPrint = (rows > ascii.size()) ? ((rows - ascii.size()) >> 1) + 1 : 1;
    size_t startColPrint = (cols > ascii[0].size()) ? ((cols - ascii[0].size()) >> 1) + 1 : 1;

    // draw art in the center of the panel
    for (size_t y = 1; y <= rows; ++y) {
        wmove(rightPanel->getWindow(), y, 1);
        for (size_t x = 1; x <= cols; ++x) {
            if (startRowPrint <= y && startColPrint <= x) {
                size_t asciiY = y - startRowPrint, asciiX = x - startColPrint;
                if (asciiY < ascii.size() && asciiX < ascii[0].size()) {
                    waddch(rightPanel->getWindow(), ascii[asciiY][asciiX]);
                    continue;
                }
            }
            waddch(rightPanel->getWindow(), ' ');
        }
    }

    wrefresh(rightPanel->getWindow());
}

void UI::refreshAscii() {
    if (!displayedImage) return;
    printAscii(displayedImage);
}

void UI::clearAscii() {
    displayedImage = nullptr;

    const auto *rightPanel = views[UIConsts::ViewIndex::PANEL_RIGHT];
    size_t panelHeight = rightPanel->getHeight(), panelWidth = rightPanel->getWidth();
    if (panelHeight <= 2 || panelWidth <= 2) return;
    // subtract 2 because we dont want to erase top, bottom, left, right panel borders
    panelHeight -= 2;
    panelWidth -= 2;

    // replace all printed chars with ' '
    for (size_t y = 1; y <= panelHeight; ++y) {
        wmove(rightPanel->getWindow(), y, 1);
        for (size_t x = 1; x <= panelWidth; ++x)
            waddch(rightPanel->getWindow(), ' ');
    }

    wrefresh(rightPanel->getWindow());
}

void UI::startAnimation(const std::vector<Image *> &images) {
    if (isAnimationStarted()) return;
    toggleMainMenuItem(UIConsts::ViewIndex::BTN_PLAY_ANIM, false);
    toggleMainMenuItem(UIConsts::ViewIndex::BTN_PAUSE_ANIM, true);
    asciiAnimationThreadDriver = new std::atomic<bool>{true};
    asciiAnimationThread = new std::thread(&UI::asciiAnimation, this,
                                           images, std::ref(*asciiAnimationThreadDriver));
}

void UI::stopAnimation() {
    if (!isAnimationStarted()) return;
    toggleMainMenuItem(UIConsts::ViewIndex::BTN_PLAY_ANIM, true);
    toggleMainMenuItem(UIConsts::ViewIndex::BTN_PAUSE_ANIM, false);
    *asciiAnimationThreadDriver = false;
    asciiAnimationThread->join();
    delete asciiAnimationThread;
    delete asciiAnimationThreadDriver;
    asciiAnimationThread = nullptr;
    asciiAnimationThreadDriver = nullptr;
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

void UI::draw() {
    for (View *view : views) view->draw();
    if (displayedImage) printAscii(displayedImage);
    update_panels();
    doupdate();
}

void UI::resize() {
    updateSizeNormalized();
    for (View *view : views) view->resize();
}

void UI::show() {
    reset_prog_mode(); // restore saved ncurses state
    refresh();
}

void UI::hide() {
    def_prog_mode(); // save ncurses state
    endwin();
}

bool UI::init() {
    return initscr() != nullptr;
}