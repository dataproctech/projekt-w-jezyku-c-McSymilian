#include "PawnsOnBoard.h"
#include <stdlib.h>
#include <stdbool.h>
#include"../SDL2-2.0.10/include/SDL_mouse.h"

/*
* PLAYER A: 
*	PAWN: 1
*	SUPER_PAWN: 2
* 
* PLAYER B: 
*	PAWN: -1
*	SUPER_PAWN: -2
*/
GameState gameState;
#define BOARD_SIZE 8

int getBoardSize() {
	return BOARD_SIZE;
}

static void init(GameState* gameState) {
	gameState->currentPlayer = true;
	gameState->pawnsOnBoard = (Board)malloc(BOARD_SIZE * sizeof(int*));
	bool addPawn = false;
	for (int i = 0; i < BOARD_SIZE; i++) {
		gameState->pawnsOnBoard[i] = (int*)malloc(BOARD_SIZE * sizeof(int));
		for (int j = 0; j < BOARD_SIZE; j++) {
			if ((i == 0 || i == 1 || i == 2) && addPawn) {
				gameState->pawnsOnBoard[i][j] = 1;
			}
			else if ((i == 5 || i == 6 || i == 7) && addPawn) {
				gameState->pawnsOnBoard[i][j] = -1;
			}
			else {
				gameState->pawnsOnBoard[i][j] = 0;
			}
			addPawn = !addPawn;
		}
		addPawn = !addPawn;
	}
}


static Board copy(Board boardSource) {
	Board copy = (Board)malloc(BOARD_SIZE * sizeof(int*)); 

	for (int i = 0; i < BOARD_SIZE; i++) {
		copy[i] = (int*)malloc(BOARD_SIZE * sizeof(int));
		for (int j = 0; j < BOARD_SIZE; j++) {
			copy[i][j] = boardSource[i][j];
		}
	}

	return copy;
}

void resetPawns() {
	if (gameState.pawnsOnBoard == 0)
		init(&gameState);
	else {
		bool addPawn = false;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if ((i == 0 || i == 1 || i == 2) && addPawn) {
					gameState.pawnsOnBoard[i][j] = 1;
				}
				else if ((i == 5 || i == 6 || i == 7) && addPawn) {
					gameState.pawnsOnBoard[i][j] = -1;
				}
				else {
					gameState.pawnsOnBoard[i][j] = 0;
				}
				addPawn = !addPawn;
			}
			addPawn = !addPawn;
		}
	}
}

/*
* If board is not initialized, it initializes it
* 
* 
* @return 2D copy array of pawns on board with size 8x8
* 
*/
Board getPawnsOnBoard() {
	if (gameState.pawnsOnBoard == 0)
		init(&gameState);
	

	return copy(gameState.pawnsOnBoard);
}

bool getCurrentPlayer() {
	return gameState.currentPlayer;
}

/*
* Copy values from updatedPawnsOnBoard to pawnsOnBoard
* 
* @param pawnsOnBoard - 2D array of pawns on board with size 8x8
*/
void upadatePawnsOnBoard(Board updatedPawnsOnBoard) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			gameState.pawnsOnBoard[i][j] = updatedPawnsOnBoard[i][j];
		}
	}
}