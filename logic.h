#pragma once
#include <vector>
#include "kaart.h"
#include "Player.h"

bool checkOnlyAce(const Deck& deck);
bool checkDoubleSeven(std::vector<Player> m_players);
int getDoubleCount(const Deck& deck);