#include "Player.h"

/*
* create a player without cards
*/
Player::Player(const string& m_name){
	this->m_name = m_name;
}

/*
* create a player with cards
*/
Player::Player(const string& m_name, const Deck& m_cards) {
	this->m_name = m_name;
	this->m_cards = m_cards;
}

/*
* returns a deck of the first n cards of the player (also consume them)
*/
const Deck& Player::layNFirstCards(const int n)
{
	return m_cards.popNFirst(n);
}

/*
* returns a deck of the last n cards of the player (also consume them)
*/
const Deck& Player::layNLastCards(const int n) {
	return m_cards.popNLast(n);
}