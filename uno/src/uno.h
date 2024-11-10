#ifndef UNO_H
#define UNO_H

#include <stddef.h>

#define CARD_ZERO 0
#define CARD_ONE 1
#define CARD_TWO 2
#define CARD_THREE 3
#define CARD_FOUR 4
#define CARD_FIVE 5
#define CARD_SIX 6
#define CARD_SEVEN 7
#define CARD_EIGHT 8
#define CARD_NINE 9
#define CARD_SKIP 10
#define CARD_REVERSE 11
#define CARD_DRAW2 12
#define CARD_WILD 13
#define CARD_DRAW4 14

#define CARD_RED 0
#define CARD_YELLOW 1
#define CARD_GREEN 2
#define CARD_BLUE 3

#define DECK_LENGTH 108

typedef struct {
  int type;
  int color;
} Card;

typedef struct {
  Card **cards;
  size_t len;
  size_t capacity;
} Deck;

typedef struct {
  Deck *p1;
  Deck *p2;
  Deck *p3;
  Deck *p4;
  Deck *draw_pile;
  Deck *discard_pile;
} Uno;

/* DECK */

Deck *uno_deck_create(size_t capacity);
void uno_deck_destroy(Deck *deck);
void uno_deck_add(Deck *deck, Card *card);
void uno_deck_swap(Deck *deck, size_t idx1, size_t idx2);
void uno_deck_shuffle(Deck *deck);
void uno_deck_print(Deck *deck);
Card *uno_deck_take(Deck *deck, size_t idx);
Card *uno_deck_draw(Deck *deck);
Card *uno_deck_peek(Deck *deck);

/* UNO */

Uno *uno_create(size_t num_players);
void uno_initialize(Uno *uno, size_t num_players);
void uno_destroy(Uno *uno);
void uno_print(Uno *uno);
void uno_print_debug(Uno *uno);

void uno_reset(Uno *uno);
void uno_draw(Deck *draw, Deck *store);

#endif
