#include "BoardController.h"
#include "Board.h"
#include "Pawns.h"

bool isGameFinished = false;

/*
 White player is 1, black player is -1.
White player starts the game.
TODO: Implement read write from file
*/
bool currentPlayer = 1;
void DrawBoardAndPawns(SDL_Surface* screen) {
	DrawBoard(screen);
	DrawPawns(screen, getPawnsOnBoard());
}

static int getColumn(int x) {
	if (x < BOARD_START_X - PADDING || x > BOARD_DRAW_SIZE + PADDING) {
		return -1;
	}
	return (x - BOARD_START_X - PADDING) / SQUARE_SIZE;
}

static int getRow(int y) {
	if (y < BOARD_START_Y - PADDING || y > BOARD_DRAW_SIZE + PADDING) {
		return -1;
	}

	return (y - BOARD_START_Y - PADDING) / SQUARE_SIZE;
}

typedef struct Pawn {
	int row;
	int column;
} Pawn;

/*
* BoardClick - board click event handling
*
* @param x - mouse x coordinate of the click
* @param y - mouse y coordinate of the click
*
*
*/

static Board board;
void BoardClick(int x, int y) {
	if (IsGameFinished()) 
		return;
	if (board == NULL) 
		board = getPawnsOnBoard();
	
	Pawn selectedPawn = (Pawn){ .row = getRow(y), .column = getColumn(x) };

	if (selectedPawn.row == -1 || selectedPawn.column == -1) 
		return;
	
	int a = board[selectedPawn.column][selectedPawn.row];
	a = a;
	if (currentPlayer == 1 && a > 0) {
		setSelected(selectedPawn.column, selectedPawn.row);
	}
	else if (currentPlayer == -1 && getPawnsOnBoard()[selectedPawn.row][selectedPawn.column] < 0) {
	}
	else {
		return;
	}
		

}


/*
* Returns true if the game is finished.
* 
* @return true if the game is finished, false otherwise.
*/
bool IsGameFinished() {
	return isGameFinished;
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