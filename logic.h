#pragma once
#include <vector>
#include "kaart.h"
#include "Player.h"

/*
dubbele ==> kaart geven
zot ==> kaart bove pak
dubbele 7==> pakjes wiselen
3 zesen ==> alle personen dood van de andere personen
enkel aas ==> zekere winst
kleinst opeenvolgend==> wine
2==> verdubele
heer en dame==> extra kaarte
*/
bool checkOnlyAce(const Deck& deck);
bool checkDoubleSeven(std::vector<Player> m_players);
int getDoubleCount(const Deck& deck);
bool checkAllConsecutive(const Deck& deck);
int countJacks(const Deck& deck);
int countNotUsedTwo(const Deck& deck);
int lowestVal(const Deck& deck);
bool checkAllSingle(std::vector<Player> m_players);
bool checkAllSingleAndFollowingUp(std::vector<Player> m_players);