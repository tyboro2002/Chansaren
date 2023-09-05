#pragma once
#include <vector>
#include "kaart.h"
#include "Player.h"

/*
* // implemented
* 2==> verdubele
* 
* // not yet implemented
* dubbele 7==> pakjes wiselen
* zot ==> kaart bove pak
* 3 zesen ==> alle personen dood van de andere personen
* enkel aas ==> zekere winst
* kleinst opeenvolgend==> wine
* dubbele ==> kaart
* heer en dame==> extra kaarte
*/
bool checkOnlyAce(const Deck& deck);
bool checkDoubleSeven(std::vector<Player> m_players);
int getDoubleCount(const Deck& deck);
bool checkAllConsecutive(const Deck& deck);
int countJacks(const Deck& deck);
int countNotUsedTwo(const Deck* deck);
int lowestVal(const Deck& deck);
bool checkAllSingle(std::vector<Player> m_players);
bool checkAllSingleAndFollowingUp(std::vector<Player> m_players);
void loopDecks(std::vector<Player> m_players, bool clockwise);