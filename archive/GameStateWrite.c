#include "GameStateIO.h"

int writeGameState(GameState gameState, int size) {
	FILE* file = fopen("gameState.txt", "w");
	if (file == NULL) {
		printf("Error while opening file\n");
		return 1;
	}
	fprintf(file, "%d\n", gameState.currentPlayer);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fprintf(file, "%d ", gameState.pawnsOnBoard[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
	return 0;
}