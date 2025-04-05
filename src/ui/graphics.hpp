#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <cmath>
#include <cstdint>
#include <ctime>

#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

namespace UI {

typedef enum {
    RED_TEXT = 1,
    GREEN_TEXT = 2,
    BLUE_TEXT = 3,
    YELLOW_TEXT = 4
} UIColorId;

typedef enum {
    USER_SELECTION_EXIT,
    USER_SELECTION_,
} UserSelection;


/**
 * @brief ncurses's WINDOW wrapper that given relative size paramethers, helps to keep a consistent UI design
 * 
 */
class DynamicWindow {
  protected:
    WINDOW *window;

    bool bordered;
    float_t relative_height;
    float_t relative_width;
    float_t relative_start_y;
    float_t relative_start_x;

  public:
  /**
   * @brief Construct a new Dynamic Window object
   * 
   * @param relative_height 
   * @param relative_width 
   * @param relative_start_y 
   * @param relative_start_x 
   * @param bordered 
   */
    DynamicWindow(float_t relative_height, float_t relative_width, float_t relative_start_y, float_t relative_start_x,
                  bool bordered);
    ~DynamicWindow();

    void render();
    bool mouse_event_inside(MEVENT mouse_event);
    void set_text(const char *text);
    void set_colored_text(const char *text, UIColorId color_id);
};

/**
 * Puts centered text inside of a window
 */
void put_centered_text(WINDOW *win, const char *text);

/**
 * Puts centered text inside of a window
 * that has a certain color
 */
void put_centered_colored_text(WINDOW *win, const char *text, UIColorId color_id);

/**
 * Returns true if the given coordinates are inside of the given window
 */
bool is_inside_window(WINDOW *win, int32_t x, int32_t y);

/**
 * Returns true if the given coordinates are inside of the given subpad
 * requires the parent's current line
 */
bool is_inside_subpad(WINDOW *subpad, int32_t x, int32_t y, int32_t current_parent_line);

/*
 * Draws ASCII art
 */
void draw_art(WINDOW *win, const char **art, uint16_t art_lines, int32_t start_y, int32_t start_x, UIColorId color_id);

/**
 * Returns a new bordered window with the given paramethers
 */
WINDOW *new_bordered_window(int32_t height, int32_t width, int32_t y, int32_t x);

/**
 * Returns a new bordered subpad with the given paramethers
 */
WINDOW *new_bordered_subpad(WINDOW *parent, int32_t height, int32_t width, int32_t y, int32_t x);

/**
 * Returns a new bordered subpad with the given paramethers
 */
WINDOW *new_colored_bordered_subpad(WINDOW *parent, int32_t height, int32_t width, int32_t y, int32_t x,
                                    UIColorId color_id);

void start_ncurses();
void stop_ncurses();

} // namespace UI

#endif