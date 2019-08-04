/*******************************************************************************
* Author: Ivan Timothy Halim                                                   *
* Date: 07/14/2019                                                             *
* Description: cardtest1.c implements a unit test of the Smithy card for       *
*              dominion.c.                                                     *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CARD_TEST "Smithy"

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

    // Draw Smithy card to player's hand
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
    testG.handCount[thisPlayer]++;

    // Test Smithy card for +3 cards
    printf("Testing %s card:\n", CARD_TEST);
    cardEffect(smithy, 0, 0, 0, &testG, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

    // Verify that 3 additional cards were added to hand
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 3) {
        printf("Test passed. 3 additional cards drawn.\n");
        numTests++;
    } else {
        printf("Test failed. Wrong cards drawn.\n");
        failedTests++;
        numTests++;
    }

    // Verify that 1 card is added to the playedCard pile
    if (testG.playedCardCount == G.playedCardCount + 1) {
        printf("Test passed. 1 card is added to the playedCardPile\n");
        numTests++;
    } else {
        printf("Test failed. playedCardCount doesn't match.\n");
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