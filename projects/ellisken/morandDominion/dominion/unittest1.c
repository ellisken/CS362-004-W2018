/***********************************************************
 ** Program Filename: unittest1.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 4, 2018
 ** Description: Unit test of supplyCount() from dominion.c
 **         that returns the count of supply for a card
 ** Input: function takes int card, struct gameState *state
 ** Output: Prints indication of Tests 1-3 passed or failed
 ***********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>


int main(){
    //Print title
    printf("\n\nUnit Test 1: supplyCount()\n\n");
    
    //Initialize gameState with 2 players
    int success_ct = 0;
    int i, j;
    int playerCount = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 3; //For randomizing the shuffling result
    struct gameState state, testState;
    
    initializeGame(playerCount, k, seed, &state);
    
    //TEST 1 - check supply count returned for curse is 10
    memcpy(&testState, &state, sizeof(struct gameState));
    printf("TEST 1: Get supply count for curse at game start (2 players)\n");
    if(supplyCount(curse, &testState) == 10 && supplyCount(curse, &testState) == supplyCount(curse, &state)){
        printf("---TEST 1 passed---\n"); success_ct++;}
    else printf("---TEST 1 failed---\n");

    //TEST 2 - check supply count returned for victory cards is 8
    memcpy(&testState, &state, sizeof(struct gameState));
    printf("TEST 2: Get supply count for vicotry cards at game start (2 players)\n");
    if(supplyCount(estate, &testState) != 8 && supplyCount(estate, &testState) == supplyCount(estate, &state))
        printf("---TEST 2 failed---\n");
    else if(supplyCount(duchy, &testState) != 8 && supplyCount(duchy, &testState) == supplyCount(duchy, &state))
        printf("---TEST 2 failed---\n");
    else if(supplyCount(province, &testState) != 8 && supplyCount(province, &testState) == supplyCount(province, &state))
        printf("---TEST 2 failed---\n");
    else {printf("---TEST 2 passed---\n"); success_ct++;}

    //TEST 3 - check supply count returned for treasure cards is correct
    memcpy(&testState, &state, sizeof(struct gameState));
    printf("TEST 3: Get supply count for treasure cards at game start (2 players)\n");
    if(supplyCount(copper, &testState) != 60-7*playerCount && supplyCount(copper, &testState) == supplyCount(copper, &state))
        printf("---TEST 3 failed---\n");
    else if(supplyCount(silver, &testState) != 40 && supplyCount(silver, &testState) == supplyCount(silver, &state))
        printf("---TEST 3 failed---\n");
    else if(supplyCount(gold, &testState) != 30 && supplyCount(gold, &testState) == supplyCount(gold, &state)) 
        printf("---TEST 3 failed---\n");
    else {printf("---TEST 3 passed---\n"); success_ct++;}

    //TEST 4 - check supply count == 1 for each kingdom card in k
    memcpy(&testState, &state, sizeof(struct gameState));
    printf("TEST 4: Get supply count for selected kingdom cards at game start (2 players)\n");
    for(i=adventurer; i < treasure_map; i++){
        for(j=0; j < 10; j++){
            if(i == k[j]){
                if(supplyCount(j, &testState) == 0)
                    printf("---TEST 4 failed on kingdom card %i---\n", i);
                else{printf("---TEST 4 passed for kingdom card %i---\n", i);
                    success_ct++;
                }
            }
        }
    }

    if(success_ct == 13) printf("\nAll tests PASSED. SUCCESS.\n");
    else printf("\nAt least one test FAILED. Please review.\n");


    return 0;
}

