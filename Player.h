#pragma once
#include "Kaart.h"

using namespace std;

class Player {
	string m_name = "";
	Deck m_cards;
	bool m_in_live = true;
	int m_comaRounds = 0;
public:
	int getDeckSize() const;
	bool getLivingStatus() const { return m_in_live; }
	int getComaCount() const { return m_comaRounds; }
	void IncreaseComaCount() { m_comaRounds++; }
	void resetComaCount() { m_comaRounds = 0; }
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
	void killPlayer() { m_in_live = false; }
	Kaart popIndexed(const int i) { return m_cards.popIndexed(i); }
};