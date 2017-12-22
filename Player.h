//
// Created by BEDNARSKIJ on 14.12.2017.
//

#ifndef KNIFFEL3_PLAYER_H
#define KNIFFEL3_PLAYER_H

#include "Entity.h"

PlayerList *init_playerList(int count);

void destruct_playerList(PlayerList *playerList);

void init_playerName(Player *player, char *name);
void playerList_setPlayerOrder(PlayerList *playerList, int i, int order);
Player *playerList_getPlayer(PlayerList *playerList, int i);
#endif //KNIFFEL3_PLAYER_H
