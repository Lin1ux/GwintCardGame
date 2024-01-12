#include<iostream>
#include <string>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Skills.h"
#include "OtherFunctions.h"

#pragma once


class Card
{
private:
	bool heroCard;
	int row;
	int currentValue;
	int value;
	int recievedDamage;
	int multiplayer;
	int cost;
	Skills skill;
	std::string name;
	ALLEGRO_BITMAP* CardImage;
	RectanglePoints vertexes;
	float PosX(float x);
	float PosY(float x);
public:
	Card(bool IsHero,int newRow,int newValue,int newCost, Skills newSkill, std::string newName, ALLEGRO_BITMAP* Image);	//Konstruktor
	Card(const Card & c);												//Konstruktor
	Card();																//Konstruktor
	int ReturnValue();													//Zwraca aktualn� warto�� karty	
	int ReturnCost();													//Zwraca koszt karty
	int ReturnRow();													//Zwraca rz�d karty na kt�ry mo�na j� zagra�
	int ReturnReceivedDamage();											//Zwraca warto�� otrzymanych obra�e�
	int ReturnMultiplayer();											//Zwraca mno�nik karty
	Skills ReturnSkill();												//Zwraca umiej�tno�� karty
	bool ReturnIsHero();												//Zwraca czy karta jest z�ota
	std::string ReturnName();											//Zwraca nazw� karty
	RectanglePoints ReturnVertexesPosition();							//Zwraca wsp�rz�dne wierzcho�k�w ostatniej narysowanej karty
	void AddDamage(int x);												//Zwi�ksza (lub zmniejsz jesli liczba jest ujemna) otrzymane obra�enia
	void ChangeMultiplayer(int x);										//Zmienia mno�nik warto�ci
	void CountValue();													//Oblicza warto�� karty
	void DrawCard(float x1, float y1);									//Rysuje kart� z podstawowymi danymi
	void DrawCard(float x1, float y1, int cardValue);						//Rysuje kart� z podstawowymi danymi i podan� warto�ci�
	void DrawBigCard(float x1, float y1);								//Rysuje kart� z wszystkimi danymi
	void DrawBigCardDescr(float x1, float y1);							//Rysuje kart� z wszystkimi danymi oraz opisem umiej�tno�ci
	void DrawSmallCard(float x1, float y1);								//Rysuje kart� z nazw� 
	RectanglePoints NormalCardVertexesPosition(float x1, float y1);		//Zwraca wsp�rz�dne wierzcho�k�w zwyk�ej karty na podanym punkcie
	bool operator == (const Card& c);									//Do por�wnanie kart
	bool operator != (const Card& c);									//Do por�wnania kart

};

