#include "PlayerInfo.h"

PlayerInfo::PlayerInfo()
{
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
	Points = 0;							//Punkty
	RoundsWon = 0;						//Wygrane rundy
	MeleeRow = std::vector<Card>();		//Karty w 1 rzêdzie (walka wrêcz)
	RangeRow = std::vector<Card>();		//Karty w 2 rzêdzie (dystansowy)

	//Dokoñczyæ ulosowiæ dobieranie rêki i reszty tali (Do testów to rozwi¹zanie jest lepsze)
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

//Zlicza punkty z obu rzêdów
//---------------------------
int PlayerInfo::CountPoints()
{
	Points = 0;
	//Zliczanie wartoœci z 1 rzêdu
	for (int i = 0; MeleeRow.size(); i++)
	{
		Points += MeleeRow[i].ReturnValue();
	}
	//Zliczanie wartoœci z 2 rzêdu
	for (int i = 0; RangeRow.size(); i++)
	{
		Points += RangeRow[i].ReturnValue();
	}
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
		Card NewCard = CardStack.back();
		CardStack.pop_back();
		PlayerHand.push_back(NewCard);
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
//Rysuje karty z rêki gracza
void PlayerInfo::DrawHand()
{
	for (int i = 0; i < PlayerHand.size(); i++)
	{
		PlayerHand[i].DrawCard(0.15f + i * 0.08f, 0.8f);
	}
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
//Zwraca liczbê kart zu¿ytych
//--------------------------------------
int PlayerInfo::ReturnAmountOfCardUsed()
{
	return CardUsed.size();
}


