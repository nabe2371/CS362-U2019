/***********************************************************************************************************************
** Program name: CS362 Assignment3 cardtest4.c
** Author: Takahiro Watanabe
** Date: 07/15/19
** Description: This is the unit testing program for the getWinners function of the Dominion game.
**              This tests 1 case and print the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *	  gcc - o cardtest4 - g cardtest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "getWinners"

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

	// ----------- TEST 1-1: testing for the winner decision --------------
	printf("\nTEST 1-1: decide a winner when all are tied (currentPlayer=0)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	int players[4];

	// manually set players' scores
	// player[0]=10, player[1]=10, player[2]=10
	testG.handCount[0] = 1;
	testG.handCount[1] = 1;
	testG.handCount[2] = 1;
	testG.hand[0][0] = duchy;
	testG.hand[1][0] = province;
	testG.hand[2][0] = province;

	testG.discardCount[0] = 1;
	testG.discardCount[1] = 1;
	testG.discardCount[2] = 1;
	testG.discard[0][0] = province;
	testG.discard[1][0] = estate;
	testG.discard[2][0] = duchy;

	testG.deckCount[0] = 1;
	testG.deckCount[1] = 1;
	testG.deckCount[2] = 1;
	testG.deck[0][0] = estate;
	testG.deck[1][0] = duchy;
	testG.deck[2][0] = estate;
	
	// manually update the current player (whoseTurn)
	testG.whoseTurn = 0;
	
	// call the endTurn function
	getWinners(players, &testG);

	// check if the 1st player's value is 0 (lost)
	stateStr = "1st player (WIN:1, LOSS:0)";
	testVal = players[0];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// check if the 2nd player's value is 1 (won)
	stateStr = "2nd player (WIN:1, LOSS:0)";
	testVal = players[1];
	expectVal = 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if the 3rd player's value is 1 (won)
	stateStr = "3rd player (WIN:1, LOSS:0)";
	testVal = players[2];
	expectVal = 1;
	asserttrue(stateStr, testVal, expectVal);

	// ----------- TEST 1-2: testing for the winner decision --------------
	printf("\nTEST 1-2: decide a winner with 2nd and 3rd players are tied 1st (currentPlayer=1)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set players' scores
	// player[0]=9, player[1]=10, player[2]=10
	testG.handCount[0] = 1;
	testG.handCount[1] = 1;
	testG.handCount[2] = 1;
	testG.hand[0][0] = duchy;
	testG.hand[1][0] = province;
	testG.hand[2][0] = province;

	testG.discardCount[0] = 1;
	testG.discardCount[1] = 1;
	testG.discardCount[2] = 1;
	testG.discard[0][0] = province;
	testG.discard[1][0] = estate;
	testG.discard[2][0] = duchy;

	testG.deckCount[0] = 0;
	testG.deckCount[1] = 1;
	testG.deckCount[2] = 1;
	testG.deck[0][0] = -1;
	testG.deck[1][0] = duchy;
	testG.deck[2][0] = estate;

	// manually update the current player (whoseTurn)
	testG.whoseTurn = 1;

	// call the endTurn function
	getWinners(players, &testG);

	// check if the 1st player's value is 0 (lost)
	stateStr = "1st player (WIN:1, LOSS:0)";
	testVal = players[0];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// check if the 2nd player's value is 0 (lost)
	stateStr = "2nd player (WIN:1, LOSS:0)";
	testVal = players[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// check if the 3rd player's value is 1 (won)
	stateStr = "3rd player (WIN:1, LOSS:0)";
	testVal = players[2];
	expectVal = 1;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 1-3: testing for the winner decision --------------
	printf("\nTEST 1-3: decide a winner with 2nd and 3rd players are tied 2nd by 2 points (currentPlayer=0)\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set players' scores
	// player[0]=10, player[1]=8, player[2]=8
	testG.handCount[0] = 1;
	testG.handCount[1] = 1;
	testG.handCount[2] = 1;
	testG.hand[0][0] = duchy;
	testG.hand[1][0] = province;
	testG.hand[2][0] = province;

	testG.discardCount[0] = 1;
	testG.discardCount[1] = 1;
	testG.discardCount[2] = 1;
	testG.discard[0][0] = province;
	testG.discard[1][0] = curse;
	testG.discard[2][0] = duchy;

	testG.deckCount[0] = 1;
	testG.deckCount[1] = 1;
	testG.deckCount[2] = 1;
	testG.deck[1][0] = estate;
	testG.deck[1][0] = duchy;
	testG.deck[2][0] = curse;

	// manually update the current player (whoseTurn)
	testG.whoseTurn = 0;

	// call the endTurn function
	getWinners(players, &testG);

	// check if the 1st player's value is 1 (won)
	stateStr = "1st player (WIN:1, LOSS:0)";
	testVal = players[0];
	expectVal = 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if the 2nd player's value is 0 (lost)
	stateStr = "2nd player (WIN:1, LOSS:0)";
	testVal = players[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// check if the 3rd player's value is 0 (lost)
	stateStr = "3rd player (WIN:1, LOSS:0)";
	testVal = players[2];
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

