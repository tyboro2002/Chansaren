#include "Table.h"

Table::Table() {
	int number_of_players;
	std::cout << "Enter number of participants: ";
	std::cout.flush();
	while (!(std::cin >> number_of_players)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
		//std::cin >> std::ws;
		std::cout << "Enter a valid number!" << std::endl;
		std::cout << "Enter number of participants: ";
		std::cout.flush();
	}

	m_playerCount = number_of_players;
	int min_number_of_decks = 1;
	while (min_number_of_decks * 52 == 0) {
		min_number_of_decks++;
	}
	int number_of_decks = 0;
	std::cout << "Enter number of decks: ";
	std::cout.flush();
	while (number_of_decks < min_number_of_decks) {
		while (!(std::cin >> number_of_decks)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
			std::cout << "Enter a valid number!" << std::endl;
			std::cout << "Enter number of decks: ";
			std::cout.flush();
		}
		if (number_of_decks < min_number_of_decks) {
			std::cout << "Not enough decks (min. " << min_number_of_decks << ")!" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
			std::cout << "Enter number of decks: ";
			std::cout.flush();
		}
	}

	Deck fullDeck;
	Deck::full(&fullDeck, number_of_decks);

	std::string playerName;
	while (m_players.size() < number_of_players) {
		std::cout << "Enter name of player " << m_players.size() + 1 << ": ";
		while (!(std::cin >> playerName)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
			std::cout << "Enter a valid name!" << std::endl;
			std::cout << "Enter name of player " << m_players.size() + 1 << ": ";
			std::cout.flush();
		}
		Player speler = Player(playerName);
		m_players.push_back(speler);
		m_onTheTable.push_back(speler); //TODO test if this is posible or other player needs to be maked
	}
	std::vector<Deck> decks(number_of_players);
	fullDeck.splitDeckIntoNDecks(&decks);
	for (int i = 0; i < number_of_players; i++) {
		m_players.at(i).recieveDeck(decks.at(i));
	}
	for (Player player : m_players) {
		std::cout << player << endl;
	}
	/*
	for (int i = 0; i < 52; i++) {
		std::cout << fullDeck.peekCardAtIndex(i) << std::endl;
	}
	*/
}

void Table::stepTable() {
	int numberOfCards;
	std::cout << "Enter number of cards: ";
	std::cout.flush();
	while (!(std::cin >> numberOfCards)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
		std::cout << "Enter a valid number!" << std::endl;
		std::cout << "Enter number of cards: ";
		std::cout.flush();
	}
}