/***********************************************************************************************************************
** Program name: CS362 Assignment3 cardtest2.c
** Author: Takahiro Watanabe
** Date: 07/15/19
** Description: This is the unit testing program for the shuffle function of the Dominion game.
**              This tests 2 cases and print the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *	  gcc - o cardtest2 - g cardtest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "shuffle"

 // function header for the asserttrue() function
void asserttrue(char*, int, int);

int main()
{
	int seed = 1000;
	int numPlayers = 3;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, estate,
			sea_hag, tribute, smithy, council_room };
	char* stateStr;
	int testVal, expectVal;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----------- TEST 1-1: testing for valid/invalid deckCount values --------------
	printf("\nTEST 1-1: testing deckCount = 0\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// set the deckCount to 0
	testG.deckCount[thisPlayer] = 0;

	// call the shuffle function
	testVal = shuffle(thisPlayer, &testG);

	// check if the return value is -1
	stateStr = "return value";
	expectVal = -1;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 1-2: testing for valid/invalid deckCount values --------------
	printf("\nTEST 1-2: testing deckCount = 1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// set the deckCount to 1
	testG.deckCount[thisPlayer] = 1;

	// call the shuffle function
	testVal = shuffle(thisPlayer, &testG);

	// check if the return value is 0
	stateStr = "return value";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 1-3: testing for valid/invalid deckCount values --------------
	printf("\nTEST 1-3: testing deckCount = 2\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// set the deckCount to 1
	testG.deckCount[thisPlayer] = 2;

	// call the shuffle function
	testVal = shuffle(thisPlayer, &testG);

	// check if the return value is 0
	stateStr = "return value";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 2: testing for the shuffled deck --------------
	printf("\nTEST 2: compare the before/after shuffled deck\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// create another gameState object for comparison purpose then copy the game state to a new one
	struct gameState beforeG;
	memcpy(&beforeG, &G, sizeof(struct gameState));

	// manually set up the deck with 10 cards
	testG.deck[thisPlayer][0] = beforeG.deck[thisPlayer][0] = gold;
	testG.deck[thisPlayer][1] = beforeG.deck[thisPlayer][1] = silver;
	testG.deck[thisPlayer][2] = beforeG.deck[thisPlayer][2] = copper;
	testG.deck[thisPlayer][3] = beforeG.deck[thisPlayer][3] = baron;
	testG.deck[thisPlayer][4] = beforeG.deck[thisPlayer][4] = minion;
	testG.deck[thisPlayer][5] = beforeG.deck[thisPlayer][5] = ambassador;
	testG.deck[thisPlayer][6] = beforeG.deck[thisPlayer][6] = tribute;
	testG.deck[thisPlayer][7] = beforeG.deck[thisPlayer][7] = mine;
	testG.deck[thisPlayer][8] = beforeG.deck[thisPlayer][8] = smithy;
	testG.deck[thisPlayer][9] = beforeG.deck[thisPlayer][9] = steward;
	testG.deckCount[thisPlayer] = beforeG.deckCount[thisPlayer] = 10;

	// call the shuffle function
	shuffle(thisPlayer, &testG);

	int samePos = 1;	// flag for the same position on the deck

	// loop through the deck and see if the card is at the same position before/after shuffling
	for (int i = 0; i < testG.deckCount[thisPlayer]; i++)
	{
		if (testG.deck[thisPlayer][0] != beforeG.deck[thisPlayer][0])
		{
			samePos = 0;
			break;
		}
	}

	// check if the deck is shuffled (samePos = 0)
	stateStr = "same deck flag (Y:1, N:0)";
	testVal = samePos;
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);


	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);

	return 0;
}

// function to show the test value against the expected value of the game state
// if they are the same, it shows the pass message. if not, the fail message is displayed.
// this is a void function and takes a c-string and two ints as parameters.
void asserttrue(char* stateStr, int testVal, int expectVal)
{
	if (testVal == expectVal)
	{
		printf("PASS: %s = %d, expected = %d\n", stateStr, testVal, expectVal);
	}
	else
	{
		printf("FAIL: %s = %d, expected = %d\n", stateStr, testVal, expectVal);
	}
}

