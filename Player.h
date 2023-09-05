#pragma once
#include "Kaart.h"

using namespace std;

class Player {
	string m_name = "";
	Deck m_cards;
public:
	Deck& getCards();
	Deck* getCardsPointer();
	std::string getName();
	void clearCards();
	Player(const string& m_name);
	Player(const string& m_name, const Deck& m_cards);
	friend std::ostream& operator<<(std::ostream& os, const Player& player);
	void layNFirstCards(Deck& fullDeck, const int n);
	void layNLastCards(Deck& fullDeck, const int n);
	void recieveCard(const Kaart& kaart);
	void recieveDeck(const Deck& deck);
	void swapDecks(Player& other);
};