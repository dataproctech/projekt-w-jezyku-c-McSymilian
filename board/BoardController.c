#include "BoardController.h"

bool isGameFinished = false;
bool currentPlayer = 1;
void DrawBoardAndPawns(SDL_Surface* screen) {
	DrawBoard(screen);
	DrawPawns(screen, getPawnsOnBoard());
}

void BoardClick(int x, int y) {

}

int getColumn(int x) {
	if (x <= BOARD_START_X + PADDING || x >= BOARD_DRAW_SIZE - PADDING) {
		return -1;
	}
	return (x - BOARD_START_X + PADDING) / SQUARE_SIZE;
}

int getRow(int y) {
	if (y <= BOARD_START_Y + PADDING || y >= BOARD_DRAW_SIZE - PADDING) {
		return -1;
	}

	return (y - BOARD_START_Y + PADDING) / SQUARE_SIZE;
}


/*
* Returns true if the game is finished.
* 
* @return true if the game is finished, false otherwise.
*/
bool IsGameFinished() {
	return IsGameFinished;
}

/*
* Returns the winner of the game.
* 0 if the game is not finished.
* 1 if the white player wins.
* -1 if the black player wins.
* 
* @return 1 if the white player wins, -1 if the black player wins, 0 if the game is not finished.
*/
int GetWinner() {
	
	return IsGameFinished() ? currentPlayer : 0;
}