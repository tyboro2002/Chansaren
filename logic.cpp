#include "logic.h"

bool checkOnlyAce(const Deck& deck){
	if (deck.numberOfCards() != 1) return false;
	if (deck.peekCardAtIndex(0).getValue() != 1) return false;
	return true;
}

bool checkDoubleSeven(std::vector<Player> m_players) {
	int sevens = 0;
	for (Player player : m_players) {
		Deck playerDeck = player.getCards();
		for (int i = 0; i < playerDeck.numberOfCards(); i++) {
			if (playerDeck.peekCardAtIndex(i).getValue() == 7) sevens++;
		}
	}
	return sevens >= 2;
}

bool checkTripleSix(const Deck& deck) {
	int six = 0;
	for (int i = 0; i < deck.numberOfCards(); i++) {
		if (deck.peekCardAtIndex(i).getValue() == 7) six++;
	}
	return six >= 3;
}

int getDoubleCount(const Deck& deck) {
	int doubles = 0;
	std::vector<Kaart> cards;
	for (int i = 0; i < deck.numberOfCards(); i++) {
		cards.push_back(deck.peekCardAtIndex(i));
	}

	// Define the comparison function (cmp) using a lambda
	auto cmp = [](const Kaart& card1, const Kaart& card2) {
		// Compare the values of the two cards
		return card1.getValue() < card2.getValue();
	};

	sort(cards.begin(), cards.end(), cmp);
	
	Kaart* prevCard = nullptr;
	int i = 1;
	while (i<cards.size()){
		if (cards.at(i-1).getValue() == cards.at(i).getValue()) {
			doubles++;
			i++;
		}
		i++;
	}
	return doubles;
}

bool checkAllConsecutive(const Deck& deck) {
	int doubles = 0;
	std::vector<Kaart> cards;
	for (int i = 0; i < deck.numberOfCards(); i++) {
		cards.push_back(deck.peekCardAtIndex(i));
	}

	// Define the comparison function (cmp) using a lambda
	auto cmp = [](const Kaart& card1, const Kaart& card2) {
		// Compare the values of the two cards
		return card1.getValue() < card2.getValue();
		};

	sort(cards.begin(), cards.end(), cmp);

	// Iterate through 'cards' and check for consecutive values
	for (size_t i = 1; i < cards.size(); i++) {
		if (cards[i].getValue() != cards[i - 1].getValue() + 1) {
			// If the values are not consecutive, return false
			return false;
		}
	}

	// If all values are consecutive, return true
	return true;
}