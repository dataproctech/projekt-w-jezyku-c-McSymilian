#pragma once
#include "../SDL2-2.0.10/include/SDL_surface.h"
#include <stdbool.h>
#include "../board/BoardParameters.h"
#include "../utility/Util.h"

void DrawResult(SDL_Surface* screen, SDL_Surface* charset, int winner);