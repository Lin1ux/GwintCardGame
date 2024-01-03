#include "DeckManager.h"

DeckManager::DeckManager()
{
	maxCost = 0;
	CurrentCost = 0;
	gold = 0;
	amountOfCards = 0;
	minAmountOfCards = 0;
	Deck = std::vector<Card>();
}

//Konstruktor
//-----------------------------------------------
DeckManager::DeckManager(int MaxGold, int MaxCard)
{
	maxCost = MaxGold;
	CurrentCost = 0;
	gold = MaxGold;
	amountOfCards = 0;
	minAmountOfCards = MaxCard;
	Deck = std::vector<Card>();
}
//Sprawdza czy może dodać kartę
//------------------------------------
bool DeckManager::CanAddCard(Card Card)
{
	if (Card.ReturnCost() <= gold)
	{
		return true;
	}
	return false;
}

//Czy można wystartować grę
//------------------------------
bool DeckManager::CanStartGame()
{
	if (ReturnAmountOfCards() < minAmountOfCards)
	{
		return false;
	}
	return true;
}

//Dodaje kartę do talii
//-------------------------------------
void DeckManager::AddCard(Card newCard)
{
	if (CanAddCard(newCard))
	{
		amountOfCards += 1;
		gold -= newCard.ReturnCost();
		CurrentCost += newCard.ReturnCost();
		Deck.push_back(newCard);
	}
}
//Usuwa kartę z tali. zwraca usuniętą kartę
//------------------------------------------
Card DeckManager::RemoveCard(int CardId)
{
	Card RemovedCard = ReturnCardById(CardId);
	amountOfCards -= 1;
	gold += RemovedCard.ReturnCost();
	CurrentCost -= RemovedCard.ReturnCost();
	Deck.erase(Deck.begin() + CardId);
	return RemovedCard;
}
//Zwraca całą talię
//-----------------------------------------
std::vector<Card> DeckManager::ReturnDeck()
{
	return Deck;
}

//Zwraca kartę o podanym Id
//--------------------------------------
Card DeckManager::ReturnCardById(int Id)
{
	if (Id < Deck.size())
	{
		return Deck[Id];
	}
	return Card();
}
//Zwraca zformatowane dane o dostępnym złocie
//-----------------------------------
std::string DeckManager::GoldText()
{
	std::string text = "";
	text += std::to_string(CurrentCost) + "/" + std::to_string(maxCost);
	return text;
}
//Zwraca liczbę kart w talii
//------------------------------------
int DeckManager::ReturnAmountOfCards()
{
	return amountOfCards;
}
