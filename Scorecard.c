#include <stdlib.h>
#include <string.h>
#include "Scorecard.h"

//Struct zur Berechnung, wie oft eine Augenzahl bei den Würfeln vorkommt
typedef struct SpotTimes {
    int spot;
    int times;
} SpotTimes;


//Struct zur Liste aller Augenzahlhäufigkeiten, Array -> Pointer
typedef struct SpotTimesList {
    int size;
    SpotTimes spotsCount[0];
} SpotTimesList;

void initSpotTimes(SpotTimes *spotTimes, int spot);

SpotTimesList *calculateSpotTimes(Dice *dice);

int pointsFullHouse(Dice *dice);

int sortAscending(const void *left, const void *right);

int pointsForSpotsInARow(Dice *dice, int expectedSpotsInARow, int points);

int pointsSmallStraight(Dice *dice);

int pointsLargeStraight(Dice *dice);

int pointsSumSame(Dice *dice, int expected);

int pointsKniffel(Dice *dice);

int pointsSum(Dice *dice);

int pointsSum1(Dice *dice);

int pointsSum2(Dice *dice);

int pointsSum3(Dice *dice);

int pointsSum4(Dice *dice);

int pointsSum5(Dice *dice);

int pointsSum6(Dice *dice);

int pointsSumMoreThanXTimes(Dice *dice, int timesExpected);

int pointsSumMoreThan3Times(Dice *dice);

int pointsSumMoreThan4Times(Dice *dice);

void initializeScorecardEntry(ScorecardEntry *scorecardEntry, char *name, char *description, int(*calculation)(Dice *),
                              int maxValue);

/* Zusatzfeature: Berechnet das Feld, für welches sich der Spieler entscheiden sollte, wenn er die maximale Punktzahl für den Zug erreichen will
* @param Spielerkarte, Würfel
* @return Index des vorgeschlagenen Eintrags
*/
int prediction(Scorecard *scorecard, Dice *dice) {
    int indexOfEntry = -1;
    double percentage = 0.0;
    for (int i = 0; i < scorecard->size; ++i) {
        if (!scorecard->entries[i].hasBeenPlayed) {
            int possiblePoints = scorecard->entries[i].calculation(dice);
            int maxPointsForEntry = scorecard->entries[i].maxPossibleValue;
            if (i == 12 && percentage > 0.10) continue;
            if (percentage <= (double) possiblePoints / (double) maxPointsForEntry) {
                percentage = (double) possiblePoints / (double) maxPointsForEntry;
                indexOfEntry = i;
            }
        }
    }
    return indexOfEntry;
}

//Initialisierung eines Eintrags auf der Spielerkarte
void initializeScorecardEntry(ScorecardEntry *scorecardEntry, char *name, char *description, int(*calculation)(Dice *),
                              int maxValue) {
    scorecardEntry->name = malloc(strlen(name) + 1);
    strcpy(scorecardEntry->name, name);
    scorecardEntry->description = malloc(strlen(description) + 1);
    strcpy(scorecardEntry->description, description);
    scorecardEntry->value = 0;
    scorecardEntry->maxPossibleValue = maxValue;
    scorecardEntry->calculation = calculation;
    scorecardEntry->hasBeenPlayed = false;
}

/* Berechnet ob ein Full House vorliegt (ob ein Augenwert 2 und ein anderer 3 mal vorhanden sind oder ob einer 5 mal vorhanden ist)
* @param Würfel
* @return 25 für Fullhouse ansonsten 0
*/
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

//Callbackfunktion für qsort, Sortierung der Würfel aufsteigend, damit einfacher auf eine Straße geprüft werden kann
int sortAscending(const void *left, const void *right) {
    return (*(int *) left - *(int *) right);
}

/* Überprüfung auf eine Straße
* Überprüfung ob ("expectedSpotsInARow") 3 oder 4 mal, der nächste Wert in der Liste gleich oder um eins inkrementiert ist
* @param Würfel, Anzahl aufeinanderfolgender Zahlen, Anzahl der Punkte
* @return Anzahl der Punkte für die Straße, wenn es eine Straße gibt, ansonsten 0
*/
int pointsForSpotsInARow(Dice *dice, int expectedSpotsInARow, int points) {
    // Kopie der Würfel in ein Array, damit die Ursprungsdaten nicht verfälscht werden
    int array[dice->size];
    for (int i = 0; i < dice->size; ++i) {
        array[i] = dice->dice[i].value;
    }
    // Sortieren der Kopie
    qsort(array, (size_t) dice->size, sizeof(int), sortAscending);
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

//Berechnung des Feldes "kleine Straße"
int pointsSmallStraight(Dice *dice) {
    pointsForSpotsInARow(dice, 4, 30);
}

//Berechnung des Feldes "große Straße"
int pointsLargeStraight(Dice *dice) {
    pointsForSpotsInARow(dice, 5, 40);
}

/* Berechnung des Feldes "Kniffel"
* @param Würfel
* @return int 50 für Kniffel, ansonsten 0
*/
int pointsKniffel(Dice *dice) {
    SpotTimesList *spotTimesList = calculateSpotTimes(dice);
    for (int i = 0; i < spotTimesList->size; ++i) {
        SpotTimes *element = &spotTimesList->spotsCount[i];
        if (element->times == 5) {
            return 50;
        }
    }
    return 0;
}

/* Berechnung des Feldes "Chance"
* @param Würfel
* @return Summe der Augenzahlen der Würfel
*/
int pointsSum(Dice *dice) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += dice->dice[i].value;
    }
    return sum;
}

