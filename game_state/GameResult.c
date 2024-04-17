#include "GameResult.h"

MatchResultRecord* createMatchResultRecord(char* playerNameA, char* playerNameB, char scoreA, char scoreB, unsigned int time)
{
	return &(MatchResultRecord) { .playerNameA = playerNameA, .playerNameB = playerNameB, .scoreA = scoreA, .scoreB = scoreB, .time = time };
}

MatchResultRecord* createGenericMatchResultRecord(bool doPlayerAWon, unsigned int time) {
	return &(MatchResultRecord) { .playerNameA = "Player A", .playerNameB = "Player B", .scoreA = doPlayerAWon ? 1 : 0, .scoreB = doPlayerAWon ? 0 : 1, .time = time };
}