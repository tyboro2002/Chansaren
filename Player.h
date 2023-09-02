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
	const Deck& layNFirstCards(const int n = 1);
	const Deck& layNLastCards(const int n = 1);
};