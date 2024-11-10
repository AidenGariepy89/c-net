#include "game.h"
#include "uno.h"

#include <stdlib.h>

GameState *game_setup(size_t num_players) {
    GameState *gs = malloc(sizeof *gs);

    uno_initialize(&gs->uno, num_players);
    uno_reset(&gs->uno);

    gs->num_players = num_players;

    return gs;
}

int game_loop(GameState *gs) {
    uno_print_debug(&gs->uno);

    return GAME_STOP;
}

void game_quit(GameState *gs) {

    uno_destroy(&gs->uno);

    free(gs);
}
