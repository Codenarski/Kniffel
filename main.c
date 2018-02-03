
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Player.h"

PlayerList *letUserSelectPlayer();

void letUserGivePlayerNames(PlayerList *playerList);
void tellUserPlayerNames(const PlayerList *playerList);
void startGame(PlayerList *playerList);
bool playRoundAndContinue(Player *player, Dice *dice, bool lastRound);
bool askUserToFinishRound(Dice *dice);
void letUserChooseScoreboardEntry(Player *player, Dice *dice);
void nextPlayer();
void letUserSelectDiceToSelect(Dice *dice);
void showUserHisResult(Dice *dice);
ScorecardEntry *askUserWhichEntryHeWantsToFill(Player *player);
bool doesUserEnteredYes();

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
    for (int round = 0; round < playerList->players[0].scorecard->size; ++round) {
        printf("Round: %d\n", round + 1);
        for (int player = 0; player < playerList->size; ++player) {
            printf("Player %d is starting\n", player + 1);
            Dice *dice = init_dice();
            for (int playerRoll = 0; playerRoll < 3; ++playerRoll) {
                printf("Player %d is playing is rolling the %d time\n", player + 1, playerRoll + 1);
                if (!playRoundAndContinue(&playerList->players[player], dice, playerRoll == 2)) {
                    break;
                }
            }
        }
    }
}

bool playRoundAndContinue(Player *player, Dice *dice, bool lastRound) {
    roll_dice(dice);
    showUserHisResult(dice);
    if (askUserToFinishRound(dice)) {
        printf("Player wants to finish round\n");
        letUserChooseScoreboardEntry(player, dice);
        return false;
    } else {
        if (lastRound) {
            letUserChooseScoreboardEntry(player, dice);
        } else {
            printf("Player wants to continue round\n");
            letUserSelectDiceToSelect(dice);
        }
        return true;
    }
}

void showUserHisResult(Dice *dice) {
    for (int i = 0; i < dice->size; ++i) {
        printf("Dice %d: %d \n", i + 1, dice->dice[i].value);
    }
}

bool askUserToFinishRound(Dice *dice) {
    printf("Do you want to finish your Round? (YES/NO)\n");
    return doesUserEnteredYes();
}

bool doesUserEnteredYes() {
    char *decision = malloc(100);
    char *YES = "YES";
    scanf("%s", decision);
    decision = strupr(decision);
    printf("%s\n", decision);
    if (strcmp(decision, YES) == 0) {
        free(decision);
        return true;
    } else {
        free(decision);
        return false;
    }
}

bool doesUserEnteredNo() {
    return !doesUserEnteredYes();
}

void letUserSelectDiceToSelect(Dice *dice) {
    printf("Please enter the Dice you want to select (Selected Dice won't be rerolled)\n");
    for (int i = 0; i < dice->size; ++i) {
        printf("Do you want to select Dice %d (YES/NO) \n", i + 1);
        if (doesUserEnteredYes()) {
            dice->dice[i].isSelected = true;
        }
    }
}

void nextPlayer() {

}

void letUserChooseScoreboardEntry(Player *player, Dice *dice) {
    printCurrentScoreboard(player);
    ScorecardEntry *entry = askUserWhichEntryHeWantsToFill(player);
    entry->value = entry->calculation(dice);
}

ScorecardEntry *askUserWhichEntryHeWantsToFill(Player *player) {
    char userInput[100], *end;
    long chosenScoreboard = -1, decision;
    bool firstRunDone = false;
    do {
        if (firstRunDone) {
            printf("Sorry, the scoreboard you entered is invalid: %li\n", chosenScoreboard + 1);
        }
        printf("Please enter the number of the row you want to put in your value\n");
        scanf("%100s", userInput);
        decision = strtol(userInput, &end, 10);
        firstRunDone = true;
        if (end == userInput) {
            printf("Invalid input, please enter a number\n");
        } else if (end[0] != '\0') {
            printf("trailing characters after number %ld: %s\n", decision, end);
        } else {
            chosenScoreboard = decision - 1;
        }
    } while (scorecardDoesNotExist(chosenScoreboard) ||
             scorecardAlreadyPlayed(&player->scorecard->entries[chosenScoreboard]));
    return &player->scorecard->entries[chosenScoreboard];
}

void letUserGivePlayerNames(PlayerList *playerList) {
    for (int i = 0; i < playerList->size; ++i) {
        char *name = malloc(100);
        printf("Please enter name of player: %d\n", i + 1);
        scanf("%s", name);
        setPlayerName(&playerList->players[i], name);
        printf("Playername: %s\n", name);
        free(name);
    }
}

PlayerList *letUserSelectPlayer() {
    char userInput[100], *end;
    long amountOfPlayers = 0;
    while (true) {
        printf("Please enter the amount of players: ");
        scanf("%100s", userInput);
        amountOfPlayers = strtol(userInput, &end, 10);
        if (end == userInput) {
            printf("Invalid input, please enter a number\n");
        } else if (end[0] != '\0') {
            printf("trailing characters after number %ld: %s\n", amountOfPlayers, end);
        } else {
            return init_playerList(amountOfPlayers);
        }
    }
}

void tellUserPlayerNames(const PlayerList *playerList) {
    for (int i = 0; i < playerList->size; ++i) {
        printf("Name of Player %d: %s\n", i + 1, playerList->players[i].name);
    }
}
