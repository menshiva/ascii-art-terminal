#ifndef SEMESTR_CONSTS_HPP
#define SEMESTR_CONSTS_HPP

/**
 * @brief User interface constants.
 *
 * Constants which are defined for better working with View components in UI.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
namespace UIConsts {
    /// Default _upper_ panel relative height (#Panel::heightRelative).
    const double UPPER_PANEL_HEIGHT = 0.125;
    /// Default _upper_ panel relative width (#Panel::widthRelative).
    const double UPPER_PANEL_WIDTH = 1.0;
    /// Default _upper_ panel relative _Y_ position (#Panel::yRelative).
    const double UPPER_PANEL_OFFSET_Y = 0.0;
    /// Default _upper_ panel relative _X_ position  (#Panel::xRelative).
    const double UPPER_PANEL_OFFSET_X = 0.0;
    /// Default _upper_ panel default visibility (#Panel::drawn flag).
    const bool UPPER_PANEL_VISIBILITY = true;

    /// Default _left_ panel relative height (#Panel::heightRelative).
    const double LEFT_PANEL_HEIGHT = 1.0 - UPPER_PANEL_HEIGHT;
    /// Default _left_ panel relative width (#Panel::widthRelative).
    const double LEFT_PANEL_WIDTH = 0.35;
    /// Default _left_ panel relative _Y_ position (#Panel::yRelative).
    const double LEFT_PANEL_OFFSET_Y = UPPER_PANEL_HEIGHT;
    /// Default _left_ panel relative _X_ position  (#Panel::xRelative).
    const double LEFT_PANEL_OFFSET_X = 0.0;
    /// Default _left_ panel default visibility (#Panel::drawn flag).
    const bool LEFT_PANEL_VISIBILITY = true;

    /// Default _right_ panel relative height (#Panel::heightRelative).
    const double RIGHT_PANEL_HEIGHT = LEFT_PANEL_HEIGHT;
    /// Default _right_ panel relative width (#Panel::widthRelative).
    const double RIGHT_PANEL_WIDTH = UPPER_PANEL_WIDTH - LEFT_PANEL_WIDTH;
    /// Default _right_ panel relative _Y_ position (#Panel::yRelative).
    const double RIGHT_PANEL_OFFSET_Y = LEFT_PANEL_OFFSET_Y;
    /// Default _right_ panel relative _X_ position  (#Panel::xRelative).
    const double RIGHT_PANEL_OFFSET_X = LEFT_PANEL_WIDTH;
    /// Default _right_ panel default visibility (#Panel::drawn flag).
    const bool RIGHT_PANEL_VISIBILITY = true;

    /// Default _error_ panel relative height (#Panel::heightRelative).
    const double ERROR_PANEL_HEIGHT = 0.25;
    /// Default _error_ panel relative width (#Panel::widthRelative).
    const double ERROR_PANEL_WIDTH = 0.45;
    /// Default _error_ panel relative _Y_ position (#Panel::yRelative).
    const double ERROR_PANEL_OFFSET_Y = 0.5 - ERROR_PANEL_HEIGHT / 2.0;
    /// Default _error_ panel relative _X_ position  (#Panel::xRelative).
    const double ERROR_PANEL_OFFSET_X = 0.5 - ERROR_PANEL_WIDTH / 2.0;
    /// Default _error_ panel default visibility (#Panel::drawn flag).
    const bool ERROR_PANEL_VISIBILITY = false;

    /// Default _exit_ panel relative height (#Panel::heightRelative).
    const double EXIT_PANEL_HEIGHT = 0.25;
    /// Default _exit_ panel relative width (#Panel::widthRelative).
    const double EXIT_PANEL_WIDTH = 0.45;
    /// Default _exit_ panel relative _Y_ position (#Panel::yRelative).
    const double EXIT_PANEL_OFFSET_Y = 0.5 - EXIT_PANEL_HEIGHT / 2.0;
    /// Default _exit_ panel relative _X_ position  (#Panel::xRelative).
    const double EXIT_PANEL_OFFSET_X = 0.5 - EXIT_PANEL_WIDTH / 2.0;
    /// Default _exit_ panel default visibility (#Panel::drawn flag).
    const bool EXIT_PANEL_VISIBILITY = false;

    /// Default _upper_ panel title text (#Text::text).
    const char *const UPPER_PANEL_TEXT = "ASCII art";
    /// Default _upper_ panel title _Y_ position (#Text::yRelative).
    const double UPPER_PANEL_TEXT_OFFSET_Y = 0.5;
    /// Default _upper_ panel title _X_ position (#Text::xRelative).
    const double UPPER_PANEL_TEXT_OFFSET_X = 0.5;

    /// Default _error_ panel title text (#Text::text).
    const char *const ERROR_PANEL_TEXT = "";
    /// Default _error_ panel title _Y_ position (#Text::yRelative).
    const double ERROR_PANEL_TEXT_OFFSET_Y = 0.35;
    /// Default _error_ panel title _X_ position (#Text::xRelative).
    const double ERROR_PANEL_TEXT_OFFSET_X = 0.5;

    /// Default _exit_ panel title text (#Text::text).
    const char *const EXIT_PANEL_TEXT = "Do you really want to exit?";
    /// Default _exit_ panel title _Y_ position (#Text::yRelative).
    const double EXIT_PANEL_TEXT_OFFSET_Y = 0.35;
    /// Default _exit_ panel title _X_ position (#Text::xRelative).
    const double EXIT_PANEL_TEXT_OFFSET_X = 0.5;

    /// Default _main_ menu _Y_ position (#Menu::yRelative).
    const double MAIN_MENU_OFFSET_Y = 0.5;
    /// Default _main_ menu _X_ position (#Menu::xRelative).
    const double MAIN_MENU_OFFSET_X = 0.5;

    /// Default _error_ menu _Y_ position (#Menu::yRelative).
    const double ERROR_MENU_OFFSET_Y = 0.7;
    /// Default _error_ menu _X_ position (#Menu::xRelative).
    const double ERROR_MENU_OFFSET_X = 0.5;

    /// Default _exit_ menu _Y_ position (#Menu::yRelative).
    const double EXIT_MENU_OFFSET_Y = 0.7;
    /// Default _exit_ menu _X_ position (#Menu::xRelative).
    const double EXIT_MENU_OFFSET_X = 0.5;

    /// _Error_ panel title text if no images added.
    const char *const ERROR_NO_IMAGES = "You have no images added.";
    /// _Error_ panel title text if art is not shown.
    const char *const ERROR_NOT_SHOWN = "Chosen art is not shown.";
    /// _Error_ panel title text if less than 1 image added.
    const char *const ERROR_FEW_IMAGES = "You have less than 1 image added.";
    /// _Error_ panel title text if animation is not started.
    const char *const ERROR_NO_ANIMATION = "Animation is not started.";

    /// Default _main_ menu button text.
    const char *const BTN_ADD_IMAGE = "Add image(s)";
    /// Default _main_ menu button text.
    const char *const BTN_SHOW_IMAGE = "Show ASCII art";
    /// Default _main_ menu button text.
    const char *const BTN_GRAYSCALE_LEVEL = "Set grayscale level";
    /// Default _main_ menu button text.
    const char *const BTN_EDIT_IMAGE = "Image effects";
    /// Default _main_ menu button text.
    const char *const BTN_REMOVE_IMAGE = "Remove image";
    /// Default _main_ menu button text.
    const char *const BTN_PLAY_ANIM = "Play animation";
    /// Default _main_ menu button text.
    const char *const BTN_PAUSE_ANIM = "Pause animation";
    /// Default _main_ menu button text.
    const char *const BTN_EXPORT_ASCII = "Export art";
    /// "OK" button text.
    const char *const BTN_OK = "Ok";
    /// "Cancel" button text.
    const char *const BTN_CANCEL = "Cancel";
    /// "Exit" button text.
    const char *const BTN_EXIT = "Exit";

    /// Default delay between "frames" in animation (_in milliseconds_).
    const unsigned long ANIMATION_SLEEP_TIME_MS = 250;

    /**
     * @brief UI childs indexes in stack.
     *
     * Constants which are defined for better obtaining View components from UI.
     *
     * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
     */
    namespace ViewIndex {
        /// _Upper_ panel index in stack.
        const unsigned long PANEL_UPPER = 0u;
        /// _Left_ panel index in stack.
        const unsigned long PANEL_LEFT = 1u;
        /// _Right_ panel index in stack.
        const unsigned long PANEL_RIGHT = 2u;
        /// _Error_ panel index in stack.
        const unsigned long PANEL_ERROR = 3u;
        /// _Exit_ panel index in stack.
        const unsigned long PANEL_EXIT = 4u;

        /// _Upper_ panel text index in stack.
        const unsigned long TEXT_UPPER = 5u;
        /// _Error_ panel text index in stack.
        const unsigned long TEXT_ERROR = 6u;
        /// _Exit_ panel text index in stack.
        const unsigned long TEXT_EXIT = 7u;

        /// _Main_ menu index in stack.
        const unsigned long MENU_MAIN = 8u;
        /// _Error_ menu index in stack.
        const unsigned long MENU_ERROR = 9u;
        /// _Exit_ menu index in stack.
        const unsigned long MENU_EXIT = 10u;
    }
}

