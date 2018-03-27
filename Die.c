#include <stdlib.h>
#include <time.h>
#include "Die.h"

/* Simulation eines Würfelwurfs
* @param none
* @return Zufallszahl von 1-6
*/
int rollDie() {
    return (rand() % 6) + 1;
}

//Initalisierung der Würfel
Dice *initializeDice() {
    srand(time(NULL));
    Dice *dice = malloc(sizeof(Dice) + 5 * sizeof(Die));
    for (int i = 0; i < sizeof(dice->dice) / sizeof(Die); ++i) {
        dice->dice[i].value = 0;
        dice->dice[i].isSelected = false;
    }
    dice->size = 5;
    return dice;
}

//Würfeln der nicht ausgewählten Würfel
void rollDice(Dice *dice) {
    for (int i = 0; i < dice->size; ++i) {
        if (!dice->dice[i].isSelected) {
            dice->dice[i].value = rollDie();
        }
    }
}
