#include "GameStateIO.h"
#include "../data_model/PawnsOnBoard.h"
Board readGameState(int size) {

	FILE* file = fopen("gameState.txt", "r");
	if (file == NULL) {
		printf("Error while opening file\n");
		return NULL;
	}

	Board gameState = (Board)malloc(size * sizeof(int*));

	for (int i = 0; i < size; i++) {
		gameState[i] = (int*)malloc(size * sizeof(int));
		for (int j = 0; j < size; j++) {
			fscanf_s(file, "%d", &gameState[i][j]);
		}
	}
	
	return gameState;
}