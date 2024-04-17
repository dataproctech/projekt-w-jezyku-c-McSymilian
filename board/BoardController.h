#pragma once
#include "Board.h"
#include "Pawns.h"

void* DrawBoardAndPawns(SDL_Surface* screen);

void ConsumeUserInput(int pointX, int pointY);

bool IsGameFinished();

int GetWinner();
