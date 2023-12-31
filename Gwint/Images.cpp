#include "Images.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//Deklaracja Postaci
ALLEGRO_BITMAP* Images::Empty;
ALLEGRO_BITMAP* Images::Bert;
ALLEGRO_BITMAP* Images::BrotherOfBlood;
ALLEGRO_BITMAP* Images::Carnothaurus;
ALLEGRO_BITMAP* Images::Crocolisk;
ALLEGRO_BITMAP* Images::FrozenChempion;
ALLEGRO_BITMAP* Images::Golem;
ALLEGRO_BITMAP* Images::Guts;
ALLEGRO_BITMAP* Images::Juggernaut;
ALLEGRO_BITMAP* Images::Liniux;
ALLEGRO_BITMAP* Images::Mimic;
ALLEGRO_BITMAP* Images::Mortar;
ALLEGRO_BITMAP* Images::FrozenDog;
ALLEGRO_BITMAP* Images::Omobamidele;
ALLEGRO_BITMAP* Images::Parasaurus;
ALLEGRO_BITMAP* Images::Raptor;
ALLEGRO_BITMAP* Images::Reptile;
ALLEGRO_BITMAP* Images::Sarco;
ALLEGRO_BITMAP* Images::Seraphin;
ALLEGRO_BITMAP* Images::Shielder;
ALLEGRO_BITMAP* Images::Terizino;
ALLEGRO_BITMAP* Images::Tytus;
ALLEGRO_BITMAP* Images::Zenon;
//Deklaracja cz�ci kart
ALLEGRO_BITMAP* Images::HeroCharacterFrame;
ALLEGRO_BITMAP* Images::CharacterFrame;
ALLEGRO_BITMAP* Images::StatFrame;
ALLEGRO_BITMAP* Images::NameFrame;
ALLEGRO_BITMAP* Images::DescrFrame;
ALLEGRO_BITMAP* Images::ReverseCard;
ALLEGRO_BITMAP* Images::StatCircle;
ALLEGRO_BITMAP* Images::MeleeCircle;
ALLEGRO_BITMAP* Images::RangeCircle;
//Deklaracja cz�ci interfejsu gry
ALLEGRO_BITMAP* Images::EmptyCrystal;
ALLEGRO_BITMAP* Images::YellowCrystal;
ALLEGRO_BITMAP* Images::PurpleCrystal;
//Deklaracja ikon umiej�tno�ci
ALLEGRO_BITMAP* Images::None;
ALLEGRO_BITMAP* Images::Brotherhood;
ALLEGRO_BITMAP* Images::Medic;
ALLEGRO_BITMAP* Images::Spy;
ALLEGRO_BITMAP* Images::Executioner;
ALLEGRO_BITMAP* Images::Archer;
ALLEGRO_BITMAP* Images::Horde;
ALLEGRO_BITMAP* Images::Thief;
ALLEGRO_BITMAP* Images::Transport;
ALLEGRO_BITMAP* Images::SummonerMortar;
ALLEGRO_BITMAP* Images::DeadEater;
ALLEGRO_BITMAP* Images::Conflagration;
ALLEGRO_BITMAP* Images::Banish;

//Za�adowuje obrazki
//-----------------------
void Images::SetImages()
{
	//Postacie
	Images::Empty = al_load_bitmap("images/Characters/Empty.png");
	Images::Bert = al_load_bitmap("images/Characters/Bert.png");
	Images::BrotherOfBlood = al_load_bitmap("images/Characters/Brat Krwi.png");
	Images::Carnothaurus = al_load_bitmap("images/Characters/Karnotaur.png");
	Images::Crocolisk = al_load_bitmap("images/Characters/Krokoliszek.png");
	Images::FrozenChempion = al_load_bitmap("images/Characters/Czempion Kultu.png");
	Images::Golem = al_load_bitmap("images/Characters/Golem.png");
	Images::Guts = al_load_bitmap("images/Characters/Jelito.png");
	Images::Juggernaut = al_load_bitmap("images/Characters/Moloch.png");
	Images::Liniux = al_load_bitmap("images/Characters/Liniux.png");
	Images::Mimic = al_load_bitmap("images/Characters/Mimik.png");
	Images::Mortar = al_load_bitmap("images/Characters/Mozdzierz.png");
	Images::FrozenDog = al_load_bitmap("images/Characters/Ogar Mrozu.png");
	Images::Omobamidele = al_load_bitmap("images/Characters/Omobamidele.png");
	Images::Parasaurus = al_load_bitmap("images/Characters/Parazaur.png");
	Images::Raptor = al_load_bitmap("images/Characters/Raptor.png");
	Images::Reptile = al_load_bitmap("images/Characters/Reptilian.png");
	Images::Sarco = al_load_bitmap("images/Characters/Sarkozuch.png");
	Images::Seraphin = al_load_bitmap("images/Characters/Serafin.png");
	Images::Shielder = al_load_bitmap("images/Characters/Tarczownik.png");
	Images::Terizino = al_load_bitmap("images/Characters/Terizino.png");
	Images::Tytus = al_load_bitmap("images/Characters/Tytus.png");
	Images::Zenon = al_load_bitmap("images/Characters/Zenon.png");
	//Deklaracja cz�ci kart
	Images::CharacterFrame = al_load_bitmap("images/UI/CharacterFrame.png");
	Images::HeroCharacterFrame = al_load_bitmap("images/UI/CharacterFrameGold.png");
	Images::StatFrame = al_load_bitmap("images/UI/StatFrame.png");
	Images::NameFrame = al_load_bitmap("images/UI/textFrame.png");
	Images::DescrFrame = al_load_bitmap("images/UI/SkillDescr.png");
	Images::ReverseCard = al_load_bitmap("images/UI/ReverseCard.png");
	Images::StatCircle = al_load_bitmap("images/Skills/StatCircle.png");
	Images::MeleeCircle = al_load_bitmap("images/Skills/Melee Circle.png");
	Images::RangeCircle = al_load_bitmap("images/Skills/Range Circle.png");
	//Deklaracja cz�ci interfejsu gry
	Images::EmptyCrystal = al_load_bitmap("images/UI/Empty Crystal.png");
	Images::YellowCrystal = al_load_bitmap("images/UI/YellowCrystal.png");
	Images::PurpleCrystal = al_load_bitmap("images/UI/PurpleCrystal.png");
	//Deklaracja ikon umiej�tno�ci
	Images::None = al_load_bitmap("images/Skills/StatCircle.png");
	Images::Brotherhood = al_load_bitmap("images/Skills/BrotherhoodSkill.png");
	Images::Medic = al_load_bitmap("images/Skills/MedicSkill.png");
	Images::Spy = al_load_bitmap("images/Skills/SpySkill.png");
	Images::Executioner = al_load_bitmap("images/Skills/ExecutionSkill.png");
	Images::Archer = al_load_bitmap("images/Skills/ArcherSkill.png");
	Images::Horde = al_load_bitmap("images/Skills/HordeSkill.png");
	Images::Thief = al_load_bitmap("images/Skills/ThiefSkill.png");
	Images::Transport = al_load_bitmap("images/Skills/TransportSkill.png");
	Images::SummonerMortar = al_load_bitmap("images/Skills/MortarSkill.png");
	Images::DeadEater = al_load_bitmap("images/Skills/DeadEaterSkill.png");
	Images::Conflagration = al_load_bitmap("images/Skills/DeadSkill.png");
	Images::Banish = al_load_bitmap("images/Skills/BanishSkill.png");
}

