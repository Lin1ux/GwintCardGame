#include "PlayerInfo.h"
#include "OtherFunctions.h"
#include "CardList.h"
#include <algorithm>
#include <random>

PlayerInfo::PlayerInfo()
{
	RoundFinished = false;
	Points = 0;
	RoundsWon = 0;
	MeleeRow = std::vector<Card>();
	RangeRow = std::vector<Card>();
	PlayerHand = std::vector<Card>();
	CardStack = std::vector<Card>();
	CardUsed = std::vector<Card>();
}

//Konstruktor, Dobiera karty do rêki i nie dobrane karty
//------------------------------------------------------
PlayerInfo::PlayerInfo(std::vector<Card> DeckCards)
{
	RoundFinished = false;				//Koniec Rundy
	Points = 0;							//Punkty
	RoundsWon = 0;						//Wygrane rundy
	MeleeRow = std::vector<Card>();		//Karty w 1 rzêdzie (walka wrêcz)
	RangeRow = std::vector<Card>();		//Karty w 2 rzêdzie (dystansowy)

	//Dokoñczyæ Odkomentowaæ linijkê pod tym komentarzem (Do testów lepiej nie tasowaæ tali)
	//std::random_shuffle(DeckCards.begin(), DeckCards.end());		//Przetasowanie kart w tali gracza
	for (int i = 0; i < DeckCards.size(); i++)
	{
		if (i < 10)
		{
			PlayerHand.push_back(DeckCards[i]);						//Karty w rêce gracza
		}
		else
		{
			CardStack.push_back(DeckCards[i]);						//Karty nie dobrane
		}
	} 
	CardUsed = std::vector<Card>();;								//Karty odrzucone
}
//Czy zakoñczono rundê
//--------------------------------
bool PlayerInfo::IsFinishedRound()
{
	return RoundFinished;
}
//Zmienia wartoœæ koñca rundy
//----------------------------------------------
void PlayerInfo::SetRoundFinished(bool newState)
{
	RoundFinished = newState;
}
//Zlicza punkty z 1 rzêdu
//---------------------------------
int PlayerInfo::ReturnMeleePoints()
{
	int MeleePoints = 0;
	//Zliczanie wartoœci z 1 rzêdu
	for (int i = 0; i<MeleeRow.size(); i++)
	{
		MeleePoints += MeleeRow[i].ReturnValue();
	}
	return MeleePoints;
}
//Zlicza punkty z 2 rzêdu
//----------------------------------
int PlayerInfo::ReturnRangePoints()
{
	int RangePoints = 0;
	//Zliczanie wartoœci z 1 rzêdu
	for (int i = 0; i<RangeRow.size(); i++)
	{
		RangePoints += RangeRow[i].ReturnValue();
	}
	return RangePoints;
}

//Zlicza punkty z obu rzêdów
//---------------------------
int PlayerInfo::CountPoints()
{
	Points = ReturnMeleePoints() + ReturnRangePoints();
	return Points;
}
//Zwraca punkty
//----------------------------
int PlayerInfo::ReturnPoints()
{
	return Points;
}

