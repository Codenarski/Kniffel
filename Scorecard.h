#ifndef KNIFFEL3_SCORECARD_H
#define KNIFFEL3_SCORECARD_H

#include "Die.h"

//struct zur Haltung der Daten eines Eintrages auf der Spielerkarte
typedef struct ScorecardEntry {
    char *name;
    char *description;

    int (*calculation)(Dice *dice);

    int value;
    int maxPossibleValue;
    bool hasBeenPlayed;
} ScorecardEntry;

//struct zur Spielerkarte
typedef struct Scorecard {
    ScorecardEntry *entries;
    int size;
    int totalAmountOfPoints;
} Scorecard;

//Vorwärtsdeklaration der Scorecard-Funktionen, die nach außen sichtbar sein müssen
int calculateTotalAmountOfPoints(Scorecard *scorecard);

int prediction(Scorecard *scorecard, Dice *dice);
Scorecard *initializeScorecard();

bool scorecardDoesNotExist(int scoreboardEntryIndex);

bool scorecardAlreadyPlayed(ScorecardEntry *scorecardEntry);

#endif //KNIFFEL3_SCORECARD_H
