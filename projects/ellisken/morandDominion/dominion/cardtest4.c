/***********************************************************
 ** Program Filename: cardtest1.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 4, 2018
 ** Description: tests play of great hall card using cardEffect()
 **         from dominion.c. Great Hall should draw 1 card
 **         for the current player and add to number of
 **         actions remaining for the player. All other
 **         gameState members should be unaffected. All other
 **         players should be unaffected.
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
    int i, j;
    int hc, dc, dis; //For recording hand, deck, and discard
    int result; //For storing cardEffect() return
    int c1, c2, c3;
    c1=c2=c3=1; //Dummy choices for calling cardEffect()
    int handPos = 1; //Dummy position for calling cardEffect()
    int *bonus; //Dummy ptr for calling cardEffect()
    int playerCount = 2;
    int player1 = 0;
    int player2 = 1;
    int success_ct = 0;
    int seed = 3;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState state, testState;

    //Print title
    printf("\n\nCard Test 4: great hall\n\n");

    //Initialize game state
    initializeGame(playerCount, k, seed, &state);

    //Copy state into testState and play card
    memcpy(&testState, &state, sizeof(struct gameState));
    result = cardEffect(great_hall, c1, c2, c3, &testState, handPos, bonus);

    //TEST 1 - Check that great hall played successfully
    //(i.e., returned 0)
    printf("\n\nTEST 1: Check return value is as expected (0)\n\n");
    if(result == 0){
        printf("---TEST 1 passed---\n");
        success_ct++;}
    else printf("---TEST 1 failed---\n");



    //TEST 2 - Check card drawn for player 1 (player 1 always plays first)
    printf("\n\nTEST 2: Check player 1 deck decreased by 1\n\n");
    if(testState.deckCount[player1] == state.deckCount[player1] - 1){
        printf("---TEST 2 passed---\n");
        success_ct++;}
    else printf("---TEST 2 failed---\n");

    
    
    //TEST 3 - Check numActions has incremented by 1
    printf("\n\nTEST 3: Check that state gained action\n\n");
    if(testState.numActions == state.numActions + 1){
        printf("---TEST 3 passed---\n");
        success_ct++;}
    else printf("---TEST 3 failed---\n");
    
    
    
    //TEST 4 - Check discardCount has increased
    printf("\n\nTEST 4: Check that player's discard pile has increased\n\n");
    if(testState.discardCount[player1] == state.discardCount[player1] + 1){
        printf("---TEST 4 passed---\n");
        success_ct++;}
    else printf("---TEST 4 failed---\n");
    
    
    
    //TEST 5 - Check state unchanged (for player 2)
    printf("\n\nTEST 5: Check that state int values unchanged for player 2\n\n");
    if(testState.numPlayers != state.numPlayers) printf("---TEST 5 failed numPlayers---\n");
    if(testState.outpostPlayed != state.outpostPlayed) printf("---TEST 5 failed outpostPlayed---\n");
    if(testState.outpostTurn != state.outpostTurn) printf("---TEST 5 failed outpostTurn---\n");
    if(testState.whoseTurn != state.whoseTurn) printf("---TEST 5 failed whoseTurn---\n");
    if(testState.phase != state.phase) printf("---TEST 5 failed phase---\n");
    if(testState.coins != state.coins) printf("---TEST 5 failed coins---\n");
    if(testState.numBuys != state.numBuys) printf("---TEST 5 failed numBuys---\n");
    if(testState.handCount[player2] != state.handCount[player2]) printf("---TEST 5 failed hand ct 2---\n");
    if(testState.deckCount[player2] != state.deckCount[player2]) printf("---TEST 5 failed deck ct 2---\n");
    if(testState.discardCount[player2] != state.discardCount[player2]) printf("---TEST 5 failed discard ct 2---\n");
    printf("Played card count before: %i, played card count after: %i\n", state.playedCardCount, testState.playedCardCount);
    if(testState.playedCardCount != state.playedCardCount) printf("---TEST 5 failed played card ct---\n");
    else{printf("---TEST 5 passed---\n");
        success_ct++;}

    
    
    //TEST 6 - Check that playing great hall through cardEffect() did not change 
    //any deck values for player 2 or any other state members
    result = 1; //set result to true
    printf("\n\nTEST 6: Check playing great hall did not affect array gameState values\n\n");
    for(i=0; i < treasure_map + 1; i++){
        if(testState.supplyCount[i] != state.supplyCount[i]){
        printf("---TEST 6 failed supplyCount---\n");
        result = 0;}}
    for(i=0; i < treasure_map + 1; i++){
        if(testState.embargoTokens[i] != state.embargoTokens[i]){
        printf("---TEST 6 failed embargoTokens---\n");
        result = 0;}}

    //Test hand, deck, and discard
        hc = state.handCount[player2];
        dc = state.deckCount[player2];
        dis = state.discardCount[player2];

        for(j=0; j < hc; j++){
            if(testState.hand[player2][j] != testState.hand[player2][j]){
                printf("---TEST 6 failed hand check---\n", i);
                result = 0;}}
        for(j=0; j < dc; j++){
            if(testState.deck[player2][j] != testState.deck[player2][j]){
                printf("---TEST 6 failed deck check---\n", i);
                result = 0;}}
        for(j=0; j < dis; j++){
            if(testState.discard[player2][j] != testState.discard[player2][j]){
            printf("---TEST 6 failed discard check---\n", i);
            result = 0;}}
    
    
    if(result == 1){
        printf("---TEST 6 passed---\n");
        success_ct++;}
    
    //Tally results
    if(success_ct == 6) printf("\nAll tests passed. SUCCESS.\n");
    else printf("\nAt least one test failed. Please review results.\n");


    return 0;
}

