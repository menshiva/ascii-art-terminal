#include "factory/ImageFactory.hpp"
#include "ui/UI.hpp"

/**
 * @mainpage ASCII art
 *
 * Image to ASCII art conversion.
 *
 * _Features_:\n
 * • User interface\n
 * • JPEG, PPM image formats\n
 * • Animation\n
 * • Contrast, negative, convolution image effects\n
 * • Your own ASCII art style\n
 * • Export art to .txt file in full image resolution
 *
 * _Third Party Libraries_:\n
 * • ncurses (https://invisible-island.net/ncurses/announce.html)\n
 * • libjpeg (http://libjpeg.sourceforge.net/)
 *
 * _Sources_:\n
 * • Image scaling algorithm: https://en.wikipedia.org/wiki/Image_scaling#Nearest-neighbor_interpolation \n
 * • RGB to Grayscale algorithm:
 * https://en.wikipedia.org/wiki/Grayscale#Colorimetric_(perceptual_luminance-preserving)_conversion_to_grayscale \n
 * • Contrast algorithm:
 * https://en.wikipedia.org/wiki/Contrast_(vision) and
 * https://math.stackexchange.com/questions/906240/algorithms-to-increase-or-decrease-the-contrast-of-an-image \n
 * • Convolution algorithm: https://setosa.io/ev/image-kernels/ \n
 * • JPEG decompression example:
 * https://github.com/LuaDist/libjpeg/blob/master/example.c#L210
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */

void addImage(UI &ui, ImageFactory &factory) {
    ui.hide();
    const bool isImageRead = factory.readImage();
    ui.show();
    if (isImageRead) {
        // enable "Show image" button
        ui.toggleMainMenuItem(1U, true);
        // enable "Remove image" button
        ui.toggleMainMenuItem(4U, true);
        if (factory.getAllImages().size() >= 2U)
            // enable "Play animation" button
            ui.toggleMainMenuItem(5U, true);
    }
}

void showImage(UI &ui, ImageFactory &factory) {
    if (factory.getAllImages().empty()) ui.showErrorPanel(UIConsts::ERROR_NO_IMAGES);
    else {
        ui.hide();
        const Image *pickedImage = factory.chooseImageFromList(ConsoleConsts::PICK_IMAGE_SHOW);
        ui.show();
        if (pickedImage) {
            ui.printAscii(pickedImage);
            // enable "Edit image" button
            ui.toggleMainMenuItem(3U, true);
            // enable "Export art" button
            ui.toggleMainMenuItem(7U, true);
        }
    }
}

void setLevel(UI &ui, ImageFactory &factory) {
    ui.hide();
    const bool isLevelChanged = factory.readGrayscaleLevel();
    ui.show();
    if (isLevelChanged && ui.getDisplayedImage()) ui.refreshAscii();
}

void editImage(UI &ui, ImageFactory &factory) {
    if (!ui.getDisplayedImage()) ui.showErrorPanel(UIConsts::ERROR_NOT_SHOWN);
    else {
        ui.hide();
        const bool isEffectApplied = factory.applyEffect(const_cast<Image *>(ui.getDisplayedImage()));
        ui.show();
        if (isEffectApplied) ui.refreshAscii();
    }
}

void removeImage(UI &ui, ImageFactory &factory) {
    if (factory.getAllImages().empty()) ui.showErrorPanel(UIConsts::ERROR_NO_IMAGES);
    else {
        ui.hide();
        Image *pickedImage = factory.chooseImageFromList(ConsoleConsts::PICK_IMAGE_REMOVE);
        ui.show();
        if (pickedImage) {
            if (pickedImage == ui.getDisplayedImage()) {
                ui.clearAscii();
                // disable "Edit image" button
                ui.toggleMainMenuItem(3U, false);
                // disable "Export art" button
                ui.toggleMainMenuItem(7U, false);
            }
            factory.removeImage(pickedImage);
            if (factory.getAllImages().empty()) {
                // disable "Show image" button
                ui.toggleMainMenuItem(1U, false);
                // disable "Edit image" button
                ui.toggleMainMenuItem(3U, false);
                // disable "Remove image" button
                ui.toggleMainMenuItem(4U, false);
                // disable "Export art" button
                ui.toggleMainMenuItem(7U, false);
            } else if (factory.getAllImages().size() < 2U)
                // disable "Play animation" button
                ui.toggleMainMenuItem(5U, false);
        }
    }
}

void playAnim(UI &ui, ImageFactory &factory) {
    if (factory.getAllImages().size() < 2U) ui.showErrorPanel(UIConsts::ERROR_FEW_IMAGES);
    else {
        // enable "Edit image" button
        ui.toggleMainMenuItem(3U, true);
        // enable "Export art" button
        ui.toggleMainMenuItem(7U, true);
        ui.startAnimation(factory.getAllImages());
    }
}

void pauseAnim(UI &ui) {
    if (!ui.isAnimationStarted()) ui.showErrorPanel(UIConsts::ERROR_NO_ANIMATION);
    else ui.stopAnimation();
}

void exportArt(UI &ui) {
    if (!ui.getDisplayedImage()) ui.showErrorPanel(UIConsts::ERROR_NOT_SHOWN);
    else {
        ui.hide();
        ImageFactory::exportImage(const_cast<Image *>(ui.getDisplayedImage()));
        ui.show();
    }
}

int main() {
    if (!initscr()) {
        std::cout << "Error initialising ncurses." << std::endl;
        return 1;
    }

    ImageFactory factory;
    UI ui;
    ui.draw();

    while (true) {
        switch (ui.keyboardListener()) {
            case RuntimeCodes::ADD_IMAGE: {
                addImage(ui, factory);
                break;
            }
            case RuntimeCodes::SHOW_IMAGE: {
                showImage(ui, factory);
                break;
            }
            case RuntimeCodes::SET_LEVEL: {
                setLevel(ui, factory);
                break;
            }
            case RuntimeCodes::EDIT_IMAGE: {
                editImage(ui, factory);
                break;
            }
            case RuntimeCodes::REMOVE_IMAGE: {
                removeImage(ui, factory);
                break;
            }
            case RuntimeCodes::PLAY_ANIM: {
                playAnim(ui, factory);
                break;
            }
            case RuntimeCodes::PAUSE_ANIM: {
                pauseAnim(ui);
                break;
            }
            case RuntimeCodes::EXPORT_ART: {
                exportArt(ui);
                break;
            }
            case RuntimeCodes::TERMINATE_PROGRAM:
                return 0;
            default: break;
        }
    }
}