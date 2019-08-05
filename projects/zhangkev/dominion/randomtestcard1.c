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
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
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
	bool case1 = false; // decided not to discard, has estate cards, more than 1 estate card in supply
	bool case2 = false; // decided not to discard, has estate cards, only 1 estate card in supply
	bool case3 = false; // decided not to discard, has no estate cards, more than 1 estate card in supply
	bool case4 = false; // decided not to discard, has no estate cards, only 1 estate card in supply
	bool case5 = false; // decided to discard, has estate cards, more than 1 estate card in supply
	bool case6 = false; // decided to discard, has estate cards, only 1 estate card in supply
	bool case7 = false; // decided to discard, has no estate cards, more than 1 estate card in supply
	bool case8 = false; // decided to discard, has no estate cards, only 1 estate card in supply
	int caseNum;
	
	// Determining what part of the baron code is covered is governed by 3 different conditions
	// Whether or not the player has decided to discard an estate card
	// Whether or not the player has any estate cards in their hand
	// Whether or not, in the event that the card draws an estate card, if the estate supply is empty afterwards
	// Altogether there are a total of 8 possible permutations of these conditions that can be tested which denotes the code coverage
	
	for(a = 0; a < 20; a++)
	{
		struct gameState newstate;
		state = newstate;
		bool hasEstate = false;
		int numPlayers = rand() % 3 + 2;
		int seed = rand() % 5000;
		int rand1 = rand() % 2;
		int rand2 = rand() % 2;
		int rand3 = rand() % 3 + 1;

		if (rand1 > 0)
			hasEstate = true;

		if (rand2 == 0)
			choice1 = 1;
		else
			choice1 = 0;

		if (choice1 == 0)
		{
			if (hasEstate)
			{
				if (rand3 > 1)
				{
					case1 = true;
					caseNum = 1;
				} else {
					case2 = true;
					caseNum = 2;
				}
			} else {
				if (rand3 > 1)
				{
					case3 = true;
					caseNum = 3;
				} else {
					case4 = true;
					caseNum = 4;
				}
			}
		} else {
			if (hasEstate)
			{
				if (rand3 > 1)
				{
					case5 = true;
					caseNum = 5;
				} else {
					case6 = true;
					caseNum = 6;
				}
			} else {
				if (rand3 > 1)
				{
					case7 = true;
					caseNum = 7;
				} else {
					case8 = true;
					caseNum = 8;
				}
			}
		}
		
		printf("Baron Test #%d, Case #%d", a+1, caseNum);
		printf("\n");
		// copy the game state to a test case
		initializeGame(numPlayers, k, seed, &state);


		for (i = 0; i < 5; i++) {
			state.hand[0][i] = copper;
		}
		if (rand1 > 0){
			int rand4 = rand() % 5;
			state.hand[0][rand4] = estate;
		}
	

		memcpy(&test, &state, sizeof(struct gameState));
		cardEffect(baron, choice1, choice2, choice3, &state, handpos, &bonus);

		player = 0;
		
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
		
		
		//Count Baron cards in hand
		count1 = 0;
		count2 = 0;
		for (i = 0; i < test.handCount[0]; i++)
			if(test.hand[0][i] = baron);
				count1++;
			
		for (i = 0; i < state.handCount[0]; i++)
			if(state.hand[0][i] = baron);
				count2++;
		
		printf("Starting baron card count: %d \n", count1);
		printf("Ending baron card count: %d \n", count2);
		printf("\n");

		//Count Estate cards in hand
		count1 = 0;
		count2 = 0;
		for (i = 0; i < test.handCount[0]; i++)
			if (test.hand[0][i] = estate);
				count1++;

		for (i = 0; i < state.handCount[0]; i++)
			if (state.hand[0][i] = estate);
				count2++;

		printf("Starting estate card count: %d \n", count1);
		printf("Ending estate card count: %d \n", count2);
		printf("\n");
		
		
		//Discard Test: Check if card was discarded
		printf("Starting discard count: %d \n", test.discardCount[player]);
		printf("Ending discard count: %d \n", state.discardCount[player]);
		printf("\n");

		//Actions Test: Check the coin counts
		printf("Starting actions count: %d \n", test.numActions);
		printf("Ending actions count: %d \n", state.numActions);
		printf("\n");
		
		//Buys Test: Check if the +1 Buys was added
		printf("Starting buys count: %d \n", test.numBuys);
		printf("Ending buys count: %d \n", state.numBuys);
		printf("\n");
		
		//Coins Test: Check the coin counts
		printf("Starting coins count: %d \n", test.coins);
		printf("Ending coins count: %d \n", state.coins);
		printf("\n");
		
		//Estate Test: Check the estate supply counts
		printf("Starting estate supply count: %d \n", test.supplyCount[estate]);
		printf("Ending estate supply count: %d \n", state.supplyCount[estate]);
		printf("\n");
		
		//Gameover Test: Check to see if it's Game Over
		printf("Game Over state is %d (1 is yes, 0 is no)\n", isGameOver(&state));
		printf("\n");
		*/
		
	
	}
	printf("End Baron Testing\n");
	if (case1)
		coverage++;
	if (case2)
		coverage++;
	if (case3)
		coverage++;
	if (case4)
		coverage++;
	if (case5)
		coverage++;
	if (case6)
		coverage++;
	if (case7)
		coverage++;
	if (case8)
		coverage++;
	coverage = coverage * 100 / 8;
	printf("Code Coverage: %lf\n", coverage);
}