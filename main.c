#include <stdio.h>
#include "Player.h"
#include "Die.h"
#include "Scorecard.h"

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
    roll_dice(dice);
    for (int i = 0; i < 5; ++i) {
        printf("Dice[%d]: %d \n", i, dice->dice[i].value);
    }
    Scorecard *scorecard = initializeScorecard();
    for (int j = 0; j < scorecard->size; ++j) {
        ScorecardEntry *entry = &scorecard->entries[j];

        //Todo: Remove Check
        printf("scorecard->entries[%d].name: %s \n", j, entry->name);
        printf("scorecard->entries[%d].description: %s \n", j, entry->description);
        printf("scorecard->entries[%d].value: %d \n", j, entry->value);
        printf("scorecard->entries[%d].calculation: %d \n", j, entry->calculation(dice));
    }
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
