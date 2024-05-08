#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "../data_model/PawnsOnBoard.h"


int writeGameState(GameState gameState, int size);

GameState readGameState();