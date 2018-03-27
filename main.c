/* ***********************************************************************
*
* DHBW Mosbach
* INF17B
* Programmentwurf WS 2017/18
**************************************************************************
*                                Kniffel
**************************************************************************
* @author Jan Bednarksi, Miguel Wolf, Rico Kraft, Julius Schinschke
*
************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Player.h"

// Vorwärtsdeklaration aller Funktionen der main
PlayerList *letUserSelectPlayer();

void letUserGivePlayerNames(PlayerList *playerList);
void tellUserPlayerNames(const PlayerList *playerList);

void letUserChooseScoreboardEntry(Player *player, Dice *dice);

void letUserSelectDiceToNotReroll(Dice *dice);

void showUserHisRollingResult(Dice *dice);

void startGame(PlayerList *playerList);

void showEndGameRanking(const PlayerList *playerList);

void askUserToPlayAnotherRound();

bool doesPlayerWantToFinishTheCurrentRound(Player *player, Dice *dice, bool lastRound);

bool askUserToFinishRoundTheCurrentRound();

bool doesUserEnteredYes();

ScorecardEntry *askUserWhichEntryHeWantsToFill(Player *player);

void askUsersIfTheyWantToUsePrediction();

/*
* Initialisierung der Spieler, Würfel und Spielkarten der Spieler
* Starten des Spiels
* Spielverlauf
* Ausgabe des Ergebnisses
* Beenden des Spiels
* Freigabe des benutzen Speichers
*/
bool userWantsToPlayAgain = false;
bool userWantsToUsePrediction = false;

int main() {
    do {
        printf("Welcome to Kniffel\n\n");
        PlayerList *playerList = letUserSelectPlayer();
        letUserGivePlayerNames(playerList);
        printf("\nStarting Kniffel with the following players\n\n");
        tellUserPlayerNames(playerList);
        askUsersIfTheyWantToUsePrediction();
        startGame(playerList);
        showEndGameRanking(playerList);
        askUserToPlayAnotherRound();
        destructPlayerList(playerList);
    } while (userWantsToPlayAgain);
    return 1337;
}

//Spielablauf
void startGame(PlayerList *playerList) {
    //Durchitarieren aller Runden
    for (int round = 0; round < playerList->players[0].scorecard->size; ++round) {
        printf("Round: %d\n", round + 1);
        //Durchitarieren aller Spieler in einer Runde
        for (int player = 0; player < playerList->size; ++player) {
            printf("Player %d is starting\n", player + 1);
            Dice *dice = initializeDice();
            //Durchitarieren aller Würfeldurchgänge pro Spieler in einer Runde
            for (int playerRoll = 0; playerRoll < 3; ++playerRoll) {
                printf("%s is playing and rolling the %d time\n", playerList->players[player].name, playerRoll + 1);
                if (!doesPlayerWantToFinishTheCurrentRound(&playerList->players[player], dice, playerRoll == 2)) {
                    break;
                }
            }
        }
    }
}

/*
* Fragen des Spielers, ob er seine Runde beenden will
* Bei Weiterspielen Auswählen der Würfel, die nochmal gewürfelt werden sollen
* Bei Beenden der Runde, Angeben des Feldes, indem der Eintrag gespeichert werden soll
* @param Spieler, Würfel, Info ob es die letzte Runde ist
* @return bool true/false ob der User seine Runde beenden will
*/
bool doesPlayerWantToFinishTheCurrentRound(Player *player, Dice *dice, bool lastRound) {
    rollDice(dice);
    showUserHisRollingResult(dice);
    if (lastRound) {
        letUserChooseScoreboardEntry(player, dice);
    } else if (askUserToFinishRoundTheCurrentRound()) {
        letUserChooseScoreboardEntry(player, dice);
        return false;
    } else {
        letUserSelectDiceToNotReroll(dice);
    }
    return true;
}

