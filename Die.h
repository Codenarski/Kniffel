//
// Created by BEDNARSKIJ on 21.12.2017.
//

#include <stdbool.h>

#ifndef KNIFFEL3_DIE_H
#define KNIFFEL3_DIE_H

typedef struct Die Die;
typedef struct Dice Dice;

Die *die_initialize(Die *die, int value, bool isSelected);
Dice *dice_initialize(Dice *dice, Die *die , int i);
void die_destruct(Die* die);
Die *dice_getDie(Dice *dice, int i);
void generate_Value(Die *die);

#endif //KNIFFEL3_DIE_H
