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
	int k[10] = {minion, minion, minion, minion, minion, minion, minion, minion, minion, minion};
	int count1 = 0;
	int count2 = 0;
	double coverage = 0;
	bool case1; // decided to take the coins, at least one other player has 5 or more cards
	bool case2; // decided to take the coins, no other player has 5 or more cards
	bool case3; // decided not take the coins, at least one other player has 5 or more cards
	bool case4; // decided not take the coins, no other player has 5 or more cards
	int caseNum;
	bool handFive;
	
	// Determining what part of the minion code is covered is governed by 2 different conditions
	// Whether or not the player has decided to take the coins or to discard their hand
	// Whether or not any other players have 5 or more cards in their hands or not
	
	for(a = 0; a < 50; a++)
	{
		int numPlayers = rand() % 7 + 2;
		int seed = rand() % 5000;
		int rand1 = rand() % 2;
		int rand2 = rand() % 11;
		
		if (rand1 == 0)
			choice1 = 1;
		else
			choice2 = 1;

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
		
		std::cout << "Minion Test #" << a+1 << ", Case #" << caseNum);
		std::cout << std::endl;
		// copy the game state to a test case
		initializeGame(numPlayers, k, seed, &state);

		for (i = 1; i < numPlayers; i++)
		{
			statehandCount[i] = rand2;
		}
		
		memcpy(&test, &state, sizeof(struct gameState));
		cardEffect(minion, choice1, choice2, choice3, &state, handpos, &bonus);

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
		
		
		//Count Minion cards in hand
		for (i = 0; i < state.handCount[0]; i++)
			if(state.hand[0][i] = minion);
				count1++;
			
		for (i = 0; i < test.handCount[0]; i++)
			if(test.hand[0][i] = minion);
				count2++;
		
		std::cout << "Starting minion card count: " << count1 << std::endl;
		std::cout << "Ending minion card count: " << count2 << std::endl;
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
		
		//Check hand and discard counts of other players
		for (i = 1; i < numPlayers; i++) {
			std::cout << "Starting hand count for player " << i+1 << ": " << test.handCount[i] << std::endl;
			std::cout << "Ending hand count for player " << i+1 << ": " << state.handCount[i] << std::endll
			std::cout << "Starting discard count for player " << i+1 << ": " << test.discardCount[i] << std::endl;
			std::cout << "Ending discard count for player " << i+1 << ": " << state.discardCount[i] << std::endl;
			std::cout << std::endl;
		}
			
	
	}
	std::cout << "End Minion Testing" << std::endl;
	if (case1)
		coverage++;
	if (case2)
		coverage++;
	if (case3)
		coverage++;
	if (case4)
		coverage++;
	coverage = coverage * 100 / 4;
	std::cout << "Code Coverage: " << coverage << "%" << std::endl;
}