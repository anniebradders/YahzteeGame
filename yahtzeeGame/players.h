#pragma once
#include <string>
#include <vector>
#include "playerHistory.h"

using namespace std;
class players
{
public:
	players(char* playerName, char* password, int score);
	~players();
	void displayPlayers();
	void singlePlayer();
	char* decrypt();
	bool greaterThan(const players* player) const;
	bool sortScore(const players* player) const;
	bool removePlayer(const players* player) const;
	bool checkName(string name);
	void openFile(int option);
	void playerNa();
	void playerSco();
	void totalScore();
	void menu2();
	void displayScore(int numLine);

	//operator overloading into a file
	friend ostream& operator<<(ostream& os, players& player)
	{
		//if the score is NULL than 0 is put into the file as it means they're a new player who has yet to play a game
		if (player.score == NULL) {
			player.score = 0;
		}
		//writes into the file in order playerName, password then score with commas between them
		os << player.playerName << "," << player.password << "," << player.score;
		return os;
	}

	//operator overloading out of a file into variables
	friend istream& operator>>(istream& is, players& player)
	{
		is >> player.playerName;
		is >> player.password;
		is >> player.score;

		return is;
	};

private:
	string input;
	char pass[11];
	char* playerName;
	char* password;
	int score, numLine, allScore, counter;
	playerHistory** scorecard;
	bool x = true;
	double average;
};

