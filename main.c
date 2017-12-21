#include <stdio.h>
#include "Player.h"
#include "Die.h"

int main() {
    int amount;
    printf("Please enter the amount of players: ");
    scanf("%d",&amount);
    printf("We will have %d players", amount);
    PlayerList* playerList = playerList_initialize(amount);
    return 0;
}