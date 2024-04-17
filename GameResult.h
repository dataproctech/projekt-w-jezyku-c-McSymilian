#pragma once

/*
Data model to handle and store game results
*/
typedef struct MatchResultRecord
{
	char* playerNameA;
	char* playerNameB;

	char scoreA;
	char scoreB;

	unsigned int time;

} MatchResultRecord;

MatchResultRecord* createMatchResultRecord(char* playerNameA, char* playerNameB, char scoreA, char scoreB, unsigned int time);