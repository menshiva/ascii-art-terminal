#include "factory/ImageFactory.hpp"
#include "ui/UI.hpp"

/**
 * @mainpage ASCII art
 *
 * Program for creation ASCII art from images.
 *
 * _Feautures_:\n
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
 * • Image scailing algorithm: https://en.wikipedia.org/wiki/Image_scaling#Nearest-neighbor_interpolation \n
 * • RGB to Grayscale algorithm:
 * https://en.wikipedia.org/wiki/Grayscale#Colorimetric_(perceptual_luminance-preserving)_conversion_to_grayscale \n
 * • Contrast algrotithm:
 * https://en.wikipedia.org/wiki/Contrast_(vision) and
 * https://math.stackexchange.com/questions/906240/algorithms-to-increase-or-decrease-the-contrast-of-an-image \n
 * • Convolution algorithm: https://setosa.io/ev/image-kernels/ \n
 * • JPEG decompression example:
 * https://github.com/LuaDist/libjpeg/blob/master/example.c#L210
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */

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
                ui.hide();
                const bool isImageRead = factory.readImage();
                ui.show();
                if (isImageRead) {
                    // enable "Show image" button
                    ui.toggleMainMenuItem(1u, true);
                    // enable "Remove image" button
                    ui.toggleMainMenuItem(4u, true);
                    if (factory.getAllImages().size() >= 2u)
                        // enable "Play animation" button
                        ui.toggleMainMenuItem(5u, true);
                }
                break;
            }
            case RuntimeCodes::SHOW_IMAGE: {
                if (factory.getAllImages().empty()) ui.showErrorPanel(UIConsts::ERROR_NO_IMAGES);
                else {
                    ui.hide();
                    const Image *pickedImage = factory.chooseImageFromList(ConsoleConsts::PICK_IMAGE_SHOW);
                    ui.show();
                    if (pickedImage) {
                        ui.printAscii(pickedImage);
                        // enable "Edit image" button
                        ui.toggleMainMenuItem(3u, true);
                        // enable "Export art" button
                        ui.toggleMainMenuItem(7u, true);
                    }
                }
                break;
            }
            case RuntimeCodes::SET_LEVEL: {
                ui.hide();
                const bool isLevelChanged = factory.readGrayscaleLevel();
                ui.show();
                if (isLevelChanged && ui.getDisplayedImage()) ui.refreshAscii();
                break;
            }
            case RuntimeCodes::EDIT_IMAGE: {
                if (!ui.getDisplayedImage()) ui.showErrorPanel(UIConsts::ERROR_NOT_SHOWN);
                else {
                    ui.hide();
                    const bool isEffectApplied = factory.applyEffect(const_cast<Image *>(ui.getDisplayedImage()));
                    ui.show();
                    if (isEffectApplied) ui.refreshAscii();
                }
                break;
            }
            case RuntimeCodes::REMOVE_IMAGE: {
                if (factory.getAllImages().empty()) ui.showErrorPanel(UIConsts::ERROR_NO_IMAGES);
                else {
                    ui.hide();
                    Image *pickedImage = factory.chooseImageFromList(ConsoleConsts::PICK_IMAGE_REMOVE);
                    ui.show();
                    if (pickedImage) {
                        if (pickedImage == ui.getDisplayedImage()) {
                            ui.clearAscii();
                            // disable "Edit image" button
                            ui.toggleMainMenuItem(3u, false);
                            // disable "Export art" button
                            ui.toggleMainMenuItem(7u, false);
                        }
                        factory.removeImage(pickedImage);
                        if (factory.getAllImages().empty()) {
                            // disable "Show image" button
                            ui.toggleMainMenuItem(1u, false);
                            // disable "Edit image" button
                            ui.toggleMainMenuItem(3u, false);
                            // disable "Remove image" button
                            ui.toggleMainMenuItem(4u, false);
                            // disable "Export art" button
                            ui.toggleMainMenuItem(7u, false);
                        } else if (factory.getAllImages().size() < 2u)
                            // disable "Play animation" button
                            ui.toggleMainMenuItem(5u, false);
                    }
                }
                break;
            }
            case RuntimeCodes::PLAY_ANIM: {
                if (factory.getAllImages().size() < 2u) ui.showErrorPanel(UIConsts::ERROR_FEW_IMAGES);
                else {
                    // enable "Edit image" button
                    ui.toggleMainMenuItem(3u, true);
                    // enable "Export art" button
                    ui.toggleMainMenuItem(7u, true);
                    ui.startAnimation(factory.getAllImages());
                }
                break;
            }
            case RuntimeCodes::PAUSE_ANIM: {
                if (!ui.isAnimationStarted()) ui.showErrorPanel(UIConsts::ERROR_NO_ANIMATION);
                else ui.stopAnimation();
                break;
            }
            case RuntimeCodes::EXPORT_ART: {
                if (!ui.getDisplayedImage()) ui.showErrorPanel(UIConsts::ERROR_NOT_SHOWN);
                else {
                    ui.hide();
                    ImageFactory::exportImage(const_cast<Image *>(ui.getDisplayedImage()));
                    ui.show();
                }
                break;
            }
            case RuntimeCodes::TERMINATE_PROGRAM:
                return 0;
            default: break;
        }
    }
}