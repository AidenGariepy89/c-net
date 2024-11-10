#ifndef GAME_H
#define GAME_H


#include "uno.h"


#define GAME_STOP     0
#define GAME_CONTINUE 1


typedef struct {
    Uno uno;

    size_t num_players;

    
} GameState;


GameState *game_setup(size_t num_players);
int game_loop(GameState *gs);
void game_quit(GameState *gs);






#endif
