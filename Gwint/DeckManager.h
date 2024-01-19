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
	DeckManager();							//Konstruktor
	DeckManager(int MaxGold, int MaxCard);	//Konstruktor
	bool CanAddCard(Card Card);				//Czy mo¿na dodaæ kartê
	bool CanStartGame();					//Czy kart w talii jest wystarczaj¹co aby zacz¹æ gre
	void AddCard(Card newCard);				//Dodaje kartê do tali
	Card RemoveCard(int CardId);			//Usuwa wybran¹ kartê z tali
	Card PopCard();							//Usuwa i zwraca ostatni¹ kartê w talii
	std::vector<Card> ReturnDeck();			//Zwraca taliê kart
	Card ReturnCardById(int Id);			//Zwraca kartê o podanym id
	std::string GoldText();					//Zwraca zformatowane dane o dostêpnym z³ocie
	int ReturnAmountOfCards();				//Zwraca liczbê kart w talii

};

