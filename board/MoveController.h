#pragma once
#include <stdbool.h>
#include "../data_model/PawnsOnBoard.h"

struct Pawn {
	int row;
	int column;
	bool isDestination;
	bool isWhite;
	bool isKing;
};

typedef struct Pawn Pawn;

Pawn* defaultPawn();

void setSelectedPawn(Pawn* pawn, Board board);

Pawn getSelectedPawn();

int parseMove(Pawn destination, Board board);

Board MovePawn(Pawn* pawn, Pawn* destination, Board board);

bool hasKnockDown(Pawn pawn, Board board);

void EndMove();
