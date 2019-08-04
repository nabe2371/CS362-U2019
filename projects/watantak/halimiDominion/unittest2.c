/***********************************************************************************************************************
** Program name: CS362 Assignment3 unittest2.c
** Author: Takahiro Watanabe
** Date: 07/11/19
** Description: This is the unit testing program for the refactored minion code of the Dominion game.
**              This tests 2 cases and print the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *	  gcc - o unittest2 - g unittest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "minion"

// function header for the asserttrue() function
void asserttrue(char*, int, int);

int main() 
{
	int xtraCoins = 0;
	int handpos = 0, choice1 = 0, choice2 = 0;
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

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1-1: testing for the updated coins --------------
	printf("\nTEST 1-1: testing for the updated coins with choice1=1 & choice2=0\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 0;
	
	// call the refactored minion code
	minionRefactor(choice1, choice2, thisPlayer, handpos, &testG);
	
	xtraCoins = 2;

	// check if 2 coins were added
	stateStr = "coins";
	testVal = testG.coins;
	expectVal = G.coins + xtraCoins;
	asserttrue(stateStr, testVal, expectVal);

	
	// ----------- TEST 1-2: testing for the updated coins --------------
	printf("\nTEST 1-2: testing for the updated coins with choice1=1 & choice2=1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 1;

	// call the refactored minion code
	minionRefactor(choice1, choice2, thisPlayer, handpos, &testG);

	xtraCoins = 2;

	// check if 2 coins were added
	stateStr = "coins";
	testVal = testG.coins;
	expectVal = G.coins + xtraCoins;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 1-3: testing for the updated coins --------------
	printf("\nTEST 1-3: testing for the updated coins with choice1=0 & choice2=1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 1;

	// call the refactored minion code
	minionRefactor(choice1, choice2, thisPlayer, handpos, &testG);

	xtraCoins = 0;

	// check if no coins were added
	stateStr = "coins";
	testVal = testG.coins;
	expectVal = G.coins + xtraCoins;
	asserttrue(stateStr, testVal, expectVal);
	

	// ----------- TEST 1-4: testing for the updated coins --------------
	printf("\nTEST 1-4: testing for the updated coins with choice1=0 & choice2=0\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 0;

	// call the refactored minion code
	minionRefactor(choice1, choice2, thisPlayer, handpos, &testG);

	xtraCoins = 0;

	// check if no coins were added
	stateStr = "coins";
	testVal = testG.coins;
	expectVal = G.coins + xtraCoins;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 2: testing for the updated hand count and discard count of each player --------------
	printf("\nTEST 2: testing for the updated hand count and discard count with choice2=1 \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// give 5 cards in hand of players whose index is odd for testing purpose
	for (int i = 1; i < numPlayers; i += 2)
	{
		for (int j = 0; j < 5; j++)
		{
			drawCard(i, &testG);
		}
	}

	// give 3 cards in hand of players whose index is even (except the current player) for testing purpose
	for (int i = 2; i < numPlayers; i += 2)
	{
		for (int j = 0; j < 3; j++)
		{
			drawCard(i, &testG);
		}
	}
	
	choice1 = 0;
	choice2 = 1;

	// call the refactored minion code
	minionRefactor(choice1, choice2, thisPlayer, handpos, &testG);

	printf("\nCurrent Player:\n");

	// check if the current player's hand count was updated to 4
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = 4;
	asserttrue(stateStr, testVal, expectVal);

	// check if the cards in the current player's initial hand were added to the discard set 
	stateStr = "discard count";
	testVal = testG.discardCount[thisPlayer];
	expectVal = G.discardCount[thisPlayer] + G.handCount[thisPlayer];
	asserttrue(stateStr, testVal, expectVal);

	// loop through other players who initially had 5 cards in hand
	for (int i = 1; i < G.numPlayers; i += 2)
	{
		if (i != thisPlayer)
		{
			printf("\nPlayer %d\n", i);

			// check if these players' hand counts were updated to 4
			stateStr = "hand count";
			testVal = testG.handCount[i];
			expectVal = 4;
			asserttrue(stateStr, testVal, expectVal);

			// check if 5 cards were added to these players' discard sets
			stateStr = "discard count";
			testVal = testG.discardCount[i];
			expectVal = G.discardCount[i] + 5;
			asserttrue(stateStr, testVal, expectVal);
		}
	}

	// loop through other players who initially had 3 cards in hand
	for (int i = 2; i < G.numPlayers; i += 2)
	{
		if (i != thisPlayer)
		{
			printf("\nPlayer %d\n", i);

			// check if there's no change in these players' hands
			stateStr = "hand count";
			testVal = testG.handCount[i];
			expectVal = 3;
			asserttrue(stateStr, testVal, expectVal);

			// check if no cards were added to these players' discard sets
			stateStr = "discard count";
			testVal = testG.discardCount[i];
			expectVal = G.discardCount[i];
			asserttrue(stateStr, testVal, expectVal);
		}
	}

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

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

