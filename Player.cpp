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
	os << endl;
	os << "has value: " << player.m_cards.calculateValue();
	return os;
}

/*
* returns the size of the players deck
*/
int Player::getDeckSize() const {
	return m_cards.numberOfCards();
}

/*
* return the cards deck of the player
*/
Deck& Player::getCards() {
	return m_cards;
}
/*
* return a pointer to the deck of the player
*/
Deck* Player::getCardsPointer() {
	return &m_cards;
}

/*
* return the name of the player
*/
std::string Player::getName() {
	return m_name;
}

/*
* clear all the cards from the player
*/
void Player::clearCards() {
	m_cards = Deck();
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
void Player::layNFirstCards(Deck& fullDeck, const int n = 1){
	m_cards.popNFirst(fullDeck, n);
}

/*
* returns a deck of the last n cards of the player (also consume them)
*/
void Player::layNLastCards(Deck& fullDeck, const int n = 1) {
	m_cards.popNLast(fullDeck, n);
}

/*
* swap the cards from this player's deck with the cards from the other players's deck keeping the multiplier
*/
void Player::swapDecks(Player& other) {
	Deck tempDeck(getCards());
	clearCards();
	recieveDeck(other.getCards());
	other.clearCards();
	other.recieveDeck(tempDeck);
}