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
    int drawnTreasure;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState state, testState;
    int deckSizes[5] = {0, 1, 2, 250, 500}; //Input array for draw pile size
    int drawCt; //For testing different draw deck sizes
    int discardCt, card; //Randomly generated each test

    //Print title
    printf("\n\nRandom Test: ADVENTURER\n\n");

    //Seed PRNG
    srand(time(NULL));


    //Invoke initializeGame() to create game state
    //for 2 players
    printf("Initializing game\n");
    intitializeGame(playerCount, k, seed, &state);

    
    //For each deck count of 0, 1, 2, 250, and 500:
    for(i=0; i < 5; i++){
        deckCt = deckSizes[i];
        discardCt = rand() % (MAX_HAND + 1); //Generate random discard count

        //Change state discard and deck numbers for player 1




    
        //Check deck and discard piles for treasure
        //If treasure cards < 2, exit and assert

        //Print initial values for drawnTreasure,
        //size of deck, size of hand, and size of discard


        //Else, make copy of state and
        //play adventurer with test copy


        //Print resulting values for drawnTreasure,
        //size of deck, and size of discard


        //TEST 1: Check drawnTreasure has increased by two

        //TEST 2: Check hand count has increased by two

        //TEST 3: Check top two hand cards are now Treasure cards

        //TEST 4: Check state has not changed for other player

    }





    return 0;
}
