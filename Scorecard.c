//
// Created by BEDNARSKIJ on 21.12.2017.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Scorecard.h"

typedef struct SpotTimes {
    int spot;
    int times;
    int productSpotsAndTimes;
} SpotTimes;

typedef struct SpotTimesList {
    int size;
    SpotTimes spotsCount[0];
} SpotTimesList;

void initSpotTimes(SpotTimes *spotTimes, int spot);

SpotTimesList *calculateSpotTimes(Dice *dice);

//TODO: Extrafeature, user entry vorschlagen für maximale pkt

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

int pointsFullHouse(Dice *dice) {
    SpotTimesList *spotTimesList = calculateSpotTimes(dice);
    bool isThereAnElement2x = false;
    bool isThereAnElement3x = false;
    bool isThereAnElement5x = false;
    for (int i = 0; i < spotTimesList->size; ++i) {
        SpotTimes *element = &spotTimesList->spotsCount[i];
        if (element->times == 2)
            isThereAnElement2x = true;
        if (element->times == 3)
            isThereAnElement3x = true;
        if (element->times == 5) {
            isThereAnElement5x = true;
        }
    }
    bool isFullHouse = ((isThereAnElement2x && isThereAnElement3x) || isThereAnElement5x);
    return isFullHouse ? 25 : 0;
}

int sortAscending(const void *left, const void *right) {
    return (*(int *) left - *(int *) right);
}

int pointsForSpotsInARow(Dice *dice, int expectedSpotsInARow, int points) {
    int array[dice->size];
    for (int i = 0; i < dice->size; ++i) {
        array[i] = dice->dice[i].value;
    }
    qsort(array, 5, sizeof(int), sortAscending);
    int count = 0;
    for (int j = 0; j < dice->size - 1; ++j) {
        int current = array[j];
        int next = array[j + 1];

        if (next == current + 1) {
            count++;
        } else if (next != current) {
            count = 0;
        }
    }
    return count >= expectedSpotsInARow - 1 ? points : 0;
}

int pointsSmallStraight(Dice *dice) {
    pointsForSpotsInARow(dice, 4, 30);
}

int pointsLargeStraight(Dice *dice) {
    pointsForSpotsInARow(dice, 5, 40);
}

int pointsYahtzee(Dice *dice) {
    SpotTimesList *spotTimesList = calculateSpotTimes(dice);
    for (int i = 0; i < spotTimesList->size; ++i) {
        SpotTimes *element = &spotTimesList->spotsCount[i];
        if (element->times == 5) {
            return 50;
        }
    }
    return 0;
}

int pointsSum(Dice *dice) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += dice->dice[i].value;
    }
    return sum;
}

int pointsSumSame(Dice *dice, int expected) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        if (expected == i) {
            sum += dice->dice[i].value;
        }
    }
    return sum;
}

int pointsSum1(Dice *dice) {
    return pointsSumSame(dice, 1);
}

int pointsSum2(Dice *dice) {
    return pointsSumSame(dice, 2);
}

int pointsSum3(Dice *dice) {
    return pointsSumSame(dice, 3);
}

int pointsSum4(Dice *dice) {
    return pointsSumSame(dice, 4);
}

int pointsSum5(Dice *dice) {
    return pointsSumSame(dice, 5);
}

int pointsSum6(Dice *dice) {
    return pointsSumSame(dice, 6);
}

int pointsSumMoreThanXTimes(Dice *dice, int timesExpected) {
    SpotTimesList *spotTimesList = calculateSpotTimes(dice);
    for (int i = 0; i < spotTimesList->size; ++i) {
        // TODO: beim foreach immer mit dem pointer arbeiten -> refactoring??
        SpotTimes *element = &spotTimesList->spotsCount[i];
        if (element->times >= timesExpected) {
            return element->productSpotsAndTimes;
        }
    }
    return 0;
}

SpotTimesList *calculateSpotTimes(Dice *dice) {
    SpotTimesList *list = malloc(sizeof(SpotTimesList) + 6 * sizeof(SpotTimes));
    list->size = 6;
    for (int i = 0; i < list->size; ++i) {
        initSpotTimes(&list->spotsCount[i], i + 1);
    }
    for (int j = 0; j < dice->size; ++j) {
        SpotTimes *element = &list->spotsCount[dice->dice[j].value - 1];
        element->times++;
        element->productSpotsAndTimes = element->spot * element->times;
    }

    for (int i = 0; i < list->size; ++i) {
        SpotTimes *element = &list->spotsCount[i];
        printf("spotTime for spot: %d, times: %d, sum: %d\n", element->spot, element->times,
               element->productSpotsAndTimes);
    }
    return list;
}

void initSpotTimes(SpotTimes *spotTimes, int spot) {
    spotTimes->spot = spot;
    spotTimes->times = 0;
    spotTimes->productSpotsAndTimes = 0;
}

int pointsSumMoreThan3Times(Dice *dice) {
    pointsSumMoreThanXTimes(dice, 3);
}

int pointsSumMoreThan4Times(Dice *dice) {
    pointsSumMoreThanXTimes(dice, 4);
}



Scorecard *initializeScorecard() {
    Scorecard *scorecard = malloc(sizeof(Scorecard));
    scorecard->size = 13;
    scorecard->entries = malloc(scorecard->size * sizeof(ScorecardEntry));
    initializeScorecardEntry(&scorecard->entries[0], "Einser", "Die Summe der Augenzahlen der Einser", pointsSum1);
    initializeScorecardEntry(&scorecard->entries[1], "Zweier", "Die Summe der Augenzahlen der Zweier", pointsSum2);
    initializeScorecardEntry(&scorecard->entries[2], "Dreier", "Die Summe der Augenzahlen der Dreier", pointsSum3);
    initializeScorecardEntry(&scorecard->entries[3], "Vierer", "Die Summe der Augenzahlen der Vierer", pointsSum4);
    initializeScorecardEntry(&scorecard->entries[4], "Fuenfer", "Die Summe der Augenzahlen der Fuenfer", pointsSum5);
    initializeScorecardEntry(&scorecard->entries[5], "Sechser", "Die Summe der Augenzahlen der Sechser", pointsSum6);
    initializeScorecardEntry(&scorecard->entries[6], "Dreierpasch", "Mindestens drei gleiche Wuerfel",
                             pointsSumMoreThan3Times);
    initializeScorecardEntry(&scorecard->entries[7], "Viererpasch", "Mindestens vier gleiche Wuerfel",
                             pointsSumMoreThan4Times);
    initializeScorecardEntry(&scorecard->entries[8], "Full House",
                             "Drei gleiche und zwei gleiche Wuerfel oder fuenf gleiche", pointsFullHouse);
    initializeScorecardEntry(&scorecard->entries[9], "Kleine Strasse", "Vier aufeinanderfolgende Augenzahlen",
                             pointsSmallStraight);
    initializeScorecardEntry(&scorecard->entries[10], "Grosse Strasse", "Fuenf aufeinanderfolgende Augenzahlen",
                             pointsLargeStraight);
    initializeScorecardEntry(&scorecard->entries[11], "Kniffel / Yahtzee", "Fuenf gleiche Wuerfel", pointsYahtzee);
    initializeScorecardEntry(&scorecard->entries[12], "Chance", "Jede Kombination", pointsSum);
    return scorecard;
}

bool scorecardDoesNotExist(int scoreboardEntryIndex) {
    return scoreboardEntryIndex < 0 || scoreboardEntryIndex > 12;
}

bool scorecardAlreadyPlayed(ScorecardEntry *scorecardEntry) {
    return scorecardEntry->hasBeenPlayed;
}