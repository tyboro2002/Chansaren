#include "Player.h"

/*
* print a player to the outputstream
*/
std::wostream& operator<<(std::wostream& os, const Player& player) {
	os << L"Player named: " << std::wstring(player.m_name.begin(), player.m_name.end()) << std::endl;
	if (player.m_cards.numberOfCards() == 0) {
		os << L"has no cards";
	}
	else {
		os << L"has " << player.m_cards.numberOfCards() << L" cards:" << std::endl;
		for (int i = 0; i < player.m_cards.numberOfCards() - 1; i++) {
			os << player.m_cards.peekCardAtIndex(i) << std::endl;
		}
		os << player.m_cards.peekCardAtIndex(player.m_cards.numberOfCards() - 1);
	}
	os << std::endl;
	os << L"has value: " << player.m_cards.calculateValue();
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
std::string Player::getName() const {
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

/*
* add a card to the players deck
*/
void Player::recieveCard(const Kaart& kaart) {
	m_cards.addCard(kaart);
}

/*
* add the cards from a deck to the players deck
*/
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