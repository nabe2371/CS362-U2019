/***********************************************************************************************************************
** Program name: CS362 Assignment3 unittest5.c
** Author: Takahiro Watanabe
** Date: 07/14/19
** Description: This is the unit testing program for the refactored mine code of the Dominion game.
**              This tests 3 cases and print the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * unittest5: unittest5.c dominion.o rngs.o
 *	  gcc - o unittest5 - g unittest5.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

// function header for the asserttrue() function
void asserttrue(char*, int, int);

int main()
{
	int choice1 = 0, choice2 = 0, handPos = 0;
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

	// ----------- TEST 1-1: testing for valid/invalid card to trash --------------
	printf("\nTEST 1-1: trash copper\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the player's hand
	testG.hand[0][1] = copper;

	choice1 = 1;		// trash copper
	choice2 = silver;	// gain silver

	// call the refactored mine code
	testVal = mineRemodel(choice1, choice2, thisPlayer, handPos, &testG);

	// check if the return value of the function is 0
	stateStr = "return value of function";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 1-2: testing for valid/invalid card to trash --------------
	printf("\nTEST 1-2: trash silver\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// manually set up the player's hand
	testG.hand[0][1] = silver;

	choice1 = 1;		// trash silver
	choice2 = gold;	// gain gold

	// call the refactored mine code
	testVal = mineRemodel(choice1, choice2, thisPlayer, handPos, &testG);

	// check if the return value of the function is 0
	stateStr = "return value of function";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 1-3: testing for valid/invalid card to trash --------------
	printf("\nTEST 1-3: trash gold\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the player's hand
	testG.hand[0][1] = gold;

	choice1 = 1;		// trash gold
	choice2 = gold;		// gain gold

	// call the refactored mine code
	testVal = mineRemodel(choice1, choice2, thisPlayer, handPos, &testG);

	// check if the return value of the function is 0
	stateStr = "return value of function";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 1-4: testing for valid/invalid card to trash --------------
	printf("\nTEST 1-4: trash curse\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the player's hand
	testG.hand[0][1] = curse;

	choice1 = 1;		// trash silver
	choice2 = copper;	// gain copper

	// call the refactored mine code
	testVal = mineRemodel(choice1, choice2, thisPlayer, handPos, &testG);

	// check if the return value of the function is -1
	stateStr = "return value of function";
	expectVal = -1;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 1-5: testing for valid/invalid card to trash --------------
	printf("\nTEST 1-5: trash treasure map\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the player's hand
	testG.hand[0][1] = treasure_map;

	choice1 = 1;		// trash treasure map
	choice2 = gold;	// gain gold

	// call the refactored mine code
	testVal = mineRemodel(choice1, choice2, thisPlayer, handPos, &testG);

	// check if the return value of the function is -1
	stateStr = "return value of function";
	expectVal = -1;
	asserttrue(stateStr, testVal, expectVal);

	
	// ----------- TEST 2-1: testing for valid/invalid combination of the trashed and gained cards --------------
	printf("\nTEST 2-1: trash silver and gain copper\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the player's hand
	testG.hand[0][1] = silver;

	choice1 = 1;		// trash silver
	choice2 = copper;	// gain copper

	// call the refactored mine code
	testVal = mineRemodel(choice1, choice2, thisPlayer, handPos, &testG);

	// check if the return value of the function is 0
	stateStr = "return value of function";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 2-2: testing for valid/invalid combination of the trashed and gained cards --------------
	printf("\nTEST 2-2: trash silver and gain gold\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the player's hand
	testG.hand[0][1] = silver;

	choice1 = 1;		// trash silver
	choice2 = gold;	// gain gold

	// call the refactored mine code
	testVal = mineRemodel(choice1, choice2, thisPlayer, handPos, &testG);

	// check if the return value of the function is 0
	stateStr = "return value of function";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 2-3: testing for valid/invalid combination of the trashed and gained cards --------------
	printf("\nTEST 2-3: trash silver and gain province\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the player's hand
	testG.hand[0][1] = silver;

	choice1 = 1;		// trash silver
	choice2 = province;	// gain province

	// call the refactored mine code
	testVal = mineRemodel(choice1, choice2, thisPlayer, handPos, &testG);

	// check if the return value of the function is -1
	stateStr = "return value of function";
	expectVal = -1;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 3: testing for the updated hand count and discard count --------------
	printf("\nTEST 3: updated hand count and discard count\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the player's hand
	testG.hand[0][1] = silver;

	choice1 = 1;		// trash silver
	choice2 = gold;		// gain gold

	// call the refactored mine code
	mineRemodel(choice1, choice2, thisPlayer, handPos, &testG);

	// check if the hand count is decreased by 1 (-2 for mine and trashed card, +1 for the gained card to hand)
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = G.handCount[thisPlayer] - 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if 1 card was added to the discard set (mine card)
	stateStr = "discard count";
	testVal = testG.discardCount[thisPlayer];
	expectVal = G.discardCount[thisPlayer] + 1;
	asserttrue(stateStr, testVal, expectVal);

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