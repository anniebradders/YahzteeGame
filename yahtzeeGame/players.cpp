#include "players.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <istream>
#include "playerHistory.h"
#include "game.h"
using namespace std;

//constructs the player using the variables playerName, password and score
players::players(char* playerName, char* password, int score) : playerName(playerName), password(password), score(score) {

}

//destructor
players::~players() {
}

//prints out the value of playerName when called
void players::playerNa() {
	cout << playerName;
}

//prints out the value of score when called
void players::playerSco() {
	cout << score;
}

//if the playerName was valid during login than this method is called to validate the password
void players::singlePlayer() {
	string inputPassword;
	cout << "Please enter password: ";
	//assigns inputPassword the user inputted value
	cin >> inputPassword;
	//runs the password retrieved from the file through the decrypt method to compare it against the inputted password
	decrypt();
	//if the decrypted password and user inputted password match than the player information screen is displayed
	if (pass == inputPassword) {
		cout << "\n";
		menu2();
	}
	else {
		//if the password is wrong than a user friendly message is displayed and the original menu is displayed
		cout << "Wrong password";
	}
}

//the player information screen
void players::menu2() {
	int option = 0;
	//calls the method openFile to create the scorecards if the playerName.txt contains any
	openFile(option);
	//loops the menu till the user chooses to exit
	while (x == true) {
		//creates an object for the class Game
		game* Game = new game;
		//sets allScore to 0 so everytime menu2 is called it is recalcuated
		allScore = 0;
		//displays a user friendly message containing the playerDetails
		cout << "\nWelcome to champion yahtzee ";
		//displays playerName
		playerNa();
		cout << "\n" << "---------------------------------------------\n" 
			<< "Highest Score: ";
		//displays the players high score
		playerSco();
		cout << "\n" << "Total games: " << numLine;
		cout << "\n" << "Accumulated score: ";
		//iterates through all the scorecards and calculates the accumlated score
		for (int i = 0; i < numLine; i++) {
			allScore += scorecard[i]->allScores();
		}
		//displays the accumlated score
		cout << allScore;
		cout << "\n" << "Average score: ";
		//if there are no scorecards 0 is displayed as you cannot divide something by 0
		if (numLine == 0) {
			average = 0;
		}
		else {
			//the average is calculated
			average = allScore / numLine;
		}
		//the average is displayed
		cout << average;
		//user friendly information to traverse the menu are displayed
		cout << "\n\n" << "1. Play Game" <<
			"\n" << "2. View historic scorecards" <<
			"\n" << "3. Return to player chooser screen" <<
			"\n\n" << "Please choose an option: ";
		//option is the value of the users input
		cin >> option;
		//traverses to the correct statement dependant on the value of option
		if (option == 1) {
			//assigns scorecard[numLine] a new instance of playerHistory where once the game is played it returns the date and score in an array
			scorecard[numLine] = new playerHistory(Game->playGame());
			//calculated the total scores for the game just played
			scorecard[numLine]->allScores();
			//if the score of the game just played is greater than the current high score, the current high score is updated
			if (scorecard[numLine]->allScores() > this->score) {
				this->score = scorecard[numLine]->allScores();
			}
			//displays the scorecard for the game just played
			scorecard[numLine]->displayScorecards();
			//increases the value of numLine by 1 so that the current instance of scorecard isn't overwritten if a new game is played
			numLine++;
		}
		else if (option == 2) {
			//displays the scorecards within the playerName.txt
			displayScore(numLine);
		}
		else if (option == 3) {
			//writes the scorecards back to the playerName.txt file
			string fileName = "";
			//adds the char string playerName to the string fileName
			fileName.append(playerName);
			//adds .txt to the string fileName to create a valid fileName
			fileName.append(".txt");
			//opens the file and prepares it to be written into
			ofstream out(fileName);
			//writes the number of scorecard to the file to the first line in file so it can be used to determine the size of the array when reopened
			out << numLine << "\n";
			//iterates through the scorecard array
			for (int i = 0; i < numLine; i++) {
				//uses operator overloading to write the values of the scorecards into the file
				out << *scorecard[i] << "\n";
			}
			//ends the loop and returns to the first menu as x != true
			x = false;
		}
		else {
			//prompts the user within a user friendly message so they input a valid value
			cout << "Not a valid option";
		}
	}
}

