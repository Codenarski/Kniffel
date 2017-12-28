//
// Created by BEDNARSKIJ on 14.12.2017.
//

#include <stdlib.h>
#include <string.h>
#include "Player.h"


PlayerList *init_playerList(int count) {
    PlayerList *list = malloc(sizeof(PlayerList) + count * sizeof(Player));
    list->size = count;
    return list;
}

void destruct_playerList(PlayerList *playerList) {
    for(int i = 0; i < playerList->size; i++) {
        if(playerList->players[i].name) {
            free(playerList->players[i].name);
        }
    }
    free(playerList);
}

void init_playerName(Player *player, char *name) {
    player->name = malloc(strlen(name) + 1);
    strcpy(player->name, name);
}

Player *playerList_getPlayer(PlayerList *playerList, int i) {
    return &playerList->players[i];
}
