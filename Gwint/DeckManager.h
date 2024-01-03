#include "Card.h"
#include "OtherFunctions.h"
#include "settings.h"
#include <vector>

#pragma once
class DeckManager
{
private:
	int maxCost;
	int CurrentCost;
	int gold;
	int amountOfCards;
	int minAmountOfCards;
	std::vector<Card> Deck;
public:
	DeckManager();
	DeckManager(int MaxGold, int MaxCard);
	bool CanAddCard(Card Card);
	bool CanStartGame();
	void AddCard(Card newCard);
	Card RemoveCard(int CardId);
	std::vector<Card> ReturnDeck();
	Card ReturnCardById(int Id);
	std::string GoldText();
	int ReturnAmountOfCards();

};

