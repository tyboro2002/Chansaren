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
	int m_playerCount = 0;
	int m_playingPlayer = 0;
public:
	Table();
};