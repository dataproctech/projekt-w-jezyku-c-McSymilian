#pragma once
#include "Board.h"
#include "Pawns.h"

void* DrawBoardAndPawns(SDL_Surface* screen);

void BoardClick(int x, int y);

bool IsGameFinished();

int GetWinner();


