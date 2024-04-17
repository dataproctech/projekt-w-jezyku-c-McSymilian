#include "GameResult.h"

MatchResultRecord* createMatchResultRecord(char* playerNameA, char* playerNameB, char scoreA, char scoreB, unsigned int time)
{
	return &(MatchResultRecord) { .playerNameA = playerNameA, .playerNameB = playerNameB, .scoreA = scoreA, .scoreB = scoreB, .time = time };
}
