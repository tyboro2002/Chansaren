// Chansaren.cpp : Defines the entry point for the application.
//

#include "Chansaren.h"
#include "Table.h"
#include "logic.h"

using namespace std;

int main(){
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
	//kaart = Kaart(FOUR, Diamonds);
	//deck.addCard(kaart);
	for (int i = 0; i < deck.numberOfCards(); i++) {
		std::cout << deck.peekCardAtIndex(i) << std::endl;
	}
	cout << deck.calculateValue() << endl;
	for (int i = 0; i < deck.numberOfCards(); i++) {
		std::cout << deck.peekCardAtIndex(i) << std::endl;
	}
	*/

	
	//Table table;
	std::vector<string> names = {"tybo", "jarno"};
	while (true) {
		Table table = Table(names, 1);
		table.stepTable();
		//cout << table;
		cout << endl;
	}
	/*
	for (Player player : table.getPlayers()) {
		std::cout << player << endl;
	}
	*/
	return 0;
}
