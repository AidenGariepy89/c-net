#include <ncurses.h>

#include "uno.h"

int main(void) {

    // initscr();
    // raw();
    // noecho();
    //
    // printw("Hello world!!!");
    // refresh();
    //
    // int ch;
    //
    // while ((ch = getch()) != 'q') {
    //     mvprintw(2, 2, "%i / %i", LINES, COLS);
    // }
    //
    // endwin();

    Uno *uno = uno_create(2);
    uno_reset(uno);

    uno_deck_print(uno->draw_pile);

    uno_destroy(uno);

    return 0;
}
