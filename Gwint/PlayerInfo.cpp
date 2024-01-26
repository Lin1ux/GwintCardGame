#include "PlayerInfo.h"
#include "OtherFunctions.h"
#include "CardList.h"
#include <algorithm>
#include <random>
#include "images.h"

PlayerInfo::PlayerInfo()
{
	RoundFinished = false;
	Points = 0;
	RoundsWon = 0;
	for (int i = 0; i < 3; i++)
	{
		RoundPoints[i] = 0;
	}
	MCardsValues = std::vector<CardValues>();
	RCardsValues = std::vector<CardValues>();
	MeleeRow = std::vector<Card>();
	RangeRow = std::vector<Card>();
	PlayerHand = std::vector<Card>();
	CardStack = std::vector<Card>();
	CardUsed = std::vector<Card>();
	ReverseCard = ::Images::ReverseCard;
}

//Konstruktor, Dobiera karty do rêki i nie dobrane karty
//------------------------------------------------------
PlayerInfo::PlayerInfo(std::vector<Card> DeckCards)
{
	RoundFinished = false;				//Koniec Rundy
	Points = 0;							//Punkty
	RoundsWon = 0;						//Wygrane rundy
	for (int i = 0; i < 3; i++)
	{
		RoundPoints[i] = 0;				//Zapisanie wszystkich punktów rund
	}
	MeleeRow = std::vector<Card>();		//Karty w 1 rzêdzie (walka wrêcz)
	RangeRow = std::vector<Card>();		//Karty w 2 rzêdzie (dystansowy)
	MCardsValues = std::vector<CardValues>();
	RCardsValues = std::vector<CardValues>();
	ReverseCard = ::Images::ReverseCard;

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
	/*for (int i = 0; i<MeleeRow.size(); i++)
	{
		MeleePoints += MeleeRow[i].ReturnValue();
	}*/
	for (int i = 0; i < MCardsValues.size(); i++)
	{
		MeleePoints += MCardsValues[i].ReturnCurrentValue();
	}
	
	return MeleePoints;
}
//Zlicza punkty z 2 rzêdu
//----------------------------------
int PlayerInfo::ReturnRangePoints()
{
	int RangePoints = 0;
	//Zliczanie wartoœci z 1 rzêdu
	for (int i = 0; i<RCardsValues.size(); i++)
	{
		//RangePoints += RangeRow[i].ReturnValue();
		RangePoints += RCardsValues[i].ReturnCurrentValue();
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
		MCardsValues.pop_back();
		CardUsed.push_back(RemovedCard);
	}
	//Czyszczenie 2 rzêdu
	while (RangeRow.size() > 0)
	{
		Card RemovedCard = RangeRow.back();
		RangeRow.pop_back();
		RCardsValues.pop_back();
		CardUsed.push_back(RemovedCard);
	}
	//Dobieranie kart
	for (int i = 0; i < 3; i++)
	{
		if (CardStack.size() > 0)
		{
			TakeCard();
		}
	}
	CountPoints();
}
//Zapisuje wartoœæ obecnej rundy
//---------------------------------
void PlayerInfo::SetRound(int index)
{
	RoundPoints[index] = CountPoints();
}
//Zwraca wartoœæ rundy (indeksy liczone s¹ od 0)
//----------------------------------------------
int PlayerInfo::ReturnRoundPoints(int index)
{
	return RoundPoints[index];
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
//Dobiera kartê z kart nie dobranych
//----------------------------------
Card PlayerInfo::TakeCardFromStack()
{
	Card Card;
	if (CardStack.size() > 0)
	{
		Card = CardStack.back();
		CardStack.pop_back();
	}
	return Card;
}
//U¿ywa wybran¹ kartê z tali kart nie dobranych i usuwa oraz zwraca j¹ jeœli znajdzie
//----------------------------------------------------------------------------------
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
		if (NewCard.ReturnRow() == CardList::front && MeleeRow.size() < 6)
		{
			return true;
		}
		if (NewCard.ReturnRow() == CardList::back && RangeRow.size() < 6)
		{
			return true;
		}		
		return false;
	}
	return false;
}
//Sprawdza czy mo¿na zagraæ kartê w podanym rzêdzie
//-------------------------------------------------
bool PlayerInfo::CanPlay(int row)
{
	if (!RoundFinished)
	{
		if (row == CardList::front && MeleeRow.size() < 6)
		{
			return true;
		}
		if (row == CardList::back && RangeRow.size() < 6)
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
		MCardsValues.push_back(CardValues(NewCard));
	}
	else if(NewCard.ReturnRow() == 2 && RangeRow.size() <6)
	{
		RangeRow.push_back(NewCard);
		RCardsValues.push_back(CardValues(NewCard));
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
//Zwraca ostatni¹ posiadan¹ kartê
//--------------------------------
Card PlayerInfo::LastCardInHand()
{
	if (PlayerHand.size() < 0)
	{
		return Card();
	}
	return PlayerHand[PlayerHand.size() - 1];
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
				MCardsValues.erase(MCardsValues.begin() + i);
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
				RCardsValues.erase(RCardsValues.begin() + i);
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
	if (row == CardList::front && index < MeleeRow.size())
	{
		RemovedCard = MeleeRow[index];
		MeleeRow.erase(MeleeRow.begin() + index);
		MCardsValues.erase(MCardsValues.begin() + index);
	}
	if (row == CardList::back && index < RangeRow.size())
	{
		RemovedCard = RangeRow[index];
		RangeRow.erase(RangeRow.begin() + index);
		RCardsValues.erase(RCardsValues.begin() + index);
	}
	return RemovedCard;
}
//Usuwa wszystkie karty o podanej wartoœci i umieszcza je w cmentarzu
//Zwraca liczbê usuniêtych kart
//-----------------------------------------------------------------
int PlayerInfo::RemoveAllCardsWithValue(int value, bool IgnoreGoldenCards)
{
	int CardNumber = 0;
	for (int i = 0; i < MeleeRow.size(); i++)
	{
		if (MCardsValues[i].ReturnCurrentValue() == value && (IgnoreGoldenCards && !MeleeRow[i].ReturnIsHero()))
		{
			AddCardToGraveyard(RemoveCardFromTable(CardList::front, i));
			CardNumber += 1;
			i -= 1;
		}
	}
	for (int i = 0; i < RangeRow.size(); i++)
	{
		if (RCardsValues[i].ReturnCurrentValue() == value && (IgnoreGoldenCards && !RangeRow[i].ReturnIsHero()))
		{
			CardNumber += 1;
			AddCardToGraveyard(RemoveCardFromTable(CardList::back, i));
			i -= 1;
		}
	}
	return CardNumber;
}
//Usuwa wszystkie karty o podanej wartoœci (umieszcza je w cmentarzu) zapisuje w histori
//Zwraca liczbê usuniêtych kart
//------------------------------------------------------------------------------------------------
int PlayerInfo::RemoveAllCardsWithValue(int value,bool IgnoreGoldenCards, HistoryStack* Stack, Card UsedCard, int Owner)
{
	int CardNumber = 0;
	Card RemovedCard;
	for (int i = 0; i < MeleeRow.size(); i++)
	{
		if (MCardsValues[i].ReturnCurrentValue() == value && (IgnoreGoldenCards && !MeleeRow[i].ReturnIsHero()))
		{
			CardNumber += 1;
			RemovedCard = RemoveCardFromTable(CardList::front, i);
			AddCardToGraveyard(RemovedCard);
			Stack->AddAction({ Owner ,UsedCard,RemovedCard ,UsedCard.ReturnSkill() });
			i -= 1;
		}
	}
	for (int i = 0; i < RangeRow.size(); i++)
	{
		if (RCardsValues[i].ReturnCurrentValue() == value && (IgnoreGoldenCards && !RangeRow[i].ReturnIsHero()))
		{
			CardNumber += 1;
			RemovedCard = RemoveCardFromTable(CardList::back, i);
			AddCardToGraveyard(RemovedCard);
			Stack->AddAction({ Owner ,UsedCard,RemovedCard ,UsedCard.ReturnSkill() });
			i -= 1;
		}
	}
	return CardNumber;
}
//Usuwa wszystkie karty o podanej wartoœci i pomijaj¹c kartê o podanym rzêdzie i indeksie (umieszcza je w cmentarzu)
//Zwraca liczbê usuniêtych kart
//------------------------------------------------------------------------------------------------------------------
int PlayerInfo::RemoveAllCardsWithValue(int row, int index, int value, bool IgnoreGoldenCards)
{
	int CardNumber = 0;
	for (int i = 0; i < MeleeRow.size(); i++)
	{
		if (row == CardList::front && index == i)
		{
			continue;
		}
		if (MCardsValues[i].ReturnCurrentValue() == value && (IgnoreGoldenCards && !MeleeRow[i].ReturnIsHero()))
		{
			CardNumber += 1;
			AddCardToGraveyard(RemoveCardFromTable(CardList::front, i));
			i -= 1;
			index -= 1;
		}
	}
	for (int i = 0; i < RangeRow.size(); i++)
	{
		if (row == CardList::back && index == i)
		{
			continue;
		}
		if (RCardsValues[i].ReturnCurrentValue() == value && (IgnoreGoldenCards && !RangeRow[i].ReturnIsHero()))
		{
			CardNumber += 1;
			AddCardToGraveyard(RemoveCardFromTable(CardList::back, i));
			i -= 1;
			index -= 1;
		}
	}
	return CardNumber;
}
//Usuwa wszystkie karty o podanej wartoœci pomijaj¹c kartê o podanym rzêdzie i indeksie (umieszcza je w cmentarzu) zapisuje w histori
//Zwraca liczbê usuniêtych kart
//---------------------------------------------------------------------------------------------------------
int PlayerInfo::RemoveAllCardsWithValue(int row, int index, int value,bool IgnoreGoldenCards, HistoryStack* Stack, Card UsedCard,int Owner)
{
	int CardNumber = 0;
	Card RemovedCard;
	for (int i = 0; i < MeleeRow.size(); i++)
	{
		if (row == CardList::front && index == i)
		{
			continue;
		}
		if (MCardsValues[i].ReturnCurrentValue() == value && (IgnoreGoldenCards && !MeleeRow[i].ReturnIsHero()))
		{
			CardNumber += 1;
			RemovedCard = RemoveCardFromTable(CardList::front, i);
			AddCardToGraveyard(RemovedCard);
			Stack->AddAction({ Owner ,UsedCard,RemovedCard ,UsedCard.ReturnSkill() });
			i -= 1;
			index -= 1;
		}
	}
	for (int i = 0; i < RangeRow.size(); i++)
	{
		if (row == CardList::back && index == i)
		{
			continue;
		}
		if (RCardsValues[i].ReturnCurrentValue() == value && (IgnoreGoldenCards && !RangeRow[i].ReturnIsHero()))
		{
			CardNumber += 1;
			RemovedCard = RemoveCardFromTable(CardList::back, i);
			AddCardToGraveyard(RemovedCard);
			Stack->AddAction({ Owner ,UsedCard,RemovedCard ,UsedCard.ReturnSkill() });
			i -= 1;
			index -= 1;
		}
	}
	return CardNumber;
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
//Ustawia rewers karty	
void PlayerInfo::SetReverse(ALLEGRO_BITMAP* Image)
{
	ReverseCard = Image;
}
//Zwraca rewers karty
ALLEGRO_BITMAP* PlayerInfo::ReturnReverse()
{
	return ReverseCard;
}

//Dodaje kartê do cmentarza
//--------------------------------------------
void PlayerInfo::AddCardToGraveyard(Card Card)
{
	CardUsed.push_back(Card);
}
//Zwraca liczbê kart danego rzêdu
//----------------------------------------------
int PlayerInfo::ReturnAmountOfCardsByRow(int row)
{
	int sum = 0;
	for (int i = 0; i < CardUsed.size(); i++)
	{
		if (CardUsed[i].ReturnRow() == row)
		{
			sum += 1;
		}
	}
	return sum;
}
//Zwraca liczbê kart w cmentarzu
//--------------------------------------
int PlayerInfo::ReturnAmountOfCardUsed()
{
	return CardUsed.size();
}
//Zwraca liczbê z³otych kart w cmentarzu
int PlayerInfo::ReturnAmountOfGraveyardGoldCard()
{
	int sum = 0;
	for (int i = 0; i < CardUsed.size(); i++)
	{
		if (CardUsed[i].ReturnIsHero())
		{
			sum += 1;
		}
	}
	return sum;
}
//Usuwa kartê z cmentarza
//-------------------------------------------------
Card PlayerInfo::RemoveCardFromGraveyard(Card CardToRemove)
{
	Card RemovedCard = Card();
	for (int i = 0; i < CardUsed.size(); i++)
	{
		if (CardToRemove == CardUsed[i])
		{
			RemovedCard = CardUsed[i];
			CardUsed.erase(CardUsed.begin() + i);
			break;
		}
	}
	return RemovedCard;
}
//Zwraca liczbê kart na stole
//-----------------------------------------
int PlayerInfo::ReturnAmountOfCardOnTable()
{
	return  MeleeRow.size() + RangeRow.size();
}
//Zwraca liczbê kart na stole ignoruj¹c z³ote karty
//------------------------------------------------------------
int PlayerInfo::ReturnAmountOfCardOnTable(bool IgnoreGoldCard)
{
	if (IgnoreGoldCard)
	{
		int num = 0;
		for (int i = 0; i < MeleeRow.size(); i++)
		{
			if (!MeleeRow[i].ReturnIsHero())
			{
				num += 1;
			}
		}
		for (int i = 0; i < RangeRow.size(); i++)
		{
			if (!RangeRow[i].ReturnIsHero())
			{
				num += 1;
			}
		}
		return num;
	}
	return ReturnAmountOfCardOnTable();
}
//Zwraca liczbê z³otych kart na stole
//---------------------------------------------
int PlayerInfo::ReturnAmountOfGoldCardOnTable()
{
	int num = 0;
	for (int i = 0; i < MeleeRow.size(); i++)
	{
		if (MeleeRow[i].ReturnIsHero())
		{
			num += 1;
		}
	}
	for (int i = 0; i < RangeRow.size(); i++)
	{
		if (RangeRow[i].ReturnIsHero())
		{
			num += 1;
		}
	}
	return num;
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
//Zwrca liczbê kart w rêce
//----------------------------------------
int PlayerInfo::ReturnAmountOfCardInHand()
{
	return PlayerHand.size();
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
//Zwraca najwiêksz¹ wartoœæ karty na stole nale¿¹ce do gracza
//-----------------------------------------------------------
int PlayerInfo::MaxValue()
{
	int max = -1;
	for (int i = 0; i < MeleeRow.size(); i++)
	{
		if (max < MCardsValues[i].ReturnCurrentValue())
		{
			max = MCardsValues[i].ReturnCurrentValue();
		}
	}
	for (int i = 0; i < RangeRow.size(); i++)
	{
		if (max < RCardsValues[i].ReturnCurrentValue())
		{
			max = RCardsValues[i].ReturnCurrentValue();
		}
	}
	return max;
}
//Zwraca najwiêksz¹ wartoœæ karty na stole nale¿ace do gracza ignoruj¹c podan¹ kartê
//----------------------------------------------------------------------------------
int PlayerInfo::MaxValue(int row, int IgnoredCard)
{
	int max = -1;
	for (int i = 0; i < MeleeRow.size(); i++)
	{
		if (i == IgnoredCard && row == CardList::front)
		{
			continue;
		}
		if (max < MCardsValues[i].ReturnCurrentValue())
		{
			max = MCardsValues[i].ReturnCurrentValue();
		}
	}
	for (int i = 0; i < RangeRow.size(); i++)
	{
		if (i == IgnoredCard && row == CardList::back)
		{
			continue;
		}
		if (max < RCardsValues[i].ReturnCurrentValue())
		{
			max = RCardsValues[i].ReturnCurrentValue();
		}
	}
	return max;
}
int PlayerInfo::MinValue()
{
	int min = -1;
	for (int i = 0; i < MeleeRow.size(); i++)
	{
		if (min > MCardsValues[i].ReturnCurrentValue() || min == -1)
		{
			min = MCardsValues[i].ReturnCurrentValue();
		}
	}
	for (int i = 0; i < RangeRow.size(); i++)
	{
		if (min > RCardsValues[i].ReturnCurrentValue() || min == -1)
		{
			min = RCardsValues[i].ReturnCurrentValue();
		}
	}
	return min;
}
//Ustawia mno¿nik karty o podanym indeksie i rzêdzie
void PlayerInfo::SetMultiplayerOfCard(int row, int index, int value)
{
	if (row == CardList::front && index < MeleeRow.size())
	{
		MeleeRow[index].ChangeMultiplayer(value);
		MCardsValues[index].SetMultiplayer(value);
	}
	if (row == CardList::back && index < RangeRow.size())
	{
		RangeRow[index].ChangeMultiplayer(value);
		RCardsValues[index].SetMultiplayer(value);
	}
}
//Ustawia modyfikator karty o podanym indeksie i rzêdzie
//----------------------------------------------------------------
void PlayerInfo::SetDiffrenceOfCard(int row, int index, int value)
{
	if (row == CardList::front && index < MeleeRow.size())
	{
		MCardsValues[index].SetDiffrence(value);
	}
	if (row == CardList::back && index < RangeRow.size())
	{
		RCardsValues[index].SetDiffrence(value);
	}
}
//Dodaje wartoœæ do modyfikatora karty o podanym indeksie i rzêdzie
//-----------------------------------------------------------------
bool PlayerInfo::AddDiffrenceOfCard(int row, int index, int value)
{
	bool dead = false;
	if (row == CardList::front && index < MeleeRow.size())
	{
		MCardsValues[index].SetDiffrence(MCardsValues[index].ReturnDiffrence() + value);
		//Usuniêcie karty jeœli ma wartoœæ mniejsz¹ lub równ¹ 0
		if (MCardsValues[index].ReturnCurrentValue() <= 0)
		{
			AddCardToGraveyard(RemoveCardFromTable(row, index));
			dead = true;
		}
	}
	if (row == CardList::back && index < RangeRow.size())
	{
		RCardsValues[index].SetDiffrence(RCardsValues[index].ReturnDiffrence() + value);
		if (RCardsValues[index].ReturnCurrentValue() <= 0)
		{
			AddCardToGraveyard(RemoveCardFromTable(row, index));
			dead = true;
		}
	}
	return dead;
}
//Zwraca aktualn¹ wartoœæ karty
//--------------------------------------------------------
int PlayerInfo::ReturnCurrentValueOfCard(int row,int index)
{
	if (row == CardList::front && index < MCardsValues.size())
	{
		 return MCardsValues[index].ReturnCurrentValue();
	}
	if (row == CardList::back && index < RCardsValues.size())
	{
		return RCardsValues[index].ReturnCurrentValue();
	}
	return -1;	//Nie poprawny rz¹d lub index
}


