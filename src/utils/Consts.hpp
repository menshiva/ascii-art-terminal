#ifndef ASCII_CONSTS_HPP
#define ASCII_CONSTS_HPP

/**
 * @brief User interface constants.
 *
 * Constants are defined for View components in UI.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
namespace UIConsts {
    /// Default _upper_ panel relative height (#Panel::heightRelative).
    const float UPPER_PANEL_HEIGHT = 0.125F;
    /// Default _upper_ panel relative width (#Panel::widthRelative).
    const float UPPER_PANEL_WIDTH = 1.0F;
    /// Default _upper_ panel relative _Y_ position (#Panel::yRelative).
    const float UPPER_PANEL_OFFSET_Y = 0.0F;
    /// Default _upper_ panel relative _X_ position  (#Panel::xRelative).
    const float UPPER_PANEL_OFFSET_X = 0.0F;
    /// Default _upper_ panel default visibility (#Panel::drawn flag).
    const bool UPPER_PANEL_VISIBILITY = true;

    /// Default _left_ panel relative height (#Panel::heightRelative).
    const float LEFT_PANEL_HEIGHT = 1.0F - UPPER_PANEL_HEIGHT;
    /// Default _left_ panel relative width (#Panel::widthRelative).
    const float LEFT_PANEL_WIDTH = 0.35F;
    /// Default _left_ panel relative _Y_ position (#Panel::yRelative).
    const float LEFT_PANEL_OFFSET_Y = UPPER_PANEL_HEIGHT;
    /// Default _left_ panel relative _X_ position  (#Panel::xRelative).
    const float LEFT_PANEL_OFFSET_X = 0.0F;
    /// Default _left_ panel default visibility (#Panel::drawn flag).
    const bool LEFT_PANEL_VISIBILITY = true;

    /// Default _right_ panel relative height (#Panel::heightRelative).
    const float RIGHT_PANEL_HEIGHT = LEFT_PANEL_HEIGHT;
    /// Default _right_ panel relative width (#Panel::widthRelative).
    const float RIGHT_PANEL_WIDTH = UPPER_PANEL_WIDTH - LEFT_PANEL_WIDTH;
    /// Default _right_ panel relative _Y_ position (#Panel::yRelative).
    const float RIGHT_PANEL_OFFSET_Y = LEFT_PANEL_OFFSET_Y;
    /// Default _right_ panel relative _X_ position  (#Panel::xRelative).
    const float RIGHT_PANEL_OFFSET_X = LEFT_PANEL_WIDTH;
    /// Default _right_ panel default visibility (#Panel::drawn flag).
    const bool RIGHT_PANEL_VISIBILITY = true;

    /// Default _error_ panel relative height (#Panel::heightRelative).
    const float ERROR_PANEL_HEIGHT = 0.25F;
    /// Default _error_ panel relative width (#Panel::widthRelative).
    const float ERROR_PANEL_WIDTH = 0.45F;
    /// Default _error_ panel relative _Y_ position (#Panel::yRelative).
    const float ERROR_PANEL_OFFSET_Y = 0.5F - ERROR_PANEL_HEIGHT / 2.0F;
    /// Default _error_ panel relative _X_ position  (#Panel::xRelative).
    const float ERROR_PANEL_OFFSET_X = 0.5F - ERROR_PANEL_WIDTH / 2.0F;
    /// Default _error_ panel default visibility (#Panel::drawn flag).
    const bool ERROR_PANEL_VISIBILITY = false;

    /// Default _exit_ panel relative height (#Panel::heightRelative).
    const float EXIT_PANEL_HEIGHT = 0.25F;
    /// Default _exit_ panel relative width (#Panel::widthRelative).
    const float EXIT_PANEL_WIDTH = 0.45F;
    /// Default _exit_ panel relative _Y_ position (#Panel::yRelative).
    const float EXIT_PANEL_OFFSET_Y = 0.5F - EXIT_PANEL_HEIGHT / 2.0F;
    /// Default _exit_ panel relative _X_ position  (#Panel::xRelative).
    const float EXIT_PANEL_OFFSET_X = 0.5F - EXIT_PANEL_WIDTH / 2.0F;
    /// Default _exit_ panel default visibility (#Panel::drawn flag).
    const bool EXIT_PANEL_VISIBILITY = false;

    /// Default _upper_ panel title text (#Text::text).
    const char *const UPPER_PANEL_TEXT = "ASCII art";
    /// Default _upper_ panel title _Y_ position (#Text::yRelative).
    const float UPPER_PANEL_TEXT_OFFSET_Y = 0.5F;
    /// Default _upper_ panel title _X_ position (#Text::xRelative).
    const float UPPER_PANEL_TEXT_OFFSET_X = 0.5F;

    /// Default _error_ panel title text (#Text::text).
    const char *const ERROR_PANEL_TEXT = "";
    /// Default _error_ panel title _Y_ position (#Text::yRelative).
    const float ERROR_PANEL_TEXT_OFFSET_Y = 0.35F;
    /// Default _error_ panel title _X_ position (#Text::xRelative).
    const float ERROR_PANEL_TEXT_OFFSET_X = 0.5F;

    /// Default _exit_ panel title text (#Text::text).
    const char *const EXIT_PANEL_TEXT = "Are you sure you want to exit?";
    /// Default _exit_ panel title _Y_ position (#Text::yRelative).
    const float EXIT_PANEL_TEXT_OFFSET_Y = 0.35F;
    /// Default _exit_ panel title _X_ position (#Text::xRelative).
    const float EXIT_PANEL_TEXT_OFFSET_X = 0.5F;

    /// Default _main_ menu _Y_ position (#Menu::yRelative).
    const float MAIN_MENU_OFFSET_Y = 0.5F;
    /// Default _main_ menu _X_ position (#Menu::xRelative).
    const float MAIN_MENU_OFFSET_X = 0.5F;

    /// Default _error_ menu _Y_ position (#Menu::yRelative).
    const float ERROR_MENU_OFFSET_Y = 0.7F;
    /// Default _error_ menu _X_ position (#Menu::xRelative).
    const float ERROR_MENU_OFFSET_X = 0.5F;

    /// Default _exit_ menu _Y_ position (#Menu::yRelative).
    const float EXIT_MENU_OFFSET_Y = 0.7F;
    /// Default _exit_ menu _X_ position (#Menu::xRelative).
    const float EXIT_MENU_OFFSET_X = 0.5F;

    /// _Error_ panel title text if no images added.
    const char *const ERROR_NO_IMAGES = "Load at least 1 image.";
    /// _Error_ panel title text if art is not shown.
    const char *const ERROR_NOT_SHOWN = "Art is not shown.";
    /// _Error_ panel title text if less than 1 image added.
    const char *const ERROR_FEW_IMAGES = "Load at least 2 images.";
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
    const char *const BTN_PAUSE_ANIM = "Stop animation";
    /// Default _main_ menu button text.
    const char *const BTN_EXPORT_ASCII = "Export art";
    /// "OK" button text.
    const char *const BTN_OK = "Ok";
    /// "Cancel" button text.
    const char *const BTN_CANCEL = "Cancel";
    /// "Exit" button text.
    const char *const BTN_EXIT = "Exit";

    /// Default delay between "frames" in animation (_in milliseconds_).
    const size_t ANIMATION_SLEEP_TIME_MS = 400;

    /**
     * @brief UI children indexes in view array.
     *
     * Constants are defined for obtaining View components from UI.
     *
     * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
     */
    namespace ViewIndex {
        /// _Add image_ button index in main menu.
        const size_t BTN_ADD_IMAGE = 0;
        /// _Show image_ button index in main menu.
        const size_t BTN_SHOW_IMAGE = 1;
        /// _Grayscale level_ button index in main menu.
        const size_t BTN_GRAYSCALE_LEVEL = 2;
        /// _Edit image_ button index in main menu.
        const size_t BTN_EDIT_IMAGE = 3;
        /// _Remove image_ button index in main menu.
        const size_t BTN_REMOVE_IMAGE = 4;
        /// _Play animation_ button index in main menu.
        const size_t BTN_PLAY_ANIM = 5;
        /// _Stop animation_ button index in main menu.
        const size_t BTN_PAUSE_ANIM = 6;
        /// _Export art_ button index in main menu.
        const size_t BTN_EXPORT_ASCII = 7;
        /// _Exit_ button index in main menu.
        const size_t BTN_EXIT = 8;

        /// _Left_ panel index in panel array.
        const size_t PANEL_LEFT = 1;
        /// _Right_ panel index in panel array.
        const size_t PANEL_RIGHT = 2;
        /// _Error_ panel index in panel array.
        const size_t PANEL_ERROR = 3;
        /// _Exit_ panel index in panel array.
        const size_t PANEL_EXIT = 4;
    }
}

