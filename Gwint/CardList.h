#include "Card.h"

#include <vector>

#include "AllSkills.h"
#include "Images.h"
//#include <allegro5/allegro.h>
//#include <allegro5/allegro_image.h> //obrazki

#pragma once
class CardList
{
public:
	static int front;
	static int back;
	static Card None;
	static Card Unknown;
	static Card Bert;
	static Card BrotherOfBlood;
	static Card Carnotaur;
	static Card Crocolisk;
	static Card Fang;	
	static Card FrozenChempion;
	static Card FrozenDog;
	static Card Golem;
	static Card Guts;
	static Card Juggernaut;
	static Card Liniux;
	static Card MasterOfIllusion;
	static Card Mimic;
	static Card Mortar;
	static Card Omobamidele;
	static Card Parasaurus;
	static Card Raptor;
	static Card Reptile;
	static Card Sarco;
	static Card Seraphin;
	static Card Shielder;
	static Card Terizino;
	static Card Terryffier;
	static Card Tytus;
	static Card Zenon;
	static void SetCards();
	static std::vector<Card> ReturnAllCards();
};

