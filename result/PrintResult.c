#include "PrintResult.h"

void DrawResult(SDL_Surface* screen, SDL_Surface* charset, int winner) {
	int xStart, yStart, resultWidth = 120, resultHeight = 40;
	xStart = SCREEN_WIDTH/2 - resultWidth/2 ;
	yStart = SCREEN_HEIGHT/2 - resultHeight/2;
	DrawRectangle(screen, xStart, yStart, resultWidth, resultHeight, 0x261203, 0xcfb29d);
	const char* result[2] = { "Black wins", "White wins" };
	int labelXStart = xStart + (resultWidth - 10 * 8) / 2;
	int labelYStart = yStart + resultHeight / 2 - 4;
	if (winner) {
		DrawString(screen, labelXStart, labelYStart, result[1], charset);
	}
	else{
		DrawString(screen, labelXStart, labelYStart, result[0], charset);
	}
}