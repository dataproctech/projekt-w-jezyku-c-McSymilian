#include "Board.h"

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
	int padding = 10;
	int boardStartX = (SCREEN_WIDTH - SQUARE_SIZE*8 - padding*2)/2;
	int boardStartY = (SCREEN_HEIGHT - SQUARE_SIZE*8 - padding*2)/2;
	DrawSquare(2, boardStartX, boardStartY, SQUARE_SIZE * 8 + padding * 2, screen);
	DrawSquare(1, boardStartX + padding - 1, boardStartY + padding - 1, SQUARE_SIZE * 8 + 2, screen);

	int color = 0;
	for (int x = boardStartX + padding; x < SQUARE_SIZE * 8 + boardStartX; x += SQUARE_SIZE) {
		for (int y = boardStartY + padding; y < SQUARE_SIZE * 8 + boardStartY; y += SQUARE_SIZE) {
			if (color == 0) {
				DrawSquare(color, x, y, SQUARE_SIZE, screen);
			}
			color += 1;
			color %= 2;
		}
		color += 1;
		color %= 2;
	}
}