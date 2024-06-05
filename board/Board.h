#pragma once
#include "../SDL2-2.0.10/include/SDL_surface.h"
#include <stdbool.h>

void DrawBoard(SDL_Surface* screen);

void clearKnockDown();
void addKnockDown(int x, int y);
void clearDestination();
void addDestination(int x, int y);
void clearHovered();
void setHovered(int x, int y);
void clearSelected();
void setSelected(int x, int y);
bool isKnockDown(int x, int y);
bool isDestination(int x, int y);

typedef struct Coordinates_s Coordinates;



