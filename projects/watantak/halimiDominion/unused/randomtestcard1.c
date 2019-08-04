#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARD_TEST "Baron"
#define NUM_TEST 50

int countEstate(int player, struct gameState *state) {
    int n = 0;
    int i;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == estate) {
            n += 1;
        }
    }

    return n;
}

int main() {

    srand(time(NULL));

    // Variables to initialize game state
    int k[10] = {council_room, feast, gardens, mine, estate,
                 village, baron, great_hall, minion, tribute};
    struct gameState G, testG;
    int seed, numPlayers;
    int thisPlayer, nextPlayer;
    int testPassed;
    int score = 0;
    int choice1;
    int i, m, n;

    printf("Testing %s card:\n", CARD_TEST);

    for (i = 0; i < NUM_TEST; i++) {
        seed       = rand() % 5000;
        numPlayers = rand() % 3 + 2;
        thisPlayer = rand() % numPlayers;
        nextPlayer = (thisPlayer + 1) % numPlayers;
        choice1    = rand() % 2;
        testPassed = 1;

        initializeGame(numPlayers, k, seed, &G);
        memcpy(&testG, &G, sizeof(struct gameState));

        // Draw Baron card to player's hand
        testG.hand[thisPlayer][testG.handCount[thisPlayer]] = baron;
        testG.handCount[thisPlayer]++;

        cardEffect(baron, choice1, 0, 0, &testG, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

        m = countEstate(thisPlayer, &G);
        n = countEstate(thisPlayer, &testG);
        if (choice1 == 0 || m == 0) {
            if (testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] + 1) {
                printf("Pass %d: discardCount doesn't match\n", i + 1);
                testPassed = 0;
            }
            if (testG.supplyCount[estate] != G.supplyCount[estate] - 1) {
                printf("Pass %d: supplyCount doesn't match\n", i + 1);
                testPassed = 0;
            }
        } else {
            if (n != m - 1) {
                printf("Pass %d: estate count doesn't match\n", i + 1);
                testPassed = 0;
            }
            if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] - 1) {
                printf("Pass %d: handCount doesn't match\n", i + 1);
                testPassed = 0;
            }
            if (testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] + 1) {
                printf("Pass %d: discardCount doesn't match\n", i + 1);
                testPassed = 0;
            }
            if (testG.coins != G.coins + 4) {
                printf("Pass %d: coins don't match\n", i + 1);
                testPassed = 0;
            }
        }

        score += testPassed;
    }

    printf("Passed %d out of %d tests.\n\n", score, NUM_TEST);

    return 0;
}