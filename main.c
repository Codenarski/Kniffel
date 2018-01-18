
#include <stdio.h>
#include <string.h>
#include "Player.h"

PlayerList *letUserSelectPlayer();
void letUserGivePlayerNames(const PlayerList *playerList);
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
    printf("Do you want to finish your Round? (Y/N)\n");
    return doesUserEnteredYes();
}

bool doesUserEnteredYes() {
    char *decision;
    scanf("%s", &decision);
    strupr(&decision);
    return strcmp(&decision, "YES") == 0 ? true : false;
}

bool doesUserEnteredNo() {
    return !doesUserEnteredYes();
}

void letUserSelectDiceToSelect(Dice *dice) {
    printf("Please enter the Dice you want to select (Selected Dice won't be rerolled)\n");
    for (int i = 0; i < dice->size; ++i) {
        printf("Do you want to select Dice %d (Y/N) \n", i + 1);
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
    //TODO: User soll nur werte von 1-13 eingeben dürfen und nicht 0-12
    long chosenScoreboard = -1;
    bool firstRunDone = false;
    do {
        if (firstRunDone) {
            printf("Sorry, the scoreboard you entered is invalid: %li\n", chosenScoreboard);
        }
        printf("Please enter the number of the row you want to put in your value\n");
        int decision;
        scanf("%d", &decision);
        firstRunDone = true;
        chosenScoreboard = decision - 1;
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
