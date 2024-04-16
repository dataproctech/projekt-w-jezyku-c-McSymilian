#include "GameStateIO.h"

int** readGameState(int size) {

	FILE* file = fopen("gameState.txt", "r");
	if (file == NULL) {
		printf("Error while opening file\n");
		return NULL;
	}

	int** gameState = (int**)malloc(size * sizeof(int*));

	for (int i = 0; i < size; i++) {
		gameState[i] = (int*)malloc(size * sizeof(int));
		for (int j = 0; j < size; j++) {
			fscanf(file, "%d", &gameState[i][j]);
		}
	}
	
	return gameState;
}