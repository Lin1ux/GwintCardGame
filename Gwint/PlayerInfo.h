#include <vector>
#include "Card.h"
#include "CardValues.h"

typedef struct CardPos
{
	Card card;			//Karta
	int index;			//Index
	bool isPlayerCard;	//Czy nale¿y do gracza (gracza 1)
}CardPos;

#pragma once
class PlayerInfo
{
private:
	bool RoundFinished;						//Czy skoñczono runde
	int Points;								//Punkty
	int RoundsWon;							//Wygrane rundy
	int RoundPoints[3];						//Zapisanie wszystkich punktów rund
	std::vector<CardValues> MCardsValues;	//Wartoœci kart I rzêdu
	std::vector<CardValues> RCardsValues;	//Wartoœci kart II rzêdu
	std::vector<Card> MeleeRow;				//Karty w 1 rzêdzie (walka wrêcz)
	std::vector<Card> RangeRow;				//Karty w 2 rzêdzie (dystansowy
	std::vector<Card> PlayerHand;			//Karty w rêce gracza
	std::vector<Card> CardStack;			//Nie dobrane karty
	std::vector<Card> CardUsed;				//Karty odrzcuone							

public:
	//Konstruktory
	PlayerInfo();
	PlayerInfo(std::vector<Card> DeckCards);							//Konstruktor, Dobiera karty do rêki i nie dobrane karty
	//Koniec rundy
	bool IsFinishedRound();												//Czy zakoñczono rundê
	void SetRoundFinished(bool newState);								//Zmienia wartoœæ koñca rundy
	//Punkty
	int ReturnMeleePoints();											//Zlicza punkty z 1 rzêdu
	int ReturnRangePoints();											//Zlicza punkty z 2 rzêdu
	int CountPoints();													//Zlicza punkty z obu rzêdów
	int ReturnPoints();													//Zwraca punkty
	//Rundy
	int ReturnRoundsWon();												//Zwraca liczbê wygranych rund
	void RoundWon();													//Zwiêksza liczbê wygranych rund o 1
	void EndRound();													//Czyœci stó³ i wrzuca usuniête karty do stosu odrzuconych
	void SetRound(int index);											//Zapisuje wartoœæ obecnej rundy
	int ReturnRoundPoints(int index);									//Zwraca wartoœæ rundy (indeksy liczone s¹ od 0)
	//Rêka gracza
	void TakeCard();													//Jeœli jest miejsce dobiera kartê do rêki
	void TakeCard(Card NewCard);										//Jeœli jest miejsce dodaje podan¹ kartê do rêki
	void DrawHand();													//Rysuje karty z rêki gracza
	int AmountOfCardsInHand();											//Zwraca liczbê kart w rêce
	//Nie dobrane karty
	void PutToStack(Card NewCard);										//Wrzuca kartê do tali nie dobranych kart
	Card TakeCardFromStack();											//Dobiera kartê z nie u¿ytych kart i zwraca j¹
	Card UseStackCard(Card CardToRemove);								//Usuwa wybran¹ kartê z nie u¿ytych kart i zwraca j¹
	int ReturnAmountOfCardStack();										//Zwraca liczbê nie u¿ytych kart
	//Zagranie karty
	bool CanPlay(Card NewCard);											//Sprawdza czy mo¿na zagraæ kartê
	bool CanPlay(int row);												//Sprawdza czy mo¿na zagraæ kartê w podanym rzêdzie
	void PlayCard(Card NewCard);										//Umieszcza kartê na stó³ do odpowiedniego rzêdu
	Card UseCard(int index);											//Usuwa kartê o podanym indeksie z rêki i zwraca j¹
	Card UseCard(Card CardToUse);										//Usuwa podan¹ kartê jeœli znajduje siê rêce i zwraca j¹
	//Stó³
	Card RemoveCardFromTable(Card CardToRemove);						//Usuwa pierwsz¹ znalezion¹ kartê 
	Card RemoveCardFromTable(int row, int index);						//Usuwa kartê z sto³u o podanym indeksie
	void RemoveAllCardsWithValue(int value);							//Usuwa wszystkie karty o podanej wartoœci (umieszcza je w cmentarzu)
	void RemoveAllCardsWithValue(int row, int index, int value);		//Usuwa wszystkie karty o podanej wartoœci pomijaj¹c kartê o podanym rzêdzie i indeksie (umieszcza je w cmentarzu)
	int ReturnAmountOfCardOnTable();									//Zwraca liczbê kart na stole
	int ReturnAmountOfCardOnTable(bool IgnoreGoldCard);					//Zwraca liczbê zwyk³ych kart na stole  ignoruj¹c z³ote karty
	int ReturnAmountOfCardOnTable(int row);								//Zwraca liczbê kart w wybranym rzêdzie
	int NumberOfCardsWithSkill(Skills Skill);							//Zwraca liczbê kart na stole posiadaj¹ce dan¹ umiejêtnoœæ
	int NumberOfSpecificCards(Card CardToFind);							//Zwraca liczbê podanych kart
	int MaxValue();														//Zwraca najwiêksz¹ wartoœæ karty na stole nale¿¹ce do gracza
	int MaxValue(int row, int IgnoredCard);								//Zwraca najwiêksz¹ wartoœæ karty na stole nale¿ace do gracza ignoruj¹c podan¹ kartê
	//Watoœci kart na stole
	void SetMultiplayerOfCard(int row, int index, int value);			//Ustawia mno¿nik karty o podanym indeksie i rzêdzie							
	void SetDiffrenceOfCard(int row, int index, int value);				//Ustawia modyfikator karty o podanym indeksie i rzêdzie
	void AddDiffrenceOfCard(int row, int index, int value);				//Dodaje wartoœæ do modyfikatora karty o podanym indeksie i rzêdzie
	int ReturnCurrentValueOfCard(int row, int index);					//Zwraca aktualn¹ wartoœæ karty
	
//Cmentarz (U¿yte karty)
	void AddCardToGraveyard(Card Card);									//Dodaje kartê do cmentarza
	int ReturnAmountOfCardsByRow(int row);								//Zwraca liczbê kart danego rzêdu
	int ReturnAmountOfCardUsed();										//Zwraca liczbê kart zu¿ytych
	Card RemoveCardFromGraveyard(Card Card);							//Usuwa kartê z cmentarza
	//Zwracanie kart
	std::vector<Card> ReturnMeleeRow();									//Zwraca karty w 1 rzêdzie
	std::vector<Card> ReturnRangeRow();									//Zwraca karty w 2 rzêdzie
	std::vector<Card> ReturnPlayerHand();								//Zwraca karty z rêki gracza
	std::vector<Card> ReturnCardStack();								//Zwraca nie u¿yte karty
	std::vector<Card> ReturnCardUsed();									//Zwraca odrzucone karty
};

