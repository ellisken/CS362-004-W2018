/***************************************************************
 ** Program Filename: randomtestadventurer.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 8, 2018
 ** Description: unit test for cardAdventurer() from dominion.c
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
    int i, j;
    int playerCount = 2;
    int player1 = 0;
    int player2 = 1;
    int seed = 1000;
    int cardDrawn; //To track drawn card during play
    int temphand[MAX_HAND]; //To track revealed cards
    int z = 0; //For indexing into temphand
    int drawnTreasure = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState state, testState;
    int deckCt; //For testing different draw deck sizes, randomly generated
    int discardCt, card; //Randomly generated each test
    int treasure; //Flag used when checking piles for treasure

    //Print title
    printf("\n\nRandom Test: ADVENTURER\n\n");

    //Seed PRNG
    srand(time(NULL));


    //Invoke initializeGame() to create game state
    //for 2 players
    printf("Initializing game\n");
    initializeGame(playerCount, k, seed, &state);

    
    //For each deck count of 0, 1, 2, 250, and 500:
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
    printf("Initial Deck: %i\t", state.deckCount[player1]);
    printf("Initial Hand: %i\t", state.handCount[player1]);
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

    if(treasure < 3) printf("No treasure in deck - results in SEGMENTATION FAULT");


    //Else, make copy of state and
    //play adventurer with test copy
    printf("Copying state into testState\n");
    memcpy(&testState, &state, sizeof(struct gameState));

    printf("Playing Adventurer card.\n");
    cardAdventurer(drawnTreasure, &testState, player1, cardDrawn, temphand, z);


    //Print resulting values for drawnTreasure,
    //size of deck, and size of discard
    printf("Adventurer card played.\n");
    


    //TEST 1: Check drawnTreasure has increased by two

    //TEST 2: Check hand count has increased by two

    //TEST 3: Check top two hand cards are now Treasure cards

    //TEST 4: Check state has not changed for other player






    return 0;
}
