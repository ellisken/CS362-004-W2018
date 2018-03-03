/***************************************************************
 ** Program Filename: randomtestadventurer.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 8, 2018
 ** Description: unit test for adventurerEffect() from dominion.c
 **     using a random input generator
 ** Input:
 ** Output:
 **************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
    //Variables
    int i, j, m;
    m = 0;
    int playerCount = 2;
    int player1 = 0;
    int player2 = 1;
    int seed = 1000;
    int temphand[MAX_HAND]; //To track revealed cards
    int drawnTreasure = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState state, testState;
    int deckCt; //For testing different draw deck sizes, randomly generated
    int discardCt, card; //Randomly generated each test
    int treasure; //Flag used when checking piles for treasure
    int card1, card2; //To store top two cards from hand during tests

    //Print title
    printf("\n\nRandom Test: ADVENTURER\n\n");

    //Seed PRNG
    srand(time(NULL));


    //Invoke initializeGame() to create game state
    //for 2 players
    printf("Initializing game\n\n\n");
    initializeGame(playerCount, k, seed, &state);

    
    //Continually generate random deck and discard piles
    //and play Adventurer until failure
    while(1){
        deckCt = rand() % (MAX_HAND + 1);
        discardCt = rand() % (MAX_HAND + 1); //Generate random discard count

        //Change state discard and deck numbers for player 1
        state.deckCount[player1] = deckCt;
        state.discardCount[player1] = discardCt;

        //Fill player 1 deck and discard with randomly selected cards
        for(j=0; j < deckCt; j++){
            card = rand() % 27; //Cards are numbered 0 through 26
            state.deck[player1][j] = card;}

        for(j=0; j < discardCt; j++){
            card = rand() % 27;
            state.discard[player1][j] = card;}


        //Print initial values for drawnTreasure,
        //size of deck, size of hand, and size of discard
        printf("\n(%i)Initial Deck: %i\t", m++, state.deckCount[player1]);
        printf("Initial Hand: %i\t\t", state.handCount[player1]);
        printf("Initial Discard: %i\n", state.discardCount[player1]);
        
        //Check deck and discard piles for treasure
        //If treasure cards < 2, exit and assert
        treasure = 0;
        for(i=0; i < deckCt; i++){
            card = state.deck[player1][i];
            if(card == gold || card == silver || card == copper)
                treasure++;}
        for(i=0; i < discardCt; i++){
            card = state.discard[player1][i];
            if(card == gold || card == silver || card == copper)
                treasure++;}

        if(treasure < 2){
            printf("---Not enough treasure in deck - results in SEGMENTATION FAULT----\n");
            exit(1);}


        //Else, make copy of state and
        //play adventurer with test copy
        printf("Copying state into testState\n");
        memcpy(&testState, &state, sizeof(struct gameState));

        printf("Playing Adventurer card.\n");
        z = 0; //Reset the value of z
        adventurerEffect(drawnTreasure, &testState, player1, temphand);


        //Print resulting values for drawnTreasure, hand count
        printf("Adventurer card played.\n");
        printf("Resulting drawnTreasure: %i\n", drawnTreasure);
        printf("Resulting Hand Count: %i\n", testState.handCount[player1]);


        //TEST 1: Check drawnTreasure has increased by two
        /*if(drawnTreasure != 2){
            printf("Error: drawnTreasure != 2 after play.\n");
            exit(1);}*/

        //TEST 2: Check hand count has increased by two
        if(testState.handCount[player1] != state.handCount[player1] + 2){
            printf("\nError: handCount should have increased by exactly 2.\n");
            exit(1);}

        //TEST 3: Check top two hand cards are now Treasure cards
        card1 = testState.hand[player1][testState.handCount[player1]-1];
        card2 = testState.hand[player1][testState.handCount[player1]-2];
        printf("Top card in hand: %i\n", card1);
        printf("Second from the top card in hand: %i\n", card2);
        if(card1 != gold && card1 != silver && card1 != copper){
            printf("\nError: top card is not Treasure. Top card: %i\n", card1);
            exit(1);}
        if(card2 != gold && card2 != silver && card2 != copper){
            printf("\nError: 2nd from top card is not Treasure. 2nd from top card: %i\n", card2);
            exit(1);}

        //TEST 4: Check state has not changed for other player
        if(testState.handCount[player2] != state.handCount[player2]){
            printf("\nError - handCount was changed for player2");
            exit(1);}
        if(testState.deckCount[player2] != state.deckCount[player2]){
            printf("\nError - deckCount was changed for player2");
            exit(1);}
        if(testState.discardCount[player2] != state.discardCount[player2]){
            printf("\nError - discardCount was changed for player2");
            exit(1);}

        printf("\nAll tests passed for iteration %i\n", m-1);
    }

    return 0;
}