/**
 * @brief Console info constants.
 *
 * Constants are defined for printing information to console.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
namespace ConsoleConsts {
    /// Default symbol at the beginning of the important information.
    const char *const TITLE_SYMBOL = "• ";
    /// Default symbols at the beginning of the user input.
    const char *const INPUT_SYMBOLS = ">>> ";

    /// Console title to enter absolute path to image.
    const char *const ENTER_IMAGE_PATH = "Enter image absolute path (.jpeg | .jpg | .ppm) or \"q\" to cancel:";
    /// Console title to enter absolute path to text file.
    const char *const ENTER_TXT_PATH = "Enter text file (.txt) absolute path to create or \"q\" to cancel:";
    /// Console title to enter grayscale level.
    const char *const ENTER_GRAY_LEVEL = "This is an optional function.\n"
                                         "Enter sequence of symbols from darkest to lightest.\n"
                                         "Your ASCII art will be shown with these symbols.\n"
                                         "Enter \"d\" to use the default grayscale level or \"q\" to cancel:";
    /// Console title to enter image index from list to show.
    const char *const PICK_IMAGE_SHOW = "Enter index of image you want to show or \"q\" to cancel:";
    /// Console title to enter image index from list to remove.
    const char *const PICK_IMAGE_REMOVE = "Enter index of image you want to remove or \"q\" to cancel:";
    /// Console title to enter effect index from list to apply.
    const char *const PICK_EFFECT = "Enter index of effect you want to apply to chosen image or \"q\" to cancel:";

    /// Console status title on converting image(s).
    const char *const STATUS_CONVERTING_WAIT = "Please wait for image to convert...";
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

    /// Console _error_ status title failed _ncurses_ initialization.
    const char *const ERROR_FAILED_NCURSES = "Error initialising ncurses.";
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
    const char *const ERROR_FILE_READ_FAIL = "Failed to read a file.";
}

/**
 * @brief ASCII art conversion constants.
 *
 * Constants are defined for _ASCII art conversion algorithm_.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
namespace AsciiConsts {
    /// Default grayscale level. @note It has 67-level grayscale ramp (for _better_ ASCII art quality).
    const char *const DEFAULT_GRAYSCALE_LEVEL = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^`'.";
    /// Default value for _contrast_ algorithm. @note Ranged from 0 to 255.
    const double DEFAULT_CONTRAST_LEVEL = 255.0;
}

#endif