/***************************************************************
 ** Program Filename: randomtestcard1.c
 ** Author: Kendra Ellis, ellisken@oregonstate.edu
 ** Date: February 15, 2018
 ** Description: unit test for playing Great Hall from dominion.c
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
    int i;
    int n=0;
    int playerCount = 2;
    int currentPlayer, otherPlayer;
    int handPos; //Will be randomly generated based on handCount
    int c1, c2, c3; //Dummy choices for calling cardEffect()
    c1=c2=c3=0;
    int *bonus; //Dummy ptr to int for calling cardEffect()
    int seed = 1000;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState state, testState;

    //Print title
    printf("\n\nrandomtestcard1: GREAT HALL\n\n");

    //Seed PRNG
    srand(time(NULL));

    //Continually generate random currentPlayer
    //and handPos and play village 1000 times
    //NOTE: while loop easily modified to run
    //until failure
    while(n < 1000){
        printf("\n\n---Iteration: %i---\n", n++);
        
        //Invoke initializeGame() to create game state
        //for 2 players
        printf("Initializing game\n\n\n");
        initializeGame(playerCount, k, seed, &state);
    
        //Generate random currentPlayer and handPos
        currentPlayer = rand() % 2;
        handPos = rand() % 5; //modulo 5 because each player starts with 5 cards in hand

        //Set current player
        state.whoseTurn = currentPlayer;

        //If currentPlayer is 2, then that player must draw 5 cards
        //due to game initialization
        if(currentPlayer + 1 == 2){
        for(i=0; i < 5; i++){
            drawCard(currentPlayer, &state);}}


        //Print initial values for size of hand, 
        //action count, played card count
        //and current hand card of player 1
        printf("Current Player: %i\n", currentPlayer + 1);
        printf("Initial Hand Count: %i\n", state.handCount[currentPlayer]);
        printf("Initial handPos: %i\n", handPos);
        printf("Initial Action count in game state: %i\n", state.numActions);
        printf("Initial Played pile count in game state: %i\n", state.playedCardCount);
        printf("Current card in hand: %i\n\n", state.hand[currentPlayer][handPos]);

        
        //Make test copy of state
        printf("Copying state into testState\n");
        memcpy(&testState, &state, sizeof(struct gameState));

        //Play Village with test state
        printf("Playing Village card.\n\n");
        cardEffect(village, c1, c2, c3, &testState, handPos, bonus);

        //Print resulting values for size of hand,
        //action count, played card count, and top of played
        //card pile
        printf("Resulting Hand Count:  %i\n", testState.handCount[currentPlayer]);
        printf("Resulting Action count in game state: %i\n", testState.numActions);
        printf("Resulting Played pile count in game state: %i\n", testState.playedCardCount);
        printf("Top of played pile: %i\n\n", testState.playedCards[testState.playedCardCount - 1]);


        //TEST 1: Check that Hand count for currentPlayer is unchanged
        //(draw 1, discard 1 during play)
        if(testState.handCount[currentPlayer] != state.handCount[currentPlayer]){
            printf("\nError: handCount should have stayed the same.\n");
            exit(1);}

        //TEST 2: Check numActions increased by 1
        if(testState.numActions != state.numActions + 1){
            printf("\nError: numActions did not increase.\n");
            exit(1);}

        //TEST 3: Check top of playedCards is the same
        //as the card initially in handPos for the currentPlayer
        if(testState.playedCards[testState.playedCardCount - 1] != state.hand[currentPlayer][handPos]){
            printf("\nError: discarded card not the same as card played.\n");
            exit(1);}

        //TEST 4: Check state has not changed for other player
        otherPlayer = (currentPlayer + 1) % 2; //Determine other player
        if(testState.handCount[otherPlayer] != state.handCount[otherPlayer]){
            printf("\nError - handCount was changed for player %i\n", otherPlayer + 1);
            exit(1);}
        if(testState.deckCount[otherPlayer] != state.deckCount[otherPlayer]){
            printf("\nError - deckCount was changed for player %i\n", otherPlayer + 1);
            exit(1);}
        if(testState.discardCount[otherPlayer] != state.discardCount[otherPlayer]){
            printf("\nError - discardCount was changed for player %i\n", otherPlayer +1);
            exit(1);}

        printf("\nAll tests passed for iteration %i\n\n", n-1);
    }

    return 0;
}
