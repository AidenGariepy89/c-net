#include "uno.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- CARD --- //

static Card *uno_card_create(int color, int type) {
    Card *card = malloc(sizeof *card);
    card->color = color;
    card->type = type;
    return card;
}

static void uno_card_print(Card *card) {
    char type, color;

    switch (card->color) {
        case CARD_RED:
            color = 'R';
            break;
        case CARD_YELLOW:
            color = 'Y';
            break;
        case CARD_GREEN:
            color = 'G';
            break;
        case CARD_BLUE:
            color = 'B';
            break;
        default:
            color = '?';
            break;
    }

    type = (char)(card->type + '0');
    if (type > '9') {
        color = ' ';
        switch (card->type) {
            case CARD_SKIP:
                type = 'S';
                break;
            case CARD_REVERSE:
                type = 'R';
                break;
            case CARD_DRAW2:
                type = 'D';
                break;
            case CARD_WILD:
                color = ' ';
                type = 'W';
                break;
            case CARD_DRAW4:
                color = 'D';
                type = '4';
                break;
            default:
                type = '?';
                break;
        }
    }

    printf("%c%c", color, type);
}

// --- DECK --- //

Deck *uno_deck_create(size_t capacity) {
    Deck *deck = malloc(sizeof *deck);
    deck->cards = calloc(capacity, sizeof(Card *));
    deck->capacity = capacity;
    deck->len = 0;
    return deck;
}

void uno_deck_destroy(Deck *deck) {
    for (size_t i = 0; i < deck->len; i++) {
        free(deck->cards[i]);
    }
    free(deck);
}

void uno_deck_add(Deck *deck, Card *card) {
    assert(deck->len < deck->capacity);

    deck->cards[deck->len] = card;
    deck->len += 1;
}

void uno_deck_swap(Deck *deck, size_t idx1, size_t idx2) {
    assert(idx1 < deck->len);
    assert(idx2 < deck->len);

    if (idx1 == idx2) {
        return;
    }

    Card *temp = deck->cards[idx1];
    deck->cards[idx1] = deck->cards[idx2];
    deck->cards[idx2] = temp;
}

void uno_deck_shuffle(Deck *deck) {
    size_t i, j;
    i = deck->len - 1;
    while (i > 0) {
        j = rand() % (i + 1);
        uno_deck_swap(deck, i, j);
        i -= 1;
    }
}

void uno_deck_print(Deck *deck) {
    for (size_t i = 0; i < deck->len; i++) {
        if (deck->cards[i] == NULL) {
            printf("(hey this one's null) ");
            continue;
        }

        uno_card_print(deck->cards[i]);
        printf(" ");

        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }

    printf("\n");
}

Card *uno_deck_take(Deck *deck, size_t idx) {
    assert(idx < deck->len);

    Card *removal = deck->cards[idx];
    size_t i;

    for (i = idx + 1; i < deck->len; i++) {
        deck->cards[idx - 1] = deck->cards[idx];
    }

    deck->len -= 1;

    return removal;
}

/**
 * Draws a card off the top of the deck.
 *
 * The caller now owns the Card.
 * Returns NULL if empty.
 */
Card *uno_deck_draw(Deck *deck) {
    if (deck->len == 0) {
        return NULL;
    }

    deck->len -= 1;
    return deck->cards[deck->len];
}

/**
 * Returns a pointer to the top card of the deck.
 *
 * The caller does NOT own the Card.
 * Returns NULL if empty.
 */
Card *uno_deck_peek(Deck *deck) {
    if (deck->len == 0) {
        return NULL;
    }

    return deck->cards[deck->len - 1];
}

// --- UNO --- //

Uno *uno_create(size_t num_players) {
    Uno *uno = malloc(sizeof *uno);

    uno_initialize(uno, num_players);

    return uno;
}

void uno_initialize(Uno *uno, size_t num_players) {
    assert(num_players >= 2);
    assert(num_players <= 4);

    uno->p1           = uno_deck_create(DECK_LENGTH);
    uno->p2           = uno_deck_create(DECK_LENGTH);
    uno->p3           = uno_deck_create(DECK_LENGTH);
    uno->p4           = uno_deck_create(DECK_LENGTH);
    uno->draw_pile    = uno_deck_create(DECK_LENGTH);
    uno->discard_pile = uno_deck_create(DECK_LENGTH);
}

void uno_destroy(Uno *uno) {
    uno_deck_destroy(uno->p1);
    uno_deck_destroy(uno->p2);
    uno_deck_destroy(uno->p3);
    uno_deck_destroy(uno->p4);
    uno_deck_destroy(uno->draw_pile);
    uno_deck_destroy(uno->discard_pile);
}

void uno_print(Uno *uno) {
    printf("Current discard: ");

    Card *card = uno_deck_peek(uno->discard_pile);
    if (card != NULL) {
        uno_card_print(card);
    }

    printf("\n");
}

void uno_print_debug(Uno *uno) {
    printf("Current draw (%zu):\n", uno->draw_pile->len);
    uno_deck_print(uno->draw_pile);

    printf("Current discard (%zu):\n", uno->discard_pile->len);
    uno_deck_print(uno->discard_pile);
}

void uno_reset(Uno *uno) {
    for (int color = CARD_RED; color <= CARD_BLUE; color++) {
        for (int type = CARD_ZERO; type <= CARD_DRAW4; type++) {
            uno_deck_add(uno->draw_pile, uno_card_create(color, type));

            if (type != CARD_ZERO && type != CARD_WILD && type != CARD_DRAW4) {
                uno_deck_add(uno->draw_pile, uno_card_create(color, type));
            }
        }
    }

    uno_deck_shuffle(uno->draw_pile);

    uno_draw(uno->draw_pile, uno->discard_pile);
}

void uno_draw(Deck *draw, Deck *store) {
    uno_deck_add(store, uno_deck_draw(draw));
}
