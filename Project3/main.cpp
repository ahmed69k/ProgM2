#include"Card.h"
#include"StandardCard.h"
#include"PenaltyCard.h"
#include"BonusCard.h"
#include"Deck.h"
#include"Game.h"
#include"Player.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <string>



using namespace std;

//Card

Card::Card() {
	number = 0;
	isFaceUp = false;
}

Card::Card(int n) {
	setNumber(n);
	isFaceUp = false;
}

int Card::getNumber() {
	if (this != nullptr)
		return number;
	else
		return -1;
}

void Card::setNumber(int num) {
	if (num > 10 || num < 0) {
		cout << "Invalid number!" << endl;
	}
	else
		number = num;
}

bool Card::Face() {
	if (isFaceUp) {
		return true;
	}
	else
		return false;
}

void Card::setFace(bool f) {
	if (this != nullptr) {
		isFaceUp = f;
	}

}
void Card::reveal() {
	setFace(true);
}
void Card::hide() {
	if (this != nullptr)
		setFace(false);
}

void Card::display() {
	if (this == nullptr) {
		cout << "| X |";
	}
	else if (!isFaceUp) {
		//cout << "| * |";
		cout << "| " << number << " |";
	}
	else {
		cout << "| " << number << " |";
	}
}

Card::~Card() {
}
//RegularCard

StandardCard::StandardCard() :Card() {}
StandardCard::StandardCard(int number) :Card(number) {}
StandardCard::~StandardCard() {}

//BonusCard

BonusCard::BonusCard() :Card() {}
BonusCard::BonusCard(int number) :Card(number) {}
BonusCard::~BonusCard() {}

//PenaltyCard

PenaltyCard::PenaltyCard() :Card() {}
PenaltyCard::PenaltyCard(int number) :Card(number) {}
PenaltyCard::~PenaltyCard() {}


//Player

Player::Player() {
	name = "";
	score = 0;
}



Player::Player(string n) {
	name = n;
	score = 0;
}

void Player::displayScore() {
	cout << name << "'s score: " << score << endl;
}

string Player::getName() {
	return name;
}

void Player::setName(string n) {
	name = n;
}

int Player::getScore() {
	return score;
}

void Player::setScore(int s) {
	score = s;
}
void Player::incrScore() {
	score += 1;
}
void Player::decrScore() {
	score -= 1;
}

//Deck

Deck::Deck() {
	cards = new Card * [16];
	int num = 1;
	for (int i = 0; i < 12; i++) {
		if (num > 6) {
			num = 1;

		}
		cards[i] = new StandardCard(num);
		num++;
	}
	for (int i = 12; i < 14; i++) {

		cards[i] = new BonusCard(7);

	}
	for (int i = 14; i < 16; i++) {

		cards[i] = new PenaltyCard(8);

	}
	//for (int i = 0; i < 16; i++) {
	//	cards[i]->setFace(true);
	//}
}

Deck::Deck(Card** cards) {
	this->cards = cards;
}

Card** Deck::getCards() {
	return cards;
}

void Deck::setCards(Card** cards) {
	this->cards = cards;
}

void Deck::shuffle() {
	srand(time(0));
	for (int i = 16 - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(cards[i], cards[j]);
	}
}
void Deck::displayGrid() {
	for (int i = 0; i < 16; i++) {
		cards[i]->display();
		if ((i + 1) % 4 == 0) {

			cout << endl;
		}


	}
}

void Deck::resetGrid() {
	for (int i = 0; i < 16; i++) {
		if (cards[i] != nullptr)
			cards[i]->setFace(false);
	}
}

void Deck::removeCard(int x, int y) {
	if (cards[x * 4 + y] != nullptr) {
		delete cards[x * 4 + y];
		cards[x * 4 + y] = nullptr;
	}

}

Card* Deck::selectCard(int x, int y) {
	if (cards[x * 4 + y] != nullptr) {
		cards[x * 4 + y]->reveal();
		return cards[x * 4 + y];
	}
	else
		return nullptr;
}

Deck::~Deck() {
	for (int i = 0; i < 16; i++) {
		delete cards[i];
	}
	delete[] cards;
}

