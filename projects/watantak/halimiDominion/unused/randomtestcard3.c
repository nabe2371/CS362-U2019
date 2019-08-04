#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARD_TEST "Tribute"
#define NUM_TEST 50

void countCards(int player, struct gameState *state, int *actionCards, int *treasureCards, int *victoryCards) {
    *actionCards = 0;
    *treasureCards = 0;
    *victoryCards = 0;

    int prevCard = -1;
    int i;
    for (i = state->handCount[player] - 1; i > state->handCount[player] - 3; i--) {
        if (state->hand[player][i] != prevCard) {
            if (state->hand[player][i] == copper || state->hand[player][i] == silver || state->hand[player][i] == gold) {
                *treasureCards += 1;
            } else if (state->hand[player][i] == estate || state->hand[player][i] == duchy || state->hand[player][i] == province || state->hand[player][i] == gardens || state->hand[player][i] == great_hall) {
                *victoryCards += 1;
            } else {
                *actionCards += 1;
            }
        } else {
            break;
        }

        prevCard = state->hand[player][i];
    }
}

int main() {

    srand(time(NULL));

    // Variables to initialize game state
    int k[10] = {council_room, feast, gardens, mine, estate,
                 village, baron, great_hall, minion, tribute};
    struct gameState G, testG;
    int seed, numPlayers;
    int thisPlayer, nextPlayer;
    int actionCards, treasureCards, victoryCards;
    int testPassed;
    int score = 0;
    int i;

    printf("Testing %s card:\n", CARD_TEST);

    for (i = 0; i < NUM_TEST; i++) {
        seed       = rand() % 5000;
        numPlayers = rand() % 3 + 2;
        thisPlayer = rand() % numPlayers;
        nextPlayer = (thisPlayer + 1) % numPlayers;
        testPassed = 1;

        initializeGame(numPlayers, k, seed, &G);
        memcpy(&testG, &G, sizeof(struct gameState));

        // Draw Tribute card to player's hand
        testG.hand[thisPlayer][testG.handCount[thisPlayer]] = tribute;
        testG.handCount[thisPlayer]++;

        cardEffect(tribute, 0, 0, 0, &testG, testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);

        countCards(nextPlayer, &G, &actionCards, &treasureCards, &victoryCards);

        if (testG.numActions != G.numActions + 2*actionCards) {
            printf("Pass %d: numActions don't match.\n", i + 1);
            testPassed = 0;
        }
        if (testG.coins != G.coins + 2*treasureCards) {
            printf("Pass %d: coins don't match\n", i + 1);
            testPassed = 0;
        }
        if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 2*victoryCards) {
            printf("Pass %d: handCount doesn't match\n", i + 1);
            testPassed = 0;
        }
        if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 2*victoryCards) {
            printf("Pass %d: deckCount doesn't match\n", i + 1);
            testPassed = 0;
        }
        if (testG.deckCount[nextPlayer] != G.deckCount[nextPlayer] - 2) {
            printf("Pass %d: next player deckCount doesn't match\n", i + 1);
            testPassed = 0;
        }
        if (testG.discardCount[nextPlayer] != G.discardCount[nextPlayer] + 2) {
            printf("Pass %d: next player discardCount doesn't match\n", i + 1);
            testPassed = 0;
        }

        score += testPassed;
    }

    printf("Passed %d out of %d tests.\n\n", score, NUM_TEST);

    return 0;
}