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
	bool CanAddCard(Card Card);				//Czy mo�na doda� kart�
	bool CanStartGame();					//Czy kart w talii jest wystarczaj�co aby zacz�� gre
	void AddCard(Card newCard);				//Dodaje kart� do tali
	Card RemoveCard(int CardId);			//Usuwa wybran� kart� z tali
	Card PopCard();							//Usuwa i zwraca ostatni� kart� w talii
	std::vector<Card> ReturnDeck();			//Zwraca tali� kart
	Card ReturnCardById(int Id);			//Zwraca kart� o podanym id
	std::string GoldText();					//Zwraca zformatowane dane o dost�pnym z�ocie
	int ReturnAmountOfCards();				//Zwraca liczb� kart w talii

};

