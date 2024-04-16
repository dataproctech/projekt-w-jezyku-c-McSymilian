#pragma once
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"

void DrawString(SDL_Surface* screen, int x, int y, const char* text,
	SDL_Surface* charset);
