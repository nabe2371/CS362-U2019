/***********************************************************************************************************************
** Program name: CS362 Assignment3 unittest1.c
** Author: Takahiro Watanabe
** Date: 07/11/19
** Description: This is the unit testing program for the refactored baron code of the Dominion game.
**              This tests 3 cases and print the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *	  gcc - o unittest1 - g unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"

// function header for the asserttrue() function
void asserttrue(char*, int, int);

int main() 
{
	int xtraCoins = 0;
	int choice1 = 0;
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

	// ----------- TEST 1-1: choice1 = discard an estate for +4 coins & player has an estate in hand --------------
	printf("\nTEST 1-1: choice1 = 1 = discard an estate for +4 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1; // choice1 = 1, but this will fail b/c of the bug introduced in Assignment2 
	int noEstate = 1;

	// make sure that the current player has an estate in hand
	for (int i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		if (testG.hand[thisPlayer][i] == estate)
		{
			noEstate = 0;
			break;
		}
	}

	// if player has no estate in hand, replace the first card in hand with an estate 
	if (noEstate == 1)
	{
		testG.hand[thisPlayer][0] = estate;
	}

	// call the refactored baron code
	baronRefactor(choice1, thisPlayer, 0, &testG);

	xtraCoins = 4;

	// check if the player gained +4 coins
	stateStr = "coins";
	testVal = testG.coins;
	expectVal = G.coins + xtraCoins;
	asserttrue(stateStr, testVal, expectVal);

	// check if 2 cards (baron and estate) are added to the discard set
	stateStr = "discard count";
	testVal = testG.discardCount[thisPlayer];
	expectVal = G.discardCount[thisPlayer] + 2;
	asserttrue(stateStr, testVal, expectVal);

	// check if 2 cards (baron and estate) are removed from hand
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = G.handCount[thisPlayer] - 2;
	asserttrue(stateStr, testVal, expectVal);

	// check if there's no change in the estate supply count
	stateStr = "estate supply count";
	testVal = testG.supplyCount[estate];
	expectVal = G.supplyCount[estate];
	// this revlealed a bug in our code!
	asserttrue(stateStr, testVal, expectVal);

	

	// ----------- TEST 1-2: choice1 = 0 --------------
	printf("\nTEST 1-2: choice1 = 0 = gain an estate\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 0; // choice1 = 0, but this will fail b/c of the bug introduced in Assignment2 
	noEstate = 1;

	// make sure that the current player has an estate in hand
	for (int i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		if (testG.hand[thisPlayer][i] == estate)
		{
			noEstate = 0;
			break;
		}
	}

	// if player has no estate in hand, replace the first card in hand with an estate 
	if (noEstate == 1)
	{
		testG.hand[thisPlayer][0] = estate;
	}

	// call the refoactored baron code
	baronRefactor(choice1, thisPlayer, 0, &testG);

	xtraCoins = 0;

	// check if the player gained 0 coins
	stateStr = "coins";
	testVal = testG.coins;
	expectVal = G.coins + xtraCoins;
	asserttrue(stateStr, testVal, expectVal);

	// check if 1 card (baron and estate) was added to the discard set
	stateStr = "discard count";
	testVal = testG.discardCount[thisPlayer];
	expectVal = G.discardCount[thisPlayer] + 2;
	asserttrue(stateStr, testVal, expectVal);

	// check if 1 card (baron) was removed from the hand
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = G.handCount[thisPlayer] - 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if 1 estate was removed from the supply
	stateStr = "estate supply count";
	testVal = testG.supplyCount[estate];
	expectVal = G.supplyCount[estate] - 1;
	// this revlealed a bug in our code!
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 2: choice1 = discard an estate but player has no estate in hand --------------
	printf("\nTEST 2: choice1 = 1 but no eastate in hand\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1;	// choice1 = 1 in this case

	// take all estates from the player's hand
	for (int i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		if (testG.hand[thisPlayer][i] == estate)
		{
			testG.hand[thisPlayer][i] = -1; // assign -1 to all estates in hand
		}
	}

	// call the refactored baron code
	baronRefactor(choice1, thisPlayer, 0, &testG);

	xtraCoins = 0;

	// check if no coins were added
	stateStr = "coins";
	testVal = testG.coins;
	expectVal = G.coins + xtraCoins;
	asserttrue(stateStr, testVal, expectVal);

	// check if 1 card (estate) were added to the discard set
	stateStr = "discard count";
	testVal = testG.discardCount[thisPlayer];
	expectVal = G.discardCount[thisPlayer] + 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if there's no change in the player's hand
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = G.handCount[thisPlayer];
	asserttrue(stateStr, testVal, expectVal);

	// check if 1 estate was removed from the supply
	stateStr = "estate supply count";
	testVal = testG.supplyCount[estate];
	expectVal = G.supplyCount[estate] - 1; 
	// this revlealed a bug in our code!
	asserttrue(stateStr, testVal, expectVal);



// ----------- TEST 3-1: testing for the supply count balance of estate --------------
printf("\nTEST 3-1: starting supply count of estate = 2\n");

// copy the game state to a test case
memcpy(&testG, &G, sizeof(struct gameState));

choice1 = 0;	// choice = 0 in this case

// set supplyCount of estate to 2
int prevCount;
testG.supplyCount[estate] = prevCount = 2;

// call the refactored baron code
baronRefactor(choice1, thisPlayer, 0, &testG);

// check if 1 estate was removed from the supply
stateStr = "estate supply count";
testVal = testG.supplyCount[estate];
expectVal = prevCount - 1;
// this revlealed a bug in our code!
asserttrue(stateStr, testVal, expectVal);


// ----------- TEST 3-2: testing for the supply count balance of estate --------------
printf("\nTEST 3-2: starting supply count of estate = 1\n");

// copy the game state to a test case
memcpy(&testG, &G, sizeof(struct gameState));

choice1 = 0;	// choice = 0 in this case

// set supplyCount of estate to 1
testG.supplyCount[estate] = prevCount = 1;

// call the refactored baron code
baronRefactor(choice1, thisPlayer, 0, &testG);

// check if 1 estate was removed from the supply
stateStr = "estate supply count";
testVal = testG.supplyCount[estate];
expectVal = prevCount - 1;
// this revlealed a bug in our code!
asserttrue(stateStr, testVal, expectVal);

// ----------- TEST 3-3: testing for the supply count balance of estate --------------
printf("\nTEST 3-3: starting supply count of estate = 0\n");

// copy the game state to a test case
memcpy(&testG, &G, sizeof(struct gameState));

choice1 = 0;	// choice = 0 in this case

// set supplyCount of estate to 0
testG.supplyCount[estate] = prevCount = 0;

// call the refactored baron code
baronRefactor(choice1, thisPlayer, 0, &testG);

// check if there's no change in the estate supply count because the initial supply count was 0 (no estate available)
stateStr = "estate supply count";
testVal = testG.supplyCount[estate];
expectVal = prevCount;
// this revlealed a bug in our code!
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

