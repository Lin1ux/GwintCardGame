#include <vector>
#include "Card.h"
#include "CardValues.h"

typedef struct CardPos
{
	Card card;			//Karta
	int index;			//Index
	bool isPlayerCard;	//Czy nale�y do gracza (gracza 1)
}CardPos;

#pragma once
class PlayerInfo
{
private:
	bool RoundFinished;						//Czy sko�czono runde
	int Points;								//Punkty
	int RoundsWon;							//Wygrane rundy
	int RoundPoints[3];						//Zapisanie wszystkich punkt�w rund
	std::vector<CardValues> MCardsValues;	//Warto�ci kart I rz�du
	std::vector<CardValues> RCardsValues;	//Warto�ci kart II rz�du
	std::vector<Card> MeleeRow;				//Karty w 1 rz�dzie (walka wr�cz)
	std::vector<Card> RangeRow;				//Karty w 2 rz�dzie (dystansowy
	std::vector<Card> PlayerHand;			//Karty w r�ce gracza
	std::vector<Card> CardStack;			//Nie dobrane karty
	std::vector<Card> CardUsed;				//Karty odrzcuone							

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
	void SetRound(int index);											//Zapisuje warto�� obecnej rundy
	int ReturnRoundPoints(int index);									//Zwraca warto�� rundy (indeksy liczone s� od 0)
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
	bool CanPlay(int row);												//Sprawdza czy mo�na zagra� kart� w podanym rz�dzie
	void PlayCard(Card NewCard);										//Umieszcza kart� na st� do odpowiedniego rz�du
	Card UseCard(int index);											//Usuwa kart� o podanym indeksie z r�ki i zwraca j�
	Card UseCard(Card CardToUse);										//Usuwa podan� kart� je�li znajduje si� r�ce i zwraca j�
	//St�
	Card RemoveCardFromTable(Card CardToRemove);						//Usuwa pierwsz� znalezion� kart� 
	Card RemoveCardFromTable(int row, int index);						//Usuwa kart� z sto�u o podanym indeksie
	void RemoveAllCardsWithValue(int value);							//Usuwa wszystkie karty o podanej warto�ci (umieszcza je w cmentarzu)
	void RemoveAllCardsWithValue(int row, int index, int value);		//Usuwa wszystkie karty o podanej warto�ci pomijaj�c kart� o podanym rz�dzie i indeksie (umieszcza je w cmentarzu)
	int ReturnAmountOfCardOnTable();									//Zwraca liczb� kart na stole
	int ReturnAmountOfCardOnTable(bool IgnoreGoldCard);					//Zwraca liczb� zwyk�ych kart na stole  ignoruj�c z�ote karty
	int ReturnAmountOfCardOnTable(int row);								//Zwraca liczb� kart w wybranym rz�dzie
	int NumberOfCardsWithSkill(Skills Skill);							//Zwraca liczb� kart na stole posiadaj�ce dan� umiej�tno��
	int NumberOfSpecificCards(Card CardToFind);							//Zwraca liczb� podanych kart
	int MaxValue();														//Zwraca najwi�ksz� warto�� karty na stole nale��ce do gracza
	int MaxValue(int row, int IgnoredCard);								//Zwraca najwi�ksz� warto�� karty na stole nale�ace do gracza ignoruj�c podan� kart�
	//Wato�ci kart na stole
	void SetMultiplayerOfCard(int row, int index, int value);			//Ustawia mno�nik karty o podanym indeksie i rz�dzie							
	void SetDiffrenceOfCard(int row, int index, int value);				//Ustawia modyfikator karty o podanym indeksie i rz�dzie
	void AddDiffrenceOfCard(int row, int index, int value);				//Dodaje warto�� do modyfikatora karty o podanym indeksie i rz�dzie
	int ReturnCurrentValueOfCard(int row, int index);					//Zwraca aktualn� warto�� karty
	
//Cmentarz (U�yte karty)
	void AddCardToGraveyard(Card Card);									//Dodaje kart� do cmentarza
	int ReturnAmountOfCardsByRow(int row);								//Zwraca liczb� kart danego rz�du
	int ReturnAmountOfCardUsed();										//Zwraca liczb� kart zu�ytych
	Card RemoveCardFromGraveyard(Card Card);							//Usuwa kart� z cmentarza
	//Zwracanie kart
	std::vector<Card> ReturnMeleeRow();									//Zwraca karty w 1 rz�dzie
	std::vector<Card> ReturnRangeRow();									//Zwraca karty w 2 rz�dzie
	std::vector<Card> ReturnPlayerHand();								//Zwraca karty z r�ki gracza
	std::vector<Card> ReturnCardStack();								//Zwraca nie u�yte karty
	std::vector<Card> ReturnCardUsed();									//Zwraca odrzucone karty
};

