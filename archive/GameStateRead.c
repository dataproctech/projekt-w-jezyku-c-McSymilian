#include "GameStateIO.h"
#include "../data_model/PawnsOnBoard.h"

GameState readGameState() {
	extern GameState gameState;
	FILE* file = fopen("gameState.txt", "r");
	if (file == NULL) {
		printf("Error while opening file\n");
		gameState.pawnsOnBoard = NULL;
		gameState.currentPlayer = true;
		gameState.isKnockDownPossible = false;
		fclose(file);
		return gameState;
	}

	gameState.pawnsOnBoard = (Board)malloc(getBoardSize() * sizeof(int*));

	int playerInput;
	fscanf_s(file, "%d\n", &playerInput);
	gameState.currentPlayer = playerInput == 1;
	int knockDownPossibleInput;
	fscanf_s(file, "%d\n", &knockDownPossibleInput);
	gameState.isKnockDownPossible = knockDownPossibleInput == 1;
	for (int i = 0; i < getBoardSize(); i++) {
		gameState.pawnsOnBoard[i] = (int*)malloc(getBoardSize() * sizeof(int));
		for (int j = 0; j < getBoardSize(); j++) 
			fscanf_s(file, "%d", &(gameState.pawnsOnBoard[i][j]));
	}

	fclose(file);

	return gameState;

}