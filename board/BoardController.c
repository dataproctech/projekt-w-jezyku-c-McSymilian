#include "BoardController.h"
#include "MoveController.h"
#include "Board.h"
#include "Pawns.h"
#include <math.h>
#include <stdbool.h>

static bool isGameFinished = false;
/*
 White player is true, black player is false.
White player starts the game.
*/
static bool isWhitesTurn = true;
static bool isPawnSelected = false;
static bool isKnockDownPossible = false;
static bool isMultiKnockDownInProgress = false;
static Pawn pawnToMove = { .row = -1, .column = -1, .isWhite = false, .isKing = false, .isDestination = false };


static void createLineOfKingsDestinations(
	int columnStart,
	int rowStart,
	int columnDirection,
	int rowDirection,
	Board pawnsOnBoard
)
{
	int nextColumn = columnStart + columnDirection;
	int nextRow = rowStart + rowDirection;
	while (nextColumn < 8 && nextRow < 8 &&
		nextColumn >= 0 && nextRow >= 0 &&
		pawnsOnBoard[nextColumn][nextRow] == 0)
	{
		addDestination(nextColumn, nextRow);
		nextColumn += columnDirection;
		nextRow += rowDirection;
	}
}
static void createDestinations(Pawn selectedPawn) {
	Board pawnsOnBoard = getPawnsOnBoard();
	bool isWhitesTurn = selectedPawn.isWhite;
	int column = selectedPawn.column;
	int row = selectedPawn.row;
	int direction = isWhitesTurn ? 1 : -1;
	if (!selectedPawn.isKing) {
		if (column + direction < 8 && column + direction >= 0) {
			if (row + 1 < 8 && pawnsOnBoard[column + direction][row + 1] == 0) {
				addDestination(column + direction, row + 1);
			}
			if (row - 1 >= 0 && pawnsOnBoard[column + direction][row - 1] == 0) {
				addDestination(column + direction, row - 1);
			}
		}
	}
	else {
		createLineOfKingsDestinations(column, row, 1, 1, pawnsOnBoard);
		createLineOfKingsDestinations(column, row, 1, -1, pawnsOnBoard);
		createLineOfKingsDestinations(column, row, -1, 1, pawnsOnBoard);
		createLineOfKingsDestinations(column, row, -1, -1, pawnsOnBoard);
	}
}

static bool createKnockDowns(int column, int row, Board pawnsOnBoard, bool drawKnockDown) {
	int currentPlayer = isWhitesTurn ? 1 : -1;
	bool knockDownFound = false;
	if (column + 2 < 8) {
		if (row + 1 < 8 && (pawnsOnBoard[column + 1][row + 1] == -currentPlayer || pawnsOnBoard[column + 1][row + 1] == - 2 * currentPlayer)) {
			if (pawnsOnBoard[column + 2][row + 2] == 0) {
				if (drawKnockDown) addKnockDown(column + 2, row + 2);
				knockDownFound = true;
			}
		}
		if (row - 1 >= 0 && (pawnsOnBoard[column + 1][row - 1] == -currentPlayer || pawnsOnBoard[column + 1][row - 1] == -2 * currentPlayer)) {
			if (pawnsOnBoard[column + 2][row - 2] == 0) {
				if (drawKnockDown) addKnockDown(column + 2, row - 2);
				knockDownFound = true;
			}
		}
	}
	if (column - 2 >= 0) {
		if (row + 1 < 8 && (pawnsOnBoard[column - 1][row + 1] == -currentPlayer || pawnsOnBoard[column - 1][row + 1] == -2 * currentPlayer)) {
			if (pawnsOnBoard[column - 2][row + 2] == 0) {
				if (drawKnockDown) addKnockDown(column - 2, row + 2);
				knockDownFound = true;
			}
		}
		if (row - 1 >= 0 && (pawnsOnBoard[column - 1][row - 1] == -currentPlayer) || pawnsOnBoard[column - 1][row - 1] == -2 * currentPlayer) {
			if (pawnsOnBoard[column - 2][row - 2] == 0) {
				if (drawKnockDown) addKnockDown(column - 2, row - 2);
				knockDownFound = true;
			}
		}
	}
	return knockDownFound;
}

