#include "Table.h"

std::vector<Player> Table::getPlayers() {
	return m_players;
}

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
	/*
	for (Player player : m_players) {
		std::cout << player << endl;
	}
	*/
	/*
	for (int i = 0; i < 52; i++) {
		std::cout << fullDeck.peekCardAtIndex(i) << std::endl;
	}
	*/
}


Table::Table(std::vector<string> names, const int number_of_decks = 1) {
	m_playerCount = names.size();
	for (string str : names) {
		Player speler = Player(str);
		m_players.push_back(speler);
		m_onTheTable.push_back(speler); //TODO test if this is posible or other player needs to be maked
	}
	Deck fullDeck;
	Deck::full(&fullDeck, number_of_decks);
	std::vector<Deck> decks(m_playerCount);
	fullDeck.splitDeckIntoNDecks(&decks);
	for (int i = 0; i < m_playerCount; i++) {
		m_players.at(i).recieveDeck(decks.at(i));
	}
	/*
	for (Player player : m_players) {
		std::cout << player << endl;
	}
	*/
}


/*
* print a table to the outputstream
*/
std::ostream& operator<<(std::ostream& os, const Table& table) {
	os << "the table has " << table.m_playerCount << " players" << endl;
	os << "the cards on the table are: " << endl;
	for (Player player : table.m_onTheTable) {
		os << player << endl;
	}
	return os;
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

	for (int i = 0; i < m_playerCount; i++) {
		Deck tempDeck;
		m_players.at(i).layNFirstCards(tempDeck, numberOfCards);
		m_onTheTable.at(i).recieveDeck(tempDeck);
	}

	checkRules();

	vector<int> winnerIndexes = checkWinner();
	cout << m_players.at(winnerIndexes.at(0)).getName() << endl;

	if (winnerIndexes.size() == 1) {
		int winnerIndex = winnerIndexes.at(0);
		Deck collected;
		for (int i = 0; i < m_playerCount; i++) {
			collected.mergeBack(m_onTheTable.at(i).getCards());
		}
		m_players.at(winnerIndex).recieveDeck(collected);
		for (int i = 2; i < m_playerCount; i++) {
			m_onTheTable.at(i).clearCards();
		}
	}
	else {
		cout << "a draw occured between players: " << endl;
		for (int index : winnerIndexes) {
			cout << "player: " << m_players.at(index).getName() << endl;
		}
	}
	
}

/*
* check the rules and ask and aply them until nothing more needed
*/
void Table::checkRules() {
	for (int i = 0; i < m_playerCount; i++) {
		int unusedTwo = countNotUsedTwo(m_onTheTable.at(i).getCards());
		if (unusedTwo) {
			Deck* tafelStapel = m_onTheTable.at(i).getCardsPointer();
			Kaart kaart = m_players.at(i).getCardsPointer()->popFirst(); //TO FIX this object is temporary so deleted if function ends
			for (int k = 0; k < tafelStapel->numberOfCards(); k++) {
				if (tafelStapel->peekCardAtIndex(k).getValue() == 2 && tafelStapel->peekCardAtIndex(k).cardOnTop() == false) {
					tafelStapel->layCardOnIndex(&kaart, k);
					tafelStapel->addCard(kaart);
					break;
				}
			}
		}
	}
	//TODO
}


/*
* checks the index of the winning player(s)
*/
const vector<int> Table::checkWinner() {
	// TODO check for special winning rules
	// (multiple consecutive players but of different lengths)

	bool ignoreValuesCons = false;
	bool ignoreValuesAce = false;
	bool singlesFolowing = checkAllSingleAndFollowingUp(m_onTheTable);

	int winnerValue = 0;
	if (!singlesFolowing) {
		for (int i = 0; i < m_playerCount; i++) {
			Deck stapel = m_onTheTable.at(i).getCards();
			int curVal = stapel.calculateValue();
			if (checkAllConsecutive(stapel)) ignoreValuesCons = true;
			if (checkOnlyAce(stapel)) ignoreValuesAce = true;
			if (curVal > winnerValue) {
				winnerValue = curVal;
			}
		}
	}
	/*
	cout << "ignoreValuesCons: " << ignoreValuesCons << endl;
	cout << "ignoreValuesAce: " << ignoreValuesAce << endl;
	cout << "singlesFolowing: " << singlesFolowing << endl;
	*/
	vector<int> winnerVector;
	if (!(ignoreValuesAce || ignoreValuesCons || singlesFolowing)) {
		for (int i = 0; i < m_playerCount; i++) {
			int curVal = m_onTheTable.at(i).getCards().calculateValue();
			if (curVal == winnerValue) winnerVector.push_back(i);
		}
		return winnerVector;
	}
	if(ignoreValuesAce){
		for (int i = 0; i < m_playerCount; i++) {
			if (checkOnlyAce(m_onTheTable.at(i).getCards())) winnerVector.push_back(i);
		}
		return winnerVector;
	}
	if (singlesFolowing) {
		int lowestCons = 999;
		for (int i = 0; i < m_playerCount; i++) {
			Deck stapel = m_onTheTable.at(i).getCards();
			if (lowestVal(stapel) < lowestCons) lowestCons = lowestVal(stapel);
		}
		for (int i = 0; i < m_playerCount; i++) {
			Deck stapel = m_onTheTable.at(i).getCards();
			if (lowestVal(stapel) == lowestCons) winnerVector.push_back(i);
		}
		return winnerVector;
	}
	if (ignoreValuesCons) {
		int lowestCons = 999;
		for (int i = 0; i < m_playerCount; i++) {
			Deck stapel = m_onTheTable.at(i).getCards();
			if (checkAllConsecutive(stapel)) {
				if (lowestVal(stapel) < lowestCons) lowestCons = lowestVal(stapel);
			}
		}
		for (int i = 0; i < m_playerCount; i++) {
			Deck stapel = m_onTheTable.at(i).getCards();
			if (checkAllConsecutive(stapel)) {
				if (lowestVal(stapel) == lowestCons) winnerVector.push_back(i);
			}
		}
		return winnerVector;
	}
}