#pragma once
#include <stdbool.h>
typedef int** Board;

struct GameState_s {
	Board pawnsOnBoard;
	bool currentPlayer;
	bool isKnockDownPossible;
};

typedef struct GameState_s GameState;

int getBoardSize();

Board getPawnsOnBoard();

void upadatePawnsOnBoard(Board updatedPawnsOnBoard);

void resetPawns();

void updateCurrentPlayer();

void updateKnockDownPossible(bool isKnockDownPossible);

bool getIsKnockDownPossible();

bool getCurrentPlayer();