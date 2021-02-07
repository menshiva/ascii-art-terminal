#ifndef ASCII_UI_HPP
#define ASCII_UI_HPP

#include <stack>
#include <atomic>
#include <thread>
#include "view/Panel.hpp"
#include "view/Menu.hpp"
#include "view/Text.hpp"
#include "../image/Image.hpp"

class UI : public View {
    std::stack<Menu *> activeMenu;
    std::vector<View *> views;
    bool mainLoopRunning;
    const Image *displayedImage;

    std::thread *asciiAnimationThread;
    std::atomic<bool> *asciiAnimationThreadDriver;

    std::function<void(UI &)> addImageCallback, showImageCallback,
            setLevelCallback, editImageCallback, removeImageCallback,
            playAnimCallback, stopAnimCallback, exportArtCallback;

    void updateSizeNormalized();
    void asciiAnimation(const std::vector<Image *> &images, std::atomic<bool> &controller);
public:
    UI();
    UI(const UI &) = delete;
    UI &operator=(const UI &) = delete;
    UI(UI &&) = delete;
    UI &operator=(UI &&) = delete;
    ~UI() override;

    const Image *getDisplayedImage() const;
    bool isAnimationStarted() const;

    void setOnAddImageCallback(const std::function<void(UI &)> &onAddImage);
    void setOnShowImageCallback(const std::function<void(UI &)> &onShowImage);
    void setOnSetLevelCallback(const std::function<void(UI &)> &onSetLevel);
    void setOnEditImageCallback(const std::function<void(UI &)> &onEditImage);
    void setOnRemoveImageCallback(const std::function<void(UI &)> &onRemoveImage);
    void setOnPlayAnimCallback(const std::function<void(UI &)> &onPlayAnim);
    void setOnStopAnimCallback(const std::function<void(UI &)> &onStopAnim);
    void setOnExportArtCallback(const std::function<void(UI &)> &onExportArt);

    void callUpdates();
    void showExitPanel();
    void showErrorPanel(const std::string &text);
    void toggleMainMenuItem(size_t idx, bool enabled);
    void printAscii(const Image *image);
    void refreshAscii();
    void clearAscii();
    void startAnimation(const std::vector<Image *> &images);
    void stopAnimation();

    WINDOW *getWindow() const override;
    size_t getHeight() const override;
    size_t getWidth() const override;

    void draw() override;
    void resize() override;
    void show() override;
    void hide() override;

    static bool init();
};

#endif