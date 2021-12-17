#include <iostream>
#include <fstream>
#include <sstream>
#include "players.h"
#include <vector>
#include <iterator>
#include <algorithm> 
#include <filesystem>
#include "playerHistory.h"
#include <iomanip>
#include "menu.h"

using namespace std;

void loadNames(vector<players*> player) {
	//iterates through the vector player
	for (vector<players*>::iterator it(player.begin()); it != player.end(); it++) {
		//passes each entry through the displayPlayers() method in the players class to display the players and their high scores
		(*it)->displayPlayers();
	}
}

bool sortOn(const players* lhs, const players* rhs) {
	//returns whether the playerName on the lhs is greater than the playerName on the rhs to sort them alphabetically
	return lhs->greaterThan(rhs);
}

bool sortScore(const players* lhs, const players* rhs) {
	//returns whether the score on the lhs is greater than the score on the rhs to get it in high-low order
	return lhs->sortScore(rhs);
}

void displaySort(vector<players*> player, int option) {
	string sortOpt;
	//allows the same method to be used for alphabetical and numerical sort dependant on option
	if (option == 4) {
		//sorts the vector by playerName alphabetically
		sort(player.begin(), player.end(), sortOn);
		sortOpt = "Alphabetically: ";
	}
	else {
		//sorts the vector by high score
		sort(player.begin(), player.end(), sortScore);
		sortOpt = "Highest Score: ";
	}
	//prints out user friendly message so the user knows how to players are sorted.
	cout << "\n" << "Player names sorted " << sortOpt << "\n" << "\n";
	//prints out the sorted vector
	loadNames(player);
}

void closeFile(vector<players*> player) {
	//sets the file up to be outputted into
	ofstream out("playerDetails.txt");
	//iterates thorugh the vector player
	for (vector<players*>::iterator it(player.begin()); it != player.end(); it++) {
		//each entry is added to the file using operator overloading, once at the end of the entry \n is used to move onto a new line
		out << *(*it) << "\n";
		//frees the memory for that space in the vector
		free(*it);
		//sets that space to NULL
		*it = NULL;
	}
}

int main() {
#ifdef _DEBUG
	// _CrtSetBreakAlloc(87);
	_onexit(_CrtDumpMemoryLeaks);
#endif
	//creates objects for the classes players and menu
	players* singPlayer;
	menu* Menu;
	//creates the variables line and input
	string line, input;
	//initalises the variable menu
	Menu = new menu();
	//opens the file playerDetails to allow it to be read
	ifstream myfile("playerDetails.txt");
	//intailises the vector players
	vector<players*> player{};
	//creates a loop while there is stil contents being read from the file
	while (myfile >> input) {
		//reads the line from the file into the string input
		stringstream ss(input);
		//creates and intialises the variables name, pass and sco
		string name = "", pass = "", sco = "";
		//assigns the data to the correct variable based off the commas within the line
		getline(ss, name, ',');
		getline(ss, pass, ',');
		getline(ss, sco, ',');
		//converts the string sco into an integer
		int score = stoi(sco);
		//creates and requests memory on the heap to store the password and playerName in char arrays
		char* password = (char*)malloc(sizeof(char) * sizeof(pass));
		char* playerName = (char*)malloc(sizeof(char) * sizeof(name));
		//copies the data from the strings pass and name and puts them into the appropriate char array
		strcpy_s(password, sizeof(pass) + 1, pass.c_str());
		strcpy_s(playerName, sizeof(name)+1, name.c_str());
		//creates a new instance of players containing playerName, password and high score
		player.push_back(new players(playerName, password, score));
	}
	//creates and intialises the variable loop
	bool loop = true;
	//the first menu will continue to display until x = false, which occurs when 9 is inputted
	while (loop) {
	//user friendly welcome message and table to view players with their scores
	cout << "Welcome to Champion Yahtzee" << "\n";
	cout << "----------------------------" << "\n";
	cout << "Player Name" << "\t" << "Highest Score" << "\n";
	//displays all the players within the vector player
	loadNames(player);
	//user friendly message to allow the user to traverse the menu
	cout << "\n1) Choose player\n" <<
		"2) Add players\n" <<
		"3) Remove player\n" <<
		"4) Sort players alphabetically\n" <<
		"5) Sort by highest score\n" <<
		"9) Exit\n" <<
		"\nPlease choose an option: ";
	//creates the variable option
	int option;
	//options value becomes the users inputted value
	cin >> option;
	//traverses to the correct method dependant on the value of option
		if (option == 1) {
			//calls the choosePlayer method within the menu class to allow the user to login
			Menu->choosePlayer(player);
			cout << "\n";
		}
		else if (option == 2) {
			//calls the addPlayer method within the menu class to allow the addition of a new player
			player = Menu->addPlayer(player);
			cout << "\n";
		}
		else if (option == 3) {
			//calls the playerRemove function within the menu class to allow the removal of a player
			player = Menu->playerRemove(player);
			cout << "\n";
		}
		else if (option == 4) {
			//calls the displaySort method and redisplays the players in alphabetical order
			displaySort(player, option);
			cout << "\n";
		}
		else if (option == 5) {
			//calls the displaySort method and redisplays the players in score order (high-low)
			displaySort(player, option);
			cout << "\n";
		}
		else if (option == 9) {
			//calls the closeFile method and writes back the contents of the vectors player to the playerDetails textfile
			closeFile(player);
			//makes loop = false so the loop breaks and the project stops running
			loop = false;
			break;
		}
		else{
			//a user friendly message to prompt the user to re-enter a valid option
			cout << "Please enter a valid option: ";
			cout << "\n";
		}
	}
	return 0;
}
