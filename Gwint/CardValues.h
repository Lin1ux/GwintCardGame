#include "Card.h"

#pragma once
class CardValues
{
private:
	int DefaultValue;				//Domyœlna wartoœæ karty
	int ValueDiffrence;				//Modyfikator karty
	int Multiplayer;				//Mno¿nik karty
	int CurrentValue;				//Obecna wartoœæ
public:
	CardValues();					//Pusty Konstruktor
	CardValues(int Value);			//Konstruktor wartoœci
	CardValues(Card Card);			//Konstruktor u¿ywaj¹cy karty
	void SetMultiplayer(int m);		//Ustawia mno¿nik karty
	void SetDiffrence(int x);		//Ustawia modyfikator wartoœci
	void Clear();					//Zeruje wartoœci klasy
	int CountCurrentValue();		//Liczy obecn¹ wartoœæ i zwraca obecn¹ wartoœæ
	int ReturnCurrentValue();		//Zwraca obecn¹ wartoœæ
	int ReturnDiffrence();			//Zwraca modyfikator
	int ReturnMultiplayer();		//Zwraca mno¿nik
	
};

