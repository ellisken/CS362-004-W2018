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
    int i;
    int playerCount = 2;
    int player1 = 0;
    int player2 = 1;
    int handPos = 0;
    int success_ct = 0;
    int hand_ct1, hand_ct2, deck_ct2;
    int seed = 3;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int test_k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState state, testState;

    //Print title
    printf("\n\nCard Test 1: cardSmithy()\n\n");

    //Initialize game state
    initializeGame(playerCount, k, seed, &state);
    printf("\nGame Initialized\n");

    //Copy state into testState and play card for player 1
    //Record state of hand and deck count prior to playing card
    memcpy(&testState, &state, sizeof(struct gameState));
    hand_ct1 = testState.handCount[player1];
    hand_ct2 = testState.handCount[player2];
    deck_ct2 = testState.deckCount[player2];
    printf("Deck count starts at: %i\n", testState.deckCount[player1]);
    cardSmithy(player1, &testState, handPos);
    printf("\nSmithy played by player 1 with hand position 0\n");
    printf("Deck count is now: %i\n", testState.deckCount[player1]);


    //TEST 1 - Check that exactly 3 cards were drawn from player's deck
    printf("\n\nTEST 1 - Check exactly 3 cards drawn from player 1's deck\n\n");
    
    assert(testState.deckCount[player1] == (state.deckCount[player1]-3));
    
    
    
    //TEST 2 - Check that exactly 3 cards added to player's hand and one
    //discarded
    printf("\n\nTEST 2 - Check exactly 3 cards added to player 1's hand\n\n");
    printf("Hand count initial (test): %i, hand count after play (test) %i\n", hand_ct1, testState.handCount[player1]);
    assert(testState.handCount[player1] == state.handCount[player1]+3-1);


    //TEST 3 - Check that deckCount, handCount, and discardCount for
    //testState have not changed
    printf("\n\nTEST 3 - Check state has not changed for player 2 (handCount, discardCount)\n\n");
    printf("Hand count initial (test): %i, hand count after play (test) %i\n", hand_ct2, testState.handCount[player2]);
    assert(testState.handCount[player2] == state.handCount[player2]);
    
    printf("Deck count initial (test): %i, deck count after play (test) %i\n", deck_ct2, testState.deckCount[player2]);
    assert(testState.deckCount[player2] == state.deckCount[player2]);

    
    //TEST 4 - Check that Kingdom pile has not changed
    printf("\n\nTEST 4 - Check state has not changed for kingdom pile\n\n");
    for(i=0; i < 10; i++){
        assert(k[i] == test_k[i]); 
    }

    printf("\n\nAll tests succesfully passed\n\n");
    return 0;
}