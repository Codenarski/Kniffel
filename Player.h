#ifndef KNIFFEL3_PLAYER_H
#define KNIFFEL3_PLAYER_H
#include "Scorecard.h"

//Struct zur Speicherung der Spielerinformationen
typedef struct Player {
    char *name;
    Scorecard *scorecard;
} Player;

//Struct für die Liste aller Spieler, da Array zu Pointer Decayen, muss die Größe immer als seperates Attribut mitgeführt werden
typedef struct PlayerList {
    int size;
    Player players[0];
} PlayerList;


//Vorwärtsdeklaration der Funktionen des Players, die nach außen hin sichtbar sein müssen
PlayerList *initializePlayerList(int amountOfPlayers);
void setPlayerName(Player *player, char *name);

void destructPlayerList(PlayerList *playerList);

void printCurrentScoreboard(Player *player);

void printRemainingScoreboardEntries(Player *player);

#endif //KNIFFEL3_PLAYER_H
