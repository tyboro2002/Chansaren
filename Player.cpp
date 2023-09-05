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
* copy constructor of the player
*/
Player::Player(const Player& other) : m_name(other.m_name) {
	// Deep copy of the player's deck
	for (int i = 0; i < other.m_cards.numberOfCards(); i++) {
		const Kaart& card = other.m_cards.peekCardAtIndex(i);
		if (card.cardOnTop()) {
			// If the card has a card on top, create a new card with the same attributes
			Kaart copiedCard((Number)card.getValue(), card.getSymbol());
			m_cards.addCard(copiedCard);
			// Update the m_on_top pointer to point to the corresponding card in the new deck
			if (card.getCardOnTop()->getValue() == card.getCardOnTop()->getValue()) {
				for (int k = 0; k < m_cards.numberOfCards(); k++) {
					const Kaart& c = m_cards.peekCardAtIndex(k);
					if (c.getValue() == card.getCardOnTop()->getValue() && c.getSymbol() == card.getCardOnTop()->getSymbol()) {
						m_cards.getCardAtIndex(m_cards.numberOfCards()-1)->layCardOnTop(m_cards.getCardAtIndex(k));
					}
				}
			}
		}
		else {
			// If the card doesn't have a card on top, simply copy it
			m_cards.addCard(card);
		}
	}
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