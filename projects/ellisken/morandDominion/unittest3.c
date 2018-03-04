/***********************************************************
 ** Program Filename: unittest3.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 4, 2018
 ** Description: Unit test of fullDeckCount(), which returns
 **     the count of a specific card in a specific player's 
 **     discard deck and hand. Tested for a 2 player game.
 ** Input: function takes struct gamestate *state, int card
 **     int player
 ** Output:
 ***********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

int main(){
    //Print title
    printf("\n\nUnit Test 3: fullDeckCount()\n\n");
    //Initialize gameState with 2 players
    int i, j, m;
    int success_ct, card_ct, man_card_ct;
    success_ct = 0;
    int playerCount = 2;
    int player1 = 0;
    int player2 = 1;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 3; //For randomizing shuffling result
    struct gameState state, testState;

    initializeGame(playerCount, k, seed, &state); 




    //TEST 1 - Change the deck contents of Player 1 and 
    //assert that fullDeckCount for Player 1 != fullDeckCount for Player 2
    printf("\n\nTEST 1: Change deck contents of Player 1, assert deck count change from Player 2 and original state\n");
    memcpy(&testState, &state, sizeof(struct gameState)); //Make copy of state for test
    for(i=0; i < testState.deckCount[player1]; i++){
        testState.deck[player1][i] =  curse;} 

    if(fullDeckCount(player1, curse, &testState) != fullDeckCount(player2, curse, &testState) &&
            fullDeckCount(player1, curse, &testState) != fullDeckCount(player1, curse, &state)){
        printf("---TEST 1 passed---\n");
        success_ct++;}
    else printf("---TEST 1 failed---\n");
    
    
    
    //TEST 2 - Change the deck contents of Players 1 and 2 and  
    //assert that fullDeckCount for original state != count for testState
    printf("\n\nTEST 2: Change deck contents of Players 1&2, assert deck count change from original state\n");
    memcpy(&testState, &state, sizeof(struct gameState)); //Make copy of state for test
    for(i=0; i < testState.deckCount[player1]; i++){
        testState.deck[player1][i] =  curse;} 
    for(i=0; i < testState.deckCount[player2]; i++){
        testState.deck[player2][i] = treasure_map;}

    if(fullDeckCount(player1, curse, &testState) != fullDeckCount(player1, curse, &state) &&
            fullDeckCount(player2, treasure_map, &testState) != fullDeckCount(player2, treasure_map, &state)){
        printf("---TEST 2 passed---\n");
        success_ct++;}
    else printf("---TEST 2 failed---\n");



    //TEST 3 -Change hand contents
    printf("\n\nTEST 3: Change hand contents of Player 1, assert hand count change from Player 2 and original state\n");
    memcpy(&testState, &state, sizeof(struct gameState)); //Make copy of state for test
    for(i=0; i < testState.handCount[player1]; i++){
        testState.hand[player1][i] =  curse;} 

    if(fullDeckCount(player1, curse, &testState) != fullDeckCount(player2, curse, &testState) &&
            fullDeckCount(player1, curse, &testState) != fullDeckCount(player1, curse, &state)){
        printf("---TEST 3 passed---\n");
        success_ct++;}
    else printf("---TEST 3 failed---\n");



    //TEST 4 - Change discard contents
    printf("\n\nTEST 4: Change discard contents of Player 1, assert deck count change from Player 2 and original state\n");
    memcpy(&testState, &state, sizeof(struct gameState)); //Make copy of state for test
    testState.discardCount[player1] = 2; //Increase discardCount for Player 1
    for(i=0; i < testState.discardCount[player1]; i++){
        testState.discard[player1][i] =  curse;} 

    if(fullDeckCount(player1, curse, &testState) != fullDeckCount(player2, curse, &testState) &&
            fullDeckCount(player1, curse, &testState) != fullDeckCount(player1, curse, &state)){
        printf("---TEST 4 passed---\n");
        success_ct++;}
    else printf("---TEST 4 failed---\n");

    

    //TEST 5 - Manually count deck for each player and compare to result from
    //fullDeckCount for each card.
    printf("\n\nTEST 5 - Compare manual deck count to fullDeckCount()\n");
    for(i=0; i < playerCount; i++){
        //Get manual count
        man_card_ct = 0;
        for(j=curse; j < treasure_map; j++){
            for(m=0; m < state.deckCount[i]; m++){
                if(state.deck[i][m] == j) man_card_ct++;}
            for(m=0; m < state.handCount[i]; m++){
                if(state.hand[i][m] == j) man_card_ct++;}
            for(m=0; m < state.discardCount[i]; m++){
                if(state.discard[i][m] == j) man_card_ct++;}
        }

        //Get fullDeckCount count
        card_ct = 0;
        for(j=curse; j <= treasure_map; j++){
            if(fullDeckCount(i, j, &state) > 0) card_ct+= fullDeckCount(i, j, &state);}
        
        
        //Compare counts
        if(man_card_ct == card_ct){
            printf("---TEST 5 passed for player %i\n", i);
            success_ct++;}
        else printf("---TEST 5 failed for player %i\n", i);
    }


    if(success_ct == 6) printf("\nAll tests PASSED. SUCCESS.\n");
    else printf("\nAt least one test FAILED. Please review.\n");
    return 0;
}
