/***********************************************************************************************************************
** Program name: CS362 Assignment3 unittest3.c
** Author: Takahiro Watanabe
** Date: 07/14/19
** Description: This is the unit testing program for the refactored ambassador code of the Dominion game.
**              This tests 3 cases and print the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *	  gcc - o unittest3 - g unittest3.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "ambassador"

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

	// ----------- TEST 1-1: testing for the number of copies in hand vs the number of copies to return to supply --------------
	printf("\nTEST 1-1: testing for the case with 1 copy in hand & 2 copies to return\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1;		// reveal the second card in hand in this case for testing purpose
	choice2 = 2;		// wants to return 2 copies of curse

	// manually set up the player's hand for testing purpose
	testG.hand[thisPlayer][0] = ambassador;
	testG.hand[thisPlayer][1] = curse;
	testG.hand[thisPlayer][2] = copper;
	testG.hand[thisPlayer][3] = silver;
	testG.hand[thisPlayer][4] = gold;

	// call the refactored ambassador code
	testVal = ambassadorRefact(choice1, choice2, &testG, handPos);

	// choice2 should be invalid b/c there's only 1 copy of curse. check if the return value is -1
	stateStr = "return value of function";
	expectVal = -1;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 1-2: testing for the number of copies in hand vs the number of copies to return to supply --------------
	printf("\nTEST 1-2: testing for the case with 2 copies in hand & 2 copies to return\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1;		// reveal the second card in hand in this case for testing purpose
	choice2 = 2;		// wants to return 2 copies of curse

	// manually set up the player's hand for testing purpose
	testG.hand[thisPlayer][0] = ambassador;
	testG.hand[thisPlayer][1] = curse;
	testG.hand[thisPlayer][2] = curse;
	testG.hand[thisPlayer][3] = silver;
	testG.hand[thisPlayer][4] = gold;

	// call the refactored ambassador code
	testVal = ambassadorRefact(choice1, choice2, &testG, handPos);

	// choice2 should be valid b/c there're 2 copies of curse. check if the return value is 0
	stateStr = "return value of function";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 1-3: testing for the number of copies in hand vs the number of copies to return to supply --------------
	printf("\nTEST 1-3: testing for the case with 3 copies in hand & 2 copies to return\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1;		// reveal the second card in hand in this case for testing purpose
	choice2 = 2;		// wants to return 2 copies of curse

	// manually set up the player's hand for testing purpose
	testG.hand[thisPlayer][0] = ambassador;
	testG.hand[thisPlayer][1] = curse;
	testG.hand[thisPlayer][2] = curse;
	testG.hand[thisPlayer][3] = curse;
	testG.hand[thisPlayer][4] = gold;

	// call the refactored ambassador code
	testVal = ambassadorRefact(choice1, choice2, &testG, handPos);

	// choice2 should be valid b/c there're 3 copies of curse. check if the return value is 0
	stateStr = "return value of function";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 2: testing for the updated supply count --------------
	printf("\nTEST 2: testing for the updated supply count\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1;		// reveal the second card in hand in this case for testing purpose
	choice2 = 2;		// wants to return 2 copies of curse

	// manually set up the player's hand for testing purpose
	testG.hand[thisPlayer][0] = ambassador;
	testG.hand[thisPlayer][1] = curse;
	testG.hand[thisPlayer][2] = curse;
	testG.hand[thisPlayer][3] = silver;
	testG.hand[thisPlayer][4] = gold;

	// call the refactored ambassador code
	testVal = ambassadorRefact(choice1, choice2, &testG, handPos);

	// check if 2 cards were added to then (numPlayers-1) cards were removed from the curse supply pile
	stateStr = "supply count of the returned card";
	testVal = testG.supplyCount[curse];
	expectVal = G.supplyCount[curse] + choice2 - (numPlayers - 1);
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 3: testing for the updated discard count of each player --------------
	printf("\nTEST 3: testing for the updated discard count of each player\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 1;		// reveal the second card in hand in this case for testing purpose
	choice2 = 2;		// wants to return 2 copies of curse

	// manually set up the player's hand for testing purpose
	testG.hand[thisPlayer][0] = ambassador;
	testG.hand[thisPlayer][1] = curse;
	testG.hand[thisPlayer][2] = curse;
	testG.hand[thisPlayer][3] = silver;
	testG.hand[thisPlayer][4] = gold;

	// call the refactored ambassador code
	testVal = ambassadorRefact(choice1, choice2, &testG, handPos);

	// check if 1 card (ambassador itself) was added to the current player's discard set
	printf("\nCurrent player:\n");
	stateStr = "discard count";
	testVal = testG.discardCount[thisPlayer];
	expectVal = G.discardCount[thisPlayer] + 1;
	asserttrue(stateStr, testVal, expectVal);

	// supplyBal tells if there are enough cards at supply to distribute to other players.
	// knowing the supply count has been updated to the value of choice2 due to the bug introduced in Assignment2,
	// supplyBal holds the value of choice2.
	int supplyBal = choice2;	

	// loop through other players who to check their discard count
	for (int i = 0; i < G.numPlayers; i++)
	{
		if (i != thisPlayer)
		{
			printf("\nPlayer %d\n", i);
						
			stateStr = "discard count";
			testVal = testG.discardCount[i];
		
			// if the player gain a card, check whether 1 card was added to these players' discard sets
			if (supplyBal > 0)
			{
				expectVal = G.discardCount[i] + 1;
				asserttrue(stateStr, testVal, expectVal);
			}
			// if the player doesn't gain a card, check whether no card was added to these players' discard sets
			else
			{
				expectVal = G.discardCount[i];
				asserttrue(stateStr, testVal, expectVal);
			}
		}
		supplyBal--;
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