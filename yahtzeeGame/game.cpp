#include "game.h"
#include <time.h>
#include "playerHistory.h"
#include <cassert>
#include <cstdlib>
#include <vector>

using namespace std;

game::game() {
}

game::~game() {
}

//creates a new round to be repeated 3 times
void game::round() {
    //passes the random number generated through the display diceface so that it is displayed in a dice format 
    for (int i = 0; i < 5; i++) {
     diceface = ranNum[i];
     displayDiceFace(diceface);
    }
    
    int x = 0;
    int storedNum[5];
    int option;
    cout << "Enter dice number to toggle held state. Enter any other number to roll again: ";
    cin >> option;
    //the inputted value is stored in the variable option

    //while option is within the range 1-5 the number will be held
    while ((option >= 1) && (option <= 5)) {
        //the option - 1 (the position within the array of ranNum) is stored within storedNum[x]
        storedNum[x++] = option-1;
        //user is reprompted to either hold another dice or move on
        cout << "Enter dice number to toggle held state. Enter any other number to roll again: ";
        cin >> option;
    }

    int reRoll[5];
    //stores value of randomly generated numbers in readNum so that it can be used by the method scoreDice
    for (int i = 0; i < 5; i++) {
        readNum[i] = ranNum[i];
    }
    //the position of the dice held is switched to 1 in the reRoll array 
    for (int i = 0; i < 5; i++) {
       if (storedNum[i] > -1) {
            reRoll[storedNum[i]] = 1;
       }
    }
 
    for (int i = 0; i < 5; i++) {
        //if the reRoll[i] doesnt equal one then the number will be randomly regenerated
        if (reRoll[i] != 1) {
            //generates a number between 1 and 6
            ranNum[i] = 1 + (rand() % 6);
        }
    }
}

string* game::playGame() {
    //stores the date and time in the variable date
    date = getTime();
    //counter which will be displayed within the game and decrease with each round
    scorecardNum = 6;
    //intialises the vector scoreMenu
    scoreMenu.push_back("Please choose how to score your dice");
    scoreMenu.push_back("\n1:\tAces");
    scoreMenu.push_back("\n2:\tTwos");
    scoreMenu.push_back("\n3:\tThrees");
    scoreMenu.push_back("\n4:\tFours");
    scoreMenu.push_back("\n5:\tFives");
    scoreMenu.push_back("\n6:\tSixes");
    scoreMenu.push_back("\nScore against: ");
    //the first element of scores will be the value within date 
    scores[0] = date;
    //the rest of the value of date is " " so that no numbers are displayed within the scorecard
    for (int i = 1; i < 7; i++) {
        scores[i] = " ";
    }

    numLine = 0;
    int counter = 0;

    //loops for 6 rounds of randomly generated numer
    for (int i = 0; i < 6; i++) {
        //creates new instance of scorecard
        scorecard[numLine] = new playerHistory(scores);
        //calculates the total score so far
        scorecard[numLine]->allScores();
        //displays the scorecard along with the total so far throughout the game
        scorecard[numLine]->displayScorecards();
        //counter increases by 1
        counter++;
        cout << "Dice roll set #" << counter << " of 6";
        for (int i = 0; i < 5; i++) {
            //5 random numbers are generated and stored in ranNum
            ranNum[i] = 1 + (rand() % 6);
        }
        for (int i = 0; i < 3; i++) {
            //3 are looped
            round();
        }
        //the dice you score against is calculated and put into the array scores
        scoreDice();
        //scorecardNum is decreased by 1
        scorecardNum--;
    }
    //returns the array scores
    return scores;
    delete[] scores;
}

//the maths for when a dice is scored against
void game::scoreDice() {
    //iterates through the vector scoreMenu 
    for (int i = 0; i < scoreMenu.size(); i++) {
        cout << scoreMenu.at(i);
    }

    int y;
    int option;
    //the user input is stored in the variable option
    cin >> option;
    //switch case which calls the correct operation depending on the value of option
    switch (option) {
    case 1:
        //the score found by multiplying numOf(option) against the value of dice and is converted to string and stored in the array
        scores[1] = to_string(numOf(option));
        //erases the scoreMenu where it is equal to "\n:\tAces:"
        scoreMenu.erase(remove(scoreMenu.begin(), scoreMenu.end(), "\n1:\tAces"), scoreMenu.end());
        break;
    case 2:
        scores[2] = to_string(numOf(option)*2);
        scoreMenu.erase(remove(scoreMenu.begin(), scoreMenu.end(), "\n2:\tTwos"), scoreMenu.end());
        break;
    case 3:
        scores[3] = to_string(numOf(option) * 3);
        scoreMenu.erase(remove(scoreMenu.begin(), scoreMenu.end(), "\n3:\tThrees"), scoreMenu.end());
        break;
    case 4:
        scores[4] = to_string(numOf(option) * 4);
        scoreMenu.erase(remove(scoreMenu.begin(), scoreMenu.end(), "\n4:\tFours"), scoreMenu.end());
        break;
    case 5:
        scores[5] = to_string(numOf(option) * 5);
        scoreMenu.erase(remove(scoreMenu.begin(), scoreMenu.end(), "\n5:\tFives"), scoreMenu.end());
        break;
    case 6:
        scores[6] = to_string(numOf(option) * 6);
        scoreMenu.erase(remove(scoreMenu.begin(), scoreMenu.end(), "\n6:\tSixes"), scoreMenu.end());
        break;
    }

}

//calculates the number of elements that are the same value as option
int game::numOf(int option) {
    //y equals 0 everytime this method is called
    y = 0;
    for (int i = 0; i < 5; i++) {
        if (readNum[i] == option) {
            //y is increased by 1 everytime an element equals option
            y++;
        }
    }
    //returns the value of y
    return y;
}

//finds the time and date a game is played
char* game::getTime() {
    //gets the local current time and date
	localtime_s(&tstruct, &t);
    //stores the date and time in a string in the style of Year-Month-Day-Time
	strftime(dateTime, sizeof(dateTime), "%Y-%m-%d.%X", &tstruct);
    //returns the date and time
	return dateTime;
}

//code which was given to us within a tutorial session by Mike
void game::displayDiceFace(int diceface)
{
    assert(diceface >= 1 && diceface <= 6);
    cout << "\r";
    cout << "\n*********\n*    *\n";
    switch (diceface)
    {
    case 1:
        cout << "*   1 *\n*   1 *\n*   1 *\n*   1 *\n*   1 *\n";
        break;
    case 2:
        cout << "* 22222 *\n*   2 *\n* 22222 *\n* 2   *\n* 22222 *\n";
        break;
    case 3:
        cout << "* 33333 *\n*   3 *\n*  333 *\n*   3 *\n* 33333 *\n";
        break;
    case 4:
        cout << "* 4  4 *\n* 4  4 *\n* 44444 *\n*   4 *\n*   4 *\n";
        break;
    case 5:
        cout << "* 55555 *\n* 5   *\n* 55555 *\n*   5 *\n* 55555 *\n";
        break;
    case 6:
        cout << "* 66666 *\n* 6   *\n* 66666 *\n* 6  6 *\n* 66666 *\n";
        break;
    }
    cout << "*    *\n*********\n";
}
