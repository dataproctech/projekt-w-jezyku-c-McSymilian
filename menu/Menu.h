#pragma once 
#include "../utility/Util.h"
#include "../window/WindowParameters.h"
#include<stdio.h>

#define BUTTON_HEIGHT 70
#define BUTTON_WIDTH 300
#define BUTTON_SPACE_BETWEEN 35

void DrawMenu(SDL_Surface* screen, SDL_Surface* charset);
void DrawMenuButtons(SDL_Surface* screen, SDL_Surface* charset);
int MenuClick(int x, int y);