/* Berechnung der Felder mit gleichen Augenzahlen (1-6)
* @param Würfel, Augenzahlen die summiert werden sollen
* @return Summe der gleichen Augenzahlen
*/
int pointsSumSame(Dice *dice, int expected) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        if (expected == dice->dice[i].value) {
            sum += dice->dice[i].value;
        }
    }
    return sum;
}

//Durch den Funktionspointer auf die calculation-Funktion muss die Funktion genau die Parameter (Dice *dice) haben, dadurch muss der Funktionsaufruf gekapselt werden
//Summiert alle Würfel mit dem übergebenen Augenzahlwert, wird für die Felder Einer - Sechser benötigt
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

/* Addiert alle Würfel mit dem übergebenen Augenzahlwert, interne Funktion für pointsSum1-6
* @param Würfel, erwartete Anzahl der Augenzahl
* @return int 
*/
int pointsSumMoreThanXTimes(Dice *dice, int timesExpected) {
    SpotTimesList *spotTimesList = calculateSpotTimes(dice);
    for (int i = 0; i < spotTimesList->size; ++i) {
        SpotTimes *element = &spotTimesList->spotsCount[i];
        if (element->times >= timesExpected) {
            return pointsSum(dice);
        }
    }
    return 0;
}

//Berechnet die Häufigkeit einer Augenzahl in der Liste der Würfel
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
    return list;
}

//Initialisierung der Augenzahlhäufigkeit
void initSpotTimes(SpotTimes *spotTimes, int spot) {
    spotTimes->spot = spot;
    spotTimes->times = 0;
    spotTimes->productSpotsAndTimes = 0;
}

//Berechnung des Dreierpasches
int pointsSumMoreThan3Times(Dice *dice) {
    pointsSumMoreThanXTimes(dice, 3);
}

//Berechnung des Viererpasches
int pointsSumMoreThan4Times(Dice *dice) {
    pointsSumMoreThanXTimes(dice, 4);
}

//Initialisierung der Spielerkarte
Scorecard *initializeScorecard() {
    Scorecard *scorecard = malloc(sizeof(Scorecard));
    scorecard->size = 13;
    scorecard->totalAmountOfPoints = 0;
    scorecard->entries = malloc(scorecard->size * sizeof(ScorecardEntry));
    initializeScorecardEntry(&scorecard->entries[0], "Einser", "Summe der Augenzahlen der Einser", pointsSum1, 5);
    initializeScorecardEntry(&scorecard->entries[1], "Zweier", "Summe der Augenzahlen der Zweier", pointsSum2, 10);
    initializeScorecardEntry(&scorecard->entries[2], "Dreier", "Summe der Augenzahlen der Dreier", pointsSum3, 15);
    initializeScorecardEntry(&scorecard->entries[3], "Vierer", "Summe der Augenzahlen der Vierer", pointsSum4, 20);
    initializeScorecardEntry(&scorecard->entries[4], "Fuenfer", "Summe der Augenzahlen der Fuenfer", pointsSum5, 25);
    initializeScorecardEntry(&scorecard->entries[5], "Sechser", "Summe der Augenzahlen der Sechser", pointsSum6, 30);
    initializeScorecardEntry(&scorecard->entries[6], "Dreierpasch",
                             "Mindestens drei gleiche Wuerfel - Summe aller Augenzahlen",
                             pointsSumMoreThan3Times, 30);
    initializeScorecardEntry(&scorecard->entries[7], "Viererpasch",
                             "Mindestens vier gleiche Wuerfel - Summe aller Augenzahlen",
                             pointsSumMoreThan4Times, 30);
    initializeScorecardEntry(&scorecard->entries[8], "Full House",
                             "Drei gleiche und zwei gleiche Wuerfel oder fuenf gleiche", pointsFullHouse, 25);
    initializeScorecardEntry(&scorecard->entries[9], "Kleine Strasse", "Vier aufeinanderfolgende Augenzahlen",
                             pointsSmallStraight, 30);
    initializeScorecardEntry(&scorecard->entries[10], "Grosse Strasse", "Fuenf aufeinanderfolgende Augenzahlen",
                             pointsLargeStraight, 40);
    initializeScorecardEntry(&scorecard->entries[11], "Kniffel", "Fuenf gleiche Wuerfel", pointsKniffel, 50);
    initializeScorecardEntry(&scorecard->entries[12], "Chance", "Summe aller Wuerfel", pointsSum, 30);
    return scorecard;
}

//Validierung auf Vorhandensein eines Eintrag in der Spielerkarte. Es existieren Einträge 0-12
bool scorecardDoesNotExist(int scoreboardEntryIndex) {
    return scoreboardEntryIndex < 0 || scoreboardEntryIndex > 12;
}

//Validierung auf bereits gespielten Eintrag, Rückgabe der "Eigenschaft" hasBeenPlayed
bool scorecardAlreadyPlayed(ScorecardEntry *scorecardEntry) {
    return scorecardEntry->hasBeenPlayed;
}

//Berechnung der Gesamtpunktzahl des Spielers
int calculateTotalAmountOfPoints(Scorecard *scorecard) {
    for (int i = 0; i < scorecard->size; ++i) {
        //Berücksichtigung des Bonus
        if (i < 5 && scorecard->entries[i].value == scorecard->entries[i].maxPossibleValue &&
            scorecard->entries[11].value == scorecard->entries[11].maxPossibleValue) {
            scorecard->totalAmountOfPoints = scorecard->totalAmountOfPoints + 50;
        }
        if (i == 5 && scorecard->totalAmountOfPoints >= 63) {
            scorecard->totalAmountOfPoints = scorecard->totalAmountOfPoints + 35;
        }
        scorecard->totalAmountOfPoints = scorecard->totalAmountOfPoints + scorecard->entries[i].value;
    }
    return scorecard->totalAmountOfPoints;
}