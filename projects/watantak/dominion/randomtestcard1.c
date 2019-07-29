/***************************************************************************************************************
** Program name: CS362 Assignment4 randomtestcard1.c
** Author: Takahiro Watanabe
** Date: 07/25/19
** Description: This is the random testing program for the refactored baron code of the Dominion game.
**              This test randomly generates the inputs to run the baron code.
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

#define TESTCARD "baron"

// function header for the test oracle (checkBaronTest() function)
void checkBaronTest(int, struct gameState*);

int main() 
{
	int i, n, r, p, insEstate, index, choice1; // , discardCount, handCount, supplyCount;

//	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	struct gameState G;

	printf("Testing refactored baron code.\n");
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

		// choice1 is a parameter of the baron code. randomly assigns a value for it.
		// but it needs to either 0 or 1 to make the test case meaningful.
		choice1 = (rand() % (1 - 0 + 1)) + 0;

		// p is randomly assigned a number of players
		p = (rand() % (MAX_PLAYERS - 2 + 1)) + 2;

		// loop through each player
		for (r = 0; r < p; r++)
		{
			// randomly generate the handCount and discardCount values, but shift the probability space
			G.handCount[r] = (rand() % (MAX_HAND - 0 + 1)) + 0;
			G.discardCount[r] = (rand() % (MAX_DECK - 0 + 1)) + 0;
		
			// insEstate holds either 0 or 1
			insEstate = (rand() % (1 - 0 + 1)) + 0;
		
			// if insEstate is 1 and handCount is 1 or more, place an esate at a radom position in a player's hand
			if ( (insEstate == 1) && (G.handCount[r] > 0) )
			{
				index = (rand() % ((G.handCount[r] - 1) - 0 + 1)) + 0;
				G.hand[r][index] = estate;
			}
		}
		
		// randomly assigns a value for the estate's supplyCount
		// shift the probability space depending on the number of players
		if (p == 2)
		{
			G.supplyCount[estate] = (rand() % (8 - 0 + 1)) + 0;
		}
		else
		{
			G.supplyCount[estate] = (rand() % (12 - 0 + 1)) + 0;
		}
		
		// decide the currently player randomly
		G.whoseTurn = (rand() % ((p - 1) - 0 + 1)) + 0;

		// call the test oracle
		checkBaronTest(choice1, &G);
	}

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}

// This is a test oracle for the random tester
// This function re-produce the expected gameState values when running the baron code
// then compared the acutal test results with the expected ones. It displays either pass or fail.
// this is a void function and takes an int and a pointer to a gameState struct object as parameters.
void checkBaronTest(int choice1, struct gameState* post)
{
	// pre holds the gameState before running the baron code
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	// call the baron code with post, the gameState object used for testing
	baronRefact(choice1, post);

	int currentPlayer = whoseTurn(&pre);
	pre.numBuys++;

	// here, I reproduce the expected gameState values when we run the baron code.
	// the below code basically does what the baron code is supposed to do.
	if (choice1 == 1)
	{
		int p = 0;	//Iterator for hand!
		int card_not_discarded = 1;			// Flag for discard set!

		while (card_not_discarded)
		{
			//Found an estate card!
			if (pre.hand[currentPlayer][p] == estate)
			{
				pre.coins += 4;		//Add 4 coins to the amount of coins
				// adding the estate card to the discarded set
				pre.discard[currentPlayer][pre.discardCount[currentPlayer]] = pre.hand[currentPlayer][p];

				pre.discardCount[currentPlayer]++;	// increment the discarded set count

				for (; p < pre.handCount[currentPlayer]; p++)
				{
					pre.hand[currentPlayer][p] = pre.hand[currentPlayer][p + 1];
				}

				pre.hand[currentPlayer][pre.handCount[currentPlayer]] = -1;
				pre.handCount[currentPlayer]--;
				card_not_discarded = 0;		//Exit the loop
			}
			// no estate in hand
			else if (p > pre.handCount[currentPlayer])
			{
				if (supplyCount(estate, &pre) > 0)
				{
					gainCard(estate, &pre, 0, currentPlayer);
//					pre.supplyCount[estate]--;		//Decrement estates

					if (supplyCount(estate, &pre) == 0)
					{
						isGameOver(&pre);
					}
				}
				card_not_discarded = 0;		//Exit the loop
			}

			else
			{
				p++;		//Next card
			}
		}
	}
	else
	{
		// the player chooses not to discard an estate
		if (supplyCount(estate, &pre) > 0)
		{
			gainCard(estate, &pre, 0, currentPlayer);	//Gain an estate
//			pre.supplyCount[estate]--;		//Decrement Estates

			if (supplyCount(estate, &pre) == 0)
			{
				isGameOver(&pre);
			}
		}
	}

	// here are the assert statements.
	// we compare the expected values with the acutal results for the gameState 
	// which the baron code is supposed to change inside it.
	if (pre.coins == post->coins)
	{
		printf("PASS: coins (expected: %d, actual: %d)\n", pre.coins, post->coins);
	}
	else
	{
		printf("FAIL: coins (expected: %d, actual: %d)\n", pre.coins, post->coins);
	}

	if (pre.discardCount[currentPlayer] == post->discardCount[currentPlayer])
	{
		printf("PASS: discardCount (expected: %d, actual: %d)\n", pre.discardCount[currentPlayer], post->discardCount[currentPlayer]);
	}
	else
	{
		printf("FAIL: discardCount (expected: %d, actual: %d)\n", pre.discardCount[currentPlayer], post->discardCount[currentPlayer]);
	}

	if (pre.handCount[currentPlayer] == post->handCount[currentPlayer])
	{
		printf("PASS: handCount (expected: %d, actual: %d)\n", pre.handCount[currentPlayer], post->handCount[currentPlayer]);
	}
	else
	{
		printf("FAIL: handCount (expected: %d, actual: %d)\n", pre.handCount[currentPlayer], post->handCount[currentPlayer]);
	}

	if (pre.supplyCount[estate] == post->supplyCount[estate])
	{
		printf("PASS: supplyCount (expected: %d, actual: %d)\n", pre.supplyCount[estate], post->supplyCount[estate]);
	}
	else
	{
		printf("FAIL: supplyCount (expected: %d, actual: %d)\n", pre.supplyCount[estate], post->supplyCount[estate]);
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

