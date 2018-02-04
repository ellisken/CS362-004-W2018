/***********************************************************
 ** Program Filename: cardtest3.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 4, 2018
 ** Description: tests gardens card play using cardEffect()
 **         from dominion.c. Gardens cannot be played,
 **         so cardEffect() should terminate with a -1,
 **         and the gameState should not be affected in
 **         any way.
 ** Input: function takes 
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
    int hc, dc, dis, pc; //For recording hand, deck, and discard counts
    int result; //For storing return value from cardEffect() and for test results
    int c1, c2, c3; //Dummy choices for calling cardEffect()
    c1=c2=c3=1;
    int handPos = 1; //Dummy choice for calling cardEffect()
    int * bonus; //Dummy ptr to int for calling cardEffect()
    int playerCount = 2;
    int player1 = 0;
    int player2 = 0;
    int success_ct = 0;
    int seed = 3;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState state, testState;

    //Initialize game state
    initializeGame(playerCount, k, seed, &state);

    //Copy state into testState and play card
    memcpy(&testState, &state, sizeof(struct gameState));
    result = cardEffect(gardens, c1, c2, c3, &testState, handPos, bonus); 

    //TEST 1 - Check that cardEffect() returned -1
    //(i.e., playing "gardens" did not work)
    printf("\n\nTEST 1: Check return value of cardEffect() as expected (== -1)\n\n");
    if(result == -1){
        printf("---TEST 1 passed---\n");
        success_ct++;}
    else printf("---TEST 1 failed---\n");



    //TEST 2 - Check that playing gardens through cardEffect() did not change 
    //any int state values for players 1 and 2
    printf("\n\nTEST 2: Check playing gardens did not affect simple gameState values\n\n");
    if(testState.numPlayers != state.numPlayers) printf("---TEST 2 failed numPlayers---\n");
    if(testState.outpostPlayed != state.outpostPlayed) printf("---TEST 2 failed outpostPlayed---\n");
    if(testState.outpostTurn != state.outpostTurn) printf("---TEST 2 failed outpostTurn---\n");
    if(testState.whoseTurn != state.whoseTurn) printf("---TEST 2 failed whoseTurn---\n");
    if(testState.phase != state.phase) printf("---TEST 2 failed phase---\n");
    if(testState.numActions != state.numActions) printf("---TEST 2 failed numActions---\n");
    if(testState.coins != state.coins) printf("---TEST 2 failed coins---\n");
    if(testState.numBuys != state.numBuys) printf("---TEST 2 failed numBuys---\n");
    if(testState.handCount[player1] != state.handCount[player1]) printf("---TEST 2 failed hand ct 1---\n");
    if(testState.deckCount[player1] != state.deckCount[player1]) printf("---TEST 2 failed deck ct 1---\n");
    if(testState.discardCount[player1] != state.discardCount[player1]) printf("---TEST 2 failed discard ct 1---\n");
    if(testState.handCount[player2] != state.handCount[player2]) printf("---TEST 2 failed hand ct 2---\n");
    if(testState.deckCount[player2] != state.deckCount[player2]) printf("---TEST 2 failed deck ct 2---\n");
    if(testState.discardCount[player2] != state.discardCount[player2]) printf("---TEST 2 failed discard ct 2---\n");
    if(testState.playedCardCount != state.playedCardCount) printf("---TEST 2 failed played card ct---\n");
    else{printf("---TEST 2 passed---\n");
        success_ct++;}



    //TEST 3 - Check that playing gardens through cardEffect() did not change 
    //any deck values for players 1 and 2
    result = 1; //set result to true
    printf("\n\nTEST 3: Check playing gardens did not affect array gameState values\n\n");
    for(i=0; i < treasure_map + 1; i++){
        if(testState.supplyCount[i] != state.supplyCount[i]){
        printf("---TEST 3 failed supplyCount---\n");
        result = 0;}}
    for(i=0; i < treasure_map + 1; i++){
        if(testState.embargoTokens[i] != state.embargoTokens[i]){
        printf("---TEST 3 failed embargoTokens---\n");
        result = 0;}}

    //Test hand, deck, and discard
    for(i=0; i < playerCount; i++){
        hc = state.handCount[i];
        dc = state.deckCount[i];
        dis = state.discardCount[i];

        for(j=0; j < hc; j++){
            if(testState.hand[i][j] != testState.hand[i][j]){
                printf("---TEST 3 failed hand check for player %i---\n", i);
                result = 0;}}
        for(j=0; j < dc; j++){
            if(testState.deck[i][j] != testState.deck[i][j]){
                printf("---TEST 3 failed deck check for player %i---\n", i);
                result = 0;}}
        for(j=0; j < dis; j++){
            if(testState.discard[i][j] != testState.discard[i][j]){
            printf("---TEST 3 failed discard check for player %i---\n", i);
            result = 0;}}
    }

    //Test played cards
    pc = state.playedCardCount;
    for(j=0; j < pc; j++){
        if(testState.playedCards[j]!= testState.playedCards[j]){
        printf("---TEST 3 failed discard check for player %i---\n", i);
        result = 0;}}
    
    if(result == 1){
        printf("---TEST 3 passed---\n");
        success_ct++;}


    return 0;
}
