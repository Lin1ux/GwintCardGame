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
	int cost;
	Skills skill;
	std::string name;
	ALLEGRO_BITMAP* CardImage;
	RectanglePoints vertexes;
	float PosX(float x);
	float PosY(float x);
public:
	Card(bool IsHero,int newRow,int newValue,int newCost, Skills newSkill, std::string newName, ALLEGRO_BITMAP* Image);
	Card(const Card & c);
	Card();
	int ReturnValue();
	int ReturnCost();
	bool ReturnIsHero();
	std::string ReturnName();
	RectanglePoints ReturnVertexesPosition();
	void DrawCard(float x1, float y1);
	void DrawBigCard(float x1, float y1);
	void DrawBigCardDescr(float x1, float y1);
	void DrawSmallCard(float x1, float y1);
	RectanglePoints NormalCardVertexesPosition(float x1, float y1);
	bool operator == (const Card & c);
	bool operator != (const Card& c);

};

