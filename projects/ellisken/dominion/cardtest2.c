/***********************************************************
 ** Program Filename: cardtest2.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 4, 2018
 ** Description: tests cardAdventurer) from dominion.c
 ** Input: function takes int drawntreasure, struct gameState
 **         *state, int currentPlayer, int cardDrawn, 
 **         int temphand[], int z
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
    int success_ct = 0;
    int playerCount = 2;
    int player1 = 0;
    int player2 = 1;
    int seed = 3;
    int cardDrawn; //To track drawn card during play
    int temphand[MAX_HAND]; //To track revealed cards
    int z = 0; //For indexing into temphand
    int drawnTreasure1 = 0;
    int drawnTreasure2 = 0; //To compare before and after play
    int deckCount_b4, deckCount;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int test_k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState state, testState;

    //Print title
    printf("\n\nCard Test 2: cardAdventurer()\n\n");

    //Initialize game state
    printf("Initializing game\n");
    initializeGame(playerCount, k, seed, &state);

    //Copy state into testState and play card for TEST 1
    printf("Copying state into testState\n");
    memcpy(&testState, &state, sizeof(struct gameState));

    //Place two treasure cards on top of deck for player 1
    //and play adventurer card
    printf("Top card is now: %i\n", testState.deck[player1][testState.deckCount[player1]-1]);//Check top card
    printf("Adding treasure cards to top of deck\n");
    deckCount = testState.deckCount[player1];
    testState.deck[player1][deckCount] = gold; //Add card
    testState.deckCount[player1]++; //Increase deck count
    printf("Top card is now: %i\n", testState.deck[player1][testState.deckCount[player1]-1]);//Check top card

    deckCount = testState.deckCount[player1]; 
    testState.deck[player1][deckCount] = silver; //Add card
    testState.deckCount[player1]++; //Increase deck count
    printf("Top card is now: %i\n", testState.deck[player1][testState.deckCount[player1]-1]);//Check top card

    deckCount_b4 = testState.deckCount[player1];

    printf("Playing Adventurer Card\n");
    cardAdventurer(drawnTreasure2, &testState, player1, cardDrawn, temphand, z);


    //TEST 1 - Check exactly 2 cards drawn from top were treasure cards/treasure
    //cards were placed into hand of player 1
    printf("\n\nTEST 1: top two deck cards == treasure (copper, silver, or gold) && cards drawn == 2\n\n");
    printf("drawnTreasure before: %i, drawnTreasure after: %i\n", drawnTreasure1, drawnTreasure2);
    printf("deck count player 1 before: %i, after: %i\n", deckCount_b4, testState.deckCount[player1]);
    printf("Top card is now: %i\n", testState.deck[player1][testState.deckCount[player1]-1]);//Check top card
   // assert(drawnTreasure2 == 2 && testState.deckCount[player1] == state.deckCount[player1] - 2);



    //Copy state into testState for TEST 2
    printf("Copying state into testState\n");
    memcpy(&testState, &state, sizeof(struct gameState));
    printf("Top card is now: %i\n", testState.deck[player1][testState.deckCount[player1]-1]);//Check top card

    //Adding 1 more treasure card to top of deck
    printf("Adding treasure cards to top of deck\n");
    deckCount = testState.deckCount[player1];
    testState.deck[player1][deckCount] = gold; //Add card
    testState.deckCount[player1]++; //Increase deck count
    printf("Top card is now: %i\n", testState.deck[player1][testState.deckCount[player1]-1]);//Check top card

    //Add non-treasure cards to top of deck - deck will now end with "gold,
    //sea_hag, gardens"
    printf("Adding non-treasure cards to top of deck\n");
    deckCount = testState.deckCount[player1];
    testState.deck[player1][deckCount] = sea_hag; //Add card
    testState.deckCount[player1]++; //Increase deck count
    printf("Top card is now: %i\n", testState.deck[player1][testState.deckCount[player1]-1]);//Check top card

    deckCount = testState.deckCount[player1]; 
    testState.deck[player1][deckCount] = gardens; //Add card
    testState.deckCount[player1]++; //Increase deck count
    printf("Top card is now: %i\n", testState.deck[player1][testState.deckCount[player1]-1]);//Check top card

    deckCount_b4 = testState.deckCount[player1];
    drawnTreasure2 = 0;//Reset drawnTreasure2

    //Replay card
    printf("Playing Adventurer Card\n");
    cardAdventurer(drawnTreasure2, &testState, player1, cardDrawn, temphand, z);



    //TEST 2 - Check that top two non-treasure cards from deck were
    //discarded- discard deck should now have
    //gardens and sea hag as top two cards
    printf("\n\nTEST 2: Test correct discarding of revealed cards\n\n");
    deckCount = testState.discardCount[player1];
    printf("Top of player 1's discard pile is: %i\n", testState.discard[player1][deckCount-1]);
    printf("Second from top is: %i\n", testState.discard[player1][deckCount-2]);
    assert(testState.discard[player1][deckCount-1] == gardens && testState.discard[player1][deckCount-2] == sea_hag);

    
    
    //TEST 3 - Check that game state did not change for player 2
    //by checking deck, hand, and discard unchanged
    printf("\n\nTEST 3: Test game state unchanged for other players (player 2)\n\n");
    assert(testState.handCount[player2] == state.handCount[player2]);
    
    assert(testState.deckCount[player2] == state.deckCount[player2]);
    
    assert(testState.discardCount[player2] == state.discardCount[player2]);


    //TEST 4 - Check that Kingdom pile has not changed
    printf("\n\nTEST 4: Check Kingdom pile unchanged\n\n");
    for(i=0; i < 10; i++){
        assert(k[i] != test_k[i]);
    }


    //Tally successes
    //if(success_ct == 15) printf("\nAll tests passed. SUCCESS.\n");
    //else printf("\nAt least one test failed. Please review results.\n");
    assert(success_ct == 15);

    return 0;
}
