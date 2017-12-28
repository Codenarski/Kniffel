//
// Created by BEDNARSKIJ on 21.12.2017.
//

#include <stdlib.h>
#include <string.h>
#include "Entity.h"

void
initializeScorecardEntry(ScorecardEntry *scorecardEntry, char *name, char *description, int(*calculation)(Dice *dice)) {
    scorecardEntry->name = malloc(strlen(name) + 1);
    strcpy(scorecardEntry->name, name);
    scorecardEntry->description = malloc(strlen(description) + 1);
    strcpy(scorecardEntry->description, description);
    scorecardEntry->value = 0;
    scorecardEntry->calculation = calculation;
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


    initializeScorecardEntry(&scorecard->entries[0], "Einser", "Die Summe der Augenzahlen der Einser", pointsSum);
    initializeScorecardEntry(&scorecard->entries[1], "Zweier", "Die Summe der Augenzahlen der Zweier", pointsSum);
    initializeScorecardEntry(&scorecard->entries[2], "Dreier", "Die Summe der Augenzahlen der Dreier", pointsSum);
    initializeScorecardEntry(&scorecard->entries[3], "Vierer", "Die Summe der Augenzahlen der Vierer", pointsSum);
    initializeScorecardEntry(&scorecard->entries[4], "Fünfer", "Die Summe der Augenzahlen der Fünfer", pointsSum);
    initializeScorecardEntry(&scorecard->entries[5], "Sechser", "Die Summe der Augenzahlen der Sechser", pointsSum);
    initializeScorecardEntry(&scorecard->entries[6], "Dreierpasch", "Mindestens drei gleiche Würfel", pointsSum);
    initializeScorecardEntry(&scorecard->entries[7], "Viererpasch", "Mindestens vier gleiche Würfel", pointsSum);
    initializeScorecardEntry(&scorecard->entries[8], "Full House",
                             "Drei gleiche und zwei gleiche Würfel oder fünf gleiche", points25);
    initializeScorecardEntry(&scorecard->entries[9], "Kleine Straße", "Vier aufeinanderfolgende Augenzahlen", points30);
    initializeScorecardEntry(&scorecard->entries[10], "Große Straße", "Fünf aufeinanderfolgende Augenzahlen", points40);
    initializeScorecardEntry(&scorecard->entries[11], "Kniffel / Yahtzee", "Fünf gleiche Würfel", points50);
    initializeScorecardEntry(&scorecard->entries[12], "Chance", "Jede Kombination", pointsSum);
    return scorecard;
}