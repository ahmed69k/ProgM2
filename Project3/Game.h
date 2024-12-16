#include"Card.h"
#include"StandardCard.h"
#include"PenaltyCard.h"
#include"BonusCard.h"
#include"Deck.h"
#include"Player.h"

#include <iostream>

class Game {

	Player* p1;
	Player* p2;
	Deck* d;
	int turn;

public:
	Game();
	Game(string p1, string p2);
	~Game();
	void initializeGame();
	void switchTurn();
	bool isGameOver();
	void startGame();
	void endGame();
	void nextTurn();
	void clearConsole();
	Player* getP1();
	Player* getP2();
	Deck* getDeck();
};

