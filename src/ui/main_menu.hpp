#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "ui/graphics.hpp"
#include <cstdint>
#include <ncurses.h>

namespace UI {

class MainMenu : BasicWindow {
  private:
    DynamicWindow *exit_button;

  public:
    MainMenu(int32_t height, int32_t width);
    ~MainMenu();

    UserSelection wait_for_user_selection();
};

} // namespace UI

#endif