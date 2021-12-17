#pragma once
#include "players.h"
class menu
{
public:
	string newPlayerName();
	vector<players*> addPlayer(vector<players*> player);
	char* encrypt();
	void choosePlayer(vector<players*> player);
	vector<players*> playerRemove(vector<players*> player);
	bool removeFunc(const players* player);

private:
	int num = 0;
	char pass[11];
	
};

