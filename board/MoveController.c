#include "MoveController.h"
#include "Board.h"
#include <math.h>

static Pawn selectedPawn = { .row = -1, .column = -1, .isWhite = false, .isKing = false, };
static Pawn pawnToMove = { .row = -1, .column = -1, .isWhite = false, .isKing = false, };


Pawn getSelectedPawn()
{	
	return selectedPawn;
}

void setSelectedPawn(Pawn* pawn, Board board)
{
	selectedPawn.column = pawn->column;
	selectedPawn.row = pawn->row;
	selectedPawn.isKing = pawn->isKing;
	selectedPawn.isWhite = pawn->isWhite;
	
	clearDestination();
	clearKnockDown();

	setSelected(selectedPawn.column, selectedPawn.row);
	if (selectedPawn.isDestination)
		return;
	

	if (selectedPawn.isKing) {
		for (int i = 1; i < 8; i++) {
			int destinationRow = selectedPawn.row + i;
			int destinationColumn = selectedPawn.column + i;

			if (destinationRow > 7 || destinationColumn > 7) 
				break;
			
			if (board[destinationColumn][destinationRow] == 0) 
				addDestination(destinationColumn, destinationRow);
			
			else if (board[destinationColumn][destinationRow] < 0) {
				if (destinationRow + 1 < 8 && destinationColumn + 1 < 8) 
					if (board[destinationColumn + 1][destinationRow + 1] == 0) 
						addKnockDown(destinationColumn + 1, destinationRow + 1);
				break;
			}
			else 
				break;			
		}
		for (int i = 1; i < 8; i++) {
			int destinationRow = selectedPawn.row - i;
			int destinationColumn = selectedPawn.column + i;

			if (destinationRow < 0 || destinationColumn > 7) 
				break;
			
			if (board[destinationColumn][destinationRow] == 0) 
				addDestination(destinationColumn, destinationRow);
			
			else if (board[destinationColumn][destinationRow] < 0) {
				if (destinationRow - 1 >= 0 && destinationColumn + 1 < 8) 
					if (board[destinationColumn + 1][destinationRow - 1] == 0) 
						addKnockDown(destinationColumn + 1, destinationRow - 1);									
				break;
			}
			else 
				break;			
		}

		for (int i = 1; i < 8; i++) {
			int destinationRow = selectedPawn.row + i;
			int destinationColumn = selectedPawn.column - i;

			if (destinationRow > 7 || destinationColumn < 0) 
				break;
			
			if (board[destinationColumn][destinationRow] == 0) 
				addDestination(destinationColumn, destinationRow);
			
			else if (board[destinationColumn][destinationRow] < 0) {
				if (destinationRow + 1 < 8 && destinationColumn - 1 >= 0) 
					if (board[destinationColumn - 1][destinationRow + 1] == 0) 
						addKnockDown(destinationColumn - 1, destinationRow + 1);	
				break;
			}
			else 
				break;
		}

		for (int i = 1; i < 8; i++) {
			int destinationRow = selectedPawn.row - i;
			int destinationColumn = selectedPawn.column - i;

			if (destinationRow < 0 || destinationColumn < 0) 
				break;
			
			if (board[destinationColumn][destinationRow] == 0) 
				addDestination(destinationColumn, destinationRow);
			
			else if (board[destinationColumn][destinationRow] < 0) {
				if (destinationRow - 1 >= 0 && destinationColumn - 1 >= 0)
					if (board[destinationColumn - 1][destinationRow - 1] == 0)
						addKnockDown(destinationColumn - 1, destinationRow - 1);
				break;
			}
			else 
				break;
		}
	}
	else {
		int destinationRow;
		int destinationColumn;
		int direction = selectedPawn.isWhite ? 1 : -1;

		if (selectedPawn.row != 7) {
			destinationRow = selectedPawn.row + 1;
			destinationColumn = selectedPawn.column + direction;

			if (board[destinationColumn][destinationRow] == 0) 
				addDestination(destinationColumn, destinationRow);
				
			else if (board[destinationColumn][destinationRow] < 0) {
				if (
					(
						selectedPawn.isWhite && destinationColumn != 7  ||
						!selectedPawn.isWhite && destinationColumn != 0
					)
					&& destinationRow != 7
				)
					if (board[destinationColumn + direction][destinationRow + 1] == 0) 
						addKnockDown(destinationColumn + direction, destinationRow + 1);
						
			}
		}

		if (selectedPawn.row != 0) {
			destinationRow = selectedPawn.row - 1;
			destinationColumn = selectedPawn.column + direction;

			if (board[destinationColumn][destinationRow] == 0) 
				addDestination(destinationColumn, destinationRow);
				
			else if (board[destinationColumn][destinationRow] < 0) {
				if (
					(
						selectedPawn.isWhite && destinationColumn != 7 ||
						!selectedPawn.isWhite && destinationColumn != 0
					)
					&& destinationRow != 0
				)
					if (board[destinationColumn + direction][destinationRow - 1] == 0) 
						addKnockDown(destinationColumn + direction, destinationRow - 1);
						
					
			}
		}
		
	}	
}

