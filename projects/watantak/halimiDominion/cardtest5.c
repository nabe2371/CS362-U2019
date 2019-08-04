/***********************************************************************************************************************
** Program name: CS362 Assignment3 cardtest5.c
** Author: Takahiro Watanabe
** Date: 07/15/19
** Description: This is the unit testing program for the drawCard function of the Dominion game.
**              This tests 2 cases and print the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * cardtest5: cardtest5.c dominion.o rngs.o
 *	  gcc - o cardtest5 - g cardtest5.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "drawCard"

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

	// ----------- TEST 1-1: testing for the various deck count --------------
	printf("\nTEST 1-1: draw a card when deck is empty\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set the starting deck count
	int startDeck = testG.deckCount[thisPlayer] = 0;

	// manually set the starting discard count
	int startDisc = testG.discardCount[thisPlayer] = 5;

	// call the endTurn function
	drawCard(thisPlayer, &testG);

	// check if the discard count is 0
	stateStr = "discard count";
	testVal = testG.discardCount[thisPlayer];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// check if the hand count is incremented by 1
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = G.handCount[thisPlayer] + 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if the deck count is initial deck count + discard count - 1
	stateStr = "deck count";
	testVal = testG.deckCount[thisPlayer];
	expectVal = startDeck + startDisc - 1;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 1-2: testing for the various deck count --------------
	printf("\nTEST 1-2: draw a card when deck has 1 card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set the starting deck count
	startDeck = testG.deckCount[thisPlayer] = 1;

	// manually set the starting discard count
	startDisc = testG.discardCount[thisPlayer] = 5;

	// call the endTurn function
	drawCard(thisPlayer, &testG);

	// check if there's no change in discard count
	stateStr = "discard count";
	testVal = testG.discardCount[thisPlayer];
	expectVal = startDisc;
	asserttrue(stateStr, testVal, expectVal);

	// check if the hand count is incremented by 1
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = G.handCount[thisPlayer] + 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if the deck count is decremented by 1
	stateStr = "deck count";
	testVal = testG.deckCount[thisPlayer];
	expectVal = startDeck - 1;
	asserttrue(stateStr, testVal, expectVal);

	
	// ----------- TEST 1-3: testing for the various deck count --------------
	printf("\nTEST 1-3: draw a card when deck has 2 card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set the starting deck count
	startDeck = testG.deckCount[thisPlayer] = 2;

	// manually set the starting discard count
	startDisc = testG.discardCount[thisPlayer] = 5;

	// call the endTurn function
	drawCard(thisPlayer, &testG);

	// check if there's no change in discard count
	stateStr = "discard count";
	testVal = testG.discardCount[thisPlayer];
	expectVal = startDisc;
	asserttrue(stateStr, testVal, expectVal);

	// check if the hand count is incremented by 1
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = G.handCount[thisPlayer] + 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if the deck count is decremented by 1
	stateStr = "deck count";
	testVal = testG.deckCount[thisPlayer];
	expectVal = startDeck - 1;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 2-1: testing for the various discard count with empty deck --------------
	printf("\nTEST 2-1: draw a card when discardCount=0 with empty deck\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set the starting deck count
	testG.deckCount[thisPlayer] = 0;

	// manually set the starting discard count
	testG.discardCount[thisPlayer] = 0;

	// call the endTurn function
	testVal = drawCard(thisPlayer, &testG);

	// check if the return value of the function is -1
	stateStr = "return value";
	expectVal = -1;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 2-2: testing for the various discard count with empty deck --------------
	printf("\nTEST 2-2: draw a card when discardCount=1 with empty deck\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set the starting deck count
	testG.deckCount[thisPlayer] = 0;

	// manually set the starting discard count
	testG.discardCount[thisPlayer] = 1;

	// call the endTurn function
	testVal = drawCard(thisPlayer, &testG);

	// check if the return value of the function is 0
	stateStr = "return value";
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