//Game
Game::Game() {
	p1 = new Player();
	p2 = new Player();
	d = new Deck();
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 1);
	turn = dis(gen);
}

Game::Game(string p1, string p2) {
	this->p1 = new Player(p1);
	this->p2 = new Player(p2);
	d = new Deck();
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 1);
	turn = dis(gen);
}

Game::~Game() {
	delete d, p1, p2;
}

void Game::initializeGame() {
	cout << "    CARD MATCHING" << endl;
	d->shuffle();
	d->displayGrid();
	p1->displayScore();
	p2->displayScore();
}

void Game::nextTurn() {

	d->resetGrid();
	cout << "    CARD MATCHING" << endl;
	d->displayGrid();
	p1->displayScore();
	p2->displayScore();

}

void Game::switchTurn() {
	if (turn == 0) {
		turn = 1;
	}
	else {
		turn = 0;
	}
}
bool Game::isGameOver() {
	Card** cards = d->getCards();
	for (int i = 0; i < 16; i++) {
		if (cards[i] != nullptr) {
			return false;
		}
	}
	return true;
}

Player* Game::getP1() {
	return p1;
}
Player* Game::getP2() {
	return p2;
}
Deck* Game::getDeck() {
	return d;
}
void Game::clearConsole() {
	system("cls");
}
void Game::startGame() {
	initializeGame();
	int x, y, a, b, choice;
	Card* c1;
	Card* c2;
	bool isPenalty = false;
	while (!isGameOver()) {
		if (turn == 0) {  // Player 1's turn
			cout << p1->getName() << "'s turn!" << "\nEnter card coordinates: ";
			cin >> x >> y;
			c1 = d->selectCard(x, y);
			c1->reveal();
			d->displayGrid();
			cout << "Enter card coordinates: ";
			cin >> a >> b;
			while (x > 3 || y > 3 || a > 3 || b > 3 || x < 0 || y < 0 || a < 0 || b < 0) {
				cout << "Invalid coordinates! \nPlease re-enter coordinates: ";
				cin >> x >> y >> a >> b;
			}
			while (a == x && b == y) {
				cout << "Cannot select same card twice! \nPlease re-enter coordinates: ";
				cin >> a >> b;
			}

			c2 = d->selectCard(a, b);
			while (c1 == nullptr || c2 == nullptr) {
				cout << "Card deleted! Please re-enter coordinates: ";
				cin >> x >> y >> a >> b;
				c1 = d->selectCard(x, y);
				c2 = d->selectCard(a, b);
			}
			c2->reveal();
			d->displayGrid();

			if (c1 && c2 && c1->getNumber() == 7 && c2->getNumber() == 7) {
				clearConsole();
				cout << "Bonus Card Selected!" << endl;
				cout << "Enter 0 to take 2 points OR Enter 1 to take 1 point and play another round!" << endl;
				cin >> choice;
				if (choice == 0) {
					p1->incrScore();
					p1->incrScore();
					d->removeCard(x, y);
					c1 = nullptr;
					d->removeCard(a, b);
					c2 = nullptr;
				}
				else {
					p1->incrScore();
					d->removeCard(x, y);
					c1 = nullptr;
					d->removeCard(a, b);
					c2 = nullptr;
				}
				if (isPenalty) {
					nextTurn();  // End the penalty turn
					isPenalty = false;
				}
				else {
					nextTurn();
				};
			}


			else if (c1 && c2 && c1->getNumber() == 8 && c2->getNumber() == 8) {
				clearConsole();
				cout << "Penalty Card Selected!" << endl;
				cout << "Enter 0 to lose 2 points OR Enter 1 to lose 1 point and skip the next turn!" << endl;
				cin >> choice;
				if (choice == 0) {
					p1->decrScore();
					p1->decrScore();
					d->removeCard(x, y);
					c1 = nullptr;
					d->removeCard(a, b);
					c2 = nullptr;
				}
				else {
					p1->decrScore();
					isPenalty = true;
					d->removeCard(x, y);
					c1 = nullptr;
					d->removeCard(a, b);
					c2 = nullptr;
				}
				if (!isPenalty) {
					switchTurn();
					nextTurn();
				}
				else {
					switchTurn();
					nextTurn();
				}
			}

			if (c1 && c2 && c1->getNumber() == 8 || c2->getNumber() == 8) {
				clearConsole();
				if (c1->getNumber() == 8) {
					p1->decrScore();
					d->removeCard(x, y);
					c1 = nullptr;
					if (isPenalty) {
						nextTurn();
						isPenalty = false;
					}
					else {
						switchTurn();
						nextTurn();
					}

				}
				else {
					p1->decrScore();
					d->removeCard(a, b);
					c2 = nullptr;
					if (isPenalty) {
						nextTurn();
						isPenalty = false;
					}
					else {
						switchTurn();
						nextTurn();
					}
				}
			}



			if (c1 && c2 && c1->getNumber() == 7 && c2->getNumber() == 8) {
				d->removeCard(x, y);
				c1 = nullptr;
				d->removeCard(a, b);
				c2 = nullptr;
				if (isPenalty) {
					nextTurn();
					isPenalty = false;
				}
				else {
					switchTurn();
					nextTurn();
				}
			}

			if (c1 && c2 && c1->getNumber() == 7 || c2->getNumber() == 7) {
				clearConsole();
				if (c1->getNumber() == 7) {
					p1->incrScore();
					d->removeCard(x, y);
					c1 = nullptr;
					if (isPenalty) {
						nextTurn();
						isPenalty = false;
					}
					else {
						switchTurn();
						nextTurn();
					};
				}
				else {
					p1->incrScore();
					d->removeCard(a, b);
					c2 = nullptr;
					if (isPenalty) {
						nextTurn();
						isPenalty = false;
					}
					else {
						switchTurn();
						nextTurn();
					};
				}

			}

			else if (c1 && c2 && c1->getNumber() == c2->getNumber()) {
				clearConsole();
				cout << "Card match!" << endl;
				p1->incrScore();
				d->removeCard(x, y);
				c1 = nullptr;
				d->removeCard(a, b);
				c2 = nullptr;
				if (isPenalty) {
					nextTurn();
					isPenalty = false;
				}
				else {
					nextTurn();
				};
			}
			else if (c1 && c2 && c1->getNumber() != c2->getNumber() && c1->getNumber() != 7 && c1->getNumber() != 8 && c2->getNumber() != 7 && c2->getNumber() != 8) {
				this_thread::sleep_for(std::chrono::seconds(1));
				clearConsole();
				cout << "Cards don't match!" << endl;
				if (isPenalty) {
					nextTurn();
					isPenalty = false;
				}
				else {
					switchTurn();
					nextTurn();
				};
			}
		}
		else {  // Player 2's turn
			cout << p2->getName() << "'s turn!" << "\nEnter card coordinates: ";
			cin >> x >> y;
			c1 = d->selectCard(x, y);
			c1->reveal();
			d->displayGrid();
			cout << "Enter card coordinates: ";
			cin >> a >> b;
			while (x > 3 || y > 3 || a > 3 || b > 3 || x < 0 || y < 0 || a < 0 || b < 0) {
				cout << "Invalid coordinates! \nPlease re-enter coordinates: ";
				cin >> x >> y >> a >> b;
			}
			while (a == x && b == y) {
				cout << "Cannot select same card twice! \nPlease re-enter coordinates: ";
				cin >> a >> b;
			}

			c2 = d->selectCard(a, b);
			while (c1 == nullptr || c2 == nullptr) {
				cout << "Card deleted! Please re-enter coordinates: ";
				cin >> x >> y >> a >> b;
				c1 = d->selectCard(x, y);
				c2 = d->selectCard(a, b);
			}
			c2->reveal();
			d->displayGrid();

			if (c1 && c2 && c1->getNumber() == 7 && c2->getNumber() == 7) {
				clearConsole();
				cout << "Bonus Card Selected!" << endl;
				cout << "Enter 0 to take 2 points OR Enter 1 to take 1 point and play another round!" << endl;
				cin >> choice;
				if (choice == 0) {
					p2->incrScore();
					p2->incrScore();
					d->removeCard(x, y);
					c1 = nullptr;
					d->removeCard(a, b);
					c2 = nullptr;
				}
				else {
					p2->incrScore();
					d->removeCard(x, y);
					c1 = nullptr;
					d->removeCard(a, b);
					c2 = nullptr;
				}
				if (isPenalty) {
					nextTurn();  // End the penalty turn
					isPenalty = false;
				}
				else {
					nextTurn();
				};
			}


			else if (c1 && c2 && c1->getNumber() == 8 && c2->getNumber() == 8) {
				clearConsole();
				cout << "Penalty Card Selected!" << endl;
				cout << "Enter 0 to lose 2 points OR Enter 1 to lose 1 point and skip the next turn!" << endl;
				cin >> choice;
				if (choice == 0) {
					p2->decrScore();
					p2->decrScore();
					d->removeCard(x, y);
					c1 = nullptr;
					d->removeCard(a, b);
					c2 = nullptr;
				}
				else {
					p2->decrScore();
					isPenalty = true;
					d->removeCard(x, y);
					c1 = nullptr;
					d->removeCard(a, b);
					c2 = nullptr;
				}
				if (!isPenalty) {
					switchTurn();
					nextTurn();
				}
				else {
					// Skip the turn after penalty
					switchTurn();
					nextTurn();
				}
			}
			if (c1 && c2 && c1->getNumber() == 8 || c2->getNumber() == 8) {
				clearConsole();
				if (c1->getNumber() == 8) {
					p2->decrScore();
					d->removeCard(x, y);
					c1 = nullptr;
					if (isPenalty) {
						nextTurn();
						isPenalty = false;
					}
					else {
						switchTurn();
						nextTurn();
					}

				}
				else {
					p2->decrScore();
					d->removeCard(a, b);
					c2 = nullptr;
					if (isPenalty) {
						nextTurn();
						isPenalty = false;
					}
					else {
						switchTurn();
						nextTurn();
					}
				}
			}

			if (c1 && c2 && c1->getNumber() == 7 || c2->getNumber() == 7) {
				clearConsole();
				if (c1->getNumber() == 7) {
					p2->incrScore();
					d->removeCard(x, y);
					c1 = nullptr;
					switchTurn();
					nextTurn();
				}
				else {
					p2->incrScore();
					d->removeCard(a, b);
					c2 = nullptr;
					switchTurn();
					nextTurn();
				}

			}

			if (c1 && c2 && c1->getNumber() == 7 && c2->getNumber() == 8) {
				d->removeCard(x, y);
				c1 = nullptr;
				d->removeCard(a, b);
				c2 = nullptr;
				if (isPenalty) {
					nextTurn();
					isPenalty = false;
				}
				else {
					switchTurn();
					nextTurn();
				}
			}

			else if (c1 && c2 && c1->getNumber() == c2->getNumber()) {
				clearConsole();
				cout << "Card match!" << endl;
				p2->incrScore();
				d->removeCard(x, y);
				c1 = nullptr;
				d->removeCard(a, b);
				c2 = nullptr;
				if (isPenalty) {
					nextTurn();
					isPenalty = false;
				}
				else {
					nextTurn();
				}
			}
			else if (c1 && c2 && c1->getNumber() != c2->getNumber()) {
				this_thread::sleep_for(std::chrono::seconds(1));
				clearConsole();
				cout << "Cards don't match!" << endl;
				if (isPenalty) {
					nextTurn();
					isPenalty = false;
				}
				else {
					switchTurn();
					nextTurn();
				}
			}
		}
	}
	clearConsole();
	cout << "Game Over!" << endl;
	if (p1->getScore() > p2->getScore()) {
		cout << p1->getName() << " wins!" << "\nScore: " << p1->getScore() << endl;
	}
	else {
		cout << p2->getName() << " wins!" << "\nScore: " << p2->getScore() << endl;
	}
}


int main() {
	Game game("Ahmed", "Malak");
	game.startGame();
	return 0;
}






