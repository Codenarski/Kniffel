#include <stdio.h>
#include <stdlib.h>
#include "Player.h"

PlayerList *letUserSelectPlayer();
void letUserGivePlayerNames(const PlayerList *playerList);
void tellUserPlayerNames(const PlayerList *playerList);

void startGame(PlayerList *playerList);

void playRound(Player *player);

bool askUserToFinishRound(Dice *dice);

void letUserChooseScoreboardEntry(Player *player, Dice *dice);

void nextPlayer();

void letUserSelectDiceToSelect();

void showUserHisResult(Dice *dice);

ScorecardEntry *askUserWhichEntryHeWantsToFill(Player *player);

int main() {
    printf("Welcome to Kniffel\n");
    PlayerList *playerList = letUserSelectPlayer();
    letUserGivePlayerNames(playerList);
    printf("\nStarting Kniffel with the following players\n");
    tellUserPlayerNames(playerList);
    startGame(playerList);

    return 0;
}

void startGame(PlayerList *playerList) {
    for (int j = 0; j < playerList->players[0].scorecard->size; ++j) {
        for (int i = 0; i < playerList->size; ++i) {
            for (int k = 0; k < 3; ++k) {
                playRound(&playerList->players[i]);
            }
        }
    }
}

void playRound(Player *player) {
    Dice *dice = init_dice();
    roll_dice(dice);
    showUserHisResult(dice);
    if (askUserToFinishRound(dice)) {
        letUserChooseScoreboardEntry(player, dice);
    } else {
        letUserSelectDiceToSelect();
    }
}

void showUserHisResult(Dice *dice) {
    for (int i = 0; i < dice->size; ++i) {
        printf("Dice %d: %d \n", i + 1, dice->dice[i].value);
    }
}

bool askUserToFinishRound(Dice *dice) {
    printf("Do you want to finish your Round? (Yes/No)\n");
    char *decision = "";
    scanf("%s", &decision);
    //Todo: Crasht bei Eingabe "yes"
    return decision == "Yes" ? true : false;
}

void letUserSelectDiceToSelect() {
    printf("");
}

void nextPlayer() {

}

void letUserChooseScoreboardEntry(Player *player, Dice *dice) {
    printCurrentScoreboard(player);
    ScorecardEntry *entry = askUserWhichEntryHeWantsToFill(player);
    entry->value = entry->calculation(dice);
}

ScorecardEntry *askUserWhichEntryHeWantsToFill(Player *player) {
    long chosenScoreboard = -1;
    bool firstRunDone = false;
    do {
        if (firstRunDone) {
            printf("Sorry, the scoreboard you entered is invalid: %li\n", chosenScoreboard);
        }
        printf("Please enter the number of the row you want to put in your value\n");
        char *decision = "";
        scanf("%s", &decision);
        chosenScoreboard = strtol(decision, NULL, 10);
        firstRunDone = true;
    } while (scorecardDoesNotExist(chosenScoreboard) ||
             scorecardAlreadyPlayed(&player->scorecard->entries[chosenScoreboard]));
    return &player->scorecard->entries[chosenScoreboard];
}


void letUserGivePlayerNames(const PlayerList *playerList) {
    // TODO: Bug, crasht wenn sich die namenslaenger aendert
    for (int i = 0; i < playerList->size; ++i) {
        char *name;
        printf("Please enter name of player %d\n", i + 1);
        scanf("%s", &name);
        setPlayerName(&playerList->players[i], &name);
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
