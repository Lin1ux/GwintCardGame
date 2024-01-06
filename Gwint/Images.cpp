#include "Images.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//Deklaracja Postaci
ALLEGRO_BITMAP* Images::Empty;
ALLEGRO_BITMAP* Images::Bert;
ALLEGRO_BITMAP* Images::BrotherOfBlood;
ALLEGRO_BITMAP* Images::FrozenChempion;
ALLEGRO_BITMAP* Images::Golem;
ALLEGRO_BITMAP* Images::Guts;
ALLEGRO_BITMAP* Images::Liniux;
ALLEGRO_BITMAP* Images::Mimic;
ALLEGRO_BITMAP* Images::Mortar;
ALLEGRO_BITMAP* Images::FrozenDog;
ALLEGRO_BITMAP* Images::Omobamidele;
ALLEGRO_BITMAP* Images::Parasaurus;
ALLEGRO_BITMAP* Images::Raptor;
ALLEGRO_BITMAP* Images::Reptile;
ALLEGRO_BITMAP* Images::Sarco;
ALLEGRO_BITMAP* Images::Terizino;
ALLEGRO_BITMAP* Images::Tytus;
ALLEGRO_BITMAP* Images::Zenon;
//Deklaracja czêœci kart
ALLEGRO_BITMAP* Images::HeroCharacterFrame;
ALLEGRO_BITMAP* Images::CharacterFrame;
ALLEGRO_BITMAP* Images::StatFrame;
ALLEGRO_BITMAP* Images::NameFrame;
ALLEGRO_BITMAP* Images::DescrFrame;
ALLEGRO_BITMAP* Images::StatCircle;
ALLEGRO_BITMAP* Images::MeleeCircle;
ALLEGRO_BITMAP* Images::RangeCircle;
//Deklaracja czêœci interfejsu gry
ALLEGRO_BITMAP* Images::EmptyCrystal;
ALLEGRO_BITMAP* Images::YellowCrystal;
ALLEGRO_BITMAP* Images::PurpleCrystal;

//Za³adowuje obrazki
//-----------------------
void Images::SetImages()
{
	//Postacie
	Images::Empty = al_load_bitmap("images/Empty.png");
	Images::Bert = al_load_bitmap("images/Bert.png");
	Images::BrotherOfBlood = al_load_bitmap("images/Brat Krwi.png");
	Images::FrozenChempion = al_load_bitmap("images/Czempion Kultu.png");
	Images::Golem = al_load_bitmap("images/Golem.png");
	Images::Guts = al_load_bitmap("images/Jelito.png");
	Images::Liniux = al_load_bitmap("images/Liniux.png");
	Images::Mimic = al_load_bitmap("images/Mimik.png");
	Images::Mortar = al_load_bitmap("images/Mozdzierz.png");
	Images::FrozenDog = al_load_bitmap("images/Ogar Mrozu.png");
	Images::Omobamidele = al_load_bitmap("images/Omobamidele.png");
	Images::Parasaurus = al_load_bitmap("images/Parazaur.png");
	Images::Raptor = al_load_bitmap("images/Raptor.png");
	Images::Reptile = al_load_bitmap("images/Reptilian.png");
	Images::Sarco = al_load_bitmap("images/Sarkozuch.png");
	Images::Terizino = al_load_bitmap("images/Terizino.png");
	Images::Tytus = al_load_bitmap("images/Tytus.png");
	Images::Zenon = al_load_bitmap("images/Zenon.png");
	//Deklaracja czêœci kart
	Images::CharacterFrame = al_load_bitmap("images/CharacterFrame.png");
	Images::HeroCharacterFrame = al_load_bitmap("images/CharacterFrameGold.png");
	Images::StatFrame = al_load_bitmap("images/StatFrame.png");
	Images::NameFrame = al_load_bitmap("images/textFrame.png");
	Images::DescrFrame = al_load_bitmap("images/SkillDescr.png");
	Images::StatCircle = al_load_bitmap("images/StatCircle.png");
	Images::MeleeCircle = al_load_bitmap("images/Melee Circle.png");
	Images::RangeCircle = al_load_bitmap("images/Range Circle.png");
	//Deklaracja czêœci interfejsu gry
	Images::EmptyCrystal = al_load_bitmap("images/Empty Crystal.png");
	Images::YellowCrystal = al_load_bitmap("images/YellowCrystal.png");
	Images::PurpleCrystal = al_load_bitmap("images/PurpleCrystal.png");
}

