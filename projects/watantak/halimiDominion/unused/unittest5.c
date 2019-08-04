/********************************************************************
* Author: Ivan Timothy Halim                                        *
* Date: 07/14/2019                                                  *
* Description: unittest5.c implements a unit test of the function   *
*              shuffle() for dominion.c.                            *
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FUNC_TEST "shuffle"

int main() {

    int failedTests = 0;
    int numTests = 0;

    // Variables to initialize game state
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int thisPlayer = 0;

    // Initialize game state
    initializeGame(numPlayer, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    // We're going to test shuffle by playing Adventurer card
    printf("Testing %s():\n", FUNC_TEST);

    // Draw Adventurer card to player's hand
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = adventurer;
    testG.handCount[thisPlayer]++;

    // Play Adventurer then shuffle discarded cards back into the deck
    cardEffect(adventurer, 0, 0, 0, &testG, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);
    shuffle(thisPlayer, &testG);

    // Verify that deckCount is the same (increased by 1 from the Adventurer card)
    if (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] + 1) {
        printf("Test passed. Cards in the discard pile shuffled back into deck.\n");
        numTests++;
    } else {
        printf("Test failed. deckCount doesn't match.\n");
        failedTests++;
        numTests++;
    }

    // Prints conclusion of testing result.
    if (!failedTests) {
        printf("All tests passed!\n\n");
    } else {
        printf("Failed %d out of %d tests.\n\n", failedTests, numTests);
    }

    return 0;
}