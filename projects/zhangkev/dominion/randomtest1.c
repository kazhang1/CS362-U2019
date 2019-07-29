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
	int k[10] = {baron, baron, baron, baron, baron, baron, baron, baron, baron, baron};
	int count1 = 0;
	int count2 = 0;
	double coverage = 0;
	bool case1; // decided not to discard, has estate cards, more than 1 estate card in supply
	bool case2; // decided not to discard, has estate cards, only 1 estate card in supply
	bool case3; // decided not to discard, has no estate cards, more than 1 estate card in supply
	bool case4; // decided not to discard, has no estate cards, only 1 estate card in supply
	bool case5; // decided to discard, has estate cards, more than 1 estate card in supply
	bool case6; // decided to discard, has estate cards, only 1 estate card in supply
	bool case7; // decided to discard, has no estate cards, more than 1 estate card in supply
	bool case8; // decided to discard, has no estate cards, only 1 estate card in supply
	int caseNum;
	bool hasEstate;
	
	// Determining what part of the baron code is covered is governed by 3 different conditions
	// Whether or not the player has decided to discard an estate card
	// Whether or not the player has any estate cards in their hand
	// Whether or not, in the event that the card draws an estate card, if the estate supply is empty afterwards
	// Altogether there are a total of 8 possible permutations of these conditions that can be tested which denotes the code coverage
	
	for(a = 0; a < 50; a++)
	{
		int numPlayers = rand() % 7 + 2;
		int seed = rand() % 5000;
		int rand1;
		int rand2 = rand() % 2;
		int rand3 = rand() % 3 + 1;
		
		for (i = 1; i < 10; i++)
		{
			rand1 = rand() % 10;
			switch( rand1 ) 
			{
				case 0:
					k[i] = curse;
				case 1:
					k[i] = estate;
					hasEstate = true;
				case 2:
					k[i] = duchy;
				case 3:
					k[i] = province;
				case 4:
					k[i] = copper;
				case 5:
					k[i] = silver;
				case 6:
					k[i] = gold;
				case 7:
					k[i] = adventurer;
				case 8:
					k[i] = council_room;
				case 9:
					k[i] = feast;
			}
		}
		
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
		
		std::cout << "Baron Test #" << a+1 << ", Case #" << caseNum);
		std::cout << std::endl;
		// copy the game state to a test case
		initializeGame(numPlayers, k, seed, &state);

		state.supplyCount[estate] = rand3;
		
		memcpy(&test, &state, sizeof(struct gameState));
		cardEffect(baron, choice1, choice2, choice3, &state, handpos, &bonus);

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
		
		
		//Count Baron cards in hand
		for (i = 0; i < state.handCount[0]; i++)
			if(state.hand[0][i] = baron);
				count1++;
			
		for (i = 0; i < test.handCount[0]; i++)
			if(test.hand[0][i] = baron);
				count2++;
		
		std::cout << "Starting baron card count: " << count1 << std::endl;
		std::cout << "Ending baron card count: " << count2 << std::endl;
		std::cout << std::endl;
		
		
		//Discard Test: Check if card was discarded
		std::cout << "Starting discard count: " << test.discardCount[player] << std::endl;
		std::cout << "Ending discard count: " << state.discardCount[player] << std::endl;
		std::cout << std::endl;
		
		//Buys Test: Check if the +1 Buys was added
		std::cout << "Starting buys count: " << test.numBuys << std::endl;
		std::cout << "Ending buys count: " << state.numBuys << std::endl;
		std::cout << std::endl;
		
		//Coins Test: Check the coin counts
		std::cout << "Starting coins count: " << test.coins << std::endl;
		std::cout << "Ending coins count: " << state.coins << std::endl;
		std::cout << std::endl;
		
		//Estate Test: Check the estate supply counts
		std::cout << "Starting estate supply count: " << test.supplyCount[estate] << std::endl;
		std::cout << "Ending estate supply count: " << state.supplyCount[estate] << std::endl;
		std::cout << std::endl;
		
		//Gameover Test: Check to see if it's Game Over
		std::cout << "Game Over state is " << isGameOver(state) << " (1 is yes, 0 is no)" << std::endl;
		std::cout << std::endl;
		
		
	
	}
	std::cout << "End Baron Testing" << std::endl;
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
	std::cout << "Code Coverage: " << coverage << "%" << std::endl;
}