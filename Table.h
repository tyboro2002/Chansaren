#pragma once
#include <map>
#include <string>
#include "Kaart.h"
#include <vector>
#include "Player.h"
#include <iostream>
#include "logic.h"

class Table {
	std::vector<Player> m_players;
	std::vector<Player> m_onTheTable;
	int m_playerCount = 0;
	int m_playingPlayer = 0;
public:
	Table();
	Table(std::vector<std::string> names, const int number_of_decks);
	Table(std::vector<Player> spelers);
	Table(std::vector<Player> spelers, std::vector<Player> onTheTable);
	friend std::ostream& operator<<(std::ostream& os, const Table& table);
	void stepTable(bool printTable, bool full_automatic);
	void nextRound(bool printTable = true, int numberOfCards = 1, bool full_automatic = false);
	std::vector<Player>& getPlayers();
	bool checkGameOver();
	Player& giveWinner();
private:
	void checkForDeadPlayers();
	void takeTopCardFromOpponents(int my_index);
	int checkRules(int sevensNeeded = 2, bool full_automatic = false);
	const std::vector<int> checkWinner();
	void letIndexedPlayersLayExtraCard(std::vector<int> indexes, int numberOfCards);
};