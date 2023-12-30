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
	static Card Bert;
	static Card BrotherOfBlood;
	static Card FrozenChempion;
	static Card Golem;
	static Card Guts;
	static Card Liniux;
	static Card Mimic;
	static Card Mortar;
	static Card FrozenDog;
	static Card Omobamidele;
	static Card Parasaurus;
	static Card Raptor;
	static Card Reptile;
	static Card Sarco;
	static Card Terizino;
	static Card Tytus;
	static Card Zenon;
	static void SetCards();
	static std::vector<Card> ReturnAllCards();
};

