#include <vector>
#include "Card.h"
#include "CardList.h"

#pragma once
class CardsToSelect
{
private:
	std::vector<Card> AvaliableCards;
	std::vector<int> CardsLeft;
public:
	CardsToSelect();
	CardsToSelect(std::vector<Card> Cards);
	void SetCard(std::vector<Card> Cards, int DeckSize);
	Card SelectCardById(int Id);
	int CardsLeftById(int Id);
	Card TakeCard(int Id, int value);
	int ReturnIdOfCard(Card Card);
	int AmountOfCards();
};

