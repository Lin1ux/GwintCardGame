#include <vector>
#include "Card.h"

#pragma once
class PlayerInfo
{
private:
	int Points;						//Punkty
	int RoundsWon;					//Wygrane rundy
	std::vector<Card> MeleeRow;		//Karty w 1 rz�dzie (walka wr�cz)
	std::vector<Card> RangeRow;		//Karty w 2 rz�dzie (dystansowy
	std::vector<Card> PlayerHand;	//Karty w r�ce gracza
	std::vector<Card> CardStack;	//Nie dobrane karty
	std::vector<Card> CardUsed;		//Karty odrzcuone
public:
	PlayerInfo();								
	PlayerInfo(std::vector<Card> DeckCards);	//Konstruktor, Dobiera karty do r�ki i nie dobrane karty
	int CountPoints();							//Zlicza punkty z obu rz�d�w
	int ReturnRoundsWon();						//Zwraca liczb� wygranych rund
	void RoundWon();							//Zwi�ksza liczb� wygranych rund o 1
	void EndRound();							//Czy�ci st� i wrzuca usuni�te karty do stosu odrzuconych
	void TakeCard();							//Je�li jest miejsce dobiera kart� do r�ki
	void TakeCard(Card NewCard);				//Je�li jest miejsce dodaje podan� kart� do r�ki
	void PutToStack(Card NewCard);				//Wrzuca kart� do tali nie dobranych kart
	void DrawHand();							//Rysuje karty z r�ki gracza
	Card UseCard(int index);					//Usuwa kart� z r�ki i zwraca j�
	std::vector<Card> ReturnMeleeRow();			//Zwraca karty w 1 rz�dzie
	std::vector<Card> ReturnRangeRow();			//Zwraca karty w 2 rz�dzie
	std::vector<Card> ReturnPlayerHand();		//Zwraca karty z r�ki gracza
	std::vector<Card> ReturnCardStack();		//Zwraca nie u�yte karty
	int ReturnAmountOfCardStack();				//Zwraca liczb� nie u�ytych kart
	std::vector<Card> ReturnCardUsed();			//Zwraca odrzucone karty
	int ReturnAmountOfCardUsed();				//Zwraca liczb� kart zu�ytych

};

