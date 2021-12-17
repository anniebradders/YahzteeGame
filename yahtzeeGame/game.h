#pragma once
#include <string>
#include <time.h>
#include <vector>
#include "playerHistory.h"

using namespace std;
class game
{
public:
	game();
	~game();
	string* playGame();
	char* getTime();
	void displayDiceFace(int diceface);
	void round();
	void scoreDice();
	int numOf(int option);

private:
	char* date;
	int numLine, y = 0;
	playerHistory** scorecard = new playerHistory*[numLine];
	string* scores = new string[7];
	char dateTime[80];
	const char* DTTMFMT = "%Y-%m-%d %H:%M:%S";
	size_t DTTMSZ = 21;
	time_t t = time(0);
	struct tm tstruct;
	int diceface, scorecardNum;
	vector<string> scoreMenu;
	int roundScores[5], ranNum[5], readNum[5];
	string finalScore[7];
	string ones, twos, threes, fours, fives, sixes;
};

