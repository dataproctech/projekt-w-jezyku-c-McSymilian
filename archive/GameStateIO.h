#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "../data_model/PawnsOnBoard.h"

typedef int** Board;

int writeGameState(int** gameState, int size, bool currentPlayer);

GameState readGameState();