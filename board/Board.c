#include "board.h"

#define DARK   0x261203
#define BRIGHT 0xcfb29d

//1-dark 2-bright
void DrawSquare(int color, int xStart, int yStart, int squareSize, SDL_Surface* screen) {
	if (color == 1) {
		color = DARK;
	}
	else {
		color = BRIGHT;
	}
	DrawRectangle(screen, xStart, yStart, squareSize, squareSize, color, color);
}

void DrawBoard(SDL_Surface* screen) {
	int color = 0;
	int squareSize = 40;
	int boardStartX = 10, boardStartY = 10;
	int padding = 10;
	DrawSquare(2, boardStartX, boardStartY, squareSize * 8 + padding * 2, screen);
	DrawSquare(1, boardStartX + padding - 1, boardStartY + padding - 1, squareSize * 8 + 2, screen);
	for (int x = boardStartX + padding; x < squareSize * 8 + boardStartX; x += squareSize) {
		for (int y = boardStartY + padding; y < squareSize * 8 + boardStartY; y += squareSize) {
			if (color == 0) {
				DrawSquare(color, x, y, squareSize, screen);
			}
			color += 1;
			color %= 2;
		}
		color += 1;
		color %= 2;
	}
}