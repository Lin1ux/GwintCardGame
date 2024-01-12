#include "Card.h"

#pragma once
class CardValues
{
private:
	int DefaultValue;
	int ValueDiffrence;
	int Multiplayer;
	int CurrentValue;
public:
	CardValues();					//Pusty Konstruktor
	CardValues(int Value);			//Konstruktor warto�ci
	CardValues(Card Card);			//Konstruktor u�ywaj�cy karty
	void SetMultiplayer(int m);		//Ustawia mno�nik karty
	void SetDiffrence(int x);		//Ustawia modyfikator warto�ci
	void Clear();					//Zeruje warto�ci klasy
	int CountCurrentValue();		//Liczy obecn� warto�� i zwraca obecn� warto��
	int ReturnCurrentValue();		//Zwraca obecn� warto��
	
};

