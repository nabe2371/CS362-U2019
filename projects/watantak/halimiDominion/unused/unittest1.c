/********************************************************************
* Author: Ivan Timothy Halim                                        *
* Date: 07/14/2019                                                  *
* Description: unittest1.c implements a unit test of the function   *
*              whoseTurn() for dominion.c.                          *
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FUNC_TEST "whoseTurn"
#define NUM_TESTS 10

int main() {
    int i;
    int turn = 0;
    int result = 0;
    int failedTests = 0;
    int numTests = 0;
    struct gameState G;

    printf("Testing %s():\n", FUNC_TEST);

    // Runs test NUM_TESTS times, incrementing turn and testing for match with result on each iteration
    for (i = 0; i < NUM_TESTS; i++) {

        G.whoseTurn = turn;
        result = whoseTurn(&G);

        if (result == turn) {
            printf("Test %d passed. Expected turn matches actual result of whoseTurn().\n", i + 1);
            numTests++;
        } else {
            printf("Test %d failed. Expected turn doesn't match actual result of whoseTurn().\n", i + 1);
            failedTests++;
            numTests++;
        }

        turn++;
    }
    
    // Prints conclusion of testing result.
    if (!failedTests) {
        printf("All tests passed!\n\n");
    } else {
        printf("Failed %d out of %d tests.\n\n", failedTests, numTests);
    }

    return 0;
}