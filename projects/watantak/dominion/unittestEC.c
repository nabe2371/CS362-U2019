/***********************************************************************************************************************
** Program name: CS362 Extra Credit Dominion Cleanup
** Author: Takahiro Watanabe
** Date: 08/10/19
** Description: This is the unit testing program for the Extra Credit Dominion Cleanup assignment.
**              This testing conssits of 6 test cases to prove the bugs in the baron (in cardEffect()), discardCard(), 
**				tribute (in cardEffect()), minion (in cardEffect()), and mine (in cardEffect()) in dominion.c file,
**				then prints the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * unittestEC: unittestEC.c dominion.o rngs.o
 *	  gcc - o unittestEC - g unittestEC.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

// function header for the asserttrue() function
void asserttrue(char*, int, int);

int main() 
{
	int xtraCoins = 0; //2; either 0 or 2 depending on the value of choice1 for the minion code
	int choice1 = 0, choice2 = 0;
	int handpos = 0;
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

	printf("\n----------------- Extra Credit Dominion Cleanup ----------------\n");

	// ----------- TEST 1: testing for the bug in the baron code (supply count of estate) --------------
	printf("\nTEST 1: Bug in the baron code (supply count of estate) \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 0;	// gain an estate from the supply

	// set supplyCount of estate to 10
	int prevCount;
	testG.supplyCount[estate] = prevCount = 10;

	// call the baron code
	cardEffect(baron, choice1, 0, 0, &testG, 0, 0);

	// check if only one estate card was removed from the supply (i.e. expecting 9)
	stateStr = "estate supply count";
	testVal = testG.supplyCount[estate];
	expectVal = prevCount - 1;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 2: testing for the bug in discardCard function --------------
	printf("\n\nTEST 2: Bug in the discardCard function (gameState (discardCount) not updated properly) \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// give 5 cards in hand of players whose indices are odd for testing purpose
	for (int i = 1; i < numPlayers; i += 2)
	{
		for (int j = 0; j < 5; j++)
		{
			drawCard(i, &testG);
		}
	}

	// give 3 cards in hand of players whose indices are even (except the current player) for testing purpose
	for (int i = 2; i < numPlayers; i += 2)
	{
		for (int j = 0; j < 3; j++)
		{
			drawCard(i, &testG);
		}
	}

	// discard hand and draw 4 cards
	choice1 = 0;
	choice2 = 1;

	// call the minion code
	cardEffect(minion, choice1, choice2, 0, &testG, handpos, 0);

	printf("\nCurrent Player:\n");

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

			// check if no cards were added to these players' discard sets
			stateStr = "discard count";
			testVal = testG.discardCount[i];
			expectVal = G.discardCount[i];
			asserttrue(stateStr, testVal, expectVal);
		}
	}

	// ----------- TEST 3: testing for the bug in the tribute code (discardCount) --------------
	printf("\n\nTEST 3: Bug in the tribute code (cards not properly moved from discard pile to deck)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = -1;
	testG.deckCount[1] = 0;
	testG.discard[1][0] = copper;
	testG.discard[1][1] = silver;
	testG.discardCount[1] = 2;

	choice1 = 0;
	choice2 = 0;

	// call the tribute code
	cardEffect(tribute, choice1, choice2, 0, &testG, handpos, 0);
	
	// check if the next player's discard count is 0 
	stateStr = "next player\'s discard count";
	testVal = testG.discardCount[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 4: testing for the bug in the tribute code (deckCount) --------------
	printf("\n\nTEST 4: Bug in the tribute code (deckCount incorrectly decremented)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = -1;
	testG.deckCount[1] = 0;
	testG.discard[1][0] = copper;
	testG.discard[1][1] = silver;
	testG.discardCount[1] = 2;

	choice1 = 0;
	choice2 = 0;

	// call the tribute code
	cardEffect(tribute, choice1, choice2, 0, &testG, handpos, 0);

	// check if the next player's deck count is 0
	stateStr = "next player\'s deck count";
	testVal = testG.deckCount[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);
	

	// ----------- TEST 5: testing for the bug in the minion code --------------
	printf("\n\nTEST 5: Bug in the minion code (no action taking place) \n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// give 5 cards in hand of players whose indices are odd for testing purpose
	for (int i = 1; i < numPlayers; i += 2)
	{
		for (int j = 0; j < 5; j++)
		{
			drawCard(i, &testG);
		}
	}

	// give 3 cards in hand of players whose indices are even (except the current player) for testing purpose
	for (int i = 2; i < numPlayers; i += 2)
	{
		for (int j = 0; j < 3; j++)
		{
			drawCard(i, &testG);
		}
	}

	// set both parameters to 0
	choice1 = 0;
	choice2 = 0;

	// call the minion code
	cardEffect(minion, choice1, choice2, 0, &testG, handpos, 0);

	printf("\nCurrent Player:\n");

	// check the number of coins
	stateStr = "coins";
	testVal = testG.coins;
	expectVal = G.coins + xtraCoins;
	asserttrue(stateStr, testVal, expectVal);

	// check the current player's handCount and discardCount 
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = 4;
	asserttrue(stateStr, testVal, expectVal);

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

			// check these players' discardCount and handCount
			stateStr = "hand count";
			testVal = testG.handCount[i];
			expectVal = 4;
			asserttrue(stateStr, testVal, expectVal);

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

			// check these players' discardCount and handCount
			stateStr = "hand count";
			testVal = testG.handCount[i];
			expectVal = 3;
			asserttrue(stateStr, testVal, expectVal);

			stateStr = "discard count";
			testVal = testG.discardCount[i];
			expectVal = G.discardCount[i];
			asserttrue(stateStr, testVal, expectVal);
		}
	}

	// ----------- TEST 6: testing for the bug in the mine code (conditional operator) --------------
	printf("\n\nTEST 6: Bug in the mine code (conditional operator)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the player's hand
	testG.hand[0][1] = gold;

	choice1 = 1;		// trash gold
	choice2 = gold;		// gain gold

	// call the mine code
	testVal = cardEffect(mine, choice1, choice2, 0, &testG, handpos, 0);

	// check if the return value of the function is 0
	stateStr = "return value of function";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	printf("\n\n >>>>> Testing complete <<<<<\n\n");
	
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