/**
 * @brief Console info constants.
 *
 * Constants which are defined for better printing information to console.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
namespace ConsoleConsts {
    /// Default symbol at the beginning of important information.
    const char *const TITLE_SYMBOL = "• ";
    /// Default symbols at the beginning of user input.
    const char *const INPUT_SYMBOLS = ">>> ";

    /// Console title to enter absolute path to image.
    const char *const ENTER_IMAGE_PATH = "Enter image absolute path (.jpeg | .jpg | .ppm) or \"q\" to cancel:";
    /// Console title to enter absolute path to text file.
    const char *const ENTER_TXT_PATH = "Enter text file (.txt) absolute path to create or \"q\" to cancel:";
    /// Console title to enter grayscale level.
    const char *const ENTER_GRAY_LEVEL = "This is an optional function.\n"
                                         "Enter sequence of symbols from darkest to lightest.\n"
                                         "Your ASCII art will be shown by this symbols.\n"
                                         "Enter \"d\" to use the default grayscale level or \"q\" to cancel:";
    /// Console title to enter image index from list to show.
    const char *const PICK_IMAGE_SHOW = "Enter index of image you want to show or \"q\" to cancel:";
    /// Console title to enter image index from list to remove.
    const char *const PICK_IMAGE_REMOVE = "Enter index of image you want to remove or \"q\" to cancel:";
    /// Console title to enter effect index from list to apply.
    const char *const PICK_EFFECT = "Enter index of effect you want to apply to chosen image or \"q\" to cancel:";

    /// Console status title on converting image(s).
    const char *const STATUS_CONVERTING_WAIT = "Please wait for image(s) to convert...";
    /// Console status title on exporting image.
    const char *const STATUS_EXPORT_WAIT = "Please wait for image to export...";
    /// Console status title on successfully converted image.
    const char *const STATUS_CONVERTING_SUCCESS = "Successfully converted to ASCII art!";
    /// Console status title on successfully exported image.
    const char *const STATUS_EXPORT_SUCCESS = "Successfully exported!";
    /// Console status title on exit from console mode suggestion.
    const char *const STATUS_CONVERTING_EXIT = "Press Enter to exit.";

    /// "Try again" information title.
    const char *const TRY_AGAIN = "Try again:";
    /// "Try another file" information title.
    const char *const TRY_ANOTHER_FILE = "Try another file:";

    /// Console _error_ status title on entering wrong symbol(s).
    const char *const ERROR_IMAGE_NOT_INDEX = "Wrong image index or command.";
    /// Console _error_ status title on entering wrong index.
    const char *const ERROR_IMAGE_BAD_INDEX = "There is no image with that index.";
    /// Console _error_ status title on entering bad _absolute_ path to file.
    const char *const ERROR_PATH_RELATIVE = "You need to enter absolute path, not relative.";
    /// Console _error_ status title on reading bad coded file.
    const char *const ERROR_FILE_BAD_CODING = "Bad coded file.";
    /// Console _error_ status title on saving file which already exists.
    const char *const ERROR_FILE_EXISTS = "This file already exists.";
    /// Console _error_ status title on reading file which does _not_ exists.
    const char *const ERROR_FILE_NOT_FOUND = "File does not exist.";
    /// Console _error_ status title on reading image file with _unsupported_ format.
    const char *const ERROR_FILE_UNSUPPORTED = "Unsupported file format.";
    /// Console _error_ status title on reading file with no read permission.
    const char *const ERROR_FILE_READ_FAIL = "Failed to read file.";
}

/**
 * @brief ASCII art convertation constants.
 *
 * Constants which are defined for better working with _ASCII art convertation algorithm_.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
namespace AsciiConsts {
    /// Default grayscale level. @note It has 67-level grayscale ramp (for _better_ ASCII art detalization).
    const char *const DEFAULT_GRAYSCALE_LEVEL = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^`'.";
    /// Default value for _contrast_ algorithm. @note Ranged from 0 to 255.
    const double DEFAULT_CONTRAST_LEVEL = 255.0;
}

/**
 * @brief Main logic runtime constants.
 *
 * Constants which are defined for better working with program runtime.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
namespace RuntimeCodes {
    /// "Add image(s)" button click event.
    const unsigned long ADD_IMAGE = 0x79u;
    /// "Show image" button click event.
    const unsigned long SHOW_IMAGE = 0x78u;
    /// "Set grayscale level" button click event.
    const unsigned long SET_LEVEL = 0x77u;
    /// "Edit image" button click event.
    const unsigned long EDIT_IMAGE = 0x76u;
    /// "Remove image" button click event.
    const unsigned long REMOVE_IMAGE = 0x75u;
    /// "Play animation" button click event.
    const unsigned long PLAY_ANIM = 0x74u;
    /// "Pause animation" button click event.
    const unsigned long PAUSE_ANIM = 0x73u;
    /// "Export art" button click event.
    const unsigned long EXPORT_ART = 0x72u;
    /// Resize UI event. @note Triggers on terminal resizing.
    const unsigned long RESIZE_UI = 0x71u;
    /// Close program event.
    const unsigned long TERMINATE_PROGRAM = 0x70u;
}

#endif