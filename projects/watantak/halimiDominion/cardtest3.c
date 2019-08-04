/***********************************************************************************************************************
** Program name: CS362 Assignment3 cardtest3.c
** Author: Takahiro Watanabe
** Date: 07/15/19
** Description: This is the unit testing program for the endTurn function of the Dominion game.
**              This tests 2 cases and print the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *	  gcc - o cardtest3 - g cardtest3.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "endTurn"

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

	// ----------- TEST 1: testing for the updated discard count and hand count --------------
	printf("\nTEST 1: testing dicard count and hand count\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the endTurn function
	endTurn(&testG);

	// check if the dicard count has been properly updated
	stateStr = "discard count";
	testVal = testG.discardCount[thisPlayer];
	expectVal = G.discardCount[thisPlayer] + G.handCount[thisPlayer];
	asserttrue(stateStr, testVal, expectVal);

	// check if the hand count is 0
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 2-1: testing for the updated turn --------------
	printf("\nTEST 2-1: updating turn when whoseTurn=1 (2nd player) and numPlayers=3\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually update the current player (whoseTurn)
	testG.whoseTurn = 1;

	// call the endTurn function
	endTurn(&testG);

	// check if it's the third player's turn now (whoseTurn should be 2)
	stateStr = "updated current player";
	testVal = whoseTurn(&testG);
	expectVal = 2;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 2-2: testing for the updated turn --------------
	printf("\nTEST 2-2: updating turn when whoseTurn=2 (3rd player) and numPlayers=3\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually update the current player (whoseTurn)
	testG.whoseTurn = 2;

	// call the endTurn function
	endTurn(&testG);

	// check if it's the first player's turn now (whoseTurn should be 0)
	stateStr = "updated current player";
	testVal = whoseTurn(&testG);
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

