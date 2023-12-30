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

//Konstruktor, Dobiera karty do r�ki i nie dobrane karty
//------------------------------------------------------
PlayerInfo::PlayerInfo(std::vector<Card> DeckCards)
{
	Points = 0;							//Punkty
	RoundsWon = 0;						//Wygrane rundy
	MeleeRow = std::vector<Card>();		//Karty w 1 rz�dzie (walka wr�cz)
	RangeRow = std::vector<Card>();		//Karty w 2 rz�dzie (dystansowy)

	//Doko�czy� ulosowi� dobieranie r�ki i reszty tali (Do test�w to rozwi�zanie jest lepsze)
	for (int i = 0; i < DeckCards.size(); i++)
	{
		if (i < 10)
		{
			PlayerHand.push_back(DeckCards[i]);						//Karty w r�ce gracza
		}
		else
		{
			CardStack.push_back(DeckCards[i]);						//Karty nie dobrane
		}

	}
	CardUsed = std::vector<Card>();;								//Karty odrzucone
}

//Zlicza punkty z obu rz�d�w
//---------------------------
int PlayerInfo::CountPoints()
{
	Points = 0;
	//Zliczanie warto�ci z 1 rz�du
	for (int i = 0; MeleeRow.size(); i++)
	{
		Points += MeleeRow[i].ReturnValue();
	}
	//Zliczanie warto�ci z 2 rz�du
	for (int i = 0; RangeRow.size(); i++)
	{
		Points += RangeRow[i].ReturnValue();
	}
	return Points;
}

//Zwraca liczb� wygranych rund
//-------------------------------
int PlayerInfo::ReturnRoundsWon()
{
	return RoundsWon;
}
//Zwi�ksza liczb� wygranych rund o 1
//----------------------------------
void PlayerInfo::RoundWon()
{
	RoundsWon += 1;
}
//Czy�ci st� i wrzuca usuni�te karty do stosu odrzuconych
//--------------------------------------------------------
void PlayerInfo::EndRound()
{
	//Czyszczenie 1 rz�du
	while (MeleeRow.size() > 0)
	{
		Card RemovedCard = MeleeRow.back();
		MeleeRow.pop_back();
		CardUsed.push_back(RemovedCard);
	}
	//Czyszczenie 2 rz�du
	while (RangeRow.size() > 0)
	{
		Card RemovedCard = RangeRow.back();
		RangeRow.pop_back();
		CardUsed.push_back(RemovedCard);
	}
	CountPoints();
}
//Je�li jest miejsce dobiera kart� do r�ki
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
//Je�li jest miejsce dodaje podan� kart� do r�ki
//----------------------------------------------
void PlayerInfo::TakeCard(Card NewCard)
{
	if (PlayerHand.size() < 10)
	{
		PlayerHand.push_back(NewCard);
	}
}
//Rysuje karty z r�ki gracza
void PlayerInfo::DrawHand()
{
	for (int i = 0; i < PlayerHand.size(); i++)
	{
		PlayerHand[i].DrawCard(0.15f + i * 0.08f, 0.8f);
	}
}
//Zwraca karty w 1 rz�dzie
//--------------------------------------------
std::vector<Card> PlayerInfo::ReturnMeleeRow()
{
	return MeleeRow;
}
//Zwraca karty w 2 rz�dzie
//--------------------------------------------
std::vector<Card> PlayerInfo::ReturnRangeRow()
{
	return RangeRow;
}
//Zwraca karty z r�ki gracza
//----------------------------------------------
std::vector<Card> PlayerInfo::ReturnPlayerHand()
{
	return PlayerHand;
}
//Zwraca nie u�yte karty
//---------------------------------------------
std::vector<Card> PlayerInfo::ReturnCardStack()
{
	return CardStack;
}
//Zwraca liczb� nie u�ytych kart
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
//Zwraca liczb� kart zu�ytych
//--------------------------------------
int PlayerInfo::ReturnAmountOfCardUsed()
{
	return CardUsed.size();
}


