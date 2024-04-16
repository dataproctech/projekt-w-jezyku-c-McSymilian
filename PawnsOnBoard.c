#include "PawnsOnBoard.h"

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

void init(int** pawnsOnBoard) {
	pawnsOnBoard = (int**)malloc(BOARD_SIZE * sizeof(int*));

	for (int i = 0; i < BOARD_SIZE; i++) {
		pawnsOnBoard[i] = (int*)malloc(BOARD_SIZE * sizeof(int));
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (i == 0 || i == 1) {
				pawnsOnBoard[i][j] = 1;
			}
			else if (i == BOARD_SIZE - 1 || i == BOARD_SIZE - 2) {
				pawnsOnBoard[i + 6][j] = -1;
			}
			else {
				pawnsOnBoard[i][j] = 0;
			}
		}
	}
}


int** copy(int** pawnsOnBoard) {
	int** copy = (int**)malloc(BOARD_SIZE * sizeof(int*)); 

	for (int i = 0; i < BOARD_SIZE; i++) {
		copy[i] = (int*)malloc(BOARD_SIZE * sizeof(int));
		for (int j = 0; j < BOARD_SIZE; j++) {
			copy[i][j] = pawnsOnBoard[i][j];
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
int** getPawnsOnBoard() {
	if (pawnsOnBoard == 0) {
		init(pawnsOnBoard);

	}

	return copy(pawnsOnBoard);
}

/*
* Copy values from updatedPawnsOnBoard to pawnsOnBoard
* 
* @param pawnsOnBoard - 2D array of pawns on board with size 8x8
*/
void upadatePawnsOnBoard(int** updatedPawnsOnBoard) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			pawnsOnBoard[i][j] = updatedPawnsOnBoard[i][j];
		}
	}
}