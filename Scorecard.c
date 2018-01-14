//
// Created by BEDNARSKIJ on 21.12.2017.
//

#include <stdlib.h>
#include <string.h>
#include "Scorecard.h"

void
initializeScorecardEntry(ScorecardEntry *scorecardEntry, char *name, char *description, int(*calculation)(Dice *dice)) {
    scorecardEntry->name = malloc(strlen(name) + 1);
    strcpy(scorecardEntry->name, name);
    scorecardEntry->description = malloc(strlen(description) + 1);
    strcpy(scorecardEntry->description, description);
    scorecardEntry->value = 0;
    scorecardEntry->calculation = calculation;
    scorecardEntry->isStrike = false;
    scorecardEntry->hasBeenPlayed = false;
}

int points25(Dice *dice) {
    return 25;
}

int points30(Dice *dice) {
    return 30;
}

int points40(Dice *dice) {
    return 40;
}

int points50(Dice *dice) {
    return 50;
}

int pointsSum(Dice *dice) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += dice->dice[i].value;
    }
    return sum;
}

Scorecard *initializeScorecard() {
    Scorecard *scorecard = malloc(sizeof(Scorecard));
    scorecard->size = 13;
    scorecard->entries = malloc(scorecard->size * sizeof(ScorecardEntry));
    //TODO: Richtige Punktekalkulation für alle Fälle + Validierung
    initializeScorecardEntry(&scorecard->entries[0], "Einser", "Die Summe der Augenzahlen der Einser", pointsSum);
    initializeScorecardEntry(&scorecard->entries[1], "Zweier", "Die Summe der Augenzahlen der Zweier", pointsSum);
    initializeScorecardEntry(&scorecard->entries[2], "Dreier", "Die Summe der Augenzahlen der Dreier", pointsSum);
    initializeScorecardEntry(&scorecard->entries[3], "Vierer", "Die Summe der Augenzahlen der Vierer", pointsSum);
    initializeScorecardEntry(&scorecard->entries[4], "Fuenfer", "Die Summe der Augenzahlen der Fuenfer", pointsSum);
    initializeScorecardEntry(&scorecard->entries[5], "Sechser", "Die Summe der Augenzahlen der Sechser", pointsSum);
    initializeScorecardEntry(&scorecard->entries[6], "Dreierpasch", "Mindestens drei gleiche Wuerfel", pointsSum);
    initializeScorecardEntry(&scorecard->entries[7], "Viererpasch", "Mindestens vier gleiche Wuerfel", pointsSum);
    initializeScorecardEntry(&scorecard->entries[8], "Full House",
                             "Drei gleiche und zwei gleiche Wuerfel oder fuenf gleiche", points25);
    initializeScorecardEntry(&scorecard->entries[9], "Kleine Strasse", "Vier aufeinanderfolgende Augenzahlen",
                             points30);
    initializeScorecardEntry(&scorecard->entries[10], "Grosse Strasse", "Fuenf aufeinanderfolgende Augenzahlen",
                             points40);
    initializeScorecardEntry(&scorecard->entries[11], "Kniffel / Yahtzee", "Fuenf gleiche Wuerfel", points50);
    initializeScorecardEntry(&scorecard->entries[12], "Chance", "Jede Kombination", pointsSum);
    return scorecard;
}

bool scorecardDoesNotExist(int scoreboardEntryIndex) {
    return scoreboardEntryIndex < 0 || scoreboardEntryIndex > 13;
}

bool scorecardAlreadyPlayed(ScorecardEntry *scorecardEntry) {
    return scorecardEntry->hasBeenPlayed;
}