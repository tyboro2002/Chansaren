#pragma once
#include "Kaart.h"

using namespace std;

class Player {
	string m_name = "";
	Deck m_cards;
public:
	Deck getCards();
	Player(const string& m_name);
	Player(const string& m_name, const Deck& m_cards);
	friend std::ostream& operator<<(std::ostream& os, const Player& player);
	const Deck& layNFirstCards(const int n = 1);
	const Deck& layNLastCards(const int n = 1);
	void recieveCard(const Kaart& kaart);
	void recieveDeck(const Deck& deck);
};