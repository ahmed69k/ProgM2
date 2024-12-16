#pragma once
#include <iostream>
using namespace std;

class Player {

	string name;
	int score;

public:
	Player();
	Player(string n);
	string getName();
	void setName(string n);
	int getScore();
	void setScore(int s);
	void displayScore();
	void incrScore();
	void decrScore();
};