#ifndef MAIN_MENU_CPP
#define MAIN_MENU_CPP

#include "ui/main_menu.hpp"
#include "ui/graphics.hpp"
#include <cstdint>
#include <cstring>
#include <ncurses.h>

namespace UI {
MainMenu::MainMenu(int32_t height, int32_t width) : BasicWindow(height, width, true) {
    const int32_t button_width = width / 5;
    const int32_t button_height = height / 6;

    this->exit_button = new_bordered_window(button_height, button_width, height / 2, width / 2 - button_width / 2);
    put_centered_colored_text(this->exit_button, "EXIT", RED_TEXT);

    wrefresh(this->exit_button);

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
    delwin(this->exit_button);
}

UserSelection MainMenu::wait_for_user_selection() {
    wgetch(this->window);
    return USER_SELECTION_EXIT;
}

} // namespace UI

#endif