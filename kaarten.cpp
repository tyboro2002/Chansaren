#include "Kaarten.h"

const std::vector<std::string> Kaart::unicode_chars{ "♠", "♥", "♣", "◆" };

/*
* print a card to the output stream
*/
std::ostream& operator<<(std::ostream& os, const Kaart& kaart) {
	os << Kaart::unicode_chars[kaart.m_symbol] << kaart.m_kleur;
	return os;
}

/*
* check if card is exact the same
*/
bool Kaart::operator==(const Kaart& other) const {
	return m_value == other.m_value && m_symbol == other.m_symbol;
}

/*
* check if 2 cards are different
*/
bool Kaart::operator!=(const Kaart& other) const {
	return m_value != other.m_value || m_symbol != other.m_symbol;
}

/*
* check if the value of a card is higer than the other card
*/
bool Kaart::operator>(const Kaart& other) const {
	return m_kleur > other.m_value;
}

/*
* check if the value of a card is lower than the other card
*/
bool Kaart::operator<(const Kaart& other) const {
	return m_kleur < other.m_value;
}

Kaart Kaart::operator=(const Kaart & other) { 
	m_value = other.m_value;
	m_symbol = other.m_symbol;
	m_kleur = other.m_kleur;
	m_on_top = other.m_on_top.value();
}

/*
* add a card to the deck
*/
void Deck::addCard(const Kaart& card) {
	m_cards.push_back(card);
}

/*
* mergeBack 2 decks into 1 deck (merging in the first deck)
*/
void Deck::mergeBack(const Deck& otherDeck) {
	Deck tempDeck = otherDeck;
	for (int i=0; i<tempDeck.m_cards.size(); i++){
		m_cards.push_back(tempDeck.m_cards.at(i));
	}
}

/*
* peek the card at the index (dont remove it)
*/
const Kaart& Deck::peekCardAtIndex(const int index) {
	return m_cards.at(index);
}

/*
* peek the card at the first index (dont remove it)
*/
const Kaart& Deck::peekFirst() {
	return m_cards.front();
}

/*
* peek the card at the last index (dont remove it)
*/
const Kaart& Deck::peekLast() {
	return m_cards.back();
}

/*
* pop the card at the first index (remove it)
*/
const Kaart& Deck::popFirst() {
	const Kaart & temp = peekFirst();
	m_cards.pop_front();
	return temp;
}

/*
* pop the card at the last index (remove it)
*/
const Kaart& Deck::popLast() {
	const Kaart& temp = peekLast();
	m_cards.pop_back();
	return temp;
}

/*
* get the numerical value of a card
*/
const int Kaart::getValue() const {
	return m_value;
}

bool Kaart::cardOnTop() const {
	if (m_on_top.has_value()) {
		return true;
	}
	return false;
}

Kaart& Kaart::getCardOnTop() const {
	if (Kaart::cardOnTop()) {
		Kaart k(m_on_top.value());
		return k;
	}
	std::string error("No card on top gie stoemerik");
	throw error;
}

/****************************************************
*
*				  deck functions
*
****************************************************/

/*
* calculate the value of a deck
*/
const int Deck::calculateValue() const{
	int score = 0;
	for(Kaart card: m_cards){
		int tempScore = card.getValue();
		Kaart temp = card;
		while (temp.cardOnTop()) {
			tempScore *= temp.getCardOnTop().getValue();
			if (temp.getCardOnTop().cardOnTop()) {
				temp = temp.getCardOnTop();
			}
		}
		score += tempScore;
	}
	return score;
}

/*
* pop the cards at the n last index (remove it)
*/
const Deck& Deck::popNLast(int number_of_cards = 1) {
	Deck fullDeck;
	for(int i = 0; i < number_of_cards; i++){
		fullDeck.addCard(popLast());
	}
	return fullDeck;
}

/*
* pop the cards at the n first index (remove it)
*/
const Deck& Deck::popNFirst(int number_of_cards = 1) {
	Deck fullDeck;
	for (int i = 0; i < number_of_cards; i++) {
		fullDeck.addCard(popFirst());
	}
	return fullDeck;
}

/*
* create n decks of shuffeld cards (n decks means n*52 cards)
*/
Deck& Deck::full(int number_of_decks = 1) {
	std::vector<Kaart> fullDeckVector;
	for (int decks = 0; decks < number_of_decks; decks++) {
		for (int symbols = 0; symbols < 4; symbols++) {
			for (int values = 1; values < 14; values++) {
				Kaart card((Number)values, (Symbol)symbols, (Colour)(symbols % 2));
				fullDeckVector.push_back(std::move(card));
			}
		}
	}
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(fullDeckVector), std::end(fullDeckVector), rng);
	Deck fullDeck;
	for (int i = 0; i < fullDeckVector.size(); i++) {
		fullDeck.addCard(fullDeckVector[i]);
	}
	return fullDeck;
}

/*
* check if deck is exact the same value
*/
bool Deck::operator==(const Deck& other) const {
	return calculateValue() == other.calculateValue();
}

/*
* check if 2 decks are different value
*/
bool Deck::operator!=(const Deck& other) const {
	return calculateValue() != other.calculateValue();
}

/*
* check if the value of a deck is higer than the other deck
*/
bool Deck::operator>(const Deck& other) const {
	return calculateValue() > other.calculateValue();
}

/*
* check if the value of a deck is lower than the other deck
*/
bool Deck::operator<(const Deck& other) const {
	return calculateValue() < other.calculateValue();
}