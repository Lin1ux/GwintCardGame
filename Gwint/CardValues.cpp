#include "CardValues.h"

//Pusty Konstruktor
//----------------------
CardValues::CardValues()
{
	DefaultValue = 0;
	ValueDiffrence = 0;
	Multiplayer = 1;
	CurrentValue = DefaultValue;
}
//Konstruktor wartoœci
//--------------------------------------
CardValues::CardValues(int Value)
{
	DefaultValue = Value;
	ValueDiffrence = 0;
	Multiplayer = 1;
	CurrentValue = DefaultValue;
}
//Konstruktor u¿ywaj¹cy karty
//-------------------------------
CardValues::CardValues(Card Card)
{
	DefaultValue = Card.ReturnValue();
	ValueDiffrence = 0;
	Multiplayer = 1;
	CurrentValue = DefaultValue;
}
//Ustawia mno¿nik karty
//------------------------------------
void CardValues::SetMultiplayer(int m)
{
	Multiplayer = m;
	CountCurrentValue();
}
//Ustawia modyfikator wartoœci
//----------------------------------
void CardValues::SetDiffrence(int x)
{
	ValueDiffrence = x;
	CountCurrentValue();
}
//Zeruje wartoœci klasy
//----------------------
void CardValues::Clear()
{
	DefaultValue = 0;
	ValueDiffrence = 0;
	Multiplayer = 1;
	CurrentValue = DefaultValue;
}
//Liczy obecn¹ wartoœæ i zwraca wartoœæ
//-------------------------------------
int CardValues::CountCurrentValue()
{
	CurrentValue = (DefaultValue + ValueDiffrence) * Multiplayer;
	return CurrentValue;
}
//Zwraca obecn¹ wartoœæ
//----------------------------------
int CardValues::ReturnCurrentValue()
{
	return CurrentValue;
}
//Zwraca modyfikator
//-------------------------------
int CardValues::ReturnDiffrence()
{
	return ValueDiffrence;
}
//Zwraca mno¿nik
//---------------------------------
int CardValues::ReturnMultiplayer()
{
	return Multiplayer;
}
