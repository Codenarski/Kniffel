//
// Created by BEDNARSKIJ on 21.12.2017.
//

#include <stdbool.h>


#ifndef KNIFFEL3_DIE_H
#define KNIFFEL3_DIE_H


typedef struct Die {
    int value;
    bool isSelected;
} Die;

typedef struct Dice {
    Die dice[5];
    int size;
} Dice;

Dice *init_dice();

void roll_dice(Dice *dice);

#endif //KNIFFEL3_DIE_H

