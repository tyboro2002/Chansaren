#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <algorithm>
#include <optional>

enum Symbol {
	Spades = 0,
	Hearts,
	Clubs,
	Diamonds
};

enum Colour {
	B = 0, R
};

enum Number {
	NOTHING = 0,
	ACE = 1,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING
};


class Kaart {
	Number m_value;
	Symbol m_symbol;
	Colour m_kleur;
	int m_multiplier = 1;
	//bool m_used = false;
	//Kaart* m_on_top = nullptr;
public:
	Kaart() : m_value(NOTHING), m_symbol(Hearts), m_kleur(R), m_multiplier(1) {}
	Kaart(Number number, Symbol symbol) : m_value(number), m_symbol(symbol), m_kleur((Colour)(symbol%2)), m_multiplier(1) {}
	Kaart(Number number, Symbol symbol, int multiplier) : m_value(number), m_symbol(symbol), m_kleur((Colour)(symbol % 2)), m_multiplier(multiplier) {}
	Kaart(Number number, Symbol symbol, Colour colour) : m_value(number), m_symbol(symbol), m_kleur(colour), m_multiplier(1) {}
	~Kaart() {};
	Kaart(const Kaart& other) : m_value(other.m_value), m_symbol(other.m_symbol), m_kleur(other.m_kleur), m_multiplier(other.m_multiplier)/*, m_used(other.m_used)*/ {}
	friend std::ostream& operator<<(std::ostream& os, const Kaart& kaart);
	bool operator==(const Kaart& other) const;
	bool operator!=(const Kaart& other) const;
	bool operator>(const Kaart& other) const;
	bool operator<(const Kaart& other) const;
	Kaart& operator=(const Kaart& other);
	static const std::vector<std::string> unicode_chars;
	const int getValue() const;
	const int getMultiplier() const;
	const Symbol getSymbol() const;

	bool cardOnTop() const;
	bool isOnTopOfCard() const;
	void layCardOnTop(Kaart& kaart);
	void removeCardFromTop(Kaart& kaart);
	//void useCard() { m_used = true; }
	//bool getUsed() const { return m_used; }
};

// List of cards
class Deck {
	std::deque<Kaart> m_cards;
public:
	Deck() = default;
	// Deep copy constructor
	Deck(const Deck& other) {
		for (int i = 0; i < other.m_cards.size(); i++) {
			const Kaart& originalCard = other.m_cards[i];
			Kaart copiedCard((Number)originalCard.getValue(), originalCard.getSymbol(), originalCard.getMultiplier()); // Create a deep copy of the card
			m_cards.push_back(copiedCard); // Add the deep copy to this Deck
		}
	}
	//Deck(const Deck& other) : m_cards(other.m_cards) {}
	Deck(Deck&& other) : m_cards(std::move(other.m_cards)) {}
	friend std::ostream& operator<<(std::ostream& os, const Deck& deck);
	static void full(Deck* fullDeck, int number_of_decks);
	void addCard(const Kaart& card);
	void clearDeck();
	void mergeBack(const Deck& otherDeck);

	const int numberOfCards() const;
	const int calculateValue() const;

	Deck& operator=(const Deck& other);
	bool operator==(const Deck& other) const;
	bool operator!=(const Deck& other) const;
	bool operator>(const Deck& other) const;
	bool operator<(const Deck& other) const;

	const Kaart & peekCardAtIndex(const int index) const;
	Kaart& peekCardAtIndexNonConst(const int index);
	Kaart* getCardAtIndex(const int index);
	const Kaart & peekFirst();
	const Kaart & peekLast();
	const Kaart & popFirst();
	const Kaart & popLast();
	void popNLast(Deck& fullDeck, int number_of_cards);
	void popNFirst(Deck& fullDeck, int number_of_cards);

	void splitDeckIntoNDecks(std::vector<Deck>* decks);
	void replaceCardAtIndex(const int index, Kaart& kaart);
	void layCardOnIndex(Kaart& kaart, const int index);
};