/***********************************************************
 ** Program Filename: cardtest1.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 4, 2018
 ** Description: tests cardSmithy() from dominion.c
 ** Input: function takes currentPlayer, gameState, handPos
 ** Output: Success or Failure
 ***********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main(){
    int i, j, m;
    int playerCount = 2;
    int player1 = 0;
    int seed = 3;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState state, testState;

    //Initialize game state
    initializeGame(playerCount, k, seed, &state);

    //Copy state into testState and play card

    //TEST 1 - Check that exactly 3 cards were drawn from
    //deckCount and 3 added to handCount





    return 0;
}
