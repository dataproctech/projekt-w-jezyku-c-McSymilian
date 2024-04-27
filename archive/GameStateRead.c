#include "GameStateIO.h"
#include "../data_model/PawnsOnBoard.h"

Board readGameState() {

	FILE* file = fopen("gameState.txt", "r");
	if (file == NULL) {
		printf("Error while opening file\n");
		return NULL;
	}

	int** gameState = (int**)malloc(getBoardSize() * sizeof(int*));

	for (int i = 0; i < getBoardSize(); i++) {
		gameState[i] = (int*)malloc(getBoardSize() * sizeof(int));
		for (int j = 0; j < getBoardSize(); j++) {
			fscanf_s(file, "%d", &gameState[i][j]);
			int a = gameState[i][j];
		}
	}
	fclose(file);
	return gameState;

}