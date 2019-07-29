/***************************************************************************************************************
** Program name: CS362 Assignment4 randomtestcard3.c
** Author: Takahiro Watanabe
** Date: 07/26/19
** Description: This is the random testing program for the refactored tribute code of the Dominion game.
**              This test randomly generates the inputs to run the tribute code.
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

#define TESTCARD "tribute"

// function header for the test oracle (checkTributeTest() function)
void checkTributeTest(struct gameState*);

int main() 
{
	int i, n, r, q, k; // , discardCount, handCount, supplyCount;

//	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	struct gameState G;

	printf("Testing refactored tribute code.\n");
	printf("RANDOM TESTS.\n\n");

	srand(time(NULL));

	// run 2000 test cases
	for (n = 0; n < 20000; n++)
	{
		// assign random bytes for the gameState
		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = (rand() % (256 - 0 + 1)) + 0;
		}

		// p is randomly assigned a number of players
		G.numPlayers = (rand() % (MAX_PLAYERS - 2 + 1)) + 2;

		// loop through each player
		for (r = 0; r < G.numPlayers; r++)
		{
			// randomly generate the handCount and discardCount values, but shift the probability space
			G.handCount[r] = (rand() % (MAX_HAND - 0 + 1)) + 0;
			G.discardCount[r] = (rand() % (MAX_DECK - 0 + 1)) + 0;
			G.deckCount[r] = (rand() % (MAX_DECK - 0 + 1)) + 0;
			G.playedCardCount = (rand() % (100 - 0 + 1)) + 0;
		}

		// randomly fill each player's hand, deck, and discard set, but shift the probaility space
		// to make sure they are filled with valid cards
		for (q = 0; q < G.numPlayers; q++)
		{
			for (k = 0; k < G.handCount[q]; k++)
			{
				G.hand[q][k] = (rand() % (26 - 0 + 1)) + 0;
			}

			for (k = 0; k < G.deckCount[q]; k++)
			{
				G.deck[q][k] = (rand() % (26 - 0 + 1)) + 0;
			}

			for (k = 0; k < G.discardCount[q]; k++)
			{
				G.discard[q][k] = (rand() % (26 - 0 + 1)) + 0;
			}
		}

		// decide the currently player randomly
		G.whoseTurn = (rand() % ((G.numPlayers - 1) - 0 + 1)) + 0;
//		G.playedCardCount = 0;
		// call the test oracle
		checkTributeTest(&G);
	}

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);

 	return 0;
}

// This is a test oracle for the random tester.
// This function re-produce the expected gameState values when running the tribute code
// then compared the acutal test results with the expected ones. It displays either pass or fail.
// this is a void function and takes two ints and a pointer to a gameState struct object as parameters.
void checkTributeTest(struct gameState* post)
{
	// pre holds the gameState before running the tribute code
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	// call the tribute code with post, the gameState object used for testing
	tributeRefact(post);

	// added an int variable to hold the current player
	int currentPlayer = whoseTurn(&pre);

	// added an int variable to hold the next player
	int nextPlayer = currentPlayer + 1;

	if (nextPlayer > (pre.numPlayers - 1))
	{
		nextPlayer = 0;
	}

	// added a container for revealed cards
	int tributeRevealedCards[2] = { -1, -1 };

	// the case where the player has only one or zero card at deck and the discard set in total
	if ((pre.discardCount[nextPlayer] + pre.deckCount[nextPlayer]) <= 1)
	{
		if (pre.deckCount[nextPlayer] > 0)
		{
			tributeRevealedCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
			pre.deckCount[nextPlayer]--;
		}
		else if (pre.discardCount[nextPlayer] > 0)
		{
			tributeRevealedCards[0] = pre.discard[nextPlayer][pre.discardCount[nextPlayer] - 1];
			pre.discardCount[nextPlayer]--;
		}
		else
		{
			//No Card to Reveal
		}
	}
	// the case where the player has two or more cards at deck and the discard set in total
	else
	{
		if (pre.deckCount[nextPlayer] == 0)
		{
			nextPlayerDiscardToDeck(&pre);	// call a newly created helper function
		}

		tributeRevealedCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
		pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1] = -1;	// minus one instead of decrement
		pre.deckCount[nextPlayer]--;

		if (pre.deckCount[nextPlayer] == 0)	// check the deck count one more time
		{
			nextPlayerDiscardToDeck(&pre);	// call a newly created helper function
		}

		tributeRevealedCards[1] = pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1];
		pre.deck[nextPlayer][pre.deckCount[nextPlayer] - 1] = -1;	// minus one instead of decrement
		pre.deckCount[nextPlayer]--;
	}

	if (tributeRevealedCards[0] == tributeRevealedCards[1])
	{
		//If we have a duplicate card, just keep both 
		pre.playedCards[pre.playedCardCount] = tributeRevealedCards[1];
		pre.playedCardCount++;
		tributeRevealedCards[1] = -1;
	}

	// get the bonus depending on the revealed card
	for (int i = 0; i < 2; i++)
	{
		if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold)
		{
			//Treasure cards
			pre.coins += 2;
		}

		else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall)
		{
			//Victory Card Found
			drawCard(currentPlayer, &pre);
			drawCard(currentPlayer, &pre);
		}

		else if (tributeRevealedCards[i] == curse)
		{
			// if it is a curse, do nothing (no bonus)
		}

		else if (tributeRevealedCards[i] == -1)
		{
			break;	// if the card is dropped, exit the loop
		}

		else
		{
			//Action Card
			pre.numActions = pre.numActions + 2;
		}
	}


	// here are the assert statements.
	// we compare the expected values with the acutal results for the gameState 
	// which the tribute code is supposed to change inside it.
	if (pre.coins == post->coins)
	{
		printf("PASS: coins (expected: %d, actual: %d)\n", pre.coins, post->coins);
	}
	else
	{
		printf("FAIL: coins (expected: %d, actual: %d)\n", pre.coins, post->coins);
	}

	if (pre.numActions == post->numActions)
	{
		printf("PASS: numActions (expected: %d, actual: %d)\n", pre.coins, post->coins);
	}
	else
	{
		printf("FAIL: numActions (expected: %d, actual: %d)\n", pre.coins, post->coins);
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

	if (pre.deckCount[currentPlayer] == post->deckCount[currentPlayer])
	{
		printf("PASS: deckCount (expected: %d, actual: %d)\n", pre.deckCount[currentPlayer], post->deckCount[currentPlayer]);
	}
	else
	{
		printf("FAIL: deckCount (expected: %d, actual: %d)\n", pre.deckCount[currentPlayer], post->deckCount[currentPlayer]);
	}

	if (pre.playedCardCount == post->playedCardCount)
	{
		printf("PASS: playedCardCount (expected: %d, actual: %d)\n", pre.playedCardCount, post->playedCardCount);
	}
	else
	{
		printf("FAIL: playedCardCount (expected: %d, actual: %d)\n", pre.playedCardCount, post->playedCardCount);
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

