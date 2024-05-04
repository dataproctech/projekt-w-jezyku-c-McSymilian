#include "GameStateIO.h"

int writeGameState(int** gameState, int size, bool currentPlayer) {
	FILE* file = fopen("gameState.txt", "w");
	if (file == NULL) {
		printf("Error while opening file\n");
		return 1;
	}
	fprintf(file, "%d\n", currentPlayer);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fprintf(file, "%d ", gameState[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
	return 0;
}