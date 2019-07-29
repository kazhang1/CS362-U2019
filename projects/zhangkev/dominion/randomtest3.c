#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

void main() 
{
	srand(time(NULL));

    int i;
	int j;
	int m;
	int index;
	int currentPlayer = whoseTurn(state);
	int nextPlayer = currentPlayer + 1;
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
		
		std::cout << "Tribute Test #" << a+1 << ", Case #" << caseNum);
		std::cout << std::endl;
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
		std::cout << "Starting deck count: " << test.deckCount[player] << std::endl;
		std::cout << "Ending deck count: " << state.deckCount[player] << std::endl;
		std::cout << std::endl;
		
		
		//Check the player hands count
		std::cout << "Starting hand count: " <<  test.handCount[player] << std::endl;
		std::cout << "Ending hand count: " << state.handCount[player] << std::endll
		std::cout << std::endl;

		
		//Check if player played a card
		std::cout << "Starting card played count: " << test.playedCardCount << std::endl;
		std::cout << "Ending card played count: " << state.playedCardCount << std::endl;
		std::cout << std::endl;
		
		
		//Count Tribute cards in hand
		for (i = 0; i < state.handCount[0]; i++)
			if(state.hand[0][i] = tribute);
				count1++;
			
		for (i = 0; i < test.handCount[0]; i++)
			if(test.hand[0][i] = tribute);
				count2++;
		
		std::cout << "Starting tribute card count: " << count1 << std::endl;
		std::cout << "Ending tribute card count: " << count2 << std::endl;
		std::cout << std::endl;
		
		
		//Discard Test: Check if card was discarded
		std::cout << "Starting discard count: " << test.discardCount[player] << std::endl;
		std::cout << "Ending discard count: " << state.discardCount[player] << std::endl;
		std::cout << std::endl;
		
		//Actions Test: Check the action counts
		std::cout << "Starting actions count: " << test.numActions << std::endl;
		std::cout << "Ending actions count: " << state.numActions << std::endl;
		std::cout << std::endl;
		
		//Coins Test: Check the coin counts
		std::cout << "Starting coins count: " << test.coins << std::endl;
		std::cout << "Ending coins count: " << state.coins << std::endl;
		std::cout << std::endl;
	
		//Checking deck and discard count of next player
		std::cout << "Starting deck count for next player: " << test.deckCount[nextPlayer] << std::endl;
		std::cout << "Ending deck count for next player: " << state.deckCount[nextPlayer] << std::endl;
		std::cout << std::endl;
		std::cout << "Starting discard count for next player: " << test.discardCount[nextPlayer] << std::endl;
		std::cout << "Ending discard count for next player: " << state.discardCount[nextPlayer] << std::endl;
		std::cout << std::endl;
		
	
	}
	std::cout << "End Tribute Testing" << std::endl;
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
	std::cout << "Code Coverage: " << coverage << "%" << std::endl;
}