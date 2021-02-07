#ifndef ASCII_UI_HPP
#define ASCII_UI_HPP

#include <stack>
#include <atomic>
#include <thread>
#include "view/Panel.hpp"
#include "../image/Image.hpp"

/**
 * @brief User interface.
 *
 * User interface logic.\n
 * Stores and controls all views (draw, resize, show etc.).\n
 * Manages connection between _main program_ logic and views.\n
 * It is derived from View due to providing the same basic logic as the other views.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class UI : public View {
    std::stack<Menu *> activeMenu; /**< Stack with visible and active menus. */
    std::vector<Panel *> panels; /**< Child panels. */
    bool mainLoopRunning; /**< Main loop driver flag. */
    const Image *displayedImage; /**< Displayed image. */

    std::thread *asciiAnimationThread; /**< Thread providing all animation logic. */
    std::atomic<bool> *asciiAnimationThreadDriver; /**< #asciiAnimationThread controller. */

    std::function<void(UI &)> addImageCallback; /**< On _Add image_ button click event listener. */
    std::function<void(UI &)> showImageCallback; /**< On _Show image_ button click event listener. */
    std::function<void(UI &)> setLevelCallback; /**< On _Set grayscale level_ button click event listener. */
    std::function<void(UI &)> editImageCallback; /**< On _Image effects_ button click event listener. */
    std::function<void(UI &)> removeImageCallback; /**< On _Remove image_ button click event listener. */
    std::function<void(UI &)> playAnimCallback; /**< On _Play animation_ button click event listener. */
    std::function<void(UI &)> stopAnimCallback; /**< On _Stop animation_ button click event listener. */
    std::function<void(UI &)> exportArtCallback; /**< On _Export art_ button click event listener. */

    ///Updates UI sizes.
    void updateSizeNormalized();

    /**
     * Provides all animation logic (for #asciiAnimationThread).\n
     * Changes #displayedImage by setting it to the next Image from _images_ and calls #printAscii().
     * @note Thread sleeps for #UIConsts::ANIMATION_SLEEP_TIME_MS after every "frame".
     *
     * @param images All images which will be used in animation.
     * @param controller Controller for #asciiAnimationThread.
     */
    void asciiAnimation(const std::vector<Image *> &images, std::atomic<bool> &controller);
public:
    /**
     * Constructor.\n
     * Initializes child #panels and their children.
     * @note #displayedImage, #asciiAnimationThread and #asciiAnimationThreadDriver are set to `nullptr` by default.
     */
    UI();

    ///@attention Copy constructor is forbidden.
    UI(const UI &) = delete;

    ///@attention Copy assignment operator is forbidden.
    UI &operator=(const UI &) = delete;

    ///@attention Move constructor is forbidden.
    UI(UI &&) = delete;

    ///@attention Move assignment operator is forbidden.
    UI &operator=(UI &&) = delete;

    /**
     * Destructor.\n
     * _Hides_ user interface by clearing the screen and _frees_ memory allocated for #panels.
     */
    ~UI() override;

    ///@return #displayedImage.
    const Image *getDisplayedImage() const;

    ///@return If #asciiAnimationThread is not `nullptr`.
    bool isAnimationStarted() const;

    /**
     * Sets _Add image_ button click event listener.
     *
     * @param onAddImage _Add image_ button click event listener.
     */
    void setOnAddImageCallback(const std::function<void(UI &)> &onAddImage);

    /**
     * Sets _Show image_ button click event listener.
     *
     * @param onShowImage _Show image_ button click event listener.
     */
    void setOnShowImageCallback(const std::function<void(UI &)> &onShowImage);

    /**
     * Sets _Set grayscale level_ button click event listener.
     *
     * @param onSetLevel _Set grayscale level_ button click event listener.
     */
    void setOnSetLevelCallback(const std::function<void(UI &)> &onSetLevel);

    /**
     * Sets _Image effects_ button click event listener.
     *
     * @param onEditImage _Image effects_ button click event listener.
     */
    void setOnEditImageCallback(const std::function<void(UI &)> &onEditImage);

    /**
     * Sets _Remove image_ button click event listener.
     *
     * @param onRemoveImage _Remove image_ button click event listener.
     */
    void setOnRemoveImageCallback(const std::function<void(UI &)> &onRemoveImage);

    /**
     * Sets _Play animation_ button click event listener.
     *
     * @param onPlayAnim _Play animation_ button click event listener.
     */
    void setOnPlayAnimCallback(const std::function<void(UI &)> &onPlayAnim);

    /**
     * Sets _Stop animation_ button click event listener.
     *
     * @param onStopAnim _Stop animation_ button click event listener.
     */
    void setOnStopAnimCallback(const std::function<void(UI &)> &onStopAnim);

    /**
     * Sets _Export art_ button click event listener.
     *
     * @param onExportArt _Export art_ button click event listener.
     */
    void setOnExportArtCallback(const std::function<void(UI &)> &onExportArt);

    ///Handles keyboard actions.
    void callUpdates();

    ///Shows _exit_ Panel (#UIConsts::ViewIndex::PANEL_EXIT).
    void showExitPanel();

    /**
     * Shows _error_ Panel (#UIConsts::ViewIndex::PANEL_ERROR).
     *
     * @param text Error Panel title.
     */
    void showErrorPanel(const std::string &text);

    /**
     * Toggles item in _main_ Menu by calling #Menu::toggleItem().
     *
     * @param idx Item index from #Menu::items.
     * @param enabled Enable/disable item.
     */
    void toggleMainMenuItem(size_t idx, bool enabled);

    /**
     * Sets _image_ as #displayedImage and prints it in the _right_ Panel (#UIConsts::ViewIndex::PANEL_RIGHT).
     *
     * @param image Image to print.
     */
    void printAscii(const Image *image);

    ///Refreshes and redraws #displayedImage.
    void refreshAscii();

    /**
     * Clears #displayedImage from the _right_ Panel (#UIConsts::ViewIndex::PANEL_RIGHT).
     * @note Sets #displayedImage to `nullptr`.
     */
    void clearAscii();

    /**
     * Sets #asciiAnimationThread by sending _images_ to it and activates it by setting
     * #asciiAnimationThreadDriver to `true`.
     *
     * @param images All images which will be used in animation.
     */
    void startAnimation(const std::vector<Image *> &images);

    /**
     * Sets #asciiAnimationThreadDriver to `false` and waits for #asciiAnimationThread to stop.
     * @note Sets #asciiAnimationThread and #asciiAnimationThreadDriver to `nullptr`.
     */
    void stopAnimation();

    ///Shows UI.
    static void show();

    ///Hides UI.
    static void hide();

    ///@return stdscr (_ncurses.h_).
    WINDOW *getWindow() const override;
    size_t getHeight() const override;
    size_t getWidth() const override;

    ///Draws all #panels.
    void draw() override;

    /**
     * Computes self's #height and #width and resizes all #panels.
     * @warning Function does _not_ draw #panels after resizing.
     */
    void resize() override;

    /**
     * Initialize _ncurses_ screen.
     *
     * @return 'true' on success, 'false' otherwise.
     */
    static bool init();
};

#endif