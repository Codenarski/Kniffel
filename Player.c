#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Player.h"

//Initialisierung des Spielers
void initPlayer(Player *player) {
    player->scorecard = initializeScorecard();
}

/* Initialisierung der Liste aller Spieler
* @param Spieleranzahl
* @return Liste aller Spielern
*/
PlayerList *initializePlayerList(int amountOfPlayers) {
    PlayerList *list = malloc(sizeof(PlayerList) + amountOfPlayers * sizeof(Player));
    list->size = amountOfPlayers;
    for (int i = 0; i < amountOfPlayers; ++i) {
        initPlayer(&list->players[i]);
    }
    return list;
}

//Freigeben des Speichers der Spielerliste
void destructPlayerList(PlayerList *playerList) {
    for(int i = 0; i < playerList->size; i++) {
        if(playerList->players[i].name) {
            free(playerList->players[i].name);
        }
    }
    free(playerList);
}

/* Setzen des Spielernamens
* @param Spieler, Spielername
* @return none
*/
void setPlayerName(Player *player, char *name) {
    player->name = malloc(strlen(name) + 1);
    strcpy(player->name, name);
}

//Gibt die spielerspezifische Spielerkarte aus
void printCurrentScoreboard(Player *player) {
    printf("\nYour current Scoreboard\n");
    for (int i = 0; i < player->scorecard->size; ++i) {
        printf("%d: %s, Value: %d \n", i + 1, player->scorecard->entries[i].name, player->scorecard->entries[i].value);
    }
    printf("\n");
}

//Gibt die Einträge aus, die noch nicht bespielt worden sind
void printRemainingScoreboardEntries(Player *player) {
    printf("\nAvailable Entries\n");
    for (int i = 0; i < player->scorecard->size; ++i) {
        if (player->scorecard->entries[i].hasBeenPlayed == false) {
            printf("%d: %s - %s \n", i + 1, player->scorecard->entries[i].name,
                   player->scorecard->entries[i].description);
        }
    }
    printf("\n");
}


