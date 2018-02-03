/***********************************************************
 ** Program Filename: unittest1.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 4, 2018
 ** Description: Unit test of supplyCount() from dominion.c
 **         that returns the count of supply for a card
 ** Input: function takes int card, struct gameState *state
 ** Output:
 ***********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>


int main(){
    //Initialize gameState with 2 players
    int numPlayers = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 1000; //For randomizing the shuffling result
    struct gameState testState;

    printf("All initializeGame inputs created.\n");

    initializeGame(numPlayers, k, seed, &testState);

    printf("initializeGame called\n");

    assert(testState != NULL);


    //For each card type whose supply is necessarily filled 
    //at initializationi (Curse, Estate, Duchy, Province, 
    //Copper, Silver, and Gold) get the count

    return 0;
}

