#include "ui/graphics.hpp"
#include "ui/main_menu.hpp"
#include <ncurses.h>

int main(int, char**){
    UI::start_ncurses();

    uint16_t window_width, window_height;
    getmaxyx(stdscr, window_height, window_width);

    UI::MainMenu main_menu = UI::MainMenu(window_height, window_width);
    main_menu.wait_for_user_selection();

    UI::stop_ncurses();
}
