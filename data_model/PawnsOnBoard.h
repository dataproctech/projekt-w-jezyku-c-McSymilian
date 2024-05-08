#pragma once
#include <stdbool.h>
typedef int** Board;

typedef struct {
	Board pawnsOnBoard;
	bool currentPlayer;
} GameState;

int getBoardSize();

Board getPawnsOnBoard();

void upadatePawnsOnBoard(Board updatedPawnsOnBoard);

void resetPawns();