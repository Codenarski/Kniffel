//
// Created by XaNNy0 on 22.12.2017.
//

#ifndef KNIFFEL3_ENTITY_H
#define KNIFFEL3_ENTITY_H

#include <stdbool.h>

typedef struct Player {
    char *name;
} Player;

typedef struct PlayerList {
    int size;
    Player players[0];
} PlayerList;

typedef struct Die {
    int value;
    bool isSelected;
} Die;

typedef struct Dice {
    Die dice[5];
    int size;
} Dice;

typedef struct ScorecardEntry {
    char *name;
    char *description;

    int (*calculation)(Dice *dice);

    int value;
} ScorecardEntry;

typedef struct Scorecard {
    ScorecardEntry *entries;
    int size;
} Scorecard;

#endif //KNIFFEL3_ENTITY_Has f