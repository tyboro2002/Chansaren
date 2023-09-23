#include "Kaart.h"

const std::vector<std::wstring> Kaart::unicode_chars{L"♠", L"♥", L"♣", L"◆"};

/*
* Assignment operator overload
*/
Kaart& Kaart::operator=(const Kaart& other) {
    if (this == &other) {
        return *this; // Avoid self-assignment
    }

    m_value = other.m_value;
    m_symbol = other.m_symbol;
    m_kleur = other.m_kleur;
	m_multiplier = other.m_multiplier; //TODO test if correct
    return *this;
}

/*
* print a card to the output stream
*/
std::wostream& operator<<(std::wostream& os, const Kaart& kaart) {
	os << Kaart::unicode_chars[kaart.m_symbol] << L" " << kaart.m_value;

	if (kaart.getValue() == NOTHING) {
		os << L" ei da mag nie" << std::endl;
	}

	if (kaart.isOnTopOfCard()) {
		os << L" has the Multiplier: " << kaart.getMultiplier();
	}

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

/*
* remove the card from the top of this card
*/
void Kaart::removeCardFromTop(Kaart& kaart) {
	m_multiplier = kaart.m_multiplier / 2;
	kaart.m_multiplier=1;
}

/*
* add a card to the top of this card
*/
void Kaart::layCardOnTop(Kaart& kaart) {
	kaart.m_multiplier = m_multiplier * 2;
	m_multiplier = 0;
}

/*
* get the numerical value of a card
*/
const int Kaart::getValue() const {
	return m_value;
}

/*
* get the numerical value of the multiplier of a card
*/
const int Kaart::getMultiplier() const {
	return m_multiplier;
}

/*
* get the symbol of a card
*/
const Symbol Kaart::getSymbol() const {
	return m_symbol;
}

/*
* check if a card has another card on top of it
*/
bool Kaart::cardOnTop() const {return m_multiplier == 0;}

/*
* check if a card is on top of another card
*/
bool Kaart::isOnTopOfCard() const {return m_multiplier >= 2;}


/****************************************************
*
*				  deck functions
*
****************************************************/

/*
* add a card to the deck
*/
void Deck::addCard(const Kaart& card) {
	m_cards.push_back(card);
}

/*
* clear all the cards from the deck
*/
void Deck::clearDeck() {
	m_cards.clear();
}

/*
* mergeBack 2 decks into 1 deck (merging in the first deck)
*/
void Deck::mergeBack(const Deck& otherDeck) {
	for (int i = 0; i < otherDeck.m_cards.size(); i++) {
		m_cards.push_back(otherDeck.m_cards.at(i));
	}
}

/*
* mergeFront 2 decks into 1 deck (merging in the first deck)
*/
void Deck::mergeFront(const Deck& otherDeck) {
	for (int i = 0; i < otherDeck.m_cards.size(); i++) {
		m_cards.push_front(otherDeck.m_cards.at(i));
	}
}

/*
* peek the card at the index (dont remove it)
* return a const kaart reference
*/
const Kaart& Deck::peekCardAtIndex(const int index) const{
	return m_cards.at(index);
}

/*
* peek the card at the index (dont remove it)
* return a kaart reference
*/
Kaart& Deck::peekCardAtIndexNonConst(const int index) {
	return m_cards.at(index);
}

/*
* get the card at the index (dont remove it)
*/
Kaart& Deck::getCardAtIndex(const int index){
	return m_cards.at(index);
}

/*
* return the card at the index and remove it from the deck
*/
Kaart Deck::popIndexed(int index) {
	Deck temp;
	while (index) {
		temp.addCard(Kaart(m_cards.front()));
		popFirst();
		index--;
	}
	Kaart tempCard = Kaart(m_cards.front());
	popFirst();
	mergeFront(temp);
	return tempCard;
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
	if (m_cards.empty()) {
		// Return a default empty card (you should define your own empty card)
		static Kaart emptyCard; // You need to define what an empty card means
		return emptyCard;
	}
	const Kaart& temp = peekFirst();
	m_cards.pop_front();
	return temp;
}

/*
* pop the card at the last index (remove it)
*/
const Kaart& Deck::popLast() {
	if (m_cards.empty()) {
		// Return a default empty card (you should define your own empty card)
		static Kaart emptyCard; // You need to define what an empty card means
		return emptyCard;
	}
	const Kaart& temp = peekLast();
	m_cards.pop_back();
	return temp;
}

/*
* assignement operator for a deck
*/
Deck& Deck::operator=(const Deck& other) {
	if (this == &other) {
		return *this; // Avoid self-assignment
	}
	// Copy data members from 'other' to 'this'
	m_cards = other.m_cards;
	return *this;
}

/*
* calculate the size of a deck
*/
const int Deck::numberOfCards() const {
	return m_cards.size();
}

/*
* calculate the value of a deck
*/
const int Deck::calculateValue() const{
	int score = 0;
	for(const Kaart& card : m_cards){
		score += (card.getValue()*card.getMultiplier());
	}
	return score;
}

/*
* pop the cards at the n last index (remove it)
*/
void Deck::popNLast(Deck& fullDeck, int number_of_cards = 1) {
	for (int i = 0; i < number_of_cards; i++) {
		if (m_cards.size() > 0) fullDeck.addCard(popLast());
	}
}

/*
* pop the cards at the n first index (remove it)
*/
void Deck::popNFirst(Deck& fullDeck, int number_of_cards = 1) {
	for (int i = 0; i < number_of_cards; i++) {
		if (m_cards.size() > 0) fullDeck.addCard(popFirst());
	}
}

/*
* create n decks of shuffeld cards (n decks means n*52 cards)
*/
void Deck::full(Deck* fullDeck, int number_of_decks = 1) {
	std::vector<Kaart> fullDeckVector;
	for (int decks = 0; decks < number_of_decks; decks++) {
		for (int symbols = 0; symbols < 4; symbols++) {
			for (int values = 1; values < 14; values++) {
				Kaart card((Number)values, (Symbol)symbols, (Colour)(symbols % 2));
				fullDeckVector.push_back(std::move(card));
			}
		}
	}
	std::random_device rd;
	std::default_random_engine rng(rd());
	std::shuffle(std::begin(fullDeckVector), std::end(fullDeckVector), rng);
	for (int i = 0; i < fullDeckVector.size(); i++) {
		fullDeck->addCard(fullDeckVector[i]);
	}
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

/*
* split this deck in to n decks in the vector that is given (n is size of decks vector) (consume the cards in this deck)
*/
void Deck::splitDeckIntoNDecks(std::vector<Deck>* decks) {
	Kaart kaart;
	int loops = numberOfCards();
	for (int i = 0; i < loops; i++) {
		kaart = popFirst();
		decks->at(i % decks->size()).addCard(kaart);
	}
}

/*
* print a deck to the output stream
*/
std::wostream& operator<<(std::wostream& os, const Deck& deck) {
	Kaart kaart;
	for (int i = 0; i < deck.numberOfCards(); i++) {
		kaart = deck.peekCardAtIndex(i);
		os << kaart << L"\n"; // Use L to denote wide string literals
	}
	return os;
}

/*
* switch the card at the index with the recieved card
*/
void Deck::replaceCardAtIndex(const int index, Kaart& kaart) {
	m_cards.at(index) = kaart;
}

/*
* lay a card on the indexed card
*/
void Deck::layCardOnIndex(Kaart& kaart, const int index) {
	Kaart& onderlegger = getCardAtIndex(index);
	onderlegger.layCardOnTop(kaart);
}

/*
* filter all cards out with the value
*/
void Deck::filterValue(const int value) {
	// Use an iterator to traverse the cards in the deck
	auto it = m_cards.begin();

	while (it != m_cards.end()) {
		// Check if the card's value matches the specified value
		if (it->getValue() == value) {
			//remove the card from the deck
			it = m_cards.erase(it);
		}
		else {
			++it; // Move to the next card
		}
	}
}