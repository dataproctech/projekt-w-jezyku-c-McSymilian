#pragma once
#include <stdbool.h>
typedef int** Board;

struct GameState_s {
	Board pawnsOnBoard;
	bool currentPlayer;
};

typedef struct GameState_s GameState;

int getBoardSize();

Board getPawnsOnBoard();

void upadatePawnsOnBoard(Board updatedPawnsOnBoard);

void resetPawns();