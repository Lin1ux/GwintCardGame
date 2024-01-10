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

//Konstruktor, Dobiera karty do r�ki i nie dobrane karty
//------------------------------------------------------
PlayerInfo::PlayerInfo(std::vector<Card> DeckCards)
{
	RoundFinished = false;				//Koniec Rundy
	Points = 0;							//Punkty
	RoundsWon = 0;						//Wygrane rundy
	MeleeRow = std::vector<Card>();		//Karty w 1 rz�dzie (walka wr�cz)
	RangeRow = std::vector<Card>();		//Karty w 2 rz�dzie (dystansowy)

	//Doko�czy� Odkomentowa� linijk� pod tym komentarzem (Do test�w lepiej nie tasowa� tali)
	//std::random_shuffle(DeckCards.begin(), DeckCards.end());		//Przetasowanie kart w tali gracza
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
//Czy zako�czono rund�
//--------------------------------
bool PlayerInfo::IsFinishedRound()
{
	return RoundFinished;
}
//Zmienia warto�� ko�ca rundy
//----------------------------------------------
void PlayerInfo::SetRoundFinished(bool newState)
{
	RoundFinished = newState;
}
//Zlicza punkty z 1 rz�du
//---------------------------------
int PlayerInfo::ReturnMeleePoints()
{
	int MeleePoints = 0;
	//Zliczanie warto�ci z 1 rz�du
	for (int i = 0; i<MeleeRow.size(); i++)
	{
		MeleePoints += MeleeRow[i].ReturnValue();
	}
	return MeleePoints;
}
//Zlicza punkty z 2 rz�du
//----------------------------------
int PlayerInfo::ReturnRangePoints()
{
	int RangePoints = 0;
	//Zliczanie warto�ci z 1 rz�du
	for (int i = 0; i<RangeRow.size(); i++)
	{
		RangePoints += RangeRow[i].ReturnValue();
	}
	return RangePoints;
}

//Zlicza punkty z obu rz�d�w
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
		Card NewCard = TakeCardFromStack();
		//Zabezpieczenie przed dodaniem pustej karty
		if (NewCard != Card())
		{
			PlayerHand.push_back(NewCard);
		}
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
//Wrzuca kart� do tali nie dobranych kart
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
//Sprawdza czy mo�na zagra� kart�
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
//Umieszcza kart� na st� do odpowiedniego rz�du
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
//Rysuje karty z r�ki gracza
void PlayerInfo::DrawHand()
{
	for (int i = 0; i < PlayerHand.size(); i++)
	{
		PlayerHand[i].DrawCard(0.15f + i * 0.08f, 0.8f);
	}
}
//Zwraca liczb� kart w r�ce
//-----------------------------------
int PlayerInfo::AmountOfCardsInHand()
{
	return PlayerHand.size();
}
//Usuwa kart� z r�ki i zwraca j�
//---------------------------------
Card PlayerInfo::UseCard(int index)
{
	Card removedCard = PlayerHand[index];
	PlayerHand.erase(PlayerHand.begin() + index);
	return removedCard;
}
//Usuwa podan� kart� je�li znajduje si� r�ce i zwraca j�
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
//Usuwa pierwsz� znalezion� kart� 
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
//Usuwa kart� z sto�u o podanym indeksie
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
void PlayerInfo::AddCardToGraveyard(Card Card)
{
	CardUsed.push_back(Card);
}
//Zwraca liczb� kart zu�ytych
//--------------------------------------
int PlayerInfo::ReturnAmountOfCardUsed()
{
	return CardUsed.size();
}
//Zwraca liczb� kart na stole
//-----------------------------------------
int PlayerInfo::ReturnAmountOfCardOnTable()
{
	return  MeleeRow.size() + RangeRow.size();
}
//Zwraca liczb� kart w wybranym rz�dzie
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
//Zwraca liczb� kart na stole posiadaj�ce dan� umiej�tno��
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
//Zwraca liczb� podanych kart
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
//Ustawia mno�nik karty o podanym indeksie i rz�dzie
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



