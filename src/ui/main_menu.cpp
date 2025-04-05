#ifndef MAIN_MENU_CPP
#define MAIN_MENU_CPP

#include "ui/main_menu.hpp"
#include "ui/graphics.hpp"
#include <cstdint>
#include <cstring>
#include <ncurses.h>

namespace UI {
MainMenu::MainMenu(int32_t height, int32_t width) : DynamicWindow(1.f, 1.f, 0.f, 0.f, true) {

    this->exit_button = new DynamicWindow(1.f / 6, 1.f / 5, 1.f / 2, 1.f / 2 - 1.f / 10, true);
    this->exit_button->set_colored_text("EXIT", RED_TEXT);

    const char *logo[] = {
        R"(   _            _ _  __        _        )", //
        R"(  /_\  ___  ___(_|_) \ \ _   _| | _____ )", //
        R"( //_\\/ __|/ __| | |  \ \ | | | |/ / _ \)", //
        R"(/  _  \__ \ (__| | /\_/ / |_| |   <  __/)", //
        R"(\_/ \_/___/\___|_|_\___/ \__,_|_|\_\___|)", //
    };

    draw_art(this->window, logo, 5, height / 7, (width - strlen(logo[0])) / 2, BLUE_TEXT);
}

MainMenu::~MainMenu() {
    delete this->exit_button;
}

UserSelection MainMenu::wait_for_user_selection() {
    keypad(stdscr, true);

    int32_t c;
    while (true) {
        c = wgetch(stdscr);
        if (c == KEY_MOUSE) {
            MEVENT mouse_event;
            if (getmouse(&mouse_event) == OK) {
                // If the left mouse button has been clicked
                if (mouse_event.bstate & BUTTON1_CLICKED || mouse_event.bstate & BUTTON1_PRESSED) {

                    // Checking if the exit button has been pressed
                    if (this->exit_button->mouse_event_inside(mouse_event)) {
                        return USER_SELECTION_EXIT;
                    }
                }
            }
        } else if (c == KEY_RESIZE) {
            this->render();

            this->exit_button->render();
            this->exit_button->set_colored_text("EXIT", RED_TEXT);

            const char *logo[] = {
                R"(   _            _ _  __        _        )", //
                R"(  /_\  ___  ___(_|_) \ \ _   _| | _____ )", //
                R"( //_\\/ __|/ __| | |  \ \ | | | |/ / _ \)", //
                R"(/  _  \__ \ (__| | /\_/ / |_| |   <  __/)", //
                R"(\_/ \_/___/\___|_|_\___/ \__,_|_|\_\___|)", //
            };

            int32_t height, width;
            getmaxyx(stdscr, height, width);

            draw_art(this->window, logo, 5, height / 7, (width - strlen(logo[0])) / 2, BLUE_TEXT);
        }
    }

    return USER_SELECTION_EXIT;
}

} // namespace UI

#endif