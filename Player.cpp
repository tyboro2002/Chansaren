#include "Player.h"

/*
* print a player to the outputstream
*/
std::ostream& operator<<(std::ostream& os, const Player& player) {
	os << "Player named: " << player.m_name << endl;
	if (player.m_cards.numberOfCards() == 0) {
		os << "has no cards";
	}else {
		os << "has " << player.m_cards.numberOfCards() << " cards: " << endl;
		for (int i = 0; i < player.m_cards.numberOfCards() - 1; i++) {
			os << player.m_cards.peekCardAtIndex(i) << endl;
		}
		os << player.m_cards.peekCardAtIndex(player.m_cards.numberOfCards()-1);
	}
	return os;
}

/*
* return the cards deck of the player
*/
Deck Player::getCards() {
	return m_cards;
}
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

void Player::recieveCard(const Kaart& kaart) {
	m_cards.addCard(kaart);
}
void Player::recieveDeck(const Deck& deck) {
	for (int i = 0; i < deck.numberOfCards(); i++) {
		m_cards.addCard(deck.peekCardAtIndex(i));
	}
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