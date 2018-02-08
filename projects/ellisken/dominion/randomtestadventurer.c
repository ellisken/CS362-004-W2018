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


    //Seed PRNG
    srand(time(NULL));


    //Invoke initializeGame() to create game state
    //for 2 players

    //Generate random deck and discard counts

    //Fill Player 1's deck with randomly generated cards
    //Fill Player 1's discard with randomly generated cards



    //Check deck and discard piles for treasure
    //If treasure cards < 2, exit and assert

    //Print initial values for drawnTreasure,
    //size of deck, and size of discard


    //Else, make copy of state and
    //play adventurer with test copy


    //Print resulting values for drawnTreasure,
    //size of deck, and size of discard


    //TEST 1: Check drawnTreasure has increased by two

    //TEST 2: Check hand count has increased by two

    //TEST 3: Check top two hand cards are now Treasure cards

    //TEST 4: Check state has not changed for other player







    return 0;
}
