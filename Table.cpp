#include "Table.h"

Table::Table() {
	int number_of_players;
	std::cout << "Enter number of participants: ";
	std::cout.flush();
	while (!(std::cin >> number_of_players)) {
		std::cin.clear();
		std::cin >> std::ws;
		std::cout << "Enter a valid number!" << std::endl;
		std::cout << "Enter number of participants: ";
		std::cout.flush();
	}
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
			std::cin >> std::ws;
			std::cout << "Enter a valid number!" << std::endl;
			std::cout << "Enter number of decks: ";
			std::cout.flush();
		}
		if (number_of_decks < min_number_of_decks) {
			std::cout << "Not enough decks (min. " << min_number_of_decks << ")!" << std::endl;
			std::cin >> std::ws;
			std::cout << "Enter number of decks: ";
			std::cout.flush();
		}
	}

	Deck& fullDeck = Deck::full(number_of_decks);
	for (int i = 0; i < 52; i++) {
		std::cout << fullDeck.peekCardAtIndex(i) << std::endl;
	}
}