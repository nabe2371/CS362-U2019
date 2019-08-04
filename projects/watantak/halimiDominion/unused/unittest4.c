/********************************************************************
* Author: Ivan Timothy Halim                                        *
* Date: 07/14/2019                                                  *
* Description: unittest4.c implements a unit test of the function   *
*              fullDeckCount() for dominion.c.                      *
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FUNC_TEST "fullDeckCount"

int main() {

    int i;
    int result;
    int failedTests = 0;
    int numTests = 0;

    // Variables to initialize game state
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int thisPlayer = 0;

    // Initialize game state
    initializeGame(numPlayer, k, seed, &G);

    printf("Testing %s():\n", FUNC_TEST);

    // Tests for condition when deck is empty.
    G.handCount[0] = 0;
    G.deckCount[0] = 0;
    G.discardCount[0] = 0;
    result = fullDeckCount(0, copper, &G);
    if (result == 0) {
        printf("Test passed. Expected deck count of 0 matches actual result.\n");
        numTests++;
    } else {
        printf("Test failed. Expected deck count does not match actual result.\n");
        failedTests++;
        numTests++;
    }

    // Initialize test hand
    for (i = 0; i < 8; i++) {
        G.hand[thisPlayer][i] = copper;
    }
    G.handCount[thisPlayer] = 8;

    // Initialize test deck
    for (i = 0; i < 2; i++) {
        G.deck[thisPlayer][i] = copper;
    }
    G.deckCount[thisPlayer] = 2;

    // Initialize test discard
    for (i = 0; i < 6; i++) {
        G.discard[thisPlayer][i] = copper;
    }
    G.discardCount[thisPlayer] = 6;

    // Tests for silvers if deck only has coppers.
    result = fullDeckCount(0, silver, &G);
    if (result == 0) {
        printf("Test passed. Expected deck count of 0 matches actual result.\n");
        numTests++;
    } else {
        printf("Test failed. Expected deck count does not match actual result.\n");
        failedTests++;
        numTests++;
    }

    // Tests for coppers if deck only has coppers.
    result = fullDeckCount(0, copper, &G);
    if (result == 16) {
        printf("Test passed. Expected deck count of 16 matches actual result.\n");
        numTests++;
    } else {
        printf("Test failed. Expected deck count does not match actual result.\n");
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