#include "Board.h"

#define DARK   0x261203
#define BRIGHT 0xcfb29d

void DrawSquare(bool isDark, int xStart, int yStart, int squareSize, SDL_Surface* screen) {
	DrawRectangle(screen, xStart, yStart, squareSize, squareSize, isDark ? DARK : BRIGHT, isDark ? DARK : BRIGHT);
}

void DrawBoard(SDL_Surface* screen) {

	DrawSquare(true, BOARD_START_X, BOARD_START_Y, BOARD_DRAW_SIZE , screen);
	DrawSquare(false, BOARD_START_X + PADDING - 1, BOARD_START_Y + PADDING - 1, SQUARE_SIZE * 8 + 2, screen);

	bool color = false;
	for (int x = BOARD_START_X + PADDING; x < SQUARE_SIZE * 8 + BOARD_START_X; x += SQUARE_SIZE) {
		for (int y = BOARD_START_Y + PADDING; y < SQUARE_SIZE * 8 + BOARD_START_Y; y += SQUARE_SIZE) {
			if (color) {
				DrawSquare(color, x, y, SQUARE_SIZE, screen);
			}
			color = !color;
		
		}
		color = !color;
	}
}