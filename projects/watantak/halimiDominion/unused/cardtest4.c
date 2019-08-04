/*******************************************************************************
* Author: Ivan Timothy Halim                                                   *
* Date: 07/14/2019                                                             *
* Description: cardtest4.c implements a unit test of the Village card for      *
*              dominion.c.                                                     *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CARD_TEST "Village"

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

    // Draw Village card to player's hand
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = village;
    testG.handCount[thisPlayer]++;

    // Test Village card for +1 card and +2 actions
    printf("Testing %s card:\n", CARD_TEST);
    cardEffect(village, 0, 0, 0, &testG, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

    // Verify that 1 additional cards were added to hand
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1) {
        printf("Test passed. 1 additional cards drawn.\n");
        numTests++;
    } else {
        printf("Test failed. Wrong cards drawn.\n");
        failedTests++;
        numTests++;
    }

    // Verify that 2 additional numActions is added to game state
    if (testG.numActions == G.numActions + 2) {
        printf("Test passed. 2 additional numActions.\n");
        numTests++;
    } else {
        printf("Test failed. Wrong numActions.\n");
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