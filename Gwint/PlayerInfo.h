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
	PlayerInfo(std::vector<Card> DeckCards);	//Konstruktor, Dobiera karty do rêki i nie dobrane karty
	int CountPoints();							//Zlicza punkty z obu rzêdów
	int ReturnRoundsWon();						//Zwraca liczbê wygranych rund
	void RoundWon();							//Zwiêksza liczbê wygranych rund o 1
	void EndRound();							//Czyœci stó³ i wrzuca usuniête karty do stosu odrzuconych
	void TakeCard();							//Jeœli jest miejsce dobiera kartê do rêki
	void TakeCard(Card NewCard);				//Jeœli jest miejsce dodaje podan¹ kartê do rêki
	void PutToStack(Card NewCard);				//Wrzuca kartê do tali nie dobranych kart
	void DrawHand();							//Rysuje karty z rêki gracza
	Card UseCard(int index);					//Usuwa kartê z rêki i zwraca j¹
	std::vector<Card> ReturnMeleeRow();			//Zwraca karty w 1 rzêdzie
	std::vector<Card> ReturnRangeRow();			//Zwraca karty w 2 rzêdzie
	std::vector<Card> ReturnPlayerHand();		//Zwraca karty z rêki gracza
	std::vector<Card> ReturnCardStack();		//Zwraca nie u¿yte karty
	int ReturnAmountOfCardStack();				//Zwraca liczbê nie u¿ytych kart
	std::vector<Card> ReturnCardUsed();			//Zwraca odrzucone karty
	int ReturnAmountOfCardUsed();				//Zwraca liczbê kart zu¿ytych

};

