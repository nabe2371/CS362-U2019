/***************************************************************************************************************
** Program name: CS362 Assignment4 randomtestcard2.c
** Author: Takahiro Watanabe
** Date: 07/25/19
** Description: This is the random testing program for the refactored minion code of the Dominion game.
**              This test randomly generates the inputs to run the minion code.
**				It compares the results with expected ones and prints pass or fail on screen.
** Source : sample code provided in CS362 (Summer 2019) Week 5 module ("How to Write a Simple Random Tester")
***************************************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define TESTCARD "minion"

// function header for the test oracle (checkMinionTest() function)
void checkMinionTest(int, int, struct gameState*, int);

int main() 
{
	int i, n, r, index, choice1, choice2, handPos; 

//	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	struct gameState G;

	printf("Testing refactored minion code.\n");
	printf("RANDOM TESTS.\n\n");

	srand(time(NULL));

	// run 2000 test cases
	for (n = 0; n < 2000; n++)
	{
		// assign random bytes for the gameState
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = (rand() % (256 - 0 + 1)) + 0;
		}

		// choice1 and choice2 are parameters of the minion code. randomly assigns them a value.
		// but they need to either 0 or 1 to make the test case meaningful.
		choice1 = (rand() % (1 - 0 + 1)) + 0;
		choice2 = (rand() % (1 - 0 + 1)) + 0;

		// p is randomly assigned a number of players
		G.numPlayers = (rand() % (MAX_PLAYERS - 2 + 1)) + 2;

		// loop through each player
		for (r = 0; r < G.numPlayers; r++)
		{
			// randomly generate the handCount and discardCount values, but shift the probability space
			G.handCount[r] = (rand() % (100 - 0 + 1)) + 0;
			G.discardCount[r] = (rand() % (MAX_DECK - 0 + 1)) + 0;
			G.deckCount[r] = (rand() % (MAX_DECK - 0 + 1)) + 0;
			G.playedCardCount = (rand() % (100 - 0 + 1)) + 0;

			// place a minion at a radom position in a player's hand
			if (G.handCount[r] > 0)
			{
				index = (rand() % ((G.handCount[r] - 1) - 0 + 1)) + 0;
				G.hand[r][index] = minion;
				handPos = index;
			}
			// if the handCount is 0, just add a minion
			else
			{
				G.handCount[r]++;
				G.hand[r][G.handCount[r] - 1] = minion;
				handPos = G.handCount[r] - 1;
			}
		}
				
		// decide the currently player randomly
		G.whoseTurn = (rand() % ((G.numPlayers - 1) - 0 + 1)) + 0;
//		G.playedCardCount = 0;
		// call the test oracle
		checkMinionTest(choice1, choice2, &G, handPos);
	}

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}

// This is a test oracle for the random tester.
// This function re-produce the expected gameState values when running the minion code
// then compared the acutal test results with the expected ones. It displays either pass or fail.
// this is a void function and takes two ints and a pointer to a gameState struct object as parameters.
void checkMinionTest(int choice1, int choice2, struct gameState* post, int handPos)
{
	// pre holds the gameState before running the minion code
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	// call the minion code with post, the gameState object used for testing
	minionRefact(choice1, choice2, post, handPos);

	// added an int variable to hold the current player
	int currentPlayer = whoseTurn(&pre);

	//+1 action
	pre.numActions++;

	//discard card from hand
	discardCard(handPos, currentPlayer, &pre, 0);

	if (choice1)		//+2 coins
	{
		pre.coins = pre.coins + 2;
	}

	else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
	{
		//discard hand
		while (numHandCards(&pre) > 0)
		{
			discardCard(handPos, currentPlayer, &pre, 0);
		}

		//the current player draws 4 cards
		for (int i = 0; i < 4; i++)
		{
			drawCard(currentPlayer, &pre);
		}

		//other players discard hand and redraw if hand size > 4
		for (int i = 0; i < pre.numPlayers; i++)
		{
	      	if (i != currentPlayer)
			{
				if (pre.handCount[i] > 4)
				{
					//discard hand
					while (pre.handCount[i] > 0)
					{
						discardCard(handPos, i, &pre, 0);
					}

					//draw 4
					for (int j = 0; j < 4; j++)
					{
						drawCard(i, &pre);
					}
				}
			}
		}

	}

	// here are the assert statements.
	// we compare the expected values with the acutal results for the gameState 
	// which the minion code is supposed to change inside it.
	for (int i = 0; i < pre.numPlayers; i++)
	{
		if (i == currentPlayer)
		{
			if (pre.discardCount[i] == post->discardCount[i])
			{
				printf("Current PASS: discardCount (expected: %d, actual: %d)\n", pre.discardCount[i], post->discardCount[i]);
			}
			else
			{
				printf("Current FAIL: discardCount (expected: %d, actual: %d)\n", pre.discardCount[i], post->discardCount[i]);
			}
		}
		else
		{
			if (pre.discardCount[i] == post->discardCount[i])
			{
				printf("Player%d PASS: discardCount (expected: %d, actual: %d)\n", i + 1, pre.discardCount[i], post->discardCount[i]);
			}
			else
			{
				printf("Player%d FAIL: discardCount (expected: %d, actual: %d)\n", i + 1, pre.discardCount[i], post->discardCount[i]);
			}
		}
	}
	
	printf("\n");

	for (int i = 0; i < pre.numPlayers; i++)
	{
		if (i == currentPlayer)
		{
			if (pre.handCount[i] == post->handCount[i])
			{
				printf("Current PASS: handCount (expected: %d, actual: %d)\n", pre.handCount[i], post->handCount[i]);
			}
			else
			{
				printf("Current FAIL: handCount (expected: %d, actual: %d)\n", pre.handCount[i], post->handCount[i]);
			}
		}
		else
		{
			if (pre.handCount[i] == post->handCount[i])
			{
				printf("Player%d PASS: handCount (expected: %d, actual: %d)\n", i + 1, pre.handCount[i], post->handCount[i]);
			}
			else
			{
				printf("Player%d FAIL: handCount (expected: %d, actual: %d)\n", i + 1, pre.handCount[i], post->handCount[i]);
			}
		}
	}

	printf("\n");

	for (int i = 0; i < pre.numPlayers; i++)
	{
		if (i == currentPlayer)
		{
			if (pre.deckCount[i] == post->deckCount[i])
			{
				printf("Current PASS: deckCount (expected: %d, actual: %d)\n", pre.deckCount[i], post->deckCount[i]);
			}
			else
			{
				printf("Current FAIL: deckCount (expected: %d, actual: %d)\n", pre.deckCount[i], post->deckCount[i]);
			}
		}
		else
		{
			if (pre.deckCount[i] == post->deckCount[i])
			{
				printf("Player%d PASS: deckCount (expected: %d, actual: %d)\n", i + 1, pre.deckCount[i], post->deckCount[i]);
			}
			else
			{
				printf("Player%d FAIL: deckCount (expected: %d, actual: %d)\n", i + 1, pre.deckCount[i], post->deckCount[i]);
			}
		}
	}

	printf("\n");

/*	if (memcmp(&pre, post, sizeof(struct gameState)) == 0)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
	}
*/
}

