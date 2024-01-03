#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //obrazki
#pragma once

class Images
{
	//Postacie
public:
	//Characters
	static ALLEGRO_BITMAP* Bert;
	static ALLEGRO_BITMAP* BrotherOfBlood;
	static ALLEGRO_BITMAP* FrozenChempion;
	static ALLEGRO_BITMAP* Golem;
	static ALLEGRO_BITMAP* Guts;
	static ALLEGRO_BITMAP* Liniux;
	static ALLEGRO_BITMAP* Mimic;
	static ALLEGRO_BITMAP* Mortar;
	static ALLEGRO_BITMAP* FrozenDog;
	static ALLEGRO_BITMAP* Omobamidele;
	static ALLEGRO_BITMAP* Parasaurus;
	static ALLEGRO_BITMAP* Raptor;
	static ALLEGRO_BITMAP* Reptile;
	static ALLEGRO_BITMAP* Sarco;
	static ALLEGRO_BITMAP* Terizino;
	static ALLEGRO_BITMAP* Tytus;
	static ALLEGRO_BITMAP* Zenon;
	//Card Parts
	static ALLEGRO_BITMAP* CharacterFrame;
	static ALLEGRO_BITMAP* HeroCharacterFrame;
	static ALLEGRO_BITMAP* StatFrame;
	static ALLEGRO_BITMAP* NameFrame;
	static ALLEGRO_BITMAP* DescrFrame;
	static ALLEGRO_BITMAP* StatCircle;
	static ALLEGRO_BITMAP* MeleeCircle;
	static ALLEGRO_BITMAP* RangeCircle;
	//Game UI
	static ALLEGRO_BITMAP* EmptyCrystal;
	static ALLEGRO_BITMAP* YellowCrystal;
	static ALLEGRO_BITMAP* PurpleCrystal;
	 
	//static ALLEGRO_BITMAP* CharacterFrame;
	//static ALLEGRO_BITMAP* CharacterFrame;

	static void SetImages();
};

