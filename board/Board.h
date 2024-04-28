#pragma once
#include "../utility/Util.h"

void DrawBoard(SDL_Surface* screen);

void clearKnockDown();
void addKnockDown(int x, int y);
void clearDestination();
void addDestination(int x, int y);
void clearHovered();
void setHovered(int x, int y);
void clearSelected();
void setSelected(int x, int y);
