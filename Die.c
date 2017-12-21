//
// Created by BEDNARSKIJ on 21.12.2017.
//

#include <stdbool.h>

typedef struct Die {
    int value;
    bool isSelected;
} Die;

typedef struct Dice {
    Die dice[5];
} Dice;

Die *die_initialize(Die *die, int value, bool isSelected) {

}

Dice *dice_initialize(Dice *dice, Die *die , int i) {

}

void die_destruct(Die* die) {

}

Die *dice_getDie(Dice *dice, int i) {
    return &dice->dice[i];
}

void generate_Value(Die *die) {

}