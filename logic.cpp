#include "logic.h"

/*
* check if a deck only has 1 card and that card is an ace
*/
bool checkOnlyAce(const Deck& deck){
	if (deck.numberOfCards() != 1) return false;
	if (deck.peekCardAtIndex(0).getValue() != 1) return false;
	return true;
}

/*
* check if there are more than n sevens on the total table
*/
bool checkMoreThanNSeven(std::vector<Player> m_players, int n) {
	int sevens = 0;
	for (Player player : m_players) {
		Deck playerDeck = player.getCards();
		for (int i = 0; i < playerDeck.numberOfCards(); i++) {
			if (playerDeck.peekCardAtIndex(i).getValue() == 7/* && playerDeck.peekCardAtIndex(i).getUsed() == false*/) sevens++;
		}
	}
	return sevens >= n;
}

/*
* count the amount of double cards
* (a double card is a card that has another card with the same value in the deck)
*/
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

/*
* check if all cards are following on each other
*/
bool checkAllConsecutive(const Deck& deck) {
	if (deck.numberOfCards() <= 1) return false;
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

/*
* count the amount of jacks
* return 0 if none found
* return amount if there are found
*/
int countJacks(const Deck& deck) {
	int jacks = 0;
	for (int i = 0; i < deck.numberOfCards(); i++) {
		if (deck.peekCardAtIndex(i).getValue() == JACK) jacks++;
	}
	return jacks;
}

/*
* count all cards with the value 2 that not have multiplier 0
*/
int countNotUsedTwo(const Deck* deck) {
	int two = 0;
	for (int i = 0; i < deck->numberOfCards(); i++) {
		if (deck->peekCardAtIndex(i).getValue() == TWO && deck->peekCardAtIndex(i).cardOnTop() == false) two++;
	}
	return two;
}

/*
* returns the lowest value of a card in the deck
*/
int lowestVal(const Deck& deck) {
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

	// If all values are consecutive, return true
	return cards[0].getValue();
}

/*
* check if all players have only 1 card on the table
*/
bool checkAllSingle(std::vector<Player> m_players) {
	for (int i = 0; i < m_players.size(); i++) {
		if (m_players.at(i).getCards().numberOfCards() != 1) return false;
	}
	return true;
}

/*
* check if all players have only 1 card on the table and all these cards are following on each other 
*/
bool checkAllSingleAndFollowingUp(std::vector<Player> m_players) {
	if (!checkAllSingle(m_players)) return false;
	Deck stapel;
	for (int i = 0; i < m_players.size(); i++) {
		stapel.mergeBack(m_players.at(i).getCards());
	}
	if (!checkAllConsecutive(stapel)) return false;
	return true;
}

/*
 * Loop the decks of the players around in the given direction:
 * Give the deck of player A to player B, B to C, and C back to player A.
 */
void loopDecks(std::vector<Player>& players, bool clockwise) {
	if (players.size() < 2) {
		return;  // Need at least 2 players for this operation.
	}
	if (!clockwise) {
		for (int i = 1; i < players.size(); i++) {
			players.at(i - 1).swapDecks(players.at(i));
		}
	}
	else {
		for (int i = players.size() - 1; i > 0; i--) {
			players.at(i).swapDecks(players.at(i-1));
		}
	}
}

/*
* kill all cards that are Jack, Queen, King in all decks on the table
*/
void killAllHumans(std::vector<Player>& players) {
	for (Player& player : players) {
		Deck& playerDeck = player.getCards();
		playerDeck.filterValue(JACK);
		playerDeck.filterValue(QUEEN);
		playerDeck.filterValue(KING);
	}
}

/*
* check if there are 3 or more cards with a value of 6 in your deck
*/
bool checkTripleSix(const Deck& deck) {
	int six = 0;
	for (int i = 0; i < deck.numberOfCards(); i++) {
		if (deck.peekCardAtIndex(i).getValue() == SIX) six++;
	}
	return six >= 3;
}

/*
* ask the player for the index of a card in there deck
* returns the index of the card
* (uses some checks so this function cant return invalid values)
*/
int askForCardIndex(const Deck& deck) {
	int index;
	for (int i = 0; i < deck.numberOfCards(); i++) {
		cout << i << ") " << deck.peekCardAtIndex(i) << endl;
	}
	cout << "what index do you want?: ";
	std::cout.flush();
	while (!(std::cin >> index) || index >= deck.numberOfCards() || index<0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
		std::cout << "what index do you want?: ";
		std::cout.flush();
	}
	return index;
}


/*
* count the amount of a card in a deck
*/
int countValue(const Deck& deck, int value) {
	int am = 0;
	for (int i = 0; i < deck.numberOfCards(); i++) {
		if (deck.peekCardAtIndex(i).getValue() == value) am++;
	}
	return am;
}

/*
* count the amount of a card on the table
*/
int countValue(std::vector<Player>& players, int value) {
	int am = 0;
	for (Player player : players) {
		Deck& playerDeck = player.getCards();
		for (int i = 0; i < playerDeck.numberOfCards(); i++) {
			if (playerDeck.peekCardAtIndex(i).getValue() == value) am++;
		}
	}
	return am;
}


bool checkKingQueenRule(std::vector<Player>& players) {
	for (size_t i = 0; i < players.size(); i++) {
		Deck deck1 = players[i].getCards();

		for (size_t j = i + 1; j < players.size(); j++) {
			Deck deck2 = players[j].getCards();

			bool kingInDeck1 = false;
			bool queenInDeck2 = false;

			for (int k = 0; k < deck1.numberOfCards(); k++) {
				Kaart card = deck1.peekCardAtIndex(k);

				if (card.getValue() == KING) {
					kingInDeck1 = true;
				}
			}

			for (int k = 0; k < deck2.numberOfCards(); k++) {
				Kaart card = deck2.peekCardAtIndex(k);

				if (card.getValue() == QUEEN) {
					queenInDeck2 = true;
				}
			}

			if (kingInDeck1 && queenInDeck2) {
				return true;
			}

			bool queenInDeck1 = false;
			bool kingInDeck2 = false;

			for (int k = 0; k < deck1.numberOfCards(); k++) {
				Kaart card = deck1.peekCardAtIndex(k);

				if (card.getValue() == QUEEN) {
					queenInDeck1 = true;
				}
			}

			for (int k = 0; k < deck2.numberOfCards(); k++) {
				Kaart card = deck2.peekCardAtIndex(k);

				if (card.getValue() == KING) {
					kingInDeck2 = true;
				}
			}

			if (queenInDeck1 && kingInDeck2) {
				return true;
			}
		}
	}

	return false; // Return false if no King and Queen in different decks were found
}
