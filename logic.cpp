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
	return 0;
}