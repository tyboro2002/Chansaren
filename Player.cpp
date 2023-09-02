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
Player::const Deck& layNFirstCards(const int n = 1){
	return m_cards.popNFirst(n);
}

/*
* returns a deck of the last n cards of the player (also consume them)
*/
Player::const Deck& layNLastCards(const int n = 1) {
	return m_cards.popNLast(n);
}