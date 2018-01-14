//
// Created by BEDNARSKIJ on 14.12.2017.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Player.h"


void initPlayer(Player *player) {
    player->scorecard = initializeScorecard();
}

PlayerList *init_playerList(int amountOfPlayers) {
    PlayerList *list = malloc(sizeof(PlayerList) + amountOfPlayers * sizeof(Player));
    list->size = amountOfPlayers;
    for (int i = 0; i < amountOfPlayers; ++i) {
        initPlayer(&list->players[i]);
    }
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

void setPlayerName(Player *player, char *name) {
    player->name = malloc(strlen(name) + 1);
    strcpy(player->name, name);
}

void printCurrentScoreboard(Player *player) {
    for (int i = 0; i < player->scorecard->size; ++i) {
        printf("%d: %s, Value: %d \n", i + 1, player->scorecard->entries[i].name, player->scorecard->entries[i].value);
    }
}


