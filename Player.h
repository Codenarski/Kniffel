//
// Created by BEDNARSKIJ on 14.12.2017.
//

#ifndef KNIFFEL3_PLAYER_H
#define KNIFFEL3_PLAYER_H
typedef struct Player Player;
typedef struct PlayerList PlayerList;

PlayerList *playerList_initialize(int count);
void playerList_destruct(PlayerList* playerList);
void playerList_initializePlayer(PlayerList *playerList, int i, char *name);
void playerList_setPlayerOrder(PlayerList *playerList, int i, int order);
Player *playerList_getPlayer(PlayerList *playerList, int i);
#endif //KNIFFEL3_PLAYER_H
