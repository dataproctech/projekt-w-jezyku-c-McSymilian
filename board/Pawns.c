#include "Pawns.h"

#define WHITE 0xFFFFFF
#define WHITE_BORDER 0x6F8F7B

#define BLACK 0x111111
#define BLACK_BORDER 0x333333

#define QUEEN_WHITE 0xFFFFFF
#define QUEEN_WHITE_BORDER 0x6F8F7B

#define QUEEN_BLACK 0x111111
#define QUEEN_BLACK_BORDER 0x333333

void DrawPawns(SDL_Surface* screen, Board pawnsOnBoard) {
	for (int i = 0; i < getBoardSize(); i++) {
		for (int j = 0; j < getBoardSize(); j++) {
				int pawn = pawnsOnBoard[i][j];
				if (pawn != 0) {
					Uint32 pawnColor;
					Uint32 pawnBorderColor;
					int radius = 10;
					switch (pawn) {
					case 1:
						 pawnColor = WHITE;
						 pawnBorderColor = WHITE_BORDER;
						 break;
					case 2:
						pawnColor = QUEEN_WHITE;
						pawnBorderColor = QUEEN_WHITE_BORDER;
						radius = 15;
						break;
					case -2:
						pawnColor = QUEEN_BLACK;
						pawnBorderColor = QUEEN_BLACK_BORDER;
						radius = 15;
						break;
					case -1:
						 pawnColor = BLACK;
						 pawnBorderColor = BLACK_BORDER;
						 break;
					}
					
					DrawCircle(
						screen,
						BOARD_START_X + PADDING + i * SQUARE_SIZE + SQUARE_SIZE / 2,
						BOARD_START_Y + PADDING + j * SQUARE_SIZE + SQUARE_SIZE / 2,
						SQUARE_SIZE / 2,
						radius,
						pawnColor,
						pawnBorderColor
					);
				}				
			
		}
	}
}