/********************************************************************
* Author: Ivan Timothy Halim                                        *
* Date: 07/14/2019                                                  *
* Description: unittest2.c implements a unit test of the function   *
*              isGameOver() for dominion.c.                         *
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FUNC_TEST "isGameOver"

int main() {
    int i;
    int failedTests = 0;
    int numTests = 0;

    printf("Testing %s():\n", FUNC_TEST);

    // Variables to initialize game state
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;

    // Initialize game state
    initializeGame(MAX_PLAYERS, k, seed, &G);

    // Tests for proper end of game or continuation behavior when provinces in supply pile > 0
    printf("supplyCount[province] = %d\n", G.supplyCount[province]);
    if (isGameOver(&G)) {
        printf("Test failed. Incorrect result of gameover.\n");
        failedTests++;
        numTests++;
    } else {
        printf("Test passed. Correct result, game continues.\n");
        numTests++;
    }

    // Tests for proper behavior when provinces in supply pile == 0 
    G.supplyCount[province] = 0;
    printf("supplyCount[province] = %d\n", G.supplyCount[province]);
    if (isGameOver(&G)) {
        printf("Test passed. Correct result of gameover.\n");
        numTests++;
    } else {
        printf("Test failed. Game incorrectly continues.\n");
        failedTests++;
        numTests++;
    }

    // Tests for proper end of game or continuation behavior when count for 3 different cards in supply pile == 0
    G.supplyCount[province] = 12; // Resets supply pile for Province card
    for (i = 0; i < 3; i++) {

        G.supplyCount[i] = 0;    // Sets supply pile to 0
        printf("%d different cards now contain empty supply piles.\n", i + 1);

        if (isGameOver(&G) && i == 2) {
            printf("Test passed. Correct result of gameover.\n");
            numTests++;
        } else if (!isGameOver(&G) && i == 2) {
            printf("Test failed. Game incorrectly continues.\n");
            failedTests++;
            numTests++;
        } else if (isGameOver(&G) && i < 2) {
            printf("Test failed. Incorrect result of gameover.\n");
            failedTests++;
            numTests++;
        } else {
            printf("Test passed. Correct result, game continues.\n");
            numTests++;
        }
    }

    // Prints conclusion of testing result.
    if (!failedTests) {
        printf("All tests passed!\n\n");
    } else {
        printf("Failed %d out of %d tests.\n\n", failedTests, numTests);
    }

    return 0;
}