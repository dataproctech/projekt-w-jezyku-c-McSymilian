#include "PawnsOnBoard.h"
#include <stdlib.h>
#include <stdbool.h>
/*
* PLAYER A: 
*	PAWN: 1
*	SUPER_PAWN: 2
* 
* PLAYER B: 
*	PAWN: -1
*	SUPER_PAWN: -2
*/
int** pawnsOnBoard;
#define BOARD_SIZE 8

int getBoardSize() {
	return BOARD_SIZE;
}

void init(Board* board) {
	*board = (Board)malloc(BOARD_SIZE * sizeof(int*));
	bool addPawn = false;
	for (int i = 0; i < BOARD_SIZE; i++) {
		(*board)[i] = (int*)malloc(BOARD_SIZE * sizeof(int));
		for (int j = 0; j < BOARD_SIZE; j++) {
			if ((i == 0 || i == 1 || i == 2) && addPawn) {
				(*board)[i][j] = 1;
			}
			else if ((i == 5 || i == 6 || i == 7) && addPawn) {
				(*board)[i][j] = -1;
			}
			else {
				(*board)[i][j] = 0;
			}
			addPawn = addPawn ? false : true;
		}
		addPawn = addPawn ? false : true;
	}
}


Board copy(Board boardSource) {
	Board copy = (Board)malloc(BOARD_SIZE * sizeof(int*)); 

	for (int i = 0; i < BOARD_SIZE; i++) {
		copy[i] = (int*)malloc(BOARD_SIZE * sizeof(int));
		for (int j = 0; j < BOARD_SIZE; j++) {
			copy[i][j] = boardSource[i][j];
		}
	}

	return copy;
}

/*
* If board is not initialized, it initializes it
* 
* 
* @return 2D copy array of pawns on board with size 8x8
* 
*/
Board getPawnsOnBoard() {
	if (pawnsOnBoard == 0) {
		init(&pawnsOnBoard);

	}

	return copy(pawnsOnBoard);
}

/*
* Copy values from updatedPawnsOnBoard to pawnsOnBoard
* 
* @param pawnsOnBoard - 2D array of pawns on board with size 8x8
*/
void upadatePawnsOnBoard(Board updatedPawnsOnBoard) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			pawnsOnBoard[i][j] = updatedPawnsOnBoard[i][j];
		}
	}
}