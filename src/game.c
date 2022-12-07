#include <stdio.h>
#include <stdlib.h>
#include "game.h"


PGame new_game(Cell owner) {
    PGame game = (PGame) malloc(sizeof(Game));

    // Initialisation du tableau
    board_create(game->board);

    // Valeur par défaut pour le reste
    game->start = time(NULL);
    game->owner = owner;
    game->playing = CELL_BLACK;
    game->has_last_move = 0;
    game->last_move = MOVE_NONE;
    game->refresh = NULL;
    game->refresh_opponent = NULL;

    return game;
}

void game_turn(PGame game, Move move) {
    // Appliquer le movement
    if (move_apply(move, game->playing, game->board, 1) == 0) {
        // Move invalide !
        printf("Move invalide !\n");
        exit(1);
    }

    // Actualiser le joueur
    game->playing = cell_opposite(game->playing);
    game->has_last_move = 1;
    game->last_move = move;

    // On emet
    State state = game_state(game);
    if (game->refresh != NULL) {
        game->refresh(game, game->owner, state);
    }
    if (game->refresh_opponent != NULL) {
        game->refresh_opponent(game, cell_opposite(game->owner), state);
    }
}

void game_start(PGame game) {
    if (game->refresh != NULL) {
        game->refresh(game, game->owner, In_progress);
    }
    if (game->refresh_opponent != NULL) {
        game->refresh_opponent(game, cell_opposite(game->owner), In_progress);
    }
}

//Renvoi l'état de la partie
State game_state(PGame game){
    // Check for time first (timeout after 15 minutes)
    time_t now = time(NULL);
    if (difftime(now, game->start) > 15*60) {
        return Out_of_time;
    }

    // Count the number of pawns
    int pawn_black = 0;
    int pawn_white = 0;
    for(int i = 0; i<BOARD_SIZE; i++){
        //Compte le nombre de pions dans la partie
        for(int j = 0; j<BOARD_SIZE; j++){
            if(board_get_cell(game->board, i, j) == CELL_BLACK) pawn_black += 1;
            if(board_get_cell(game->board, i, j) == CELL_WHITE) pawn_white += 1;
        }
    }
    if(pawn_black < PAWN_TOT) return Win_white;
    if(pawn_white < PAWN_TOT) return Win_black;

    return In_progress;
}
