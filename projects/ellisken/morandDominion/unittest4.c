/***********************************************************
 ** Program Filename: unittest4.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 4, 2018
 ** Description: Unit test of scoreFor() which calculates
 **     a specific player's current score.
 ** Input: function takes struct gamestate *state and int player
 ** Output: Success or failure
 ***********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

/* Title: totalDeckCount()
 * Description: Gets the total deck count for a given player
 * Inputs: player, gameState
 * Dependencies: Uses fullDeckCount() from dominion.c
 * Output: returns total count of all cards from player's deck
* */
int totalDeckCount(int player, struct gameState state){
    int count = 0;
    int i;

    for(i=curse; i <= treasure_map; i++){
        if(fullDeckCount(player, i, &state) > 0) count+= fullDeckCount(player, i, &state);
    }

    printf("Full deck count for player %i is: %i\n", player, count);
    return count;
}

int main(){
    //Initialize gameState with 2 players
    int i,j;
    int playerCount = 2;
    int player1 = 0;
    int player2 = 1;
    int success_ct = 0;
    int man_card_ct, card_ct;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 3; //For randomizing shuffling result
    struct gameState state, testState;

    //Print title
    printf("\n\nUnit Test 4: scoreFor()\n\n");

    initializeGame(playerCount, k, seed, &state); 

    //TEST 1 - Manually test and compare score from deck based on deck at game
    //start
    printf("i\n\nTEST 1: Compare manual score count with scoreFor() result\n\n");
    for(i=0; i < playerCount; i++){
        //Get manual score
        man_card_ct = 0;
        for(j=0; j < state.handCount[i]; j++){
            printf("\n\nManually counting hand card %i\n", j);
            if(state.hand[i][j] == curse) man_card_ct = man_card_ct - 1;
            if(state.hand[i][j] == estate) man_card_ct += 1;
            if(state.hand[i][j] == duchy) man_card_ct +=3;
            if(state.hand[i][j] == province) man_card_ct += 6;
            if(state.hand[i][j] == gardens) 
                man_card_ct += (totalDeckCount(i, state) / 10);
            if(state.hand[i][j] == great_hall) man_card_ct += 1;
            printf("Card: %i, manual count total: %i\n", state.hand[i][j], man_card_ct);}
        
        for(j=0; j < state.deckCount[i]; j++){
            printf("\n\nManually counting deck card %i\n", j);
            if(state.deck[i][j] == curse) man_card_ct = man_card_ct - 1;
            if(state.deck[i][j] == estate) man_card_ct += 1;
            if(state.deck[i][j] == duchy) man_card_ct +=3;
            if(state.deck[i][j] == province) man_card_ct += 6;
            if(state.deck[i][j] == gardens) 
                man_card_ct += (totalDeckCount(i, state) / 10);
            if(state.deck[i][j] == great_hall) man_card_ct += 1;
            printf("Card: %i, manual count total: %i\n", state.deck[i][j], man_card_ct);}
        
        for(j=0; j < state.discardCount[i]; j++){
            printf("\n\nManually counting discard card %i\n", j);
            if(state.discard[i][j] == curse) man_card_ct = man_card_ct - 1;
            if(state.discard[i][j] == estate) man_card_ct += 1;
            if(state.discard[i][j] == duchy) man_card_ct +=3;
            if(state.discard[i][j] == province) man_card_ct += 6;
            if(state.discard[i][j] == gardens) 
                man_card_ct += (totalDeckCount(i, state) / 10);
            if(state.discard[i][j] == great_hall) man_card_ct += 1;
            printf("Card: %i, manual count total: %i\n", state.discard[i][j], man_card_ct);}
        
        printf("Manual score at start: %i\n", man_card_ct);

        //Get functional score from scoreFor()
        card_ct = scoreFor(i, &state);
        printf("Functional score at start: %i\n", card_ct);
    
        //Compare results
        if(man_card_ct == card_ct){
            printf("---TEST 1 passed for player %i---\n", i);
            success_ct++;}
        else printf("---TEST 1 failed for player %i---\n", i);
    }



    //TEST 2 - Create test state and change values in test. Compare score with
    //original state
    printf("\n\nTEST 2: Change card counts for first player in test state and compare\n\n");

    memcpy(&testState, &state, sizeof(struct gameState));//Copy into test state for comparison

    //Erase all cards for player 1
    testState.deckCount[player1] = 0;
    testState.handCount[player1] = 0;
    testState.discardCount[player1] = 0;

    //Give player 1 a copy of each card that affects score for deck, hand, and
    //discard
    for(j=0; j < 6; j++){
        if(j==0){
            testState.deck[player1][j] = curse;
            testState.deckCount[player1]++;
            testState.hand[player1][j] = curse;
            testState.handCount[player1]++;
            testState.deck[player1][j] = curse;
            testState.handCount[player1]++;}

        else if(j==1){
            testState.deck[player1][j] = estate;
            testState.deckCount[player1]++;
            testState.hand[player1][j] = estate;
            testState.handCount[player1]++;
            testState.deck[player1][j] = estate;
            testState.handCount[player1]++;}

        else if(j==2){
            testState.deck[player1][j] = duchy;
            testState.deckCount[player1]++;
            testState.hand[player1][j] = duchy;
            testState.handCount[player1]++;
            testState.deck[player1][j] = duchy;
            testState.handCount[player1]++;}

        else if(j==3){
            testState.deck[player1][j] = province;
            testState.deckCount[player1]++;
            testState.hand[player1][j] = province;
            testState.handCount[player1]++;
            testState.deck[player1][j] = province;
            testState.handCount[player1]++;}

        else if(j==4){
            testState.deck[player1][j] = great_hall;
            testState.deckCount[player1]++;
            testState.hand[player1][j] = great_hall;
            testState.handCount[player1]++;
            testState.deck[player1][j] = great_hall;
            testState.handCount[player1]++;}

        else if(j==5){
            testState.deck[player1][j] = gardens;
            testState.deckCount[player1]++;
            testState.hand[player1][j] = gardens;
            testState.handCount[player1]++;
            testState.deck[player1][j] = gardens;
            testState.handCount[player1]++;}
    }

    //Compare testState to state
    int testState_exp = 66; // 6 cards * (-1+1+3+6+1) + floor(18cards/10)*6
    int state_exp = 3; //From TEST 1

    printf("scoreFor testState Player 1 EXPECTED: %i\n", testState_exp);
    printf("scoreFor testState Player 1 ACTUAL: %i\n", scoreFor(player1, &testState));
    printf("scoreFor state Player 1 EXPECTED: %i\n", state_exp);
    printf("scoreFor testState Player 1 ACTUAL: %i\n", scoreFor(player1, &state));

    if(scoreFor(player1, &testState) == (scoreFor(player1, &state)+(testState_exp - state_exp))){
        printf("---TEST 2 success---\n");
        success_ct++;}
    else printf("---TEST 2 failure---\n");


    if(success_ct == 2) printf("\nALL tests passed. SUCCESS.\n");
    else printf("\nAt least one test failed. Please review results.\n");


    return 0;
}
