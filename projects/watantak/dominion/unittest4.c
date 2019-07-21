/***********************************************************************************************************************
** Program name: CS362 Assignment3 unittest4.c
** Author: Takahiro Watanabe
** Date: 07/14/19
** Description: This is the unit testing program for the refactored tribute code of the Dominion game.
**              This tests 4 cases and print the test results to screen.
** Source : cardtest4.c file provided in CS362 (Summer 2019) Week 3 module ("Assignment 3: Testing for business rules")
************************************************************************************************************************/

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *	  gcc - o unittest4 - g unittest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "tribute"

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

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1-1: testing for the case where the total number of next player’s deck count and discard count is 1 or less --------------
	printf("\nTEST 1-1: Next player\'s starting discard count is 1 & deck count is 0\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = -1;
	testG.deckCount[1] = 0;
	testG.discard[1][0] = copper;
	testG.discardCount[1] = 1;

	// call the refactored tribute code
	tributeRefact(&testG);

	// check if the next player's discard count is 1 (the revealed card should be discarded)
	stateStr = "next player\'s discard count";
	testVal = testG.discardCount[1];
	expectVal = 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if the next player's deck count is 0
	stateStr = "next player\'s deck count";
	testVal = testG.deckCount[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// check if the revealed card is the same as the one in the discard set (copper in this case)
	// but it turns out we cannot check it because we don't have access to tributeRevealedCard[0],
	// which is defined inside the refactored tirbute code. This should be another improvement of the source code.
/*	stateStr = "revealed card #1";
	testVal = tributeRevealedCard[0];
	expectVal = copper;
	asserttrue(stateStr, testVal, expectVal);
*/

// ----------- TEST 1-2: testing for the case where the total number of next player’s deck count and discard count is 1 or less --------------
	printf("\nTEST 1-2: Next player\'s starting discard count is 0 & deck count is 1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = copper;
	testG.deckCount[1] = 1;
	testG.discard[1][0] = -1;
	testG.discardCount[1] = 0;

	// call the refactored tribute code
	tributeRefact(&testG);

	// check if the next player's discard count is 1 (the revealed card should be discarded)
	stateStr = "next player\'s discard count";
	testVal = testG.discardCount[1];
	expectVal = 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if the next player's deck count is 0
	stateStr = "next player\'s deck count";
	testVal = testG.deckCount[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// check if the revealed card is the same as the one on the deck (copper in this case)
	// but it turns out we cannot check it because we don't have access to tributeRevealedCard[0],
	// which is defined inside the refactored tirbute code. This should be another improvement of the source code.
/*	stateStr = "revealed card #1";
	testVal = tributeRevealedCard[0];
	expectVal = copper;
	asserttrue(stateStr, testVal, expectVal);
*/

	// ----------- TEST 1-3: testing for the case where the total number of next player’s deck count and discard count is 1 or less --------------
	printf("\nTEST 1-3: Next player\'s starting discard count is 0 & deck count is 0\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = -1;
	testG.deckCount[1] = 0;
	testG.discard[1][0] = -1;
	testG.discardCount[1] = 0;

	// call the refactored tribute code
	tributeRefact(&testG);

	// check if the next player's discard count is 0
	stateStr = "next player\'s discard count";
	testVal = testG.discardCount[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// check if the next player's deck count is 0
	stateStr = "next player\'s deck count";
	testVal = testG.deckCount[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);
	
	// check if there was no card revelaed
	// but it turns out we cannot check it because we don't have access to tributeRevealedCard[0],
	// which is defined inside the refactored tirbute code. This should be another improvement of the source code.
/*	stateStr = "revealed card #1";
	testVal = tributeRevealedCard[0];
	expectVal = -1;
	asserttrue(stateStr, testVal, expectVal);
*/

// ----------- TEST 2-1: testing for the case where the total number of next player’s deck count and discard count is 2 or more --------------
	printf("\nTEST 2-1: Next player\'s starting discard count is 2 & deck count is 0\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = -1;
	testG.deckCount[1] = 0;
	testG.discard[1][0] = copper;
	testG.discard[1][1] = silver;
	testG.discardCount[1] = 2;

	// call the refactored tribute code
	tributeRefact(&testG);

	// check if the next player's discard count is 2 (revealed cards should be discarded)
	stateStr = "next player\'s discard count";
	testVal = testG.discardCount[1];
	expectVal = 2;
	asserttrue(stateStr, testVal, expectVal);

	// check if the next player's deck count is 0
	stateStr = "next player\'s deck count";
	testVal = testG.deckCount[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// wanted to check if the revealed cards are the same as ones in the discard set (copper and silver in this case)
	// but it turns out we cannot check it because we don't have access to tributeRevealedCard[0]and[1],
	// which is defined inside the refactored tirbute code. This should be another improvement of the source code.


// ----------- TEST 2-2: testing for the case where the total number of next player’s deck count and discard count is 2 or more --------------
	printf("\nTEST 2-2: Next player\'s starting discard count is 0 & deck count is 2\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = copper;
	testG.deck[1][1] = silver;
	testG.deckCount[1] = 2;
	testG.discard[1][0] = -1;
	testG.discardCount[1] = 0;

	// call the refactored tribute code
	tributeRefact(&testG);

	// check if the next player's discard count is 2 (revealed cards should be discarded)
	stateStr = "next player\'s discard count";
	testVal = testG.discardCount[1];
	expectVal = 2;
	asserttrue(stateStr, testVal, expectVal);

	// check if the next player's deck count is 0
	stateStr = "next player\'s deck count";
	testVal = testG.deckCount[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// wanted to check if the revealed cards are the same as ones on the deck (copper and silver in this case)
	// but it turns out we cannot check it because we don't have access to tributeRevealedCard[0]and[1],
	// which is defined inside the refactored tirbute code. This should be another improvement of the source code.


	// ----------- TEST 2-3: testing for the case where the total number of next player’s deck count and discard count is 2 or more --------------
	printf("\nTEST 2-3: Next player\'s starting discard count is 1 & deck count is 1\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = copper;
	testG.deckCount[1] = 1;
	testG.discard[1][0] = silver;
	testG.discardCount[1] = 1;

	// call the refactored tribute code
	tributeRefact(&testG);

	// check if the next player's discard count is 2 (revealed cards should be discarded)
	stateStr = "next player\'s discard count";
	testVal = testG.discardCount[1];
	expectVal = 2;
	asserttrue(stateStr, testVal, expectVal);

	// check if the next player's deck count is 0
	stateStr = "next player\'s deck count";
	testVal = testG.deckCount[1];
	expectVal = 0;
	asserttrue(stateStr, testVal, expectVal);

	// wanted to check if the revealed cards are the same as ones on the deck and discard set (copper and silver in this case)
	// but it turns out we cannot check it because we don't have access to tributeRevealedCard[0]and[1],
	// which is defined inside the refactored tirbute code. This should be another improvement of the source code.


	// ----------- TEST 3-1: testing for the case where the code drops one of the 2 identical revealed cards --------------
	printf("\nTEST 3-1: 2 revealed cards are the same\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = -1;
	testG.deckCount[1] = 0;
	testG.discard[1][0] = copper;
	testG.discard[1][1] = copper;
	testG.discardCount[1] = 2;

	// call the refactored tribute code
	tributeRefact(&testG);

	// check if the played card count is increased by 1
	stateStr = "played card count";
	testVal = testG.playedCardCount;
	expectVal = G.playedCardCount + 1;
	asserttrue(stateStr, testVal, expectVal);

	// check if one of the card is added to the played card
	stateStr = "played card";
	testVal = testG.playedCards[G.playedCardCount];
	expectVal = copper;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 3-2: testing for the case where the code drops one of the 2 identical revealed cards --------------
	printf("\nTEST 3-2: 2 revealed cards are different\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = -1;
	testG.deckCount[1] = 0;
	testG.discard[1][0] = copper;
	testG.discard[1][1] = silver;
	testG.discardCount[1] = 2;

	// call the refactored tribute code
	tributeRefact(&testG);

	// check if there's no change in the played card count
	stateStr = "played card count";
	testVal = testG.playedCardCount;
	expectVal = G.playedCardCount;
	asserttrue(stateStr, testVal, expectVal);

	// check if there's no addition to the played card
	stateStr = "played card";
	testVal = testG.playedCards[G.playedCardCount];
	expectVal = -9999;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 4-1: testing for the correct bonus --------------
	printf("\nTEST 4-1: treasure and victory cards are revealed\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = -1;
	testG.deckCount[1] = 0;
	testG.discard[1][0] = copper;
	testG.discard[1][1] = province;
	testG.discardCount[1] = 2;

	// call the refactored tribute code
	tributeRefact(&testG);

	// check if the player gained +2 coins
	stateStr = "coins";
	testVal = testG.coins;
	expectVal = G.coins + 2;
	asserttrue(stateStr, testVal, expectVal);

	// check if 2 cards were added to the player's hand
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = G.handCount[thisPlayer] + 2;
	asserttrue(stateStr, testVal, expectVal);


	// check if there's no change in numActions
	stateStr = "numActions";
	testVal = testG.numActions;
	expectVal = G.numActions;
	asserttrue(stateStr, testVal, expectVal);


	// ----------- TEST 4-2: testing for the correct bonus --------------
	printf("\nTEST 4-2: curse and action cards are revealed\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// manually set up the next player's deck and discard set for testing purpose
	testG.deck[1][0] = -1;
	testG.deckCount[1] = 0;
	testG.discard[1][0] = curse;
	testG.discard[1][1] = smithy;
	testG.discardCount[1] = 2;

	// call the refactored tribute code
	tributeRefact(&testG);

	// check if the player gained 0 coins
	stateStr = "coins";
	testVal = testG.coins;
	expectVal = G.coins;
	asserttrue(stateStr, testVal, expectVal);

	// check if no cards were added to the player's hand
	stateStr = "hand count";
	testVal = testG.handCount[thisPlayer];
	expectVal = G.handCount[thisPlayer];
	asserttrue(stateStr, testVal, expectVal);


	// check if +2 numActions were added
	stateStr = "numActions";
	testVal = testG.numActions;
	expectVal = G.numActions + 2;
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