#include "Table.h"

#define MAX_CARDS_PER_ROUND 3
#define COMA_ROUNDS 3

/*
* returns the player vector of the table
* (the vector of the players with the cards they have in their hand not the one with the cards they have on the table)
*/
std::vector<Player>& Table::getPlayers() {
	return m_players;
}

/*
* initialise a table
*/
Table::Table() {
	int number_of_players;
	std::cout << "Enter number of participants: ";
	std::cout.flush();
	while (!(std::cin >> number_of_players)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
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

/*
* initiate a table with players with the names given in the names vector
* use number_of_decks decks (52 cards) to distribute
*/
Table::Table(std::vector<std::string> names, const int number_of_decks = 1) {
	m_playerCount = names.size();
	for (std::string str : names) {
		Player speler = Player(str);
		m_players.push_back(speler);
		m_onTheTable.push_back(speler);
	}
	Deck fullDeck;
	Deck::full(&fullDeck, number_of_decks);
	std::vector<Deck> decks(m_playerCount);
	fullDeck.splitDeckIntoNDecks(&decks);
	for (int i = 0; i < m_playerCount; i++) {
		m_players.at(i).recieveDeck(decks.at(i));
	}
}

/*
* initiate a table with players
*/
Table::Table(std::vector<Player> spelers) {
	m_playerCount = spelers.size();
	m_players = spelers;
	m_playingPlayer = 0;

	std::vector<Player> tablePlayers;
	for (const Player& player : spelers) {
		// Create a new player with the same name and an empty deck
		Player newPlayer = Player(player.getName());
		// Add the new player to the new vector
		tablePlayers.push_back(newPlayer);
	}
	m_onTheTable = tablePlayers;
}

/*
* initiate a table with players
* the onTheTable vector is for the cards on the table
*/
Table::Table(std::vector<Player> spelers, std::vector<Player> onTheTable) {
	m_playerCount = spelers.size();
	m_players = spelers;
	m_playingPlayer = 0;
	m_onTheTable = onTheTable;
}

/*
* print a table to the outputstream
*/
std::ostream& operator<<(std::ostream& os, const Table& table) {
	os << "the table has " << table.m_playerCount << " players" << std::endl;
	os << "the cards on the table are: " << std::endl;
	for (int i = 0; i < table.m_onTheTable.size()-1;i++) {
		os << "player has: " << table.m_players.at(i).getDeckSize() << " cards and player is ";
		if (table.m_players.at(i).getLivingStatus()) os << "alive." << std::endl;
		else os << "dead." << std::endl;
		os << table.m_onTheTable.at(i) << std::endl << std::endl;
	}
	os << "player has: " << table.m_players.at(table.m_onTheTable.size() - 1).getDeckSize() << " cards and player is ";
	if (table.m_players.at(table.m_players.size() - 1).getLivingStatus()) os << "alive." << std::endl;
	else os << "dead." << std::endl;
	os << table.m_onTheTable.at(table.m_onTheTable.size() - 1);
	return os;
}

/*
* ask the players how many cards they want to be layed on the table this round and lays them on the table
*/
void Table::stepTable(bool printTable, bool full_automatic) {
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
	nextRound(printTable, numberOfCards, full_automatic);
}

/*
* lays numberOfCards cards on the table for each player
* when the player hasnt enough cards there just are less cards in his deck
*/
void Table::nextRound(bool printTable, int numberOfCards, bool full_automatic) {
	for (int i = 0; i < m_playerCount; i++) {
		if (m_players.at(i).getLivingStatus()) {
			Deck tempDeck;
			m_players.at(i).layNFirstCards(tempDeck, numberOfCards);
			m_onTheTable.at(i).recieveDeck(tempDeck);
		}
	}

	if (printTable) std::cout << *this << std::endl;
	int sevensNeeded = 2;
	startOfTable:
	sevensNeeded = checkRules(sevensNeeded, full_automatic);

	if (printTable) std::cout << *this << std::endl;
	std::vector<int> winnerIndexes = checkWinner();

	if (winnerIndexes.size() == 1) {
		std::cout << "the player named: " << m_players.at(winnerIndexes.at(0)).getName() << " won this round." << std::endl << std::endl;
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
		std::cout << "no winners found: " << std::endl;
		winnerIndexes = checkWinner();
		std::cerr << "this is not suposed to happen" << std::endl;
		std::cout << "TODO throw a nice error" << std::endl; //TODO this isnt suposed to happen so throw a nice error
		for (int i = 0; i < m_playerCount; i++) {
			m_onTheTable.at(i).clearCards();
		}
	}
	else {
		std::cout << "a draw occured between players: " << std::endl;
		for (int index : winnerIndexes) {
			std::cout << "player: " << m_players.at(index).getName() << std::endl;
		}
		letIndexedPlayersLayExtraCard(winnerIndexes, 1);
		goto startOfTable;
	}
	//std::cout << *this << endl;
	checkForDeadPlayers();
}

/*
* check the rules and ask and aply them until nothing more needed
* returns the amount of sevensNeeded
*/
int Table::checkRules(int sevensNeeded, bool full_automatic) {
	for (int i = 0; i < m_playerCount; i++) {
		Deck& stapel = m_onTheTable.at(i).getCards();
		if (checkTripleSix(stapel)) killAllHumans(m_onTheTable);
	}
	if (checkMoreThanNSeven(m_onTheTable, sevensNeeded)) {
		//useTwoSevens(m_onTheTable);
		std::cout << "double seven occured looping the decks" << std::endl;
		loopDecks(m_onTheTable, true);
		loopDecks(m_players, true);
		return checkRules(sevensNeeded+2, full_automatic);
	}
	for (int i = 0; i < m_playerCount; i++) {
		int unusedTwo = countNotUsedTwo(m_onTheTable.at(i).getCardsPointer());
		if (unusedTwo) {
			Deck* tafelStapel = m_onTheTable.at(i).getCardsPointer();
			for (int k = 0; k < tafelStapel->numberOfCards(); k++) {
				if (tafelStapel->peekCardAtIndex(k).getValue() == 2 && tafelStapel->peekCardAtIndex(k).cardOnTop() == false) {
					if (m_players.at(i).getDeckSize() > 0) { // make a player only lay a extra card on the 2 when it has cards
						tafelStapel->addCard(m_players.at(i).getCardsPointer()->popFirst());
						tafelStapel->layCardOnIndex(tafelStapel->peekCardAtIndexNonConst(tafelStapel->numberOfCards() - 1), k);
						return checkRules(sevensNeeded, full_automatic);
					}
					break;
				}
			}
		}
	}
	for (int i = 0; i < m_playerCount; i++) {
		int doubles = getDoubleCount(m_onTheTable.at(i).getCards());
		while (doubles) {
			for (int j = 0; j < m_playerCount; j++) {
				if (j != i) {
					std::cout << m_onTheTable.at(j).getName() << " giving to: " << m_onTheTable.at(i).getName() << std::endl;
					int selectedCard;
					if (full_automatic) {
						selectedCard = 0;
					}
					else {
						selectedCard = askForCardIndex(m_onTheTable.at(j).getCards());
					}
					if (m_onTheTable.at(j).getDeckSize() > 0) {
						Kaart kaart = m_onTheTable.at(j).popIndexed(selectedCard);
						m_onTheTable.at(i).recieveCard(kaart);
					}
				}
			}
			doubles--;
		}
	}

	if (checkKingQueenRule(m_onTheTable)) {
		std::cout << "king queen rule found" << std::endl;
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
	return sevensNeeded;
}


/*
* checks the index of the winning player(s)
*/
const std::vector<int> Table::checkWinner() {
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
	std::vector<int> winnerVector;
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

/*
* take a card from the top of each players hand and lay it on top of the player at my_index's hand
*/
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

/*
* check if there is only 1 alive player
*/
bool Table::checkGameOver() {
	int alive_players = 0;
	for (Player& player : m_players) {
		if (player.getLivingStatus()) alive_players++;
	}
	return alive_players == 1;
}

/*
* returns the winner of the game
* (returns the first alive player so when multiple players
* are alive this function defaults to the first one found)
*/
Player& Table::giveWinner() {
	for (Player& player : m_players) {
		if (player.getLivingStatus()) return player;
	}
}


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

/*
* all the players whos index is in the vector will lay numberOfCards aditional cards on the table
* only lays extra cards for the player if player is alive
*/
void Table::letIndexedPlayersLayExtraCard(std::vector<int> indexes, int numberOfCards) {
	for (int i: indexes) {
		if (m_players.at(i).getLivingStatus()) {
			Deck tempDeck;
			m_players.at(i).layNFirstCards(tempDeck, numberOfCards);
			m_onTheTable.at(i).recieveDeck(tempDeck);
		}
	}
}