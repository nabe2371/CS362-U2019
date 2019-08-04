/********************************************************************
* Author: Ivan Timothy Halim                                        *
* Date: 07/14/2019                                                  *
* Description: unittest3.c implements a unit test of the function   *
*              updateCoins() for dominion.c.                        *
*********************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FUNC_TEST "updateCoins"

//unit test 1 tests existance of Copper, Silver and Gold Coins 
int main (int argc, char** argv)	{
	int i;
    int failedTests = 0;
    int numTests = 0;

    struct gameState G;
    int thisPlayer = 0;
	G.coins = 0;
    int bonus = 2;
	
	printf("Testing %s():\n", FUNC_TEST);
	
    // Test for copper
	printf("Copper Test:\n");
    for (i = 0; i < 10; i++) {
        G.hand[thisPlayer][i] = copper;
    }
    G.handCount[thisPlayer] = 10;
	updateCoins(thisPlayer, &G, 0);
	printf("We should have 10 copper coins: %d\n", G.coins);
	if (G.coins == 10) {
		printf("Test passed. Correct number of coins.\n\n");
        numTests++;
    } else {
		printf("Test failed. Incorrect number of coins.\n\n");
        failedTests++;
        numTests++;
    }
	
    // Test for silver
	printf("Silver Test:\n");
	for (i = 0; i < 10; i++) {
        G.hand[thisPlayer][i] = silver;
    }
    G.handCount[thisPlayer] = 10;
	updateCoins(thisPlayer, &G, 0);
	printf("We should have 10 silver coins: %d\n", G.coins);
	if (G.coins == 20) {
		printf("Test passed. Correct number of coins.\n\n");
        numTests++;
    } else {
		printf("Test failed. Incorrect number of coins.\n\n");
        failedTests++;
        numTests++;
    }
	
    // Test for gold
	printf("Gold Test:\n");
	for (i = 0; i < 10; i++) {
        G.hand[thisPlayer][i] = gold;
    }
    G.handCount[thisPlayer] = 10;
	updateCoins(thisPlayer, &G, 0);
	printf("We should have 10 gold coins: %d\n", G.coins);
	if (G.coins == 30) {
		printf("Test passed. Correct number of coins.\n\n");
        numTests++;
    } else {
		printf("Test failed. Incorrect number of coins.\n\n");
        failedTests++;
        numTests++;
    }
	
	// Test for no coins
	printf("No Coins Test:\n");
	for (i = 0; i < 10; i++) {
        G.hand[thisPlayer][i] = adventurer;
    }
    G.handCount[thisPlayer] = 10;
	updateCoins(thisPlayer, &G, 0);
	printf("We should have 0 coins: %d\n", G.coins);
	if (G.coins == 0) {
		printf("Test passed. Correct number of coins.\n\n");
        numTests++;
    } else {
		printf("Test failed. Incorrect number of coins.\n\n");
        failedTests++;
        numTests++;
    }

    // Test for bonus
    printf("Bonus Test:\n");
	updateCoins(thisPlayer, &G, bonus);
	printf("We should have 0 coins and +2 bonus: %d\n", G.coins);
	if (G.coins == 0 + bonus) {
		printf("Test passed. Correct number of coins.\n\n");
        numTests++;
    } else {
		printf("Test failed. Incorrect number of coins.\n\n");
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