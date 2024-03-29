﻿#include "Card.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_ttf.h>			//Wczytywanie czcionek .ttf
#include <allegro5/allegro_font.h>			//Czcionki
#include <iostream>
#include <string.h>

#include "Colors.h"
#include "settings.h"
#include "Images.h"
#include "Fonts.h"
#include "AllSkills.h"
#include "OtherFunctions.h"

//Konstruktor
//-----------
Card::Card(bool IsHero, int newRow, int newValue,int newCost, Skills newSkill, std::string newName, ALLEGRO_BITMAP* Image)
{
	heroCard = IsHero;
	value = newValue;
	recievedDamage = 0;
	multiplayer = 1;
	currentValue = value;
	cost = newCost;
	row = newRow;
	skill = newSkill;
	name = newName;
	CardImage = Image;
	Point zeroPoint = { 0,0 };
	vertexes = { zeroPoint ,zeroPoint ,zeroPoint ,zeroPoint };
}
Card::Card(const Card& c)
{
	heroCard = c.heroCard;
	value = c.value;
	recievedDamage = 0;
	multiplayer = 1;
	currentValue = value;
	cost = c.cost;
	row = c.row;
	skill = c.skill;
	name = c.name;
	CardImage = c.CardImage;
	Point zeroPoint = { 0,0 };
	vertexes = { zeroPoint ,zeroPoint ,zeroPoint ,zeroPoint };
}
//Konstruktor
//-----------
Card::Card()
{
	heroCard = false;
	value = 0;
	recievedDamage = 0;
	multiplayer = 1;
	currentValue = value;
	cost = 0;
	row = 1;
	skill = AllSkills::None;
	name = "";
	CardImage = Images::Empty;
	Point zeroPoint = { 0,0 };
	vertexes = { zeroPoint ,zeroPoint ,zeroPoint ,zeroPoint };
}
//Rysuje wizualizacje karty
//-------------------------
void Card::DrawCard(float x1, float y1)
{
	float ImgSizeX = (PosX(x1 + 0.07) - PosX(x1))/settings::ScrWidth();
	float DownEdgePos = y1 + (ImgSizeX * 1.1 * settings::ProportionScreenWH());;
	
	//Portret postaci
	al_draw_scaled_bitmap(Card::CardImage, 0, 0, 300, 300, PosX(x1+0.003), PosY(y1+0.003), PosX(ImgSizeX), PosY(ImgSizeX * settings::ProportionScreenWH()), NULL);
	if (heroCard)
	{
		al_draw_scaled_bitmap(Images::HeroCharacterFrame, 0, 0, 330, 330, PosX(x1), PosY(y1), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 1.1 * settings::ProportionScreenWH()), NULL);
	}
	else
	{
		al_draw_scaled_bitmap(Images::CharacterFrame, 0, 0, 330, 330, PosX(x1), PosY(y1), PosX(ImgSizeX*1.1), PosY(ImgSizeX* 1.1 * settings::ProportionScreenWH()), NULL);
	}
	//Dane karty
	al_draw_scaled_bitmap(Images::StatFrame, 0, 0, 330, 100, PosX(x1), PosY(DownEdgePos), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 0.3 * settings::ProportionScreenWH()), NULL);
	if (row == 1)
	{
		al_draw_scaled_bitmap(Images::MeleeCircle, 0, 0, 100, 100, PosX(x1 + 0.005), PosY(DownEdgePos + 0.002), PosX(ImgSizeX * 0.25), PosY(ImgSizeX * 0.25 * settings::ProportionScreenWH()), NULL);
	}
	else
	{
		al_draw_scaled_bitmap(Images::RangeCircle, 0, 0, 100, 100, PosX(x1 + 0.005), PosY(DownEdgePos + 0.002), PosX(ImgSizeX * 0.25), PosY(ImgSizeX * 0.25 * settings::ProportionScreenWH()), NULL);
	}
	al_draw_scaled_bitmap(Images::StatCircle, 0, 0, 100, 100, PosX(x1 + 0.029), PosY(DownEdgePos + 0.002), PosX(ImgSizeX * 0.25), PosY(ImgSizeX * 0.25 * settings::ProportionScreenWH()), NULL);
	al_draw_scaled_bitmap(skill.ReturnIcon(), 0, 0, 100, 100, PosX(x1 + 0.0525), PosY(DownEdgePos + 0.002), PosX(ImgSizeX * 0.25), PosY(ImgSizeX * 0.25 * settings::ProportionScreenWH()), NULL);
	if (heroCard)
	{
		al_draw_text(Fonts::SmallValueFont, Colors::lightGold, PosX(x1 + 0.038), PosY(DownEdgePos - 0.0005), ALLEGRO_ALIGN_CENTER, std::to_string(currentValue).c_str());
	}
	else if(currentValue == value)
	{
		al_draw_text(Fonts::SmallValueFont, Colors::white, PosX(x1 + 0.038), PosY(DownEdgePos - 0.0005), ALLEGRO_ALIGN_CENTER, std::to_string(currentValue).c_str());
	}
	else if (currentValue > value)
	{
		al_draw_text(Fonts::SmallValueFont, Colors::lightGreen, PosX(x1 + 0.038), PosY(DownEdgePos - 0.0005), ALLEGRO_ALIGN_CENTER, std::to_string(currentValue).c_str());
	}
	else if (currentValue < value)
	{
		al_draw_text(Fonts::SmallValueFont, Colors::lightRed, PosX(x1 + 0.038), PosY(DownEdgePos - 0.0005), ALLEGRO_ALIGN_CENTER, std::to_string(currentValue).c_str());
	}
	vertexes = NormalCardVertexesPosition(x1, y1);
	//OtherFunctions::DrawRectangle(vertexes, Colors::red, 5);
}
//Rysuje kartę z podstawowymi danymi i podaną wartością
//------------------------------------------------
void Card::DrawCard(float x1, float y1, int cardValue)
{
	float ImgSizeX = (PosX(x1 + 0.07) - PosX(x1)) / settings::ScrWidth();
	float DownEdgePos = y1 + (ImgSizeX * 1.1 * settings::ProportionScreenWH());;

	//Portret postaci
	al_draw_scaled_bitmap(Card::CardImage, 0, 0, 300, 300, PosX(x1 + 0.003), PosY(y1 + 0.003), PosX(ImgSizeX), PosY(ImgSizeX * settings::ProportionScreenWH()), NULL);
	if (heroCard)
	{
		al_draw_scaled_bitmap(Images::HeroCharacterFrame, 0, 0, 330, 330, PosX(x1), PosY(y1), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 1.1 * settings::ProportionScreenWH()), NULL);
	}
	else
	{
		al_draw_scaled_bitmap(Images::CharacterFrame, 0, 0, 330, 330, PosX(x1), PosY(y1), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 1.1 * settings::ProportionScreenWH()), NULL);
	}
	//Dane karty
	al_draw_scaled_bitmap(Images::StatFrame, 0, 0, 330, 100, PosX(x1), PosY(DownEdgePos), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 0.3 * settings::ProportionScreenWH()), NULL);
	if (row == 1)
	{
		al_draw_scaled_bitmap(Images::MeleeCircle, 0, 0, 100, 100, PosX(x1 + 0.005), PosY(DownEdgePos + 0.002), PosX(ImgSizeX * 0.25), PosY(ImgSizeX * 0.25 * settings::ProportionScreenWH()), NULL);
	}
	else
	{
		al_draw_scaled_bitmap(Images::RangeCircle, 0, 0, 100, 100, PosX(x1 + 0.005), PosY(DownEdgePos + 0.002), PosX(ImgSizeX * 0.25), PosY(ImgSizeX * 0.25 * settings::ProportionScreenWH()), NULL);
	}
	al_draw_scaled_bitmap(Images::StatCircle, 0, 0, 100, 100, PosX(x1 + 0.029), PosY(DownEdgePos + 0.002), PosX(ImgSizeX * 0.25), PosY(ImgSizeX * 0.25 * settings::ProportionScreenWH()), NULL);
	al_draw_scaled_bitmap(skill.ReturnIcon(), 0, 0, 100, 100, PosX(x1 + 0.0525), PosY(DownEdgePos + 0.002), PosX(ImgSizeX * 0.25), PosY(ImgSizeX * 0.25 * settings::ProportionScreenWH()), NULL);
	if (heroCard)
	{
		al_draw_text(Fonts::SmallValueFont, Colors::lightGold, PosX(x1 + 0.038), PosY(DownEdgePos - 0.0005), ALLEGRO_ALIGN_CENTER, std::to_string(cardValue).c_str());
	}
	else if (cardValue == value)
	{
		al_draw_text(Fonts::SmallValueFont, Colors::white, PosX(x1 + 0.038), PosY(DownEdgePos - 0.0005), ALLEGRO_ALIGN_CENTER, std::to_string(cardValue).c_str());
	}
	else if (cardValue > value)
	{
		al_draw_text(Fonts::SmallValueFont, Colors::lightGreen, PosX(x1 + 0.038), PosY(DownEdgePos - 0.0005), ALLEGRO_ALIGN_CENTER, std::to_string(cardValue).c_str());
	}
	else if (cardValue < value)
	{
		al_draw_text(Fonts::SmallValueFont, Colors::lightRed, PosX(x1 + 0.038), PosY(DownEdgePos - 0.0005), ALLEGRO_ALIGN_CENTER, std::to_string(cardValue).c_str());
	}
	vertexes = NormalCardVertexesPosition(x1, y1);
}
//Rysuje dokładniejszą kartę
//---------------------------------------
void Card::DrawBigCard(float x1, float y1)
{
	float ImgSizeX = (PosX(x1 + 0.12) - PosX(x1)) / settings::ScrWidth();
	float DownEdgePos;

	//Wierzchołek karty
	vertexes.P1 = { PosX(x1), PosY(y1) };
	vertexes.P2 = { PosX(ImgSizeX*1.1+x1), PosY(y1) };

	//Portret
	al_draw_scaled_bitmap(Card::CardImage, 0, 0, 300, 300, PosX(x1 + 0.006), PosY(y1 + 0.006), PosX(ImgSizeX), PosY(ImgSizeX * settings::ProportionScreenWH()), NULL);
	//Ramka Portretu
	if (heroCard)
	{
		al_draw_scaled_bitmap(Images::HeroCharacterFrame, 0, 0, 330, 330, PosX(x1), PosY(y1), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 1.1 * settings::ProportionScreenWH()), NULL);
	}
	else
	{
		al_draw_scaled_bitmap(Images::CharacterFrame, 0, 0, 330, 330, PosX(x1), PosY(y1), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 1.1 * settings::ProportionScreenWH()), NULL);
	}
	//Dane karty
	DownEdgePos = y1 + (ImgSizeX * 1.1 * settings::ProportionScreenWH());
	//Nazwa karty
	al_draw_scaled_bitmap(Images::NameFrame, 0, 0, 330, 100, PosX(x1), PosY(DownEdgePos), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 0.3 * settings::ProportionScreenWH()), NULL);
	al_draw_text(Fonts::NameFont, Colors::white, PosX(x1+0.065), PosY(DownEdgePos+0.012), ALLEGRO_ALIGN_CENTER, name.c_str());
	DownEdgePos += (ImgSizeX * 0.3 * settings::ProportionScreenWH());
	al_draw_scaled_bitmap(Images::StatFrame, 0, 0, 330, 100, PosX(x1), PosY(DownEdgePos), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 0.3 * settings::ProportionScreenWH()), NULL);
	//Dane karty
	al_draw_scaled_bitmap(Images::StatCircle, 0, 0, 100, 100, PosX(x1 + 0.01), PosY(DownEdgePos + 0.012), PosX(ImgSizeX * 0.2), PosY(ImgSizeX * 0.2 * settings::ProportionScreenWH()), NULL);
	if (row == 1)
	{
		al_draw_scaled_bitmap(Images::MeleeCircle, 0, 0, 100, 100, PosX(x1 + 0.04), PosY(DownEdgePos + 0.012), PosX(ImgSizeX * 0.2), PosY(ImgSizeX * 0.2 * settings::ProportionScreenWH()), NULL);
	}
	else
	{
		al_draw_scaled_bitmap(Images::RangeCircle, 0, 0, 100, 100, PosX(x1 + 0.04), PosY(DownEdgePos + 0.012), PosX(ImgSizeX * 0.2), PosY(ImgSizeX * 0.2 * settings::ProportionScreenWH()), NULL);
	}
	al_draw_scaled_bitmap(Images::StatCircle, 0, 0, 100, 100, PosX(x1 + 0.07), PosY(DownEdgePos + 0.012), PosX(ImgSizeX * 0.2), PosY(ImgSizeX * 0.2 * settings::ProportionScreenWH()), NULL);
	al_draw_scaled_bitmap(skill.ReturnIcon(), 0, 0, 100, 100, PosX(x1 + 0.1), PosY(DownEdgePos + 0.012), PosX(ImgSizeX * 0.2), PosY(ImgSizeX * 0.2 * settings::ProportionScreenWH()), NULL);
	al_draw_text(Fonts::ValueFont, Colors::white, PosX(x1 + 0.022), PosY(DownEdgePos + 0.009), ALLEGRO_ALIGN_CENTER, std::to_string(cost).c_str());
	if (heroCard)
	{
		al_draw_text(Fonts::ValueFont, Colors::lightGold, PosX(x1 + 0.082), PosY(DownEdgePos + 0.009), ALLEGRO_ALIGN_CENTER, std::to_string(value).c_str());
	}
	else
	{
		al_draw_text(Fonts::ValueFont, Colors::white, PosX(x1 + 0.082), PosY(DownEdgePos + 0.009), ALLEGRO_ALIGN_CENTER, std::to_string(value).c_str());
	}
	//Dolne pozycje wierzchołków
	DownEdgePos += (ImgSizeX * 0.3 * settings::ProportionScreenWH());
	vertexes.P3 = { PosX(x1), PosY(DownEdgePos) };
	vertexes.P4 = { PosX(ImgSizeX * 1.1 + x1), PosY(DownEdgePos) };
	//OtherFunctions::DrawRectangle(vertexes, Colors::red, 5);
}
//Rysuje małą wizualizacje karty
//------------------------------------------
void Card::DrawSmallCard(float x1, float y1)
{
	float ImgSizeX = (PosX(x1 + 0.03) - PosX(x1)) / settings::ScrWidth();
	float DownEdgePos;

	//Wierzchołek karty
	vertexes.P1 = { PosX(x1), PosY(y1) };
	vertexes.P2 = { PosX(ImgSizeX * 5.5 + x1), PosY(y1) };
	//Portret
	al_draw_scaled_bitmap(Card::CardImage, 0, 0, 300, 300, PosX(x1 + 0.001), PosY(y1 + 0.001), PosX(ImgSizeX), PosY(ImgSizeX * settings::ProportionScreenWH()), NULL);
	//Ramka Portretu
	if (heroCard)
	{
		al_draw_scaled_bitmap(Images::HeroCharacterFrame, 0, 0, 330, 330, PosX(x1), PosY(y1), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 1.1 * settings::ProportionScreenWH()), NULL);
	}
	else
	{
		al_draw_scaled_bitmap(Images::CharacterFrame, 0, 0, 330, 330, PosX(x1), PosY(y1), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 1.1 * settings::ProportionScreenWH()), NULL);
	}
	//Nazwa Karty
	al_draw_scaled_bitmap(Images::NameFrame, 0, 0, 330, 100, PosX(x1 + ImgSizeX * 1.1), PosY(y1), PosX(ImgSizeX * 4.4), PosY(ImgSizeX * 1.1 * settings::ProportionScreenWH()), NULL);
	al_draw_text(Fonts::NameFont, Colors::white, PosX(x1 + ImgSizeX * 3.3), PosY(y1+0.008), ALLEGRO_ALIGN_CENTER, name.c_str());
	//Dane karty
	DownEdgePos = y1 + (ImgSizeX * 1.1 * settings::ProportionScreenWH());
	vertexes.P3 = { PosX(x1), PosY(DownEdgePos) };
	vertexes.P4 = { PosX(ImgSizeX * 5.5 + x1), PosY(DownEdgePos) };
	//OtherFunctions::DrawRectangle(vertexes, Colors::red, 5);
	
}
//Rysuje dużą kartę z opisem umiejętności
//---------------------------------------
void Card::DrawBigCardDescr(float x1, float y1)
{
	DrawBigCard(x1, y1);
	float ImgSizeX = (PosX(x1 + 0.12) - PosX(x1)) / settings::ScrWidth();	//Szerokość karty
	float DownEdgePos = vertexes.P3.y;										//Dolna krawędź karty (współrzędna y)
	al_draw_scaled_bitmap(Images::DescrFrame, 0, 0, 330, 400, PosX(x1), DownEdgePos, PosX(ImgSizeX*1.1), PosY(ImgSizeX*1.21f * settings::ProportionScreenWH()), NULL); //ALLEGRO_ALIGN_CENTER
	al_draw_multiline_text(Fonts::NameFont, Colors::white, (vertexes.P1.x+ vertexes.P2.x)/2, DownEdgePos+(DownEdgePos*0.01), PosX(ImgSizeX), PosY(ImgSizeX * 0.1f * settings::ProportionScreenWH()), ALLEGRO_ALIGN_CENTER, (skill.ReturnName() + ":\n" + skill.ReturnDescr()).c_str());
}
//Rysuje mały obrazek karty
//----------------------------------------
void Card::DrawPicture(float x1, float y1)
{
	float ImgSizeX = (PosX(x1 + 0.04) - PosX(x1)) / settings::ScrWidth();
	//Portret
	al_draw_scaled_bitmap(Card::CardImage, 0, 0, 300, 300, PosX(x1 + 0.001), PosY(y1 + 0.001), PosX(ImgSizeX), PosY(ImgSizeX * settings::ProportionScreenWH()), NULL);
	//Ramka Portretu
	if (heroCard)
	{
		al_draw_scaled_bitmap(Images::HeroCharacterFrame, 0, 0, 330, 330, PosX(x1), PosY(y1), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 1.1 * settings::ProportionScreenWH()), NULL);
	}
	else
	{
		al_draw_scaled_bitmap(Images::CharacterFrame, 0, 0, 330, 330, PosX(x1), PosY(y1), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 1.1 * settings::ProportionScreenWH()), NULL);
	}
}
//Zwraca Obecną wartość karty
//---------------------
int Card::ReturnValue()
{
	return currentValue;
}
//Zwraca koszt karty
//--------------------
int Card::ReturnCost()
{
	return cost;
}
//Zwraca rząd karty
//-------------------
int Card::ReturnRow()
{
	return row;
}
//Zwraca wartość otrzymanych obrażeń
//----------------------------------
int Card::ReturnReceivedDamage()
{
	return recievedDamage;
}
//Zwraca mnożnik karty
//---------------------------
int Card::ReturnMultiplayer()
{
	return multiplayer;
}
//Zwraca Umiejętność karty
//------------------------
Skills Card::ReturnSkill()
{
	return skill;
}
//Czy karta jest bohaterem
//------------------------
bool Card::ReturnIsHero()
{
	return heroCard;
}
std::string Card::ReturnName()
{
	return name;
}
//Zwraca pozycje wierzchołków ostatnio narysowanej karty
//------------------------------------------------------
RectanglePoints Card::ReturnVertexesPosition()
{
	return vertexes;
}
//Zwiększa (lub zmniejsz jesli liczba jest ujemna) otrzymane obrażenia
//-------------------------
void Card::AddDamage(int x)
{
	recievedDamage += x;
	CountValue();
}
void Card::ChangeMultiplayer(int x)
{
	multiplayer = x;
	CountValue();
}
//Oblicza wartość karty
//---------------------
void Card::CountValue()
{
	currentValue = (value - recievedDamage) * multiplayer;
}
//Zwraca pozycję X z względu na procent
//-------------------------------------
float Card::PosX(float x)
{
	return (settings::ScrWidth() * x);
}
//Zwraca pozycję Y z względu na procent
//-------------------------------------
float Card::PosY(float y)
{
	return (settings::ScrHeight() * y);
}
//Porównywanie dwóch kard
//----------------------------------
bool Card::operator==(const Card& c)
{
	if (this->heroCard == c.heroCard && this->value == c.value
		&& this->cost == c.cost && this->row == c.row && this->name == c.name)
	{
		return true;
	}
	return false;
}
//Zwraca pozycje wierzchołków dla zwykłych wymiarów karty
//------------------------------------------------------------------
RectanglePoints Card::NormalCardVertexesPosition(float x1, float y1)
{
	float ImgSizeX = (PosX(x1 + 0.07) - PosX(x1)) / settings::ScrWidth();
	float DownEdgePos = y1 + (ImgSizeX * 1.1 * settings::ProportionScreenWH()) + (ImgSizeX * 0.3 * settings::ProportionScreenWH());
	RectanglePoints vertex;
	//Obliczanie pozycji wierzchołków
	vertex.P1 = { PosX(x1), PosY(y1) };
	vertex.P2 = { PosX(ImgSizeX * 1.1 + x1), PosY(y1) };
	vertex.P3 = { PosX(x1), PosY(DownEdgePos) };
	vertex.P4 = { PosX(ImgSizeX * 1.1 + x1), PosY(DownEdgePos) };
	return vertex;
}
//Porównywanie dwóch kard
//----------------------------------
bool Card::operator!=(const Card& c)
{
	if (this->heroCard != c.heroCard || this->value != c.value
		|| this->cost != c.cost || this->row != c.row || this->name != c.name)
	{
		return true;
	}
	return false;
}