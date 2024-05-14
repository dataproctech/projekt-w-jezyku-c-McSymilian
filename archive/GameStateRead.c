#include "GameStateIO.h"
#include "../data_model/PawnsOnBoard.h"

GameState readGameState() {
	GameState gameState;
	FILE* file = fopen("gameState.txt", "r");
	if (file == NULL) {
		printf("Error while opening file\n");
		gameState.pawnsOnBoard = NULL;
		gameState.currentPlayer = true;
		fclose(file);
		return gameState;
	}

	gameState.pawnsOnBoard = (Board)malloc(getBoardSize() * sizeof(int*));

	fscanf_s(file, "%d\n", &gameState.currentPlayer);
	for (int i = 0; i < getBoardSize(); i++) {
		gameState.pawnsOnBoard[i] = (int*)malloc(getBoardSize() * sizeof(int));
		for (int j = 0; j < getBoardSize(); j++) 
			fscanf_s(file, "%d", &gameState.pawnsOnBoard[i][j]);
	}

	fclose(file);

	return gameState;

}