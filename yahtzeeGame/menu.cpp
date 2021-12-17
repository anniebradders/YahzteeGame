#include <iostream>
#include "menu.h"
#include <sstream>
#include <string>
#include <filesystem>
using namespace std;
using namespace std;

//gets the users input and stores it in name
string menu::newPlayerName() {
	string name = "";
	//if its the first time addPlayer is called then cin.ignore() 
	if (num == 0) {
		cin.ignore();
	}
	cout << "Player name: ";
	getline(cin, name);
	return name;
}

//adds player to the vector player
vector<players*> menu::addPlayer(vector<players*> player) {
	string name;
	//score equals 0 as no games have been played by the player yet
	int score = 0;
	//gets the users inputted name and stores it in the variable name
	name = newPlayerName();
	//iterates through the vector player to check if the name is already in use
	for (vector<players*>::iterator it(player.begin()); it != player.end(); it++) {
		//returns whether the name matches a playerName stored within the vector
		bool x = (*it)->checkName(name);
		//if it is true than the user is prompted to re-enter a name which is not in use
		while (x == true) {
			cout << "That name is already in use" << "\n";
			//num is increased by 1 so that cin.ignore() is passed by
			num++;
			name = newPlayerName();
			x = (*it)->checkName(name);
		}

	}
	//creates a file with the playerName
	string filename(name + ".txt");
	fstream output_fstream;
	output_fstream.open(filename, std::ios_base::out);
	string password= " ";
	cout << "Password: ";
	//stores the user inputted password in the variable password
	cin >> password;
	//if the password inputted is greater than 10 then the user is prompted to reeneter a password of smaller length
	while (password.size() > 10) {
		cout << "Please enter a password less than 10 characters: ";
		cin >> password;
	}
	//copies the contents of password to the char array pass
	strcpy_s(pass, password.c_str());
	//runs the encryption method and stores it in the string encryptPass
	string encryptPass = encrypt();
	//creates and requests memory on the heap to store the encryptedPass in char arrays
	char* encryptedPass = (char*)malloc(sizeof(char) * sizeof(encryptPass));
	//copies the data from encryptPass and stores it in encryptedPass
	strcpy_s(encryptedPass, sizeof(encryptPass) + 1, encryptPass.c_str());
	//creates and requests memory on the heap to store the playerName in char arrays
	char* playerName = (char*)malloc(sizeof(char) * sizeof(name));
	//copies the data from name and puts it into the char array
	strcpy_s(playerName, sizeof(name)+1, name.c_str());
	//creates a new instance of players containing the new data which the user just inputted
	player.push_back(new players(playerName, encryptedPass, score));
	//returns the vector player
	return player;
}

char* menu::encrypt() {
	//converts string password to a char array
	
	for (int i = 0; (i < 11 && pass[i] != '\0'); i++) {
		//10 acsii characters are taken from the value at password[i]
		pass[i] = pass[i] - 10;
	}
	//returns the char array pass
	return pass;
}

//validates the name for the player login
void menu::choosePlayer(vector<players*> player) {
	string input;
	bool x = true;
	cin.ignore();
	cout << "Enter name: ";
	//stores the user input in the variable input
	getline(cin, input);
	//iterates through the vector player
	for (vector<players*>::iterator it(player.begin()); it != player.end(); it++) {
		//checks whether or not the name inputted matches any of the playerNames in the vector player
		x = (*it)->checkName(input);
		//if the name matches then the method singlePlayer is called and that value of player is passed through to validate the password
		if (x == true) {
			(*it)->singlePlayer();
			break;
		}
	}
	//checkName returns false after iterating through the whole vector then a user frendly message is displayed that, that user does not exist
	if (x != true) {
		cout << "User not found\n";
	}
}

//checks whether the player exists in order to remove them
bool menu::removeFunc(const players* player) {
	return player->removePlayer(player);
}

//method to remove player from the vector player
vector<players*> menu::playerRemove(vector<players*> player) {
	string name;
	char fileName[20];
	cin.ignore();
	cout << "Enter name of player: ";
	//stores the inputted value in the variable name
	getline(cin, name);
	//iterates through the vector players
	for (vector<players*>::iterator it(player.begin()); it != player.end(); it++) {
		//checks whether or not the name matches a playerName in the vector player
		bool x = (*it)->checkName(name);
		//if there is a match than the player is removed
		if (x == true) {
			//removes the entire instance of player from the vector
			player.erase(it);
			//stores the name and .txt in the char array fileName so that it can be removed
			strcpy_s(fileName, (name + ".txt").c_str());
			//deletes the file
			remove(fileName);
			//breaks the loop
			break;
		}
	}
	//returns the vector player
	return player;
}

