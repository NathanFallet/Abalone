#include <assert.h>
#include "ia.test.h"

void test_ia_update() {
	Game *game = game_new(CELL_BLACK, 0);
	ia_update(game, CELL_BLACK, STATE_PLAYING);
	assert(game->playing == CELL_WHITE);
}

void test_ia_update_not_my_turn() {
	Game *game = game_new(CELL_BLACK, 0);
	ia_update(game, CELL_WHITE, STATE_PLAYING);
	assert(game->playing == CELL_BLACK);
}

void test_ia_update_not_playing() {
	Game *game = game_new(CELL_BLACK, 0);
	ia_update(game, CELL_BLACK, STATE_WIN_BLACK);
	assert(game->playing == CELL_BLACK);
}

void test_ia_minimax_victory() {
	Board board;
	board_create(board);
	board_set_cell(board, 1, 0, CELL_BLACK);
	board_set_cell(board, 2, 0, CELL_BLACK);
	board_set_cell(board, 7, 0, CELL_EMPTY);
	board_set_cell(board, 7, 1, CELL_EMPTY);
	assert(ia_minimax(CELL_BLACK, board, 1) == move_from_string("C1:A1"));
	assert(ia_minimax(CELL_BLACK, board, 2) == move_from_string("C1:A1"));
	assert(ia_minimax(CELL_BLACK, board, 3) == move_from_string("C1:A1"));
	assert(ia_minimax(CELL_BLACK, board, 4) == move_from_string("C1:A1"));
}

void test_ia_minimax_avoid_defeat() {
	Board board;
	board_create(board);
	board_set_cell(board, 3, 0, CELL_WHITE);
	board_set_cell(board, 3, 1, CELL_BLACK);
	board_set_cell(board, 3, 2, CELL_BLACK);
	board_set_cell(board, 4, 0, CELL_BLACK);
	board_set_cell(board, 0, 0, CELL_EMPTY);
	board_set_cell(board, 7, 0, CELL_EMPTY);
	board_set_cell(board, 7, 1, CELL_EMPTY);
	board_set_cell(board, 7, 2, CELL_EMPTY);
	assert(ia_minimax(CELL_WHITE, board, 2) == move_from_string("D1:C1"));
	assert(ia_minimax(CELL_WHITE, board, 3) == move_from_string("D1:C1"));
	assert(ia_minimax(CELL_WHITE, board, 4) == move_from_string("D1:C1"));
}

void test_ia() {
	test_ia_update();
	test_ia_update_not_my_turn();
	test_ia_update_not_playing();
	test_ia_minimax_victory();
	test_ia_minimax_avoid_defeat();
}
