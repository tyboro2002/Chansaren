#include "Table.h"

#define MAX_CARDS_PER_ROUND 3
#define COMA_ROUNDS 3

std::vector<Player>& Table::getPlayers() {
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
	for (int i = 0; i < table.m_onTheTable.size()-1;i++) {
		os << "player has: " << table.m_players.at(i).getDeckSize() << " cards and player is ";
		if (table.m_players.at(i).getLivingStatus()) os << "alive." << endl;
		else os << "dead." << endl;
		os << table.m_onTheTable.at(i) << endl << endl;
	}
	os << "player has: " << table.m_players.at(table.m_onTheTable.size() - 1).getDeckSize() << " cards and player is ";
	if (table.m_players.at(table.m_players.size() - 1).getLivingStatus()) os << "alive." << endl;
	else os << "dead." << endl;
	os << table.m_onTheTable.at(table.m_onTheTable.size() - 1);
	return os;
}

void Table::stepTable(bool printTable = true) {
	int numberOfCards = 0;
	std::cout << "Enter number of cards: ";
	std::cout.flush();
	while (!(std::cin >> numberOfCards) || numberOfCards > MAX_CARDS_PER_ROUND || numberOfCards <= 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
		std::cout << "Enter a valid number, you can only enter a number from 1 to "<< MAX_CARDS_PER_ROUND <<"!" << std::endl;
		std::cout << "Enter number of cards: ";
		std::cout.flush();
	}
	nextRound(printTable, numberOfCards);
}

void Table::nextRound(bool printTable, int numberOfCards) {
	for (int i = 0; i < m_playerCount; i++) {
		if (m_players.at(i).getLivingStatus()) {
			Deck tempDeck;
			m_players.at(i).layNFirstCards(tempDeck, numberOfCards);
			m_onTheTable.at(i).recieveDeck(tempDeck);
		}
	}

	//std::cout << *this << endl;
	//if (printTable) std::cout << *this << endl << endl;
	checkRules();

	if (printTable) std::cout << *this << endl;
	vector<int> winnerIndexes = checkWinner();

	if (winnerIndexes.size() == 1) {
		cout << "the player named: " << m_players.at(winnerIndexes.at(0)).getName() << " won this round." << endl << endl;
		int winnerIndex = winnerIndexes.at(0);
		Deck collected;
		for (int i = 0; i < m_playerCount; i++) {
			collected.mergeBack(m_onTheTable.at(i).getCards());
		}
		m_players.at(winnerIndex).recieveDeck(collected);
		for (int i = 0; i < m_playerCount; i++) {
			m_onTheTable.at(i).clearCards();
		}
	}
	else if (winnerIndexes.size() == 0) {
		cout << "no winners found: " << endl;
		winnerIndexes = checkWinner();
		cerr << "this is not suposed to happen" << endl;
		cout << "TODO throw a nice error" << endl; //TODO this isnt suposed to happen so throw a nice error
		for (int i = 0; i < m_playerCount; i++) {
			m_onTheTable.at(i).clearCards();
		}
	}
	else {
		cout << "a draw occured between players: " << endl;
		for (int index : winnerIndexes) {
			cout << "player: " << m_players.at(index).getName() << endl;
		}
		Deck collected;
		for (int i = 0; i < m_playerCount; i++) {
			collected.mergeBack(m_onTheTable.at(i).getCards());
		}
		m_players.at(winnerIndexes.at(0)).recieveDeck(collected);
		cout << "TODO ask players for a new card" << endl; //TODO ask players for a extra card and recheck the rules
		for (int i = 0; i < m_playerCount; i++) {
			m_onTheTable.at(i).clearCards();
		}
	}
	//std::cout << *this << endl;
	checkForDeadPlayers();
}

/*
* check the rules and ask and aply them until nothing more needed
*/
void Table::checkRules(int sevensNeeded) {
	for (int i = 0; i < m_playerCount; i++) {
		Deck& stapel = m_onTheTable.at(i).getCards();
		if (checkTripleSix(stapel)) killAlHumansOfOpponents(m_onTheTable, i); //TODO make that when 2 players have 3 sixes that they both keep humans
	}
	if (checkMoreThanNSeven(m_onTheTable, sevensNeeded)) {
		//useTwoSevens(m_onTheTable);
		cout << "double seven occured looping the decks" << endl;
		loopDecks(m_onTheTable, true);
		checkRules(sevensNeeded+2);
	}
	for (int i = 0; i < m_playerCount; i++) {
		int unusedTwo = countNotUsedTwo(m_onTheTable.at(i).getCardsPointer());
		if (unusedTwo) {
			Deck* tafelStapel = m_onTheTable.at(i).getCardsPointer();
			for (int k = 0; k < tafelStapel->numberOfCards(); k++) {
				if (tafelStapel->peekCardAtIndex(k).getValue() == 2 && tafelStapel->peekCardAtIndex(k).cardOnTop() == false) {
					tafelStapel->addCard(m_players.at(i).getCardsPointer()->popFirst());
					tafelStapel->layCardOnIndex(tafelStapel->peekCardAtIndexNonConst(tafelStapel->numberOfCards()-1), k);
					checkRules(sevensNeeded);
					break;
				}
			}
		}
	}

	for (int i = 0; i < m_playerCount; i++) {
		Deck& tafelStapel = m_onTheTable.at(i).getCards();
		int jacks = countJacks(tafelStapel);
		while (jacks) {
			takeTopCardFromOpponents(i);
			jacks--;
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
			Deck& stapel = m_onTheTable.at(i).getCards();
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

void Table::takeTopCardFromOpponents(int my_index) {
	Player& ik = m_players.at(my_index);
	Deck afleg;
	for (int i = 0; i < m_playerCount; i++) {
		if (i != my_index) {
			m_players.at(i).layNFirstCards(afleg, 1);
		}
	}
	ik.getCards().mergeFront(afleg);
}


bool Table::checkGameOver() {
	int alive_players = 0;
	for (Player& player : m_players) {
		if (player.getLivingStatus()) alive_players++;
	}
	return alive_players == 1;
}

Player& Table::giveWinner() {
	for (Player& player : m_players) {
		if (player.getLivingStatus()) return player;
	}
}

/*
void Table::checkForDeadPlayers() {
	for (Player& player : m_players) {
		if (player.getDeckSize() == 0) {
			player.killPlayer();
		}
	}
}
*/

void Table::checkForDeadPlayers() {
	for (int i = 0; i < m_players.size(); ++i) {
		if (m_players[i].getDeckSize() == 0 && m_players[i].getComaCount() >= COMA_ROUNDS) {
			m_players.erase(m_players.begin() + i);  // Remove the dead player from m_players
			m_onTheTable.erase(m_onTheTable.begin() + i);  // Remove the corresponding player from m_onTheTable
			--m_playerCount;  // Decrement the player count
			--i;  // Decrement the index to recheck the current position
		}
		else if (m_players[i].getDeckSize() == 0) {
			m_players[i].IncreaseComaCount();
		}else {
			m_players[i].resetComaCount();
		}
	}
}