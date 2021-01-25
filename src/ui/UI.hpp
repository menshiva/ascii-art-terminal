#ifndef SEMESTR_UI_HPP
#define SEMESTR_UI_HPP

#include "view/Panel.hpp"
#include "view/Menu.hpp"
#include "view/Text.hpp"
#include "../image/Image.hpp"
#include <thread>
#include <atomic>

/**
 * @brief User interface.
 *
 * This class provides user interface logic.\n
 * It stores all views and can control (draw, resize, show etc.) them.\n
 * Manages connection between _main program_ logic and views.\n
 * It is derived from View because of providing the same basic logic as the other views.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class UI : public View {
    std::vector<View *> views; /**< Child views. */
    mutable const Image *displayedImage; /**< Currently displaying image. */

    std::thread *asciiAnimationThread; /**< Thread which is providing all animation logic. */
    std::atomic<bool> *asciiAnimationThreadDriver; /**< Controller for #asciiAnimationThread. */
public:
    /**
     * Constructor which initializes _ncurses_ screen and all child #views.
     * @note At this point, #displayedImage, #asciiAnimationThread and #asciiAnimationThreadDriver
     * are `nullptr`.
     */
    UI();

    /**
     * @attention Copy constructor is forbidden.
     */
    UI(const UI &) = delete;

    /**
     * @attention Assignment operator is forbidden.
     */
    UI &operator=(const UI &) = delete;

    /**
     * Sets _image_ as #displayedImage and prints it in the _right_ Panel (#UIConsts::ViewIndex::PANEL_RIGHT).
     *
     * @param image Image to print.
     */
    void printAscii(const Image *image) const;

    /**
     * Refreshes and redraws #displayedImage.
     */
    void refreshAscii() const;

    /**
     * Clears #displayedImage from the _right_ Panel (#UIConsts::ViewIndex::PANEL_RIGHT).
     * @note At this point, #displayedImage is `nullptr`.
     */
    void clearAscii() const;

    /**
     * Sets #asciiAnimationThread by sending _images_ to it and activate it by setting
     * #asciiAnimationThreadDriver to `true`.
     *
     * @param images All images which will be used in animation.
     */
    void startAnimation(const std::vector<Image *> &images);

    /**
     * Sets #asciiAnimationThreadDriver to `false` and waits #asciiAnimationThread to stop.
     * @note At this point, #asciiAnimationThread and #asciiAnimationThreadDriver are `nullptr`.
     */
    void stopAnimation();

    /**
     * @return #displayedImage.
     */
    const Image *getDisplayedImage() const;

    /**
     * Shows _error_ Panel (#UIConsts::ViewIndex::PANEL_ERROR).
     *
     * @param text Error Panel title.
     */
    void showErrorPanel(const std::string &text);

    /**
     * Toggles item in _main_ Menu (#UIConsts::ViewIndex::MENU_MAIN) by calling #Menu::toggleItem().
     *
     * @param itemPos Item index from #items.
     * @param enabled Enable/disable item.
     */
    void toggleMainMenuItem(size_t itemPos, bool enabled);

    /**
     * Draws all child #views.
     * @note Sets #drawn flag to `true`.
     */
    void draw() const override;

    /**
     * Computes self's #height and #width and resizes all child #views.
     * @note Sets #drawn flag to `false`.
     * @warning Function does _not_ draw #views after computing.
     */
    void resize() override;

    /**
     * Shows UI.
     */
    void show() const override;

    /**
     * Hides UI.
     */
    void hide() const override;

    /**
     * @return stdscr (_ncurses.h_).
     */
    WINDOW *getWindow() const override;

    /**
     * @return #height.
     */
    size_t getHeight() const override;

    /**
     * @return #width.
     */
    size_t getWidth() const override;

    /**
     * Handles keyboard actions and updates _main_ Menu (#UIConsts::ViewIndex::MENU_MAIN), basing on this actions.
     *
     * @return Index of chosen item from _main_ Menu (#UIConsts::ViewIndex::MENU_MAIN).
     */
    size_t keyboardListener();

    /**
     * @return If #asciiAnimationThread is not `nullptr`.
     */
    bool isAnimationStarted() const;

    /**
     * Destructor. _Hides_ user interface by clearing the screen and _deletes_ all allocated #views.
     */
    ~UI() override;

private:
    /**
     * Provides all logic for #asciiAnimationThread.\n
     * Changes #displayedImage by setting it to next Image from _images_ and calls #printAscii().
     * @note Thread sleeps for #UIConsts::ANIMATION_SLEEP_TIME_MS after every "frame".
     *
     * @param images All images which will be used in animation.
     * @param controller Controller for #asciiAnimationThread.
     * @relatesalso UI
     */
    void asciiAnimation(const std::vector<Image *> &images, std::atomic<bool> &controller) const;

    /**
     * Shows _exit_ Panel (#UIConsts::ViewIndex::PANEL_EXIT).
     *
     * @return If "Exit" button in _exit_ Menu (#UIConsts::ViewIndex::MENU_EXIT) was clicked.
     */
    bool showExitPanel();
};

#endif