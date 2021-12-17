#include <iostream>
#include <sstream>
#include "playerHistory.h"
#include <string>

using namespace std;

playerHistory::playerHistory(string scores[7])
{	
	//adds the scores from array thats passed through the class to the scores array used within the class
	for (int i = 0; i < 7; i++) {
		this->scores[i] = scores[i];
	}
}

playerHistory::~playerHistory()
{
}

//displays the number of games and date which is only needed when the full scorecards are being displayed
void playerHistory::display(int counter, int numLine) {
	//as counter starts at 0 have to add 1 to make it valid, numLine is the number of scorecards there within a file
	cout << "Game:" << "\t" << (counter + 1) << " of " << numLine;
	//the date and time are held in first element of the array
	cout << "\n" << "Date: " << "\t" << scores[0];
	//calls the method to display the rest of the scorecard
	displayScorecards();
}

void playerHistory::displayScorecards() {
	//displays the scorecard in a user friendly format with each element within the array relating to an ace, two. three, etc
	cout << "\n" << "-----SCORECARD-----" <<
		"\n" << "Aces:" << "\t" << scores[1] <<
		"\n" << "Twos:" << "\t" << scores[2] <<
		"\n" << "Threes:" << "\t" << scores[3] <<
		"\n" << "Fours:" << "\t" << scores[4] <<
		"\n" << "Fives:" << "\t" << scores[5] <<
		"\n" << "Sixes:" << "\t" << scores[6] <<
		"\n" << "--------------------";
	//allScore holds the total of all the elements within the array (except the date) added
	cout << "\n" << "Total:" << "\t\t" << allScore <<
			"\n" << "--------------------";
}

//calculates the total score of the scorecard
int playerHistory::allScores() {
	allScore = 0;
	for (int i = 1; i < 7; i++)
	{
		//if there is no element within the scores array than nothing is added to allScore
		if (scores[i] != " ") {
			int tempNum = 0;
			//converts the scores into integers and stores them in tempNum
			tempNum = stoi(scores[i]);
			//added them to allScore
			allScore += tempNum;
		}
	}
	//returns the value of allScore
	return allScore;
}




