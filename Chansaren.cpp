// Chansaren.cpp : Defines the entry point for the application.
//

#include "Chansaren.h"
#include "Table.h"
#include "logic.h"
#include "tests.h"

#define RUN_TESTS 0 // Set to 1 to run tests, 0 to run the main program
#define FULL_AUTOMATIC 1 // set to 1 to do the full automatic game, 0 to 

#define PRINT_TABLE true
#define FULL_AUTOMATIC_AMOUNT 3 // define how many cards are layed each round in full automatic mode

using namespace std;

int main(){
#if RUN_TESTS
	TestRunner testRunner;
	return testRunner.runAutomatedTestCases();
#else
	/*
	Deck deck;
	Kaart kaart = Kaart(ACE, Spades);
	deck.addCard(kaart);
	kaart = Kaart(ACE, Clubs);
	deck.addCard(kaart);
	kaart = Kaart(SEVEN, Hearts);
	deck.addCard(kaart);
	kaart = Kaart(THREE, Spades);
	deck.addCard(kaart);
	kaart = Kaart(SIX, Spades);
	deck.addCard(kaart);
	kaart = Kaart(FOUR, Diamonds);
	deck.addCard(kaart);
	int i = askForCardIndex(deck);
	cout << "the player choose: " << i << endl;
	*/

	/*
	for (int i = 0; i < deck.numberOfCards(); i++) {
		std::cout << deck.peekCardAtIndex(i) << std::endl;
	}
	cout << deck.calculateValue() << endl;
	for (int i = 0; i < deck.numberOfCards(); i++) {
		std::cout << deck.peekCardAtIndex(i) << std::endl;
	}
	*/

	bool loop = true;

	while (loop) {
		//Table table;
		std::vector<string> names = { "tybo", "jarno", "mathis" };
		Table table = Table(names, 1);
		int round = 0;

		while (!table.checkGameOver()) {
			cout << "round " << round++ << " started" << endl;
			#if FULL_AUTOMATIC
				table.nextRound(PRINT_TABLE, FULL_AUTOMATIC_AMOUNT, FULL_AUTOMATIC);
			#else
				table.stepTable(PRINT_TABLE, FULL_AUTOMATIC);
			#endif
		}
		Player& winner = table.giveWinner();
		cout << "the game is won by: " << winner.getName() << " this player has " << winner.getDeckSize() << " cards after " << round << " rounds" << endl;
		//loop = false;
	}

	

	/*
	cout << table.getPlayers().at(0) << endl;
	cout << table.getPlayers().at(1) << endl;
	cout << table.getPlayers().at(2) << endl << endl << endl;
	killAlHumansOfOpponents(table.getPlayers(), 0);
	cout << table.getPlayers().at(0) << endl;
	cout << table.getPlayers().at(1) << endl;
	cout << table.getPlayers().at(2) << endl;
	*/

	//cout << table << endl;
	//table.nextRound(true, 3);
	//table.nextRound(true, 3);

	/*
	while (true) {
		table = Table(names, 1);
		//table.stepTable(true);
		table.nextRound(true,3);
		//cout << "this should print empty table" << endl;
		//cout << table << endl;
	}
	*/

	/*
	for (Player player : table.getPlayers()) {
		std::cout << player << endl;
	}
	*/
	return 0;
#endif
}
