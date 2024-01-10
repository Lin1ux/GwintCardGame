#include <vector>
#include "Card.h"

typedef struct CardPos
{
	Card card;  //Karta
	int index;  //Returned Index
}CardPos;

#pragma once
class PlayerInfo
{
private:
	bool RoundFinished;				//Czy sko�czono runde
	int Points;						//Punkty
	int RoundsWon;					//Wygrane rundy
	std::vector<Card> MeleeRow;		//Karty w 1 rz�dzie (walka wr�cz)
	std::vector<Card> RangeRow;		//Karty w 2 rz�dzie (dystansowy
	std::vector<Card> PlayerHand;	//Karty w r�ce gracza
	std::vector<Card> CardStack;	//Nie dobrane karty
	std::vector<Card> CardUsed;		//Karty odrzcuone

public:
	//Konstruktory
	PlayerInfo();
	PlayerInfo(std::vector<Card> DeckCards);							//Konstruktor, Dobiera karty do r�ki i nie dobrane karty
	//Koniec rundy
	bool IsFinishedRound();												//Czy zako�czono rund�
	void SetRoundFinished(bool newState);								//Zmienia warto�� ko�ca rundy
	//Punkty
	int ReturnMeleePoints();											//Zlicza punkty z 1 rz�du
	int ReturnRangePoints();											//Zlicza punkty z 2 rz�du
	int CountPoints();													//Zlicza punkty z obu rz�d�w
	int ReturnPoints();													//Zwraca punkty
	//Rundy
	int ReturnRoundsWon();												//Zwraca liczb� wygranych rund
	void RoundWon();													//Zwi�ksza liczb� wygranych rund o 1
	void EndRound();													//Czy�ci st� i wrzuca usuni�te karty do stosu odrzuconych
	//R�ka gracza
	void TakeCard();													//Je�li jest miejsce dobiera kart� do r�ki
	void TakeCard(Card NewCard);										//Je�li jest miejsce dodaje podan� kart� do r�ki
	void DrawHand();													//Rysuje karty z r�ki gracza
	int AmountOfCardsInHand();											//Zwraca liczb� kart w r�ce
	//Nie dobrane karty
	void PutToStack(Card NewCard);										//Wrzuca kart� do tali nie dobranych kart
	Card TakeCardFromStack();											//Dobiera kart� z nie u�ytych kart i zwraca j�
	Card UseStackCard(Card CardToRemove);								//Usuwa wybran� kart� z nie u�ytych kart i zwraca j�
	int ReturnAmountOfCardStack();										//Zwraca liczb� nie u�ytych kart
	//Zagranie karty
	bool CanPlay(Card NewCard);											//Sprawdza czy mo�na zagra� kart�
	void PlayCard(Card NewCard);										//Umieszcza kart� na st� do odpowiedniego rz�du
	Card UseCard(int index);											//Usuwa kart� o podanym indeksie z r�ki i zwraca j�
	Card UseCard(Card CardToUse);										//Usuwa podan� kart� je�li znajduje si� r�ce i zwraca j�
	//St�
	Card RemoveCardFromTable(Card CardToRemove);						//Usuwa pierwsz� znalezion� kart� 
	Card RemoveCardFromTable(int row, int index);						//Usuwa kart� z sto�u o podanym indeksie
	int ReturnAmountOfCardOnTable();									//Zwraca liczb� kart na stole
	int ReturnAmountOfCardOnTable(int row);								//Zwraca liczb� kart w wybranym rz�dzie
	int NumberOfCardsWithSkill(Skills Skill);							//Zwraca liczb� kart na stole posiadaj�ce dan� umiej�tno��
	int NumberOfSpecificCards(Card CardToFind);							//Zwraca liczb� podanych kart
	void SetMultiplayerOfCard(int row, int index, int value);			//Ustawia mno�nik karty o podanym indeksie i rz�dzie							
	//Cmentarz (U�yte karty)
	void AddCardToGraveyard(Card Card);									//Dodaje kart� do cmentarza
	int ReturnAmountOfCardUsed();										//Zwraca liczb� kart zu�ytych
	//Zwracanie kart
	std::vector<Card> ReturnMeleeRow();									//Zwraca karty w 1 rz�dzie
	std::vector<Card> ReturnRangeRow();									//Zwraca karty w 2 rz�dzie
	std::vector<Card> ReturnPlayerHand();								//Zwraca karty z r�ki gracza
	std::vector<Card> ReturnCardStack();								//Zwraca nie u�yte karty
	std::vector<Card> ReturnCardUsed();									//Zwraca odrzucone karty
	//Testowe
};

