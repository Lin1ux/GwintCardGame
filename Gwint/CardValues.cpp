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
//Konstruktor warto�ci
//--------------------------------------
CardValues::CardValues(int Value)
{
	DefaultValue = Value;
	ValueDiffrence = 0;
	Multiplayer = 1;
	CurrentValue = DefaultValue;
}
//Konstruktor u�ywaj�cy karty
//-------------------------------
CardValues::CardValues(Card Card)
{
	DefaultValue = Card.ReturnValue();
	ValueDiffrence = 0;
	Multiplayer = 1;
	CurrentValue = DefaultValue;
}
//Ustawia mno�nik karty
//------------------------------------
void CardValues::SetMultiplayer(int m)
{
	Multiplayer = m;
	CountCurrentValue();
}
//Ustawia modyfikator warto�ci
//----------------------------------
void CardValues::SetDiffrence(int x)
{
	ValueDiffrence = x;
	CountCurrentValue();
}
//Zeruje warto�ci klasy
//----------------------
void CardValues::Clear()
{
	DefaultValue = 0;
	ValueDiffrence = 0;
	Multiplayer = 1;
	CurrentValue = DefaultValue;
}
//Liczy obecn� warto�� i zwraca warto��
//-------------------------------------
int CardValues::CountCurrentValue()
{
	CurrentValue = (DefaultValue + ValueDiffrence) * Multiplayer;
	return CurrentValue;
}
//Zwraca obecn� warto��
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
//Zwraca mno�nik
//---------------------------------
int CardValues::ReturnMultiplayer()
{
	return Multiplayer;
}
