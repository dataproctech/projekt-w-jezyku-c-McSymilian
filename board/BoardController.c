#include "BoardController.h"
#include "MoveController.h"
#include "Board.h"
#include "Pawns.h"
#include <math.h>
#include <stdbool.h>

bool isGameFinished = false;

/*
 White player is true, black player is false.
White player starts the game.
TODO: Implement read write player from file
*/
bool currentPlayerIndicator = true;
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

typedef struct Cooordinates {
	int row;
	int column;
} Cooordinates;

static Board board;

static Pawn getPawn(Cooordinates coordinates, Board board) {
	int val = board[coordinates.column][coordinates.row];
	return (Pawn) { 
		.row = coordinates.row,
		.column = coordinates.column,
		.isWhite = val > 0,
		.isKing =  abs(val) == 2,
		.isDestination = val == 0
	};
}

/*
* BoardClick - board click event handling
*
* @param x - mouse x coordinate of the click
* @param y - mouse y coordinate of the click
*
*
*/
void BoardClick(int x, int y) {
	if (IsGameFinished()) 
		return;

	if (board == NULL) 
		board = getPawnsOnBoard();
	
	Cooordinates selectedCoords = (Cooordinates){ .row = getRow(y), .column = getColumn(x) };

	if (selectedCoords.row == -1 || selectedCoords.column == -1) 
		return;
	
	Pawn selectedField = getPawn(selectedCoords, board);

	//palyer A
	if (currentPlayerIndicator && selectedField.isWhite && !selectedField.isDestination) {
		setSelectedPawn(&selectedField, board);	
	}
	//Player B
	else if (!currentPlayerIndicator && !selectedField.isWhite && !selectedField.isDestination) {
		setSelectedPawn(&selectedField, board);
	}
	//empty square
	else if (selectedField.isDestination && getSelectedPawn().column != -1) {
		int moveParseResult = parseMove(selectedField, board);
		if (moveParseResult == 0) {
			Pawn pawn = getSelectedPawn();
			board = MovePawn(&pawn, &selectedField, board);
			upadatePawnsOnBoard(board);

			setSelectedPawn(&selectedField, board);
			EndMove();
			currentPlayerIndicator  = !currentPlayerIndicator;
		}
		else if (moveParseResult == 1) {
			//board = MovePawn(getSelectedPawn(), &pawn, board);

			//upadatePawnsOnBoard(board);

			////setSelectedPawn(defaultPawn(), board);
			//if (!hasKnockDown(pawn, board)) {
			//	currentPlayer = -1;
			//	setSelectedPawn(*defaultPawn(), board);
			//}
		}
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
	
	return IsGameFinished() ? currentPlayerIndicator : 0;
}