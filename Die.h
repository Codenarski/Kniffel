#ifndef KNIFFEL3_DIE_H
#define KNIFFEL3_DIE_H

#include <stdbool.h>

//struct zum Speichern der Würfeldaten
typedef struct Die {
    int value;
    bool isSelected;
} Die;

//Liste aller Würfel, hier gleiches Problem wie beim Spieler, Array to Pointer Decay.
typedef struct Dice {
    Die dice[5];
    int size;
} Dice;

//Vorwärtsdeklaration der Funktionen des Die, die nach außen hin sichtbar sein müssen
Dice *initializeDice();

void rollDice(Dice *dice);

#endif //KNIFFEL3_DIE_H