void lookForKnockDowns() {
	int currentPlayer = isWhitesTurn ? 1 : -1;
	Board pawnsOnBoard = getPawnsOnBoard();
	Pawn currentPawn;
	for (int i = 0; i < getBoardSize(); i++) {
		for (int j = 0; j < getBoardSize(); j++) {
			if (pawnsOnBoard[i][j] == currentPlayer) {
				currentPawn.column = i;
				currentPawn.row = j;
				currentPawn.isWhite = currentPlayer;
				if (createKnockDowns(i, j, pawnsOnBoard, false)) {
					isKnockDownPossible = true;
					return;
				}
			}
		}
	}
}

void handlePawnSelection(Pawn selectedPawn) {
	if (selectedPawn.isWhite != isWhitesTurn) return;
	setSelected(selectedPawn.column, selectedPawn.row);
	if (!isKnockDownPossible) {
		createDestinations(selectedPawn);
	}
	else {
		createKnockDowns(selectedPawn.column, selectedPawn.row, getPawnsOnBoard(), true);
	}
	isPawnSelected = true;
	pawnToMove.row = selectedPawn.row;
	pawnToMove.column = selectedPawn.column;
}

void DrawBoardAndPawns(SDL_Surface* screen) {
	DrawBoard(screen);
	DrawPawns(screen, getPawnsOnBoard());
}
 
static int getColumn(int x) {
	if (x < BOARD_START_X + PADDING || x > BOARD_START_X + BOARD_DRAW_SIZE - PADDING) {
		return -1;
	}
	return (x - BOARD_START_X - PADDING) / SQUARE_SIZE;
}

static int getRow(int y) {
	if (y < BOARD_START_Y + PADDING || y > BOARD_START_Y + BOARD_DRAW_SIZE - PADDING) {
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
	if (!isPawnSelected) {
		if (board[selectedCoords.column][selectedCoords.row] == 0) return;
		handlePawnSelection(selectedField);
		pawnToMove = selectedField;
	}
	else {
		//selected pawn
		if (selectedField.column == pawnToMove.column && selectedField.row == pawnToMove.row) {
			isPawnSelected = false;
			clearSelected();
			clearDestination();
			clearKnockDown();
			return;
		}
		//knockdown
		if (isKnockDownPossible) {
			if (isKnockDown(selectedField.column, selectedField.row)) {
				board[pawnToMove.column][pawnToMove.row] = 0;
				board[selectedField.column][selectedField.row] = isWhitesTurn ? 1 : -1;
				board[(pawnToMove.column + selectedField.column) / 2][(pawnToMove.row + selectedField.row) / 2] = 0;
				upadatePawnsOnBoard(board);
				clearSelected();
				clearKnockDown();
				if (!createKnockDowns(selectedField.column, selectedField.row, board, true)) {
					isWhitesTurn = !isWhitesTurn;
					isKnockDownPossible = false;
					isPawnSelected = false;
					lookForKnockDowns();
				}
				else {
					pawnToMove.column = selectedField.column;
					pawnToMove.row = selectedField.row;
					setSelected(selectedField.column, selectedField.row);
				}
			}
			else {
				clearKnockDown();
				clearSelected();
				isPawnSelected = false;
			}
		} else {
			if (isDestination(selectedField.column, selectedField.row)) {
				board = MovePawn(&pawnToMove, &selectedField, board);
				upadatePawnsOnBoard(board);
				clearSelected();
				clearDestination();
				isWhitesTurn = !isWhitesTurn;
				isPawnSelected = false;
				lookForKnockDowns();
			}
			else {
				clearDestination();
				isPawnSelected = false;
			}
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
	return IsGameFinished() ? isWhitesTurn : -1;
}

bool  getControllCurrentPlayer() {
	return isWhitesTurn;
}

void setCurrentPlayer(bool currentPlayer) {
	isWhitesTurn = currentPlayer;
}