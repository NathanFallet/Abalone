#ifndef GAME_H_
#define GAME_H_

/* existing libraries */
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "move.h"
#include "cell.h"
#include "state.h"

typedef struct game_t {
	// Time de début de partie
	time_t start;

	// Plateau : vide, pion noir ou pion blanc
	Cell board[ROWS][COLS];

	// Joueur qui a lancé la partie, et celui qui doit jouer
	Cell owner;
	Cell playing;

	// Dernier coup joué
	int has_last_move;
	Move last_move;

	// Callback pour actualiser les joueurs
	void (*refresh)(struct game_t *game, Cell me, State state);
	void (*refresh_opponent)(struct game_t *game, Cell me, State state);
} Game;
typedef Game* PGame;

PGame new_game(Cell owner);
void game_turn(PGame game, Move move);
void game_start(PGame game);
State game_state(PGame game);

#endif
