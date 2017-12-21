//
// Created by BEDNARSKIJ on 14.12.2017.
//

#include <stdlib.h>
#include <string.h>


typedef struct Player {
    char *name;
    int order;
} Player;

typedef struct PlayerList {
    int size;
    Player players[0];
} PlayerList;

PlayerList *playerList_initialize(int count) {
    PlayerList *list = malloc(sizeof(PlayerList) + count * sizeof(Player));
    list->size = count;
}

void playerList_destruct(PlayerList* playerList) {
    for(int i = 0; i < playerList->size; i++) {
        if(playerList->players[i].name) {
            free(playerList->players[i].name);
        }
    }
    free(playerList);
}

void playerList_initializePlayer(PlayerList *playerList, int i, char *name) {
    playerList->players[i].name = malloc(strlen(name) + 1);
    strcpy(playerList->players[i].name, name);
}

void playerList_setPlayerOrder(PlayerList *playerList, int i, int order) {
    playerList->players[i].order = order;
}

Player *playerList_getPlayer(PlayerList *playerList, int i) {
    return &playerList->players[i];
}
