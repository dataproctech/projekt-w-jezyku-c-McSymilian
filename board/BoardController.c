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
static Pawn pawnToMove = { .row = -1, .column = -1, .isWhite = false, .isKing = false };
typedef struct Cooordinates {
	int row;
	int column;
} Cooordinates;

static Board board;

static int checkForKingTransformation(int column, int row) {
	if (isWhitesTurn && column == 7) {
		return 2;
	}
	if (!isWhitesTurn && column == 0) {
		return -2;
	}
	return isWhitesTurn ? 1 : -1;
}

static bool canNextPlayerMove() {
	int direction = isWhitesTurn ? 1 : -1;
	for (int row = 0; row < getBoardSize(); row++) {
		for (int column = 0; column < getBoardSize(); column++) {
			if (board[column][row] == direction || board[column][row] == 2 * direction) {
				if (column + direction < 8 && column - direction >= 0) {
					if (row + 1 < 8 && board[column + direction][row + 1] == 0) {
						return true;
					}
					if (row - 1 >= 0 && board[column + direction][row - 1] == 0) {
						return true;
					}
				}
				if (column - 1 >= 0 && board[row][column] == direction * 2) {
					if (row + 1 < 8 && board[column - direction][row + 1] == 0) {
						return true;
					}
					if (row - 1 >= 0 && board[column - direction][row - 1] == 0) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

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

static bool findKingsKnockDownInLine(
	int columnStart,
	int rowStart,
	int columnDirection,
	int rowDirection,
	bool drawKnockDown,
	Board pawnsOnBoard
	) 
{
	int currentPlayer = isWhitesTurn ? 1 : -1;
	int nextColumn = columnStart + columnDirection;
	int nextRow = rowStart + rowDirection;
	while (nextColumn < 8 && nextRow < 8 &&
		nextColumn >= 0 && nextRow >= 0 &&
		pawnsOnBoard[nextColumn][nextRow] == 0)
	{
		nextColumn += columnDirection;
		nextRow += rowDirection;
	}
	if (nextColumn + columnDirection < 8 && nextRow + rowDirection < 8 &&
			nextColumn + columnDirection >= 0 && nextRow + rowDirection >= 0 &&
			pawnsOnBoard[nextColumn + columnDirection][nextRow + rowDirection] == 0)
		{
		if (nextColumn < 8 && nextRow < 8 && nextColumn >= 0 && nextRow >= 0 &&
			(pawnsOnBoard[nextColumn][nextRow] == -currentPlayer || pawnsOnBoard[nextColumn][nextRow] == -2 * currentPlayer))
			{
			if (drawKnockDown) addKnockDown(nextColumn + columnDirection, nextRow + rowDirection);
			return true;
		}
	}
	return false;
}

static bool createKingsKnockDowns(int column, int row, Board pawnsOnBoard, bool drawKnockDown) {
	int currentPlayer = isWhitesTurn ? 1 : -1;
	bool knockDownFound = false;
	if (findKingsKnockDownInLine(column, row, 1, 1, drawKnockDown, pawnsOnBoard)) knockDownFound = true;
	if (findKingsKnockDownInLine(column, row, 1, -1, drawKnockDown, pawnsOnBoard)) knockDownFound = true;
	if (findKingsKnockDownInLine(column, row, -1, 1, drawKnockDown, pawnsOnBoard)) knockDownFound = true;
	if (findKingsKnockDownInLine(column, row, -1, -1, drawKnockDown, pawnsOnBoard)) knockDownFound = true;
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
			if (pawnsOnBoard[i][j] == 2 * currentPlayer) {
				currentPawn.column = i;
				currentPawn.row = j;
				currentPawn.isWhite = currentPlayer;
				if (createKingsKnockDowns(i, j, pawnsOnBoard, false)) {
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
		if (selectedPawn.isKing) {
			createKingsKnockDowns(selectedPawn.column, selectedPawn.row, getPawnsOnBoard(), true);
		}
		else {
			createKnockDowns(selectedPawn.column, selectedPawn.row, getPawnsOnBoard(), true);
		}
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
	int column = (x - BOARD_START_X - PADDING) / SQUARE_SIZE;
	if (column >= 0 && column < 8) {
		return column;
	}
	else {
		return -1;
	}
}

static int getRow(int y) {
	int row = (y - BOARD_START_Y - PADDING) / SQUARE_SIZE;
	if ( row >= 0 && row < 8) {
		return row;
	}
	else {
		return -1;
	}
}

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
				board[selectedField.column][selectedField.row] = (isWhitesTurn ? 1 : -1) * (pawnToMove.isKing ? 2 : 1);
				int knockedDownPawnRow = ((selectedField.row - pawnToMove.row) > 0 ? -1 : 1) + selectedField.row;
				int knockedDownPawnColumn = ((selectedField.column - pawnToMove.column) > 0 ? -1 : 1) + selectedField.column;
				board[knockedDownPawnColumn][knockedDownPawnRow] = 0;
				//check for kings
				if (!pawnToMove.isKing) {
					board[selectedField.column][selectedField.row] = checkForKingTransformation(selectedField.column, selectedField.row);
					if (board[selectedField.column][selectedField.row] == 2 || board[selectedField.column][selectedField.row] == -2) {
						pawnToMove.isKing = true;
					}
				}
				upadatePawnsOnBoard(board);
				clearSelected();
				clearKnockDown();
				if (
					pawnToMove.isKing ? 
					!createKingsKnockDowns(selectedField.column, selectedField.row, board, true)
					:
					!createKnockDowns(selectedField.column, selectedField.row, board, true)
					) {
					isWhitesTurn = !isWhitesTurn;
					updateCurrentPlayer();
					isKnockDownPossible = false;
					isPawnSelected = false;
					lookForKnockDowns();
					updateKnockDownPossible(isKnockDownPossible);
					if (!isKnockDownPossible) {
						if (!canNextPlayerMove()) {
							isGameFinished = true;
							isWhitesTurn = !isWhitesTurn;
							updateCurrentPlayer();
						}
					}
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
		//move
		} else {
			if (isDestination(selectedField.column, selectedField.row)) {
				board = MovePawn(&pawnToMove, &selectedField, board);
				//check for kings
				if (!pawnToMove.isKing) {
					board[selectedField.column][selectedField.row] = checkForKingTransformation(selectedField.column, selectedField.row);
				}
				upadatePawnsOnBoard(board);
				clearSelected();
				clearDestination();
				isWhitesTurn = !isWhitesTurn;
				updateCurrentPlayer();
				isPawnSelected = false;
				lookForKnockDowns();
				updateKnockDownPossible(isKnockDownPossible);
				//check if opp has any moves available, if not - game is finished
				if (!isKnockDownPossible) {
					if (!canNextPlayerMove() && arePawnsOnBoard()) {
						isGameFinished = true;
						isWhitesTurn = !isWhitesTurn;
						updateCurrentPlayer();
					}
				}
				
			}
			else {
				clearDestination();
				clearSelected();
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
void setIsGameFinished(bool isFinished) {
	isGameFinished = isFinished;
}

/*
* Returns the winner of the game.
* 0 if the game is not finished.
* 1 if the white player wins.
* -1 if the black player wins.
* 
* @return 1 if the white player wins, 0 if the black player wins, -1 if the game is not finished.
*/
int GetWinner() {	
	return IsGameFinished() ? isWhitesTurn : -1;
}

bool getControllCurrentPlayer() {
	return isWhitesTurn;
}

void setCurrentPlayer(bool currentPlayer) {
	isWhitesTurn = currentPlayer;
}

void setIsKnockDownPossible(bool wasKnockDownPossible) {
	isKnockDownPossible = wasKnockDownPossible;
}

void setIsPawnSelected(bool isSelected) {
	isPawnSelected = isSelected;
}

bool arePawnsOnBoard() {
	for (int i = 0; i < getBoardSize(); i++) {
		for (int j = 0; j < getBoardSize(); j++) {
			if (board[i][j] != 0) {
				return true;
			}
		}
	}
	return false;
}