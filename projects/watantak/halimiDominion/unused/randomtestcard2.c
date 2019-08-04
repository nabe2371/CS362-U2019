#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARD_TEST "Minion"
#define NUM_TEST 50

int main() {

    srand(time(NULL));

    // Variables to initialize game state
    int k[10] = {council_room, feast, gardens, mine, estate,
                 village, baron, great_hall, minion, tribute};
    struct gameState G, testG;
    int seed, numPlayers;
    int choice1, choice2;
    int thisPlayer;
    int testPassed;
    int score = 0;
    int i, j;

    printf("Testing %s card:\n", CARD_TEST);

    for (i = 0; i < NUM_TEST; i++) {
        seed       = rand() % 5000;
        numPlayers = rand() % 3 + 2;
        thisPlayer = rand() % numPlayers;
        choice1    = rand() % 2;
        choice2    = rand() % 2;
        testPassed = 1;

        initializeGame(numPlayers, k, seed, &G);
        memcpy(&testG, &G, sizeof(struct gameState));

        // Draw Minion card to player's hand
        testG.hand[thisPlayer][testG.handCount[thisPlayer]] = minion;
        testG.handCount[thisPlayer]++;

        cardEffect(minion, choice1, choice2, 0, &testG, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

        if (testG.numActions != G.numActions + 1) {
            printf("Pass %d: numActions don't match\n", i + 1);
            testPassed = 0;
        }

        if (choice1) {
            if (testG.coins != G.coins + 2) {
                printf("Pass %d: coins don't match\n", i + 1);
                testPassed = 0;
            }
        } else if (choice2) {
            if (testG.handCount[thisPlayer] != 4) {
                printf("Pass %d: handCount doesn't match\n", i + 1);
                testPassed = 0;
            }
            if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 4) {
                printf("Pass %d: deckCount doesn't match\n", i + 1);
                testPassed = 0;
            }

            for (j = 0; j < numPlayers; j++) {
                if (j != thisPlayer) {
                    if (G.handCount[j] >= 5) {
                        if (testG.handCount[j] != 4) {
                            printf("Pass %d: other players handCount doesn't match\n", i + 1);
                            testPassed = 0;
                        }
                        if (testG.deckCount[j] != G.deckCount[j] - 4) {
                            printf("Pass %d: other players deckCount doesn't match\n", i + 1);
                            testPassed = 0;
                        }
                    } else {
                        if (testG.handCount[j] != G.handCount[j]) {
                            printf("Pass %d: other players handCount doesn't match\n", i + 1);
                            testPassed = 0;
                        }
                        if (testG.deckCount[j] != G.deckCount[j]) {
                            printf("Pass %d: other players deckCount doesn't match\n", i + 1);
                            testPassed = 0;
                        }
                    }
                }
            }
        }

        score += testPassed;
    }

    printf("Passed %d out of %d tests.\n\n", score, NUM_TEST);

    return 0;
}