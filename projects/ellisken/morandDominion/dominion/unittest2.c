/***********************************************************
 ** Program Filename: unittest2.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 4, 2018
 ** Description: Unit test of isGameOver() from dominion.c
 **     which checks the number of provinces or if three
 **     supply piles are empty to determine if the game
 **     is over.
 ** Input: function takes struct gamestate *state
 ** Output:
 ***********************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

int assertTrue(int exp){
    if(exp)
        return 1;
    else return 0;
}

int main(){
    //Print title
    printf("\n\nUnit Test 2: isGameOver()\n\n");

    //Initialize gameState with 2 players
    int i;
    int success_ct = 0; //For tallying successful tests
    int playerCount = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 3; //For randomizing shuffling result
    struct gameState state, testState;

    initializeGame(playerCount, k, seed, &state);



    //TEST 1 - Test if Game is over based on supply piles/province count
    //at game beginning. Province cards == 8 and no supply == 0, so Game should not be over.
    //This test is meant as a control.
    printf("TEST 1: Game NOT over after initialization of gameState for play\n");
    if(isGameOver(&state) == 0){
        printf("---TEST 1 passed---\n");
        success_ct++;}
    else printf("---TEST 1 failed---\n");


    //TEST 2 - Change province card count to empty and check Game over detection.
    memcpy(&testState, &state, sizeof(struct gameState)); //Copy original state to test state
    testState.supplyCount[province] = 0;

    printf("TEST 2: Game OVER after province supply set to 0\n");

    if(isGameOver(&testState) == !isGameOver(&state)){
        printf("---TEST 2 passed---\n");
        success_ct++;}
    else printf("---TEST 2 failed---\n");



    //TEST 3 - Change supply count of each card in the supply pile
    //to 0, but keep the supply of province greater than 0
    for(i=curse; i < treasure_map; i++){
        testState.supplyCount[i] = 0;
    }

    testState.supplyCount[province] = 1;

    printf("TEST 3: Game OVER when province supply > 0, but all other supplies empty\n");
    if(isGameOver(&testState) == !isGameOver(&state)){
        printf("---TEST 3 passed---\n");
        success_ct++;}
    else printf("---TEST 3 failed---\n");



    //TEST 4 - Change supply count of each card in the supply pile
    //to 1, then change the supply count of 2 non-province
    //cards to 0. Checks when empty supply pile < 3
    for(i=curse; i < treasure_map; i++){
        testState.supplyCount[i] = 1;
    }

    testState.supplyCount[curse] = 0;
    testState.supplyCount[estate] = 0;

    printf("TEST 4: Game NOT over when province > 0 and exactly 2 cards in beginning of enum==0\n");
    if(isGameOver(&testState) == isGameOver(&state)){
        printf("---TEST 4 passed---\n");
        success_ct++;}
    else printf("---TEST 4 failed---\n");

    
    
    //TEST 5 - Change supply count of each card in the supply pile
    //to nonzero, then change the supply count of 2 non-province
    //cards in end of card enum to 0. Checks when empty supply pile < 3
    for(i=curse; i < treasure_map; i++){
        testState.supplyCount[i] = 1;
    }

    testState.supplyCount[sea_hag] = 0;
    testState.supplyCount[treasure_map] = 0;

    printf("TEST 5: Game NOT over when province > 0 and exactly 2 cards in end of enum==0\n");
    if(isGameOver(&testState) == isGameOver(&state)){
        printf("---TEST 5 passed---\n");
        success_ct++;}
    else printf("---TEST 5 failed---\n");


    //TEST 6 - Change supply count of each card in the supply pile
    //to nonzero, then change the supply count of 3 non-province
    //cards in the beginning of card enum to 0. Checks when empty supply pile == 3
    for(i=curse; i <= treasure_map; i++){
        testState.supplyCount[i] = 1;
    }

    testState.supplyCount[curse] = 0;
    testState.supplyCount[estate] = 0;
    testState.supplyCount[duchy] = 0;

    printf("TEST 6: Game OVER when province > 0 and exactly 3 cards in beginning of enum==0\n");
    if(isGameOver(&testState) == !isGameOver(&state)){
        printf("---TEST 6 passed---\n");
        success_ct++;}
    else printf("---TEST 6 failed---\n");


    //TEST 7 - Change supply count of each card in the supply pile
    //to nonzero, then change the supply count of 3 non-province
    //cards in the end of card enum to 0. Checks when empty supply pile == 3
    for(i=curse; i <= treasure_map; i++){
        testState.supplyCount[i] = 1;
    }

    testState.supplyCount[salvager] = 0;
    testState.supplyCount[sea_hag] = 0;
    testState.supplyCount[treasure_map] = 0;
    
    printf("TEST 7: Game OVER when province > 0 and exactly 3 cards in end of enum==0\n");
    if(isGameOver(&testState) == !isGameOver(&state)){
        printf("---TEST 7 passed---\n");
        success_ct++;}
    else printf("---TEST 7 failed---\n");


    //TEST 8 - Change supply count of each card in the supply pile
    //to nonzero, then change the supply count of 4 non-province
    //cards to 0. Checks when empty supply pile > 3
    for(i=curse; i <= treasure_map; i++){
        testState.supplyCount[i] = 1;
    }

    testState.supplyCount[curse] = 0;
    testState.supplyCount[estate] = 0;
    testState.supplyCount[duchy] = 0;
    testState.supplyCount[copper] = 0;
    
    printf("TEST 8: Game OVER when province > 0 and exactly 4 cards in supply are empty\n");
    if(isGameOver(&testState) == !isGameOver(&state)){
        printf("---TEST 8 passed---\n");
        success_ct++;}
    else printf("---TEST 8 failed---\n");

    
    //TEST 9 - Change supply count of each card in the supply pile
    //to zero
    for(i=curse; i <= treasure_map; i++){
        testState.supplyCount[i] = 0;
    }

    printf("TEST 9: Game OVER when supply of ALL cards is empty\n");
    if(isGameOver(&testState) == !isGameOver(&state)){
        printf("---TEST 9 passed---\n");
        success_ct++;}
    else printf("---TEST 9 failed---\n");

    if(success_ct == 9) printf("\nAll tests PASSED. SUCCESS.\n");
    else printf("\nAt least one test FAILED. please review.\n");

    return 0;
}
