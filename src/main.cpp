#include "ui/UI.hpp"
#include "factory/ImageFactory.hpp"

void addImage(UI &ui, ImageFactory &factory) {
    UI::hide();
    bool isImageRead = factory.readImage();
    UI::show();
    if (isImageRead) {
        ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_SHOW_IMAGE, true);
        ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_REMOVE_IMAGE, true);
        if (factory.getAllImages().size() >= 2)
            ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_PLAY_ANIM, true);
    }
}

void showImage(UI &ui, ImageFactory &factory) {
    if (factory.getAllImages().empty()) ui.showErrorPanel(UIConsts::ERROR_NO_IMAGES);
    else {
        UI::hide();
        Image *pickedImage = factory.chooseImageFromList(ConsoleConsts::PICK_IMAGE_SHOW);
        UI::show();
        if (pickedImage) {
            ui.printAscii(pickedImage);
            ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_EDIT_IMAGE, true);
            ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_EXPORT_ASCII, true);
        }
    }
}

void setLevel(UI &ui, ImageFactory &factory) {
    UI::hide();
    bool isLevelChanged = factory.readGrayscaleLevel();
    UI::show();
    if (isLevelChanged && ui.getDisplayedImage()) ui.refreshAscii();
}

void editImage(UI &ui, ImageFactory &factory) {
    if (!ui.getDisplayedImage()) ui.showErrorPanel(UIConsts::ERROR_NOT_SHOWN);
    else {
        UI::hide();
        bool isEffectApplied = factory.applyEffect(const_cast<Image *>(ui.getDisplayedImage()));
        UI::show();
        if (isEffectApplied) ui.refreshAscii();
    }
}

void removeImage(UI &ui, ImageFactory &factory) {
    if (factory.getAllImages().empty()) ui.showErrorPanel(UIConsts::ERROR_NO_IMAGES);
    else {
        UI::hide();
        Image *pickedImage = factory.chooseImageFromList(ConsoleConsts::PICK_IMAGE_REMOVE);
        UI::show();
        if (pickedImage) {
            if (pickedImage == ui.getDisplayedImage()) {
                ui.clearAscii();
                ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_EDIT_IMAGE, false);
                ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_EXPORT_ASCII, false);
            }
            factory.removeImage(pickedImage);
            if (factory.getAllImages().empty()) {
                ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_SHOW_IMAGE, false);
                ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_EDIT_IMAGE, false);
                ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_REMOVE_IMAGE, false);
                ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_EXPORT_ASCII, false);
            } else if (factory.getAllImages().size() < 2)
                ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_PLAY_ANIM, false);
        }
    }
}

void playAnim(UI &ui, ImageFactory &factory) {
    if (factory.getAllImages().size() < 2) ui.showErrorPanel(UIConsts::ERROR_FEW_IMAGES);
    else {
        ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_EDIT_IMAGE, true);
        ui.toggleMainMenuItem(UIConsts::ViewIndex::BTN_EXPORT_ASCII, true);
        ui.startAnimation(factory.getAllImages());
    }
}

void stopAnim(UI &ui) {
    if (!ui.isAnimationStarted()) ui.showErrorPanel(UIConsts::ERROR_NO_ANIMATION);
    else ui.stopAnimation();
}

void exportArt(UI &ui) {
    if (!ui.getDisplayedImage()) ui.showErrorPanel(UIConsts::ERROR_NOT_SHOWN);
    else {
        UI::hide();
        ImageFactory::exportImage(const_cast<Image *>(ui.getDisplayedImage()));
        UI::show();
    }
}

int main() {
    if (!UI::init()) {
        std::cout << ConsoleConsts::ERROR_FAILED_NCURSES << std::endl;
        return 1;
    }

    ImageFactory factory;
    UI ui;
    ui.setOnAddImageCallback([&factory](UI &ui) -> void { addImage(ui, factory); });
    ui.setOnShowImageCallback([&factory](UI &ui) -> void { showImage(ui, factory); });
    ui.setOnSetLevelCallback([&factory](UI &ui) -> void { setLevel(ui, factory); });
    ui.setOnEditImageCallback([&factory](UI &ui) -> void { editImage(ui, factory); });
    ui.setOnRemoveImageCallback([&factory](UI &ui) -> void { removeImage(ui, factory); });
    ui.setOnPlayAnimCallback([&factory](UI &ui) -> void { playAnim(ui, factory); });
    ui.setOnStopAnimCallback([](UI &ui) -> void { stopAnim(ui); });
    ui.setOnExportArtCallback([](UI &ui) -> void { exportArt(ui); });

    ui.draw();
    ui.callUpdates();
    return 0;
}