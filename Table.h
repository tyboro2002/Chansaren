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
	Table(std::vector<string> names, const int number_of_decks);
	friend std::ostream& operator<<(std::ostream& os, const Table& table);
	void stepTable(bool printTable);
	std::vector<Player> getPlayers();
private:
	void checkRules();
	const vector<int> checkWinner();
};