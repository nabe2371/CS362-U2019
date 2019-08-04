/*******************************************************************************
* Author: Ivan Timothy Halim                                                   *
* Date: 07/14/2019                                                             *
* Description: cardtest3.c implements a unit test of the Council Room card for *
*              dominion.c.                                                     *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CARD_TEST "Council Room"

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

    // Draw Council Room card to player's hand
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = council_room;
    testG.handCount[thisPlayer]++;

    // Test Council Room card for +4 cards and +1 buy
    printf("Testing %s card:\n", CARD_TEST);
    cardEffect(council_room, 0, 0, 0, &testG, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

    // Verify that 4 additional cards were added to hand
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 4) {
        printf("Test passed. 4 additional cards drawn.\n");
        numTests++;
    } else {
        printf("Test failed. Wrong cards drawn.\n");
        failedTests++;
        numTests++;
    }

    // Verify that an additional numBuy is added to game state
    if (testG.numBuys == G.numBuys + 1) {
        printf("Test passed. 1 additional numBuys.\n");
        numTests++;
    } else {
        printf("Test failed. Wrong numBuys.\n");
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