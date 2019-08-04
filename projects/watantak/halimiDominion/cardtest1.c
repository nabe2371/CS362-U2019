/***********************************************************************************************************************
** Program name: CS362 Assignment3 cardtest1.c
** Author: Takahiro Watanabe
** Date: 07/15/19
** Description: This is the unit testing program for the initializeGame function of the Dominion game.
**              This tests 4 cases and print the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *	  gcc - o cardtest1 - g cardtest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "initializeGame"

// function header for the asserttrue() function
void asserttrue(char*, int, int);

int main() 
{
	int seed = 1000;
	int numPlayers = 3;
//	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, estate,
			sea_hag, tribute, smithy, council_room };
	char* stateStr;
	int testVal, expectVal;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	// ----------- TEST 1-1: testing for valid/invalid kingdom card supplies --------------
	printf("\nTEST 1-1: selected kingdom cards are different\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the initializeGame function
	testVal = initializeGame(numPlayers, k, seed, &testG);

	// check if the return value is 0
	stateStr = "return value";
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);
	
	// ----------- TEST 1-2: testing for valid/invalid kingdom card supplies --------------
	printf("\nTEST 1-2: some of the selected kingdom cards are the same\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// reset the kingdom cards 
	int newK[10] = { adventurer, embargo, village, minion, mine, estate,
		sea_hag, tribute, smithy, adventurer };

	// call the initializeGame function
	testVal = initializeGame(numPlayers, newK, seed, &testG);

	// check if the return value is -1
	stateStr = "return value";
	expectVal = -1;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 2-1: testing for the supply count of curse --------------
	printf("\nTEST 2-1: the supply count of curse (numPlayers=2)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// update the numPlayers
	numPlayers = 2;

	// call the initializeGame function
	initializeGame(numPlayers, k, seed, &testG);

	// check if the supply count of curse is 10
	stateStr = "supply count";
	testVal = testG.supplyCount[curse];
	expectVal = 10;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 2-2: testing for the supply count of curse --------------
	printf("\nTEST 2-2: the supply count of curse (numPlayers=3)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// update the numPlayers
	numPlayers = 3;

	// call the initializeGame function
	initializeGame(numPlayers, k, seed, &testG);

	// check if the supply count of curse is 20
	stateStr = "supply count";
	testVal = testG.supplyCount[curse];
	expectVal = 20;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 2-3: testing for the supply count of curse --------------
	printf("\nTEST 2-3: the supply count of curse (numPlayers=4)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// update the numPlayers
	numPlayers = 4;

	// call the initializeGame function
	initializeGame(numPlayers, k, seed, &testG);

	// check if the supply count of curse is 30
	stateStr = "supply count";
	testVal = testG.supplyCount[curse];
	expectVal = 30;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 3-1: testing for the supply count of victory cards --------------
	printf("\nTEST 3-1: the supply count of victory cards (numPlayers=2)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// update the numPlayers
	numPlayers = 2;

	// call the initializeGame function
	initializeGame(numPlayers, k, seed, &testG);

	// check if the supply count of a victory card (province for testing purpose) is 8
	stateStr = "supply count";
	testVal = testG.supplyCount[province];
	expectVal = 8;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 3-2: testing for the supply count of victory cards --------------
	printf("\nTEST 3-2: the supply count of victory cards (numPlayers=3)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// update the numPlayers
	numPlayers = 3;

	// call the initializeGame function
	initializeGame(numPlayers, k, seed, &testG);

	// check if the supply count of a victory card (province for testing purpose) is 12
	stateStr = "supply count";
	testVal = testG.supplyCount[province];
	expectVal = 12;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 4-1: testing for the kingdom card supply pile settings --------------
	printf("\nTEST 4-1: kingdom card supply count (numPlayers=2)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually reset the kingdom cards 
	int newK2[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		gardens, tribute, smithy, great_hall };

	// update the numPlayers
	numPlayers = 2;

	// call the initializeGame function
	initializeGame(numPlayers, newK2, seed, &testG);

	// check if the supply count of gardens is 8
	stateStr = "supply count";
	testVal = testG.supplyCount[gardens];
	expectVal = 8;
	asserttrue(stateStr, testVal, expectVal);

	// check if the supply count of great hall is 8
	stateStr = "supply count";
	testVal = testG.supplyCount[great_hall];
	expectVal = 8;
	asserttrue(stateStr, testVal, expectVal);

	// check if the supply count of minion is 10 (in the kingdom set)
	stateStr = "supply count";
	testVal = testG.supplyCount[minion];
	expectVal = 10;
	asserttrue(stateStr, testVal, expectVal);

	// check if the supply count of baron is -1 (not in the kingdom set)
	stateStr = "supply count";
	testVal = testG.supplyCount[baron];
	expectVal = -1;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 4-2: testing for the kingdom card supply pile settings --------------
	printf("\nTEST 4-2: kingdom card supply count (numPlayers=3)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// update the numPlayers
	numPlayers = 3;

	// call the initializeGame function
	initializeGame(numPlayers, newK2, seed, &testG);

	// check if the supply count of gardens is 12
	stateStr = "supply count";
	testVal = testG.supplyCount[gardens];
	expectVal = 12;
	asserttrue(stateStr, testVal, expectVal);

	// check if the supply count of great hall is 12
	stateStr = "supply count";
	testVal = testG.supplyCount[great_hall];
	expectVal = 12;
	asserttrue(stateStr, testVal, expectVal);

	// check if the supply count of minion is 10 (in the kingdom set)
	stateStr = "supply count";
	testVal = testG.supplyCount[minion];
	expectVal = 10;
	asserttrue(stateStr, testVal, expectVal);

	// check if the supply count of baron is -1 (not in the kingdom set)
	stateStr = "supply count";
	testVal = testG.supplyCount[baron];
	expectVal = -1;
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

