#ifndef GRAPHICS_CPP
#define GRAPHICS_CPP

#include "ui/graphics.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <ncurses.h>
#include <string.h>

namespace UI {

BasicWindow::BasicWindow(int32_t height, int32_t width, bool bordered) {
    if (bordered) {
        this->window = new_bordered_window(height, width, 0, 0);
    } else {
        this->window = newwin(height, width, 0, 0);
        refresh();
    }
    this->bordered = bordered;
}

BasicWindow::~BasicWindow() {
    delwin(this->window);
}

void BasicWindow::resize_window(int32_t new_height, int32_t new_width) {
    wresize(this->window, new_height, new_width);

    if(bordered) {
        box(this->window, 0, 0);
    }
}

void put_centered_text(WINDOW *win, const char *text) {
    mvwprintw(win, getmaxy(win) / 2, (getmaxx(win) - strlen(text)) / 2, "%s", text);
}

void put_centered_colored_text(WINDOW *win, const char *text, UIColorId color_id) {
    wattron(win, COLOR_PAIR(color_id));
    put_centered_text(win, text);
    wattroff(win, COLOR_PAIR(color_id));
}

bool is_inside_window(WINDOW *win, int32_t x, int32_t y) {
    return (getbegx(win) <= x && (getbegx(win) + getmaxx(win)) >= x) &&
           (getbegy(win) <= y && (getbegy(win) + getmaxy(win)) >= y);
}

bool is_inside_subpad(WINDOW *subpad, int32_t x, int32_t y, int32_t current_parent_line) {
    return (getparx(subpad) <= x && (getparx(subpad) + getmaxx(subpad)) >= x) &&
           ((getpary(subpad) - current_parent_line) <= y &&
            (getpary(subpad) + getmaxy(subpad) - current_parent_line) >= y);
}

void draw_art(WINDOW *win, const char **art, uint16_t art_lines, int32_t start_y, int32_t start_x, UIColorId color_id) {
    int32_t max_y, max_x;
    getmaxyx(win, max_y, max_x);

    wattron(win, COLOR_PAIR(color_id));
    for (int32_t i = 0; i < art_lines; i++) {
        int32_t y_pos = start_y + i;
        int32_t x_pos = start_x;
        if (y_pos >= 0 && y_pos < max_y && x_pos >= 0) {
            mvwaddstr(win, y_pos, x_pos, art[i]);
        }
    }
    wattroff(win, COLOR_PAIR(color_id));
    wrefresh(win);
}

WINDOW *new_bordered_window(int32_t height, int32_t width, int32_t y, int32_t x) {
    WINDOW *window = newwin(height, width, y, x);
    refresh();
    box(window, 0, 0);
    wrefresh(window);
    return window;
}
WINDOW *new_bordered_subpad(WINDOW *parent, int32_t height, int32_t width, int32_t y, int32_t x) {
    WINDOW *window = subpad(parent, height, width, y, x);
    refresh();
    box(window, 0, 0);
    wrefresh(window);
    return window;
}

WINDOW *new_colored_bordered_subpad(WINDOW *parent, int32_t height, int32_t width, int32_t y, int32_t x,
                                    UIColorId color_id) {
    WINDOW *window = subpad(parent, height, width, y, x);
    refresh();
    wattron(window, COLOR_PAIR(color_id));
    box(window, 0, 0);
    wattroff(window, COLOR_PAIR(color_id));
    wrefresh(window);
    return window;
}

void start_ncurses() {
    initscr();
    start_color();

    init_pair(UI::RED_TEXT, COLOR_RED, COLOR_BLACK);
    init_pair(UI::GREEN_TEXT, COLOR_GREEN, COLOR_BLACK);
    init_pair(UI::BLUE_TEXT, COLOR_BLUE, COLOR_BLACK);
    init_pair(UI::YELLOW_TEXT, COLOR_YELLOW, COLOR_BLACK);

    mousemask(ALL_MOUSE_EVENTS, NULL); // Mouse events

    noecho(); // No keys on the screen
    curs_set(0);
}

void stop_ncurses() {
    erase();
    endwin();
}

} // namespace UI

#endif