//Ausgabe neu erwürfelter Augenzahlen
void showUserHisRollingResult(Dice *dice) {
    printf("\n");
    for (int i = 0; i < dice->size; ++i) {
        printf("Dice %d: %d \n", i + 1, dice->dice[i].value);
    }
}

//Fragen des Users ob, er seine Runde beenden will, Validierung der Eingabe
bool askUserToFinishRoundTheCurrentRound() {
    printf("Do you want to finish your Round? (YES/NO) - ");
    return doesUserEnteredYes();
}

/* Validierung der User-Eingabe (YES)
* @param none
* @return bool ob der user Ja eingeben hat
*/
bool doesUserEnteredYes() {
    char *decision = malloc(1000);
    scanf(" %s", decision);
    decision = strupr(decision);
    if ((strcmp(decision, "YES") == 0) || (strcmp(decision, "Y") == 0) || (strcmp(decision, "YE") == 0) ||
        (strcmp(decision, "SEY") == 0) || (strcmp(decision, "YSE") == 0) || (strcmp(decision, "SYE") == 0)) {
        free(decision);
        return true;
    } else {
        free(decision);
        return false;
    }
}

/*
* Auswählen der Würfel, die nicht nochmal gewürfelt werden sollen
* @param Würfel
* @return none
*/
void letUserSelectDiceToNotReroll(Dice *dice) {
    printf("\nPlease enter the Dice you want to select (selected Dice won't be rerolled)\n\n");
    for (int i = 0; i < dice->size; ++i) {
        printf("Do you want to select Dice %d <YES/NO> - ", i + 1);
        if (doesUserEnteredYes()) {
            dice->dice[i].isSelected = true;
        }
    }
    printf("\n");
}

/* Gibt die noch nicht gespielten Felder aus und prüft ob der User das extra Feature "Prediciton" verwenden will
* Trägt Würfel in das ausgewählte Feld ein und gibt aktuelle Spielkarte des derzeitigen Spielers aus
* @param Spieler, Würfel
* @return none
*/
void letUserChooseScoreboardEntry(Player *player, Dice *dice) {
    printRemainingScoreboardEntries(player);

    if (userWantsToUsePrediction) {
        printf("You get the maximum amount of points if you select entry %d - %s\n",
               prediction(player->scorecard, dice) + 1,
               player->scorecard->entries[prediction(player->scorecard, dice)].name);
    }

    ScorecardEntry *entry = askUserWhichEntryHeWantsToFill(player);
    entry->value = entry->calculation(dice);
    entry->hasBeenPlayed = true;
    printCurrentScoreboard(player);
}

/* Gibt Eintrag zurück in dem der User seine Würfel eintragen will
* Validierung der Usereingabe
* @param Spieler
* @return Pointer
*/
ScorecardEntry *askUserWhichEntryHeWantsToFill(Player *player) {
    char userInput[1000], *end;
    long chosenScoreboard = -1, decision;
    bool firstValidationDone = false;
    do {
        //Falls der User bei der ersten Eingabe keinen validen Wert eingibt, kommt die Ausgabe: "Valide Eingaben: 0-12"
        if (firstValidationDone) {
            printf("\nSorry, the scoreboard you entered is invalid: %li\n", chosenScoreboard + 1);
        }
        printf("\nPlease enter the number of the row you want to put in your value\n");
        scanf("%1000s", userInput);
        decision = strtol(userInput, &end, 10);
        firstValidationDone = true;
        if (end == userInput) {
            printf("Invalid input, please enter a number\n");
        } else if (end[0] != '\0') {
            printf("trailing characters after number %ld: %s\n", decision, end);
        }
        chosenScoreboard = decision - 1;
    } while (scorecardDoesNotExist(chosenScoreboard) ||
             scorecardAlreadyPlayed(&player->scorecard->entries[chosenScoreboard]));
    return &player->scorecard->entries[chosenScoreboard];
}

/* Eingeben der Spielernamen, alle Eingaben sind hier valide
* @param Pointer Spielerliste
* @return none
*/
void letUserGivePlayerNames(PlayerList *playerList) {
    for (int i = 0; i < playerList->size; ++i) {
        char *name = malloc(1000);
        printf("Please enter the name of player %d: ", i + 1);
        scanf("%s", name);
        setPlayerName(&playerList->players[i], name);
        free(name);
    }
    printf("\n");
}

/* Eingeben der Anzahl der Spieler mit denen gespielt werden soll
* Validierung der Usereingabe, (1-99) Spieler sind erlaubt
* @param none
* @return Pointer Funktion
*/
PlayerList *letUserSelectPlayer() {
    char userInput[1000], *end;
    long amountOfPlayers = 0;
    while (true) {
        printf("Please enter the amount of players: ");
        scanf("%1000s", userInput);
        amountOfPlayers = strtol(userInput, &end, 10);
        if (end == userInput) {
            printf("Invalid input, please enter a number\n");
        } else if (end[0] != '\0') {
            printf("Trailing characters after number %ld: %s\n", amountOfPlayers, end);
        } else if (amountOfPlayers <= 0 || amountOfPlayers > 99) {
            printf("You can only play with 1-99 Players\n");
        } else {
            printf("\n");
            return initializePlayerList(amountOfPlayers);
        }
    }
}

/* Ausgabe der Spielernamen
* @param Pointer Spielerliste
* @return none
*/ 
void tellUserPlayerNames(const PlayerList *playerList) {
    for (int i = 0; i < playerList->size; ++i) {
        printf("Name of player %d: %s\n", i + 1, playerList->players[i].name);
    }
    printf("\n");
}

/* Callbackfunktion Sortierung absteigend für qsort
* @param zwei Werte die verglichen werden sollen
* @return int
*/
int sortDescanding(const void *left, const void *right) {
    return (*(int *) right) - (*(int *) left);
}

/* Kopieren der derzeitigen Punkte in ein Array, in dem diese absteigend für das Ranking sortiert werden
* Spieler werden in Reihenfolge der Punktzahlen auf Konsole ausgegeben
* @param Pointer Spielerliste
* @return none
*/
void showEndGameRanking(const PlayerList *playerList) {
    int array[playerList->size];
    for (int i = 0; i < playerList->size; ++i) {
        calculateTotalAmountOfPoints(playerList->players[i].scorecard);
        array[i] = playerList->players[i].scorecard->totalAmountOfPoints;
    }
    printf("\nRANKING\n");
    qsort(array, (size_t) playerList->size, sizeof(int), sortDescanding);
    for (int j = 0; j < playerList->size; ++j) {
        for (int i = 0; i < playerList->size; ++i) {
            if (array[j] == playerList->players[i].scorecard->totalAmountOfPoints) {
                printf("%d. %s - points: %d\n", j + 1, playerList->players[i].name,
                       playerList->players[i].scorecard->totalAmountOfPoints);
            }
        }
    }
}

//fragt ob der User nochmal spielen will
void askUserToPlayAnotherRound() {
    printf("\nDo you want to play again? <YES/NO>\n");
    userWantsToPlayAgain = doesUserEnteredYes();
}

/* Fragt User ob er das extra Feature "Prediction" verwenden will
* @param none
* @return none
*/
void askUsersIfTheyWantToUsePrediction() {
    printf("Do you want to use predictions in this game? <YES/NO>\n");
    printf("This feature will tell the player with which entry he reaches\n");
    printf("the maximum amount of points for the round\n");
    printf("keep in mind, sometimes your brain is smarter than the machine!\n");
    printf("\n");
    userWantsToUsePrediction = doesUserEnteredYes();
    char *outcome = userWantsToUsePrediction ? "ON" : "OFF";
    printf("\nPrediction is set to %s\n\n", outcome);
}
