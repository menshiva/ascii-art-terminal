#ifndef ASCII_CONSTS_HPP
#define ASCII_CONSTS_HPP

namespace UIConsts {
    const static float TITLE_PANEL_HEIGHT_REL = 0.1f;
    const static float CONTROLS_PANEL_WIDTH_REL = 0.25f;

    const static float ERROR_PANEL_HEIGHT = 0.25F;
    const static float ERROR_PANEL_WIDTH = 0.45F;
    const static float ERROR_PANEL_OFFSET_Y = 0.5F - ERROR_PANEL_HEIGHT / 2.0F;
    const static float ERROR_PANEL_OFFSET_X = 0.5F - ERROR_PANEL_WIDTH / 2.0F;
    const static bool ERROR_PANEL_VISIBILITY = false;

    const static float EXIT_PANEL_HEIGHT = 0.25F;
    const static float EXIT_PANEL_WIDTH = 0.45F;
    const static float EXIT_PANEL_OFFSET_Y = 0.5F - EXIT_PANEL_HEIGHT / 2.0F;
    const static float EXIT_PANEL_OFFSET_X = 0.5F - EXIT_PANEL_WIDTH / 2.0F;
    const static bool EXIT_PANEL_VISIBILITY = false;

    const static char *const TITLE_TEXT = "ASCII art";

    const static char *const ERROR_PANEL_TEXT = "";
    const static float ERROR_PANEL_TEXT_OFFSET_Y = 0.35F;
    const static float ERROR_PANEL_TEXT_OFFSET_X = 0.5F;

    const static char *const EXIT_PANEL_TEXT = "Are you sure you want to exit?";
    const static float EXIT_PANEL_TEXT_OFFSET_Y = 0.35F;
    const static float EXIT_PANEL_TEXT_OFFSET_X = 0.5F;

    const static float MAIN_MENU_OFFSET_Y = 0.5F;
    const static float MAIN_MENU_OFFSET_X = 0.5F;

    const static float ERROR_MENU_OFFSET_Y = 0.7F;
    const static float ERROR_MENU_OFFSET_X = 0.5F;

    const static float EXIT_MENU_OFFSET_Y = 0.7F;
    const static float EXIT_MENU_OFFSET_X = 0.5F;

    const static char *const ERROR_NO_IMAGES = "Load at least 1 image.";
    const static char *const ERROR_NOT_SHOWN = "Art is not shown.";
    const static char *const ERROR_FEW_IMAGES = "Load at least 2 images.";
    const static char *const ERROR_NO_ANIMATION = "Animation is not started.";

    const static char *const BTN_ADD_IMAGE = "[1] Add image(s)";
    const static char *const BTN_SHOW_IMAGE = "[2] Show ASCII art";
    const static char *const BTN_GRAYSCALE_LEVEL = "[3] Set grayscale level";
    const static char *const BTN_EDIT_IMAGE = "[4] Image effects";
    const static char *const BTN_REMOVE_IMAGE = "[5] Remove image";
    const static char *const BTN_PLAY_ANIM = "[6] Play animation";
    const static char *const BTN_PAUSE_ANIM = "[7] Stop animation";
    const static char *const BTN_EXPORT_ASCII = "[8] Export art";
    const static char *const BTN_EXIT = "[9] Exit";

    const static char *const BTN_OK = "Ok";
    const static char *const BTN_CANCEL = "Cancel";

    const static size_t ANIMATION_SLEEP_TIME_MS = 400;

    enum ViewId : uint8_t {};
}

namespace ConsoleConsts {
    const static char *const TITLE_SYMBOL = "• ";
    const static char *const INPUT_SYMBOLS = ">>> ";

    const static char *const ENTER_IMAGE_PATH = "Enter image absolute path (.jpeg | .jpg | .ppm) or \"q\" to cancel:";
    const static char *const ENTER_TXT_PATH = "Enter text file (.txt) absolute path to create or \"q\" to cancel:";
    const static char *const ENTER_GRAY_LEVEL = "This is an optional function.\n"
                                         "Enter sequence of symbols from darkest to lightest.\n"
                                         "Your ASCII art will be shown with these symbols.\n"
                                         "Enter \"d\" to use the default grayscale level or \"q\" to cancel:";
    const static char *const PICK_IMAGE_SHOW = "Enter index of image you want to show or \"q\" to cancel:";
    const static char *const PICK_IMAGE_REMOVE = "Enter index of image you want to remove or \"q\" to cancel:";
    const static char *const PICK_EFFECT = "Enter index of effect you want to apply to chosen image or \"q\" to cancel:";

    const static char *const STATUS_CONVERTING_WAIT = "Please wait for image to convert...";
    const static char *const STATUS_EXPORT_WAIT = "Please wait for image to export...";
    const static char *const STATUS_CONVERTING_SUCCESS = "Successfully converted to ASCII art!";
    const static char *const STATUS_EXPORT_SUCCESS = "Successfully exported!";
    const static char *const STATUS_CONVERTING_EXIT = "Press Enter to exit.";

    const static char *const TRY_AGAIN = "Try again:";
    const static char *const TRY_ANOTHER_FILE = "Try another file:";

    const static char *const ERROR_FAILED_NCURSES = "Error initialising ncurses.\n";
    const static char *const ERROR_IMAGE_NOT_INDEX = "Wrong image index or command.";
    const static char *const ERROR_IMAGE_BAD_INDEX = "There is no image with that index.";
    const static char *const ERROR_PATH_RELATIVE = "You need to enter absolute path, not relative.";
    const static char *const ERROR_FILE_BAD_CODING = "Bad coded file.";
    const static char *const ERROR_FILE_EXISTS = "This file already exists.";
    const static char *const ERROR_FILE_NOT_FOUND = "File does not exist.";
    const static char *const ERROR_FILE_UNSUPPORTED = "Unsupported file format.";
    const static char *const ERROR_FILE_READ_FAIL = "Failed to read a file.";
}

namespace AsciiConsts {
    const static char *const DEFAULT_GRAYSCALE_LEVEL = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^`'.";
    const static double DEFAULT_CONTRAST_LEVEL = 255.0;
}

#endif