static bool isKockDown(Pawn from, Pawn to, Board board)
{
	if (from.isKing) {
		
		//todo

		return false;
	}
	else {
		int heightDiff = to.row - from.row;
		if (from.isWhite) 
			return to.column == from.column + 2 && abs(heightDiff) == 2 && board[from.column + 1][from.row + heightDiff] < 0;
		
		else
			return to.column == from.column - 2 && abs(heightDiff) == 2 && board[from.column - 1][from.row + heightDiff] > 0;
	}
}

static Pawn getPawn(int x, int y, Board board)
{
	if (x < 0 || x >= getBoardSize() || y < 0 || y >= getBoardSize() || board[x][y] == 0)
		return *defaultPawn();

	Pawn pawn = { .row = y, .column = x, .isWhite = board[x][y] > 0, .isKing = abs(board[x][y]) == 2 };
	return pawn;
}

bool hasKnockDown(Pawn pawn, Board board) {
		if (pawn.isKing) {
		//todo
		return false;
	}
	else {
		if (pawn.isWhite) {
			if (pawn.column + 2 < 8 && pawn.row + 2 < 8) {
				if (board[pawn.column + 1][pawn.row + 1] < 0 && board[pawn.column + 2][pawn.row + 2] == 0) {
					return true;
				}
			}
			if (pawn.column - 2 >= 0 && pawn.row + 2 < 8) {
				if (board[pawn.column - 1][pawn.row + 1] < 0 && board[pawn.column - 2][pawn.row + 2] == 0) {
					return true;
				}
			}
		}
		else {
			if (pawn.column + 2 < 8 && pawn.row - 2 >= 0) {
				if (board[pawn.column + 1][pawn.row - 1] > 0 && board[pawn.column + 2][pawn.row - 2] == 0) {
					return true;
				}
			}
			if (pawn.column - 2 >= 0 && pawn.row - 2 >= 0) {
				if (board[pawn.column - 1][pawn.row - 1] > 0 && board[pawn.column - 2][pawn.row - 2] == 0) {
					return true;
				}
			}
		}
	}
	return false;
}


void EndMove()
{
	selectedPawn = *defaultPawn();
	clearDestination();
	clearKnockDown();
}


static bool kockDownExists(Board board, bool whiteTurn)
{
	for (int i = 0; i < getBoardSize(); i++) {
		for (int j = 0; j < getBoardSize(); j++) {
			Pawn pawn = getPawn(i, j, board);
			if (board[i][j] != 0 && hasKnockDown(pawn, board)) 
				return true;
		}
	}
	return false;
}

/*
* @param destination - the destination of the move
* @param board - the current state of the board
* 
* @return -1 if the move is invalid, 0 if the move is valid, 1 if the move is valid and the pawn is knocked down
*/
int parseMove(Pawn destination, Board board)
{
	if (!destination.isDestination)
		return -1;

	if (isKockDown(selectedPawn, destination, board))
		return 1;

	if (kockDownExists(board, selectedPawn.isWhite))
		return -1;

	return 0;
	
}

Board MovePawn(Pawn* pawn, Pawn* destination, Board board) {

	int color = pawn->isWhite ? 1 : -1;
	board[destination->column][destination->row] = color * (pawn->isKing ? 2 : 1);

	int directionX = destination->column > pawn->column ? 1 : -1;
	int directionY = destination->row > pawn->row ? 1 : -1;

	for (int i = pawn->column, j = pawn->row; i != destination->column; i += directionX, j += directionY)
		board[i][j] = 0;
	
	return board;
}


Pawn* defaultPawn() {
	return &((Pawn) { .row = -1, .column = -1, .isWhite = false, .isKing = false, .isDestination = false });
}