//menu for the displayed scorecards
void players::displayScore(int numLine) {
	//sets counter to 0
	counter = 0;
	//creates loop until the user chooses to exit
	while (x == true) {
		//while the counter is between 0 and the max value of scorecards the scorecards are displayed
		if ((counter < numLine) && (counter >= 0)) {
			//passes the scorecard at value of counter through the display method within playerHistory
			scorecard[counter]->display(counter, numLine);
		}
		else {
			//if the counter is outside of the range than the user is prompted with a user friendly message
			cout << "\nNo more scorecards";
			//counter is set to numLine so that it does not continue increasing or decreasing
			counter = numLine;
		}
		int input;
		//displays a user friendly menu to allow the user to traverse the menu
		cout << "\n\n" << "1) View the previous scorecard" <<
			"\n" << "2) View the next scorecard" <<
			"\n" << "3) Return to player statistics screen" <<
			"\n\n" << "Please choose an option: ";
		//input becomes the value of the user input
		cin >> input;

		if ((input == 1)) {
			//counter is decreased by 1 so the previous scorecard will be displayed
			counter--;
		}
		else if ((input == 2)) {
			//counter is increased by 1 so the next scorecard will be displayed
			counter++;
		}
		else if (input == 3) {
			//if the user chooses the exit the menu than they are taken back to the previous menu 
			menu2();
			//x equals false to break the loop
			x = false;
		}
		else {
			//a user friendly message so that the user inputs a valid choice
			cout << "\nEnter a valid option";
		}
	}
}

void players::openFile(int option)
{
	string line;
	int index = 0;
	numLine = 0;
	string data[7];
	//creates and intialises string fileName
	string fileName = "";
	//adds the char string playerName to the string fileName
	fileName.append(playerName);
	//adds .txt to the string fileName to create a valid fileName
	fileName.append(".txt");
	//opens the file to prepare it to be read from
	ifstream input(fileName, ifstream::binary);
	//uses operator overloading to get the first line of the file which will determine the size of the array scorecard
	input >> numLine;
	//intialises the array scorecard will the size of numLine taken from the file
	scorecard = new playerHistory*[numLine];
	//while the index is less than the number of scorecards within the fille
	while (index < numLine) {
		//a new instance of playerHistory is created and assigned to the scorecard[index] 
		scorecard[index] = new playerHistory(data);
		//the value of that line within the sting is passed into scorecard[index] which was just created
		input >> *scorecard[index];
		//index is increased by one so that each line from the file is put into a seperate scorecard
		index++;
	}
}

//displays the high score
void players::totalScore() {
	cout << score;
}

//displays the playerName and the players high score
void players::displayPlayers() {
	cout << this->playerName;
	cout << "\t\t" << this->score << "\n";
}

//runs the password from the file through a decryptio algorithm so get the decrypted password
char* players::decrypt() {
	strncpy_s(pass, password, sizeof(pass));
	//each value of the password array is ran through the loop (it only goes to 11 as the max length of a password is 10)
	for (int i = 0; (i < 11 && password[i] != '\0'); i++) {
		//10 acsii characters are added onto the value at password[i] and stored in the char array pass
		pass[i] = pass[i] + 10;
	}
	//returns pass
	return pass;
}

bool players::greaterThan(const players* player) const {
	//returns whether the current playerName is less than the playerName being passed through for an alphabetical sort
	return (playerName < player->playerName);
}

bool players::sortScore(const players* player) const {
	//returns whether the current score is greater than the score being passed through to sort them from high to low
	return (score > player->score);
}
bool players::removePlayer(const players* player)const {
	//checks whether the inputted value is equal to playerName
	return input == playerName;
}

bool players::checkName(string name) {
	//checks whether name is equal to playerName
	return name == playerName;
}



