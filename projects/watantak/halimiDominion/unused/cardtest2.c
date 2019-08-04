/*******************************************************************************
* Author: Ivan Timothy Halim                                                   *
* Date: 07/14/2019                                                             *
* Description: cardtest2.c implements a unit test of the Adventurer card for   *
*              dominion.c.                                                     *
********************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CARD_TEST "Adventurer"

int main() {

    int failedTests = 0;
    int numTests = 0;

    int i;
    int cardDrawn1, cardDrawn2;
    int finalCount = 0;
    int originalCount = 0;

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

    // Draw Adventurer card to player's hand
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = adventurer;
    testG.handCount[thisPlayer]++;

    // Test Adventurer card for draw of 2 treasure cards
    printf("Testing %s card:\n", CARD_TEST);
    cardEffect(adventurer, 0, 0, 0, &testG, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

    // Count the number of treasure cards in testG
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        cardDrawn1 = testG.hand[thisPlayer][i];
        if (cardDrawn1 == copper || cardDrawn1 == silver || cardDrawn1 == gold) {
            finalCount++;
        }
    }
    
    // Count the number of treasure cards in G
    for (i = 0; i < G.handCount[thisPlayer]; i++) {
        cardDrawn2 = G.hand[thisPlayer][i];
        if (cardDrawn2 == copper || cardDrawn2 == silver || cardDrawn2 == gold) {
            originalCount++;
        }
    }

    // Verify that 2 additional treasure cards were added to hand
    if (finalCount == originalCount + 2) {
        printf("Test passed. 2 additional treasure cards drawn.\n");
        numTests++;
    } else {
        printf("Test failed. Wrong no. of treasure cards.\n");
        failedTests++;
        numTests++;
    }

    // Verify that 2 additional cards were added to hand
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2) {
        printf("Test passed. 2 additional cards drawn.\n");
        numTests++;
    } else {
        printf("Test failed. Wrong cards drawn.\n");
        failedTests++;
        numTests++;
    }

    // Verify that revealed cards are added to the discard pile
    int revealedCards = (G.handCount[thisPlayer] + G.deckCount[thisPlayer]) - (testG.handCount[thisPlayer] + testG.deckCount[thisPlayer]);
    if (testG.playedCardCount == G.playedCardCount + revealedCards + 1) {
        printf("Test passed. Revealed cards are added to the discard pile.\n");
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