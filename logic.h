#pragma once
#include <vector>
#include "kaart.h"
#include "Player.h"

/*
* // implemented
* 2 ==> verdubele
* dubbele 7 ==> pakjes wiselen
* zot ==> kaart bove pak
* 3 zesen ==> alle personen dood van de andere personen
* kleinst opeenvolgend ==> wine
* enkel aas ==> zekere winst
* dubbele ==> kaart
* 
* // not yet implemented
* heer en dame==> extra kaarte
*/

bool checkOnlyAce(const Deck& deck);
bool checkMoreThanNSeven(std::vector<Player> m_players, int n);
int getDoubleCount(const Deck& deck);
bool checkAllConsecutive(const Deck& deck);
int countJacks(const Deck& deck);
int countNotUsedTwo(const Deck* deck);
int lowestVal(const Deck& deck);
bool checkAllSingle(std::vector<Player> m_players);
bool checkAllSingleAndFollowingUp(std::vector<Player> m_players);
void loopDecks(std::vector<Player>& players, bool clockwise);
void killAllHumans(std::vector<Player>& players);
bool checkTripleSix(const Deck& deck);
int askForCardIndex(const Deck& deck);
int countValue(const Deck& deck, int value);
int countValue(std::vector<Player>& players, int value);
bool checkKingQueenRule(std::vector<Player>& players);