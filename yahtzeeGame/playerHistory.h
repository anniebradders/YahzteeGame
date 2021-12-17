#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;
class playerHistory 
{
public:
	playerHistory(string scores[6]);
	~playerHistory();
	friend istream& operator>>(istream& is, playerHistory& playerHis)
	{
		for (int i = 0; i < 7; i++) {
			is >> playerHis.scores[i];
		}
		return is;
	};

	//operator overloading into a file
	friend ostream& operator<<(ostream& os, playerHistory& playerHis)
	{
		for (int i = 0; i < 7; i++) {
			os << playerHis.scores[i] << " ";
		} 
		return os;
	}

	void display(int counter, int numLine);
	int allScores();
	void displayScorecards();

private:
	int gameID = 0;
	double allScore= 0;
	string date;
	bool x = true;
	string scores[7];
};

