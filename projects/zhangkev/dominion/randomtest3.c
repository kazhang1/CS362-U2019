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
	int k[10] = {tribute, tribute, tribute, tribute, tribute, tribute, tribute, tribute, tribute, tribute};
	int count1 = 0;
	int count2 = 0;
	double coverage = 0;
	bool case1; // Only 1 card in the deck and 0 in the discard
	bool case2; // 0 cards in the deck and 1 in the discard
	bool case3; // no cards at all in deck or discard
	bool case4; // 0 cards in the deck and 2 or more in the discard
	bool case5; // 2 or more cards in the deck
	bool case6; // treasure card revealed
	bool case7; // victory card revealed
	bool case8; // action card revealed
	bool case9; // the two cards are duplicates
	int caseNum;
	
	// The tribute code has two distinct sections
	// Section 1 covers how to get the cards in different circumstances
	// Only 1 card in the deck and 0 in the discard
	// 0 cards in the deck and 1 in the discard
	// no cards at all in deck or discard
	// 0 cards in the deck and 2 or more in the discard
	// 2 or more cards in the deck
	//
	// Section 2 covers how to deal with each card type
	// If the cards are duplicates one is dropped
	// Different action taken for each type of card: treasure, victory, and action
	
	for(a = 0; a < 50; a++)
	{
		int numPlayers = rand() % 7 + 2;
		int seed = rand() % 5000;
		int rand1;
		int rand2 = rand() % 5;
		int cards[2] = {-1, -1};
		
		for (i = 1; i < 3; i++)
		{
			rand1 = rand() % 9;
			switch( rand1 ) 
			{
				case 0:
					cards[i] = copper;
					case6 = true;
				case 1:
					cards[i] = silver;
					case6 = true;
				case 2:
					cards[i] = gold;
					case6 = true;
				case 3:
					cards[i] = estate;
					case7 = true;
				case 4:
					cards[i] = duchy;
					case7 = true;
				case 5:
					cards[i] = province;
					case7 = true;
				case 6:
					cards[i] = baron;
					case8 = true;
				case 7:
					cards[i] = minion;
					case8 = true;
				case 8:
					cards[i] = tribute;
					case8 = true;
			}
		}
		
		if (cards[1] == cards[2])
			case9 = true;
		
		switch( rand2 )
		{
		case 0:
			case1 = true;
			caseNum = 1;
		case 1:
			case2 = true;
			caseNum = 2;
		case 2:
			case3 = true;
			caseNum = 3;
		case 3:
			case4 = true;
			caseNum = 4;
		case 4:
			case5 = true;
			caseNum = 5;
		}
		
		printf("Tribute Test #%d, Case #%d", a+1, caseNum);
		printf("\n");
		// copy the game state to a test case
		initializeGame(numPlayers, k, seed, &state);

		switch( rand2 )
		{
		case 0:
			state.deckCount[nextPlayer] = 1;
			state.discardCount[nextPlayer] = 0;
			state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = cards[0];
		case 1:
			state.deckCount[nextPlayer] = 0;
			state.discardCount[nextPlayer] = 1;
			state.discard[nextPlayer][state.discardCount[nextPlayer]-1] = cards[0];
		case 2:
			state.deckCount[nextPlayer] = 0;
			state.discardCount[nextPlayer] = 0;
		case 3:
			state.deckCount[nextPlayer] = 0;
			state.discardCount[nextPlayer] = 2;
			state.discard[nextPlayer][0] = cards[0];
			state.discard[nextPlayer][1] = cards[1];
		case 4:
			state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = cards[0];
			state.deck[nextPlayer][state.deckCount[nextPlayer]-2] = cards[1];
		}
		
		memcpy(&test, &state, sizeof(struct gameState));
		cardEffect(tribute, choice1, choice2, choice3, &state, handpos, &bonus);

		player = whoseTurn(&test);
		
		
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
		
		
		//Count Tribute cards in hand
		for (i = 0; i < state.handCount[0]; i++)
			if(state.hand[0][i] = tribute);
				count1++;
			
		for (i = 0; i < test.handCount[0]; i++)
			if(test.hand[0][i] = tribute);
				count2++;
		
		printf("Starting tribute card count: %d \n", count1);
		printf("Ending tribute card count: %d \n", count2);
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
	
		//Checking deck and discard count of next player
		printf("Starting deck count for next player: %d \n", test.deckCount[nextPlayer]);
		printf("Ending deck count for next player: %d \n", state.deckCount[nextPlayer]);
		printf("\n");
		printf("Starting discard count for next player: %d \n", test.discardCount[nextPlayer]);
		printf("Ending discard count for next player: %d \n", state.discardCount[nextPlayer]);
		printf("\n");
		
	
	}
	printf("End Tribute Testing\n");
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
	if (case9)
		coverage++;
	coverage = coverage * 100 / 9;
	printf("Code Coverage: %lf% \n", coverage);
}