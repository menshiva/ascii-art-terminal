#include "ui/Screen.hpp"
#include "utils/Consts.hpp"

int main() {
    if (!Screen::init()) {
        puts(ConsoleConsts::ERROR_FAILED_NCURSES);
        return 1;
    }

    const View::Id titlePanelId = 0;
    const View::Id controlsPanelId = 1;
    const View::Id asciiPanelId = 2;
    const View::Id exitPanelId = 3;
    const View::Id mainMenuId = 4;
    const View::Id exitMenuId = 5;

    Screen screen;

    const auto &toggleExitPanel = [&](bool visible) {
        return [&, visible]() -> void {
            screen.getView<Menu>(mainMenuId)->setActive(!visible);
            screen.getView<Menu>(exitMenuId)->setActive(visible);
            screen.getView<Panel>(titlePanelId)->setVisibility(!visible);
            screen.getView<Panel>(controlsPanelId)->setVisibility(!visible);
            screen.getView<Panel>(asciiPanelId)->setVisibility(!visible);
            screen.getView<Panel>(exitPanelId)->setVisibility(visible);
            screen.markDirty();
        };
    };
    const auto &closeApp = [&]() -> void {
        screen.close();
    };

    screen.withChildren({
        {titlePanelId, (new Panel(true))->withChildren({
            (new Text(UIConsts::TITLE_TEXT))->withCenteredInParentHeight()->withCenteredInParentWidth()
        })->withRelativeHeight(UIConsts::TITLE_PANEL_HEIGHT_REL)},
        {controlsPanelId, (new Panel(true))->withChildren({
            {mainMenuId, (new Menu(true))->withChildren({
                new Text(UIConsts::BTN_ADD_IMAGE),
                new Text(UIConsts::BTN_SHOW_IMAGE),
                new Text(UIConsts::BTN_GRAYSCALE_LEVEL),
                new Text(UIConsts::BTN_EDIT_IMAGE),
                new Text(UIConsts::BTN_REMOVE_IMAGE),
                new Text(UIConsts::BTN_PLAY_ANIM),
                new Text(UIConsts::BTN_PAUSE_ANIM),
                new Text(UIConsts::BTN_EXPORT_ASCII),
                new Text(UIConsts::BTN_EXIT)
            })->withCallbacks({
                {'9', toggleExitPanel(true)}
            })->withCenteredInParentHeight()->withCenteredInParentWidth()}
        })->withRelativeWidth(UIConsts::CONTROLS_PANEL_WIDTH_REL)->withAttachedBelow(true, 0)},
        {asciiPanelId, (new Panel(true))->withChildren({
            // TODO
        })->withAttachedBelow(true, 0)->withAttachedRight(true, 1)},
        {exitPanelId, (new Panel(false))->withChildren({
            (new Text(UIConsts::EXIT_PANEL_TEXT))->withAbsoluteY(1)->withAbsoluteX(1),
            (new Space())->withAttachedBelow(false, 0)->withAbsoluteHeight(1)->withAbsoluteWidth(0),
            {exitMenuId, (new Menu(false))->withChildren({
                new Text(UIConsts::EXIT_PANEL_YES),
                new Text(UIConsts::EXIT_PANEL_CANCEL)
            })->withCallbacks({
                {'1', closeApp},
                {'2', toggleExitPanel(false)}
            })->withAttachedBelow(false, 1)->withCenteredInParentWidth()}
        })->withWrapContent()->withCenteredInParentHeight()->withCenteredInParentWidth()}
    });
    screen.mainLoop();
    return 0;
}
