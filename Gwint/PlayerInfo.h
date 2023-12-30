#include <vector>
#include "Card.h"

#pragma once
class PlayerInfo
{
private:
	int Points;						//Punkty
	int RoundsWon;					//Wygrane rundy
	std::vector<Card> MeleeRow;		//Karty w 1 rzêdzie (walka wrêcz)
	std::vector<Card> RangeRow;		//Karty w 2 rzêdzie (dystansowy
	std::vector<Card> PlayerHand;	//Karty w rêce gracza
	std::vector<Card> CardStack;	//Nie dobrane karty
	std::vector<Card> CardUsed;		//Karty odrzcuone
public:
	PlayerInfo();
	PlayerInfo(std::vector<Card> DeckCards);
	int CountPoints();
	int ReturnRoundsWon();
	void RoundWon();
	void EndRound();
	void TakeCard();
	void TakeCard(Card NewCard);
	void DrawHand();
	std::vector<Card> ReturnMeleeRow();
	std::vector<Card> ReturnRangeRow();
	std::vector<Card> ReturnPlayerHand();
	std::vector<Card> ReturnCardStack();
	int ReturnAmountOfCardStack();
	std::vector<Card> ReturnCardUsed();
	int ReturnAmountOfCardUsed();

};

