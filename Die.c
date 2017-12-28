//
// Created by BEDNARSKIJ on 21.12.2017.
//
#include <stdlib.h>
#include <time.h>
#include "Die.h"

int roll_die() {
    return (rand() % 6) + 1;
}

Dice *init_dice() {
    srand(time(NULL));
    Dice *dice = malloc(sizeof(Dice) + 5 * sizeof(Die));
    for (int i = 0; i < sizeof(dice->dice) / sizeof(Die); ++i) {
        dice->dice[i].value = 0;
        dice->dice[i].isSelected = false;
    }
    return dice;
}

void roll_dice(Dice *dice) {
    for (int i = 0; i < sizeof(dice->dice) / sizeof(Die); ++i) {
        if (!dice->dice->isSelected) {
            dice->dice[i].value = roll_die();
        }
    }
}
