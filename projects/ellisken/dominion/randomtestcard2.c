/***************************************************************
 ** Program Filename: randomtestcard2.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 15, 2018
 ** Description: unit test for playing Council Room from dominion.c
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
    int n=0;
    int playerCount = 4;
    int currentPlayer;
    int handPos; //Will be randomly generated based on handCount
    int c1, c2, c3; //Dummy choices for calling cardEffect()
    c1=c2=c3=0;
    int *bonus; //Dummy ptr to int for calling cardEffect()
    int seed = 1000;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState state, testState;

    //Print title
    printf("\n\nrandomtestcard2: COUNCIL ROOM\n\n");

    //Seed PRNG
    srand(time(NULL));

    //Continually generate random currentPlayer
    //and handPos and play Council Room  1000 times
    //NOTE: while loop easily modified to run
    //until failure
    while(n < 1000){
        printf("\n\n---Iteration: %i---\n", n++);
        
        //Invoke initializeGame() to create game state
        //for 4 players
        printf("Initializing game\n\n\n");
        initializeGame(playerCount, k, seed, &state);
    
        //Generate random currentPlayer and handPos
        currentPlayer = rand() % 4;
        handPos = rand() % 5; //modulo 5 because each player starts with 5 cards in hand

        //Set current player
        state.whoseTurn = currentPlayer;

        //Give the rest of the players 5 cards
        //for their hands to start
        for(j=1; j < playerCount; j++){
            for(i=0; i < 5; i++){
            drawCard(j, &state);}}


        //Print initial values for size of hand, 
        //action count, played card count
        //and current hand card of player 1
        printf("Current Player: %i\n", currentPlayer + 1);
        printf("Initial Hand Count (current Player): %i\n", state.handCount[currentPlayer]);
        printf("Initial handPos: %i\n", handPos);
        printf("Initial Buy count in game state: %i\n", state.numBuys);
        printf("Initial Played pile count in game state: %i\n", state.playedCardCount);
        printf("Current card in hand: %i\n\n", state.hand[currentPlayer][handPos]);

        
        //Make test copy of state
        printf("Copying state into testState\n");
        memcpy(&testState, &state, sizeof(struct gameState));

        //Play Council Room with test state
        printf("Playing Council Room card.\n\n");
        cardEffect(council_room, c1, c2, c3, &testState, handPos, bonus);

        //Print resulting values for size of hand,
        //action count, played card count, and top of played
        //card pile
        printf("Resulting Hand Count for current player:  %i\n", testState.handCount[currentPlayer]);
        printf("Resulting Buy count in game state: %i\n", testState.numBuys);
        printf("Resulting Played pile count in game state: %i\n", testState.playedCardCount);
        printf("Top of played pile: %i\n\n", testState.playedCards[testState.playedCardCount - 1]);
        //Print resulting handCount for each non-current player
        for(j=0; j < playerCount; j++){
            if(j != currentPlayer){
                printf("Resulting hand count for player %i: %i\n", j+1, testState.handCount[j]);}}


        //TEST 1: Check that Hand count for currentPlayer has increased by 3
        //(draw 4, discard 1 during play)
        if(testState.handCount[currentPlayer] != state.handCount[currentPlayer] + 3){
            printf("\nError: handCount should have increased by 3.\n");
            exit(1);}

        //TEST 2: Check numBuys increased by 1
        if(testState.numBuys != state.numBuys + 1){
            printf("\nError: numBuys did not increase.\n");
            exit(1);}

        //TEST 3: Check top of playedCards is the same
        //as the card initially in handPos for the currentPlayer
        if(testState.playedCards[testState.playedCardCount - 1] != state.hand[currentPlayer][handPos]){
            printf("\nError: discarded card not the same as card played.\n");
            exit(1);}

        //TEST 4: Check hand count has increased by 1 for all other
        //players. Unable to test unchanged state for deck and discard
        //count for other players due to nature of drawCard() when 
        //a player's deck has 0 or few cards.
        for(j=0; j < playerCount; j++){
            if(j != currentPlayer && testState.handCount[j] != state.handCount[j] + 1){
                printf("\nError - handCount was not increased 1 for player %i\n", j + 1);
                exit(1);}}

        printf("\nAll tests passed for iteration %i\n\n", n-1);
    }

    return 0;
}
