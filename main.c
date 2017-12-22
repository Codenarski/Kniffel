#include <stdio.h>
#include "Player.h"
#include "Die.h"

PlayerList *letUserSelectPlayer();

void letUserGivePlayerNames(const PlayerList *playerList);

void tellUserPlayerNames(const PlayerList *playerList);

int main() {
    printf("Welcome to Kniffel\n");
    PlayerList *playerList = letUserSelectPlayer();
    letUserGivePlayerNames(playerList);
    printf("\nStarting Kniffel with the following players\n");
    tellUserPlayerNames(playerList);

    Dice *dice = init_dice();

    for (int i = 0; i < 5; ++i) {
        printf("Dice[%d]: %d \n", i, dice->dice[i].value);
    }
    roll_dice(dice);

    return 0;
}

void letUserGivePlayerNames(const PlayerList *playerList) {
    char *name;
    for (int i = 0; i < playerList->size; ++i) {
        printf("Please enter name of player %d\n", i + 1);
        scanf("%s", &name);
        init_playerName(&playerList->players[i], &name);
    }

}

PlayerList *letUserSelectPlayer() {
    int amount;
    printf("Please enter the amount of players: ");
    //todo: Validation
    scanf("%d", &amount);
    return init_playerList(amount);
}

void tellUserPlayerNames(const PlayerList *playerList) {
    for (int i = 0; i < playerList->size; ++i) {
        printf("Name of Player %d: %s\n", i + 1, playerList->players[i].name);
    }

}
