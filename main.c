#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "window.h"

// Function to display a menu

// char ** menu_items declares menu_items as a pointer to a pointer to characters. It can be used to point to an array of pointers to characters. 
// This is useful when you want to dynamically allocate memory for an array of strings, where each string can have a different length.
void display_menu(char **menu_items, int num_items, int highlight) {
    clear();
    for (int i = 0; i < num_items; i++) {
        if (i == highlight) {
            attron(A_REVERSE);
        }
        mvprintw(i + 1, 1, "%s", menu_items[i]);
        attroff(A_REVERSE);
    }
    refresh();
}

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Define menu items
    char *menu_items[] = {
        "1. Option 1",
        "2. Option 2",
        "3. Option 3",
        "4. Exit"
    };

    // get the total size of the array in bytes and divide by the size of the first element to give us the number of elements. 
    // This technique is commonly used in C to calculate the size of arrays, especially when the size is not explicitly specified.
    // It's particularly useful for ensuring that loops iterate over all elements of an array, regardless of its size.
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);
    // choice used in our switch 
    int choice;
    // highlight used to keep track of which menu item is currently selected
    int highlight = 0;

    // Display menu
    while (1) {
        display_menu(menu_items, num_items, highlight);
        // Get user input
        choice = getch();
        switch(choice) {
            case KEY_UP:
                highlight--;
                if (highlight < 0) highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight >= num_items) highlight = num_items - 1;
                break;
            case 10: // Enter key
                if (highlight == num_items - 1) {
                    endwin();
                    return 0;
                }
                // Print a message indicating the user's choice below the menu options
                mvprintw(num_items + 2, 1, "You chose: %s", menu_items[highlight]);
                // ^ mvprintw is used to print formatted output at a specific position on the screen
                // ^ num_items + 2 specifies the row where the message will be printed, 2 lines below the last menu item
                // ^ 1 specifies the column where the message will be printed, starting at the first column
                // ^ "You chose: %s" is the format string that will be printed, %s is a placeholder for a string
                // ^ menu_items[highlight] is the string that will be substituted for %s, representing the selected menu item

                // Check if selected menu item is "Option 1" and call display_window if it is
                if (strcmp(menu_items[highlight], menu_items[0]) == 0) {
                    display_window();
                }
                refresh();
                getch(); // Wait for user to press any key
                break;
        }
    }

    // Clean up
    endwin();
    return 0;
}