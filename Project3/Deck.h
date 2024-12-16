#include "Card.h"
#pragma once


class Deck {

	Card** cards;

public:
	Deck();
	Deck(Card** cards);
	void shuffle();
	void displayGrid();
	Card** getCards();
	void setCards(Card** cards);
	void resetGrid();
	Card* selectCard(int x, int y);
	void removeCard(int x, int y);
	~Deck();

};
