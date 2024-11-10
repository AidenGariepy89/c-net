#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
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

    srand(time(NULL));

    GameState *gs = game_setup(2);
    int loopstate;

    while ((loopstate = game_loop(gs)) != GAME_STOP) {
    }

    game_quit(gs);

    return 0;
}
