/*******************************************************************************
* Author: Ivan Timothy Halim                                                   *
* Date: 07/14/2019                                                             *
* Description: cardtest5.c implements a unit test of the Remodel card for      *
*              dominion.c.                                                     *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CARD_TEST "Remodel"

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
    int i, choice1, choice2;

    // Initialize game state
    initializeGame(numPlayer, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    // Draw Remodel card to player's hand
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = remodel;
    testG.handCount[thisPlayer]++;

    choice1 = 0;
    for (i = curse; i <= treasure_map; i++) {
        if (getCost(i) <= getCost(testG.hand[thisPlayer][choice1]) + 2) {
            choice2 = i;
            break;
        }
    }

    // Test Remodel card for trash 1 card and gain 1 card in the discard pile
    printf("Testing %s card:\n", CARD_TEST);
    cardEffect(remodel, choice1, choice2, 0, &testG, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

    // Verify that 1 card is added to the discardCount
    if (testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1) {
        printf("Test passed. 1 card added to the discard pile.\n");
        numTests++;
    } else {
        printf("Test failed. discardCount doesn't match.\n");
        failedTests++;
        numTests++;
    }

    // Verify that only 1 card is added to the playedCard pile
    if (testG.playedCardCount == G.playedCardCount + 1) {
        printf("Test passed. 1 card added to playedCard pile\n");
        numTests++;
    } else {
        printf("Test failed. playedCardCount doesn't match\n");
        failedTests++;
        numTests++;
    }

    // Verify that handCount is 1 card less
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1) {
        printf("Test passed. 1 card less in handCount\n");
        numTests++;
    } else {
        printf("Test failed. handCount doesn't match\n");
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