// window.c

#include "window.h"

void display_window() {
    // Create a new window
    WINDOW *win;
    int height = 10, width = 40;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "This is a new window");
    wrefresh(win);

    // Wait for user input to exit the window
    getch();

    // Clean up the window
    delwin(win);
}
