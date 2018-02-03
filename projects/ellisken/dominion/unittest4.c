/***********************************************************
 ** Program Filename: unittest2.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 4, 2018
 ** Description: Unit test of isGameOver() from dominion.c
 **     which checks the number of provinces or if three
 **     supply piles are empty to determine if the game
 **     is over.
 ** Input: function takes struct gamestate *state
 ** Output:
 ***********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main(){
    //Initialize gameState with 2 players
    int i,j;
    int playerCount = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 3; //For randomizing shuffling result
    struct gameState testState;

    initializeGame(playerCount, k, see, &testState); 

    //TEST 1 - Test if Game is over based on supply piles/province count
    //at game beginning. Province cards == 8, so Game should not be over
    if(isGameOver())
        printf("---TEST 1 failed---\n");
    else printf("---TEST 1 passed---\n");









    return 0;
}
