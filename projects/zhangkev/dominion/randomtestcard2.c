#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void main() 
{
	srand(time(NULL));

	int a;
    int i;
	int j;
	int m;
	int index;
	int tributeRevealedCards[2] = {-1, -1};
	int temphand[MAX_HAND];
	int drawntreasure=0;
	int cardDrawn;
	int z = 0;// this is the counter for the temp hand
    int handpos = 0;
	
	int bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int player=0;
	struct gameState state;
	struct gameState test;
	int currentPlayer = whoseTurn(&state);
	int nextPlayer = currentPlayer + 1;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, ambassador, cutpurse,
		   tribute, baron };
	int count1 = 0;
	int count2 = 0;
	double coverage = 0;
	bool case1 = false; // decided to take the coins, at least one other player has 5 or more cards
	bool case2 = false; // decided to take the coins, no other player has 5 or more cards
	bool case3 = false; // decided not take the coins, at least one other player has 5 or more cards
	bool case4 = false; // decided not take the coins, no other player has 5 or more cards
	int caseNum;
	
	
	// Determining what part of the minion code is covered is governed by 2 different conditions
	// Whether or not the player has decided to take the coins or to discard their hand
	// Whether or not any other players have 5 or more cards in their hands or not
	
	for(a = 0; a < 50; a++)
	{
		struct gameState newstate;
		state = newstate;
		bool handFive = false;
		int choice1 = 0;
		int choice2 = 0;
		int choice3 = 0;
		int numPlayers = rand() % 3 + 2;
		int seed = rand() % 5000;
		int rand1 = rand() % 2;
		int rand2 = rand() % 11;
		
		if (rand1 == 0)
			choice1 = 1;
		else
			choice2 = 1;

		if (rand2 >= 5)
			handFive = true;

		if (choice1 == 1)
		{
			if (handFive)
			{
				case1 = true;
				caseNum = 1;
			} else {
				case2 = true;
				caseNum = 2;
			}
		} else {
			if (handFive)
			{
				case3 = true;
				caseNum = 3;
			} else {
				case4 = true;
				caseNum = 4;
			}
		}
		
		printf("Minion Test #%d, Case #%d", a+1, caseNum);
		printf("\n");
		// copy the game state to a test case
		initializeGame(numPlayers, k, seed, &state);

		for (i = 1; i < numPlayers; i++)
		{
			state.handCount[i] = rand2;
		}
		
		memcpy(&test, &state, sizeof(struct gameState));
		cardEffect(minion, choice1, choice2, choice3, &state, handpos, &bonus);

		player = whoseTurn(&test);
		
		/*
		//Deck Count
		printf("Starting deck count: %d \n", test.deckCount[player]);
		printf("Ending deck count: %d \n", state.deckCount[player]);
		printf("\n");
		
		
		//Check the player hands count
		printf("Starting hand count: %d \n", test.handCount[player]);
		printf("Ending hand count: %d \n", state.handCount[player]);
		printf("\n");

		
		//Check if player played a card
		printf("Starting card played count: %d \n", test.playedCardCount);
		printf("Ending card played count: %d \n", state.playedCardCount);
		printf("\n");
		
		count1 = 0;
		count2 = 0;
		//Count Minion cards in hand
		for (i = 0; i < test.handCount[0]; i++)
			if(test.hand[0][i] = minion);
				count1++;
			
		for (i = 0; i < state.handCount[0]; i++)
			if(state.hand[0][i] = minion);
				count2++;
		
		printf("Starting minion card count: %d \n",  count1);
		printf("Ending minion card count: %d \n", count2);
		printf("\n");
		
		//Discard Test: Check if card was discarded
		printf("Starting discard count: %d \n", test.discardCount[player]);
		printf("Ending discard count: %d \n", state.discardCount[player]);
		printf("\n");
		
		//Actions Test: Check the action counts
		printf("Starting actions count: %d \n", test.numActions);
		printf("Ending actions count: %d \n", state.numActions);
		printf("\n");
		
		//Coins Test: Check the coin counts
		printf("Starting coins count: %d \n", test.coins);
		printf("Ending coins count: %d \n", state.coins);
		printf("\n");
		
		//Check hand and discard counts of other players
		for (i = 1; i < numPlayers; i++) {
			printf("Starting hand count for player %d : %d\n", i+1, test.handCount[i]);
			printf("Ending hand count for player %d : %d\n", i+1, state.handCount[i]);
			printf("Starting discard count for player %d : %d\n", i+1, test.discardCount[i]);
			printf("Ending discard count for player %d : %d\n", i+1, state.discardCount[i]);
			printf("\n");
		}
			*/
	
	}
	printf("End Minion Testing\n");
	if (case1)
		coverage++;
	if (case2)
		coverage++;
	if (case3)
		coverage++;
	if (case4)
		coverage++;
	coverage = coverage * 100 / 4;
	printf("Code Coverage: %lf% \n", coverage);
}