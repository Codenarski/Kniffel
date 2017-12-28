//
// Created by BEDNARSKIJ on 14.12.2017.
//

#ifndef KNIFFEL3_PLAYER_H
#define KNIFFEL3_PLAYER_H

#include "Scorecard.h"

typedef struct Player {
    char *name;
    Scorecard *scorecard;
} Player;

typedef struct PlayerList {
    int size;
    Player players[0];
} PlayerList;

PlayerList *init_playerList(int amountOfPlayers);

void setPlayerName(Player *player, char *name);
void destruct_playerList(PlayerList *playerList);

#endif //KNIFFEL3_PLAYER_H
