#pragma once
#include <stdbool.h>
#include "../SDL2-2.0.10/include/SDL_surface.h"

void DrawBoardAndPawns(SDL_Surface* screen);

void BoardClick(int x, int y);

bool IsGameFinished();

int GetWinner();

bool getControllCurrentPlayer();

void setCurrentPlayer(bool currentPlayer);

void setIsKnockDownPossible(bool isKnockDownPossible);

void setIsPawnSelected(bool isPawnSelected);