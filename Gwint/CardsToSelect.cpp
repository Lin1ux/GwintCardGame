#include "CardsToSelect.h"

CardsToSelect::CardsToSelect()
{
	std::vector<Card> Cards = CardList::ReturnAllCards();
	for (int i = 0; i < Cards.size(); i++)
	{
		AvaliableCards.push_back(Cards[i]);
		if (AvaliableCards[i].ReturnIsHero())
		{
			CardsLeft.push_back(1);
		}
		else
		{
			CardsLeft.push_back(3);
		}
	}
}

//Konstruktor
//--------------------------------------------------
CardsToSelect::CardsToSelect(std::vector<Card> Cards)
{
	for (int i = 0; i < Cards.size(); i++)
	{
		AvaliableCards.push_back(Cards[i]);
		if (AvaliableCards[i].ReturnIsHero())
		{
			CardsLeft.push_back(1);
		}
		else
		{
			CardsLeft.push_back(3);
		}
	}
}
//Ustawia nowe karty
//--------------------------------------------------
void CardsToSelect::SetCard(std::vector<Card> Cards, int DeckSize)
{
	if (DeckSize == 0)
	{
		CardsLeft.clear();
		AvaliableCards.clear();
		for (int i = 0; i < Cards.size(); i++)
		{
			AvaliableCards.push_back(Cards[i]);
			if (AvaliableCards[i].ReturnIsHero())
			{
				CardsLeft.push_back(1);
			}
			else
			{
				CardsLeft.push_back(3);
			}
		}
	}
}
//Zwraca kartę o podanym id
//----------------------------------------
Card CardsToSelect::SelectCardById(int Id)
{
	if (Id < AvaliableCards.size())
	{
		return AvaliableCards[Id];
	}
	return Card();
}
//Zwraca ilość pozostałych kart o podanym id
//------------------------------------------
int CardsToSelect::CardsLeftById(int Id)
{
	if (Id < CardsLeft.size())
	{
		return CardsLeft[Id];
	}
	return -1;
}
//Zwraca kartę i zmienia liczbę kart
Card CardsToSelect::TakeCard(int Id, int value)
{
	Card card = SelectCardById(Id);
	CardsLeft[Id] += value;
	if (CardsLeft[Id] < 0)
	{
		CardsLeft[Id] = 0;
	}
	if (card.ReturnIsHero() && CardsLeft[Id] > 1)
	{
		CardsLeft[Id] = 1;
	}
	else if(!card.ReturnIsHero() && CardsLeft[Id] > 3)
	{
		CardsLeft[Id] = 3;
	}
	return card;
}
//Zwraca pozycje podanej karty
int CardsToSelect::ReturnIdOfCard(Card Card)
{
	int id = -1;
	for (int i = 0; i < AmountOfCards(); i++)
	{
		if (SelectCardById(i) == Card)
		{
			id = i;
			break;
		}
	}
	return id;
}
//Zwraca liczbę typów kart
//--------------------------------
int CardsToSelect::AmountOfCards()
{
	return AvaliableCards.size();
}
