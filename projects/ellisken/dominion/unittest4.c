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

    initializeGame(playerCount, k, seed, &state); 

    //TEST 1 - Manually test and compare score from deck based on deck at game
    //start
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









    return 0;
}