//Zwraca liczbê wygranych rund
//-------------------------------
int PlayerInfo::ReturnRoundsWon()
{
	return RoundsWon;
}
//Zwiêksza liczbê wygranych rund o 1
//----------------------------------
void PlayerInfo::RoundWon()
{
	RoundsWon += 1;
}
//Czyœci stó³ i wrzuca usuniête karty do stosu odrzuconych
//--------------------------------------------------------
void PlayerInfo::EndRound()
{
	//Czyszczenie 1 rzêdu
	while (MeleeRow.size() > 0)
	{
		Card RemovedCard = MeleeRow.back();
		MeleeRow.pop_back();
		CardUsed.push_back(RemovedCard);
	}
	//Czyszczenie 2 rzêdu
	while (RangeRow.size() > 0)
	{
		Card RemovedCard = RangeRow.back();
		RangeRow.pop_back();
		CardUsed.push_back(RemovedCard);
	}
	CountPoints();
}
//Jeœli jest miejsce dobiera kartê do rêki
//----------------------------------------
void PlayerInfo::TakeCard()
{
	if (PlayerHand.size() < 10)
	{
		Card NewCard = TakeCardFromStack();
		//Zabezpieczenie przed dodaniem pustej karty
		if (NewCard != Card())
		{
			PlayerHand.push_back(NewCard);
		}
	}
}
//Jeœli jest miejsce dodaje podan¹ kartê do rêki
//----------------------------------------------
void PlayerInfo::TakeCard(Card NewCard)
{
	if (PlayerHand.size() < 10)
	{
		PlayerHand.push_back(NewCard);
	}
}
//Wrzuca kartê do tali nie dobranych kart
//---------------------------------------
void PlayerInfo::PutToStack(Card NewCard)
{
	CardStack.insert(CardStack.begin(), NewCard);
}
Card PlayerInfo::TakeCardFromStack()
{
	Card Card = CardStack.back();
	CardStack.pop_back();
	return Card;
}
Card PlayerInfo::UseStackCard(Card CardToRemove)
{
	for (int i = 0; i < CardStack.size(); i++)
	{
		if (CardToRemove == CardStack[i])
		{
			Card removedCard = CardStack[i];
			CardStack.erase(CardStack.begin() + i);
			return removedCard;
		}
	}
	return Card();
}
//Sprawdza czy mo¿na zagraæ kartê
//------------------------------------
bool PlayerInfo::CanPlay(Card NewCard)
{
	if (!RoundFinished)
	{
		if (NewCard.ReturnRow() == 1 && MeleeRow.size() < 6)
		{
			return true;
		}
		if (NewCard.ReturnRow() == 2 && RangeRow.size() < 6)
		{
			return true;
		}		
		return false;
	}
	return false;
}
//Umieszcza kartê na stó³ do odpowiedniego rzêdu
//----------------------------------------------
void PlayerInfo::PlayCard(Card NewCard)
{
	if (NewCard.ReturnRow() == 1 && MeleeRow.size()<6)
	{
		MeleeRow.push_back(NewCard);
	}
	else if(NewCard.ReturnRow() == 2 && RangeRow.size() <6)
	{
		RangeRow.push_back(NewCard);
	}
}
//Rysuje karty z rêki gracza
void PlayerInfo::DrawHand()
{
	for (int i = 0; i < PlayerHand.size(); i++)
	{
		PlayerHand[i].DrawCard(0.15f + i * 0.08f, 0.8f);
	}
}
//Zwraca liczbê kart w rêce
//-----------------------------------
int PlayerInfo::AmountOfCardsInHand()
{
	return PlayerHand.size();
}
//Usuwa kartê z rêki i zwraca j¹
//---------------------------------
Card PlayerInfo::UseCard(int index)
{
	Card removedCard = PlayerHand[index];
	PlayerHand.erase(PlayerHand.begin() + index);
	return removedCard;
}
//Usuwa podan¹ kartê jeœli znajduje siê rêce i zwraca j¹
//--------------------------------------------------------
Card PlayerInfo::UseCard(Card CardToUse)
{
	for (int i = 0; i < PlayerHand.size();i++)
	{
		if (CardToUse == PlayerHand[i])
		{
			Card removedCard = PlayerHand[i];
			PlayerHand.erase(PlayerHand.begin() + i);
			return removedCard;
		}
	}
	return Card();
}
//Usuwa pierwsz¹ znalezion¹ kartê 
//-----------------------------------------------------
Card PlayerInfo::RemoveCardFromTable(Card CardToRemove)
{
	Card RemovedCard = Card();
	if (CardToRemove.ReturnRow() == CardList::front)
	{
		for (int i = 0; i < MeleeRow.size(); i++)
		{
			if (CardToRemove == MeleeRow[i])
			{
				RemovedCard = MeleeRow[i];
				MeleeRow.erase(MeleeRow.begin() + i);
				break;
			}
		}	
	}
	if (CardToRemove.ReturnRow() == CardList::back)
	{
		for (int i = 0; i < RangeRow.size(); i++)
		{
			if (CardToRemove == RangeRow[i])
			{
				RemovedCard = MeleeRow[i];
				RangeRow.erase(RangeRow.begin() + i);
				break;
			}
		}
	}
	return RemovedCard;
}
//Usuwa kartê z sto³u o podanym indeksie
//------------------------------------------------------
Card PlayerInfo::RemoveCardFromTable(int row, int index)
{
	Card RemovedCard = Card();
	if (row == CardList::front)
	{
		RemovedCard = MeleeRow[index];
		MeleeRow.erase(MeleeRow.begin() + index);
	}
	if (row == CardList::back)
	{
		RemovedCard = RangeRow[index];
		RangeRow.erase(MeleeRow.begin() + index);
	}
	return RemovedCard;
}
//Zwraca karty w 1 rzêdzie
//--------------------------------------------
std::vector<Card> PlayerInfo::ReturnMeleeRow()
{
	return MeleeRow;
}
//Zwraca karty w 2 rzêdzie
//--------------------------------------------
std::vector<Card> PlayerInfo::ReturnRangeRow()
{
	return RangeRow;
}
//Zwraca karty z rêki gracza
//----------------------------------------------
std::vector<Card> PlayerInfo::ReturnPlayerHand()
{
	return PlayerHand;
}
//Zwraca nie u¿yte karty
//---------------------------------------------
std::vector<Card> PlayerInfo::ReturnCardStack()
{
	return CardStack;
}
//Zwraca liczbê nie u¿ytych kart
//---------------------------------------
int PlayerInfo::ReturnAmountOfCardStack()
{
	return CardStack.size();
}
//Zwraca odrzucone karty
//--------------------------------------------
std::vector<Card> PlayerInfo::ReturnCardUsed()
{
	return CardUsed;
}
void PlayerInfo::AddCardToGraveyard(Card Card)
{
	CardUsed.push_back(Card);
}
//Zwraca liczbê kart zu¿ytych
//--------------------------------------
int PlayerInfo::ReturnAmountOfCardUsed()
{
	return CardUsed.size();
}
//Zwraca liczbê kart na stole
//-----------------------------------------
int PlayerInfo::ReturnAmountOfCardOnTable()
{
	return  MeleeRow.size() + RangeRow.size();
}
//Zwraca liczbê kart w wybranym rzêdzie
//------------------------------------------------
int PlayerInfo::ReturnAmountOfCardOnTable(int row)
{
	if (row == CardList::front)
	{
		return MeleeRow.size();
	}
	if (row == CardList::back)
	{
		return RangeRow.size();
	}
	return 0;
}
//Zwraca liczbê kart na stole posiadaj¹ce dan¹ umiejêtnoœæ
int PlayerInfo::NumberOfCardsWithSkill(Skills Skill)
{
	int sum = 0;
	for (int i = 0; i < MeleeRow.size(); i++)
	{
		if (MeleeRow[i].ReturnSkill() == Skill)
		{
			sum += 1;
		}
	}
	for (int i = 0; i < RangeRow.size(); i++)
	{
		if (RangeRow[i].ReturnSkill() == Skill)
		{
			sum += 1;
		}
	}
	return sum;
}
//Zwraca liczbê podanych kart
//----------------------------------------------------
int PlayerInfo::NumberOfSpecificCards(Card CardToFind)
{
	int sum = 0;
	for (int i = 0; i < MeleeRow.size(); i++)
	{
		if (MeleeRow[i] == CardToFind)
		{
			sum += 1;
		}
	}
	for (int i = 0; i < RangeRow.size(); i++)
	{
		if (RangeRow[i] == CardToFind)
		{
			sum += 1;
		}
	}
	return sum;
}
//Ustawia mno¿nik karty o podanym indeksie i rzêdzie
void PlayerInfo::SetMultiplayerOfCard(int row, int index, int value)
{
	Card test;
	if (row == CardList::front)
	{
		MeleeRow[index].ChangeMultiplayer(value);
	}
	if (row == CardList::back)
	{
		RangeRow[index].ChangeMultiplayer(value);
	}
}



