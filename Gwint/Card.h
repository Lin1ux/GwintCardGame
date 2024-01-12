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
	int ReturnValue();													//Zwraca aktualn¹ wartoœæ karty	
	int ReturnCost();													//Zwraca koszt karty
	int ReturnRow();													//Zwraca rz¹d karty na który mo¿na j¹ zagraæ
	int ReturnReceivedDamage();											//Zwraca wartoœæ otrzymanych obra¿eñ
	int ReturnMultiplayer();											//Zwraca mno¿nik karty
	Skills ReturnSkill();												//Zwraca umiejêtnoœæ karty
	bool ReturnIsHero();												//Zwraca czy karta jest z³ota
	std::string ReturnName();											//Zwraca nazwê karty
	RectanglePoints ReturnVertexesPosition();							//Zwraca wspó³rzêdne wierzcho³ków ostatniej narysowanej karty
	void AddDamage(int x);												//Zwiêksza (lub zmniejsz jesli liczba jest ujemna) otrzymane obra¿enia
	void ChangeMultiplayer(int x);										//Zmienia mno¿nik wartoœci
	void CountValue();													//Oblicza wartoœæ karty
	void DrawCard(float x1, float y1);									//Rysuje kartê z podstawowymi danymi
	void DrawCard(float x1, float y1, int cardValue);						//Rysuje kartê z podstawowymi danymi i podan¹ wartoœci¹
	void DrawBigCard(float x1, float y1);								//Rysuje kartê z wszystkimi danymi
	void DrawBigCardDescr(float x1, float y1);							//Rysuje kartê z wszystkimi danymi oraz opisem umiejêtnoœci
	void DrawSmallCard(float x1, float y1);								//Rysuje kartê z nazw¹ 
	RectanglePoints NormalCardVertexesPosition(float x1, float y1);		//Zwraca wspó³rzêdne wierzcho³ków zwyk³ej karty na podanym punkcie
	bool operator == (const Card& c);									//Do porównanie kart
	bool operator != (const Card& c);									//Do porównania kart

};

