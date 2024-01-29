#include "Images.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//Deklaracja Postaci
ALLEGRO_BITMAP* Images::Unknown;
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
ALLEGRO_BITMAP* Images::MasterOfIllusion;
ALLEGRO_BITMAP* Images::Mimic;
ALLEGRO_BITMAP* Images::Mortar;
ALLEGRO_BITMAP* Images::Fang;
ALLEGRO_BITMAP* Images::FrozenDog;
ALLEGRO_BITMAP* Images::Omobamidele;
ALLEGRO_BITMAP* Images::Parasaurus;
ALLEGRO_BITMAP* Images::Raptor;
ALLEGRO_BITMAP* Images::Reptile;
ALLEGRO_BITMAP* Images::Sarco;
ALLEGRO_BITMAP* Images::Seraphin;
ALLEGRO_BITMAP* Images::Shielder;
ALLEGRO_BITMAP* Images::Terizino;
ALLEGRO_BITMAP* Images::Terryfier;
ALLEGRO_BITMAP* Images::Tytus;
ALLEGRO_BITMAP* Images::Zenon;
//Deklaracja czêœci kart
ALLEGRO_BITMAP* Images::HeroCharacterFrame;
ALLEGRO_BITMAP* Images::CharacterFrame;
ALLEGRO_BITMAP* Images::StatFrame;
ALLEGRO_BITMAP* Images::NameFrame;
ALLEGRO_BITMAP* Images::DescrFrame;
ALLEGRO_BITMAP* Images::LongDescrFrame;
ALLEGRO_BITMAP* Images::ReverseCard;
ALLEGRO_BITMAP* Images::RedReverseCard;
ALLEGRO_BITMAP* Images::BlueReverseCard;
ALLEGRO_BITMAP* Images::StatCircle;
ALLEGRO_BITMAP* Images::MeleeCircle;
ALLEGRO_BITMAP* Images::RangeCircle;
//Deklaracja czêœci interfejsu gry
ALLEGRO_BITMAP* Images::Cursor;
ALLEGRO_BITMAP* Images::EmptyCrystal;
ALLEGRO_BITMAP* Images::YellowCrystal;
ALLEGRO_BITMAP* Images::PurpleCrystal;
ALLEGRO_BITMAP*  Images::Tansparent;
ALLEGRO_BITMAP* Images::SmallButton;
//Deklaracja t³a
ALLEGRO_BITMAP* Images::MenuBackground;
ALLEGRO_BITMAP* Images::GameBeginBackground;
ALLEGRO_BITMAP* Images::RedGameBackground;
ALLEGRO_BITMAP* Images::BlueGameBackground;
ALLEGRO_BITMAP* Images::GraveyardBackground;
//Deklaracja ikon umiejêtnoœci
ALLEGRO_BITMAP* Images::None;
ALLEGRO_BITMAP* Images::Brotherhood;
ALLEGRO_BITMAP* Images::Medic;
ALLEGRO_BITMAP* Images::GoldenMedic;
ALLEGRO_BITMAP* Images::Spy;
ALLEGRO_BITMAP* Images::Executioner;
ALLEGRO_BITMAP* Images::Archer;
ALLEGRO_BITMAP* Images::Horde;
ALLEGRO_BITMAP* Images::Thief;
ALLEGRO_BITMAP* Images::Transport;
ALLEGRO_BITMAP* Images::SummonerMortar;
ALLEGRO_BITMAP* Images::DeadEater;
ALLEGRO_BITMAP* Images::GoldenDeadEater;
ALLEGRO_BITMAP* Images::Slayer;
ALLEGRO_BITMAP* Images::Banish;


//Za³adowuje obrazki
//-----------------------
void Images::SetImages()
{
	//Postacie
	Images::Empty = al_load_bitmap("images/Characters/Empty.png");
	Images::Unknown = al_load_bitmap("images/Characters/Unknown.png");
	Images::Bert = al_load_bitmap("images/Characters/Bert.png");
	Images::BrotherOfBlood = al_load_bitmap("images/Characters/Brat Krwi.png");
	Images::Carnothaurus = al_load_bitmap("images/Characters/Karnotaur.png");
	Images::Crocolisk = al_load_bitmap("images/Characters/Krokoliszek.png");
	Images::FrozenChempion = al_load_bitmap("images/Characters/Czempion Kultu.png");
	Images::Golem = al_load_bitmap("images/Characters/Golem.png");
	Images::Guts = al_load_bitmap("images/Characters/Jelito.png");
	Images::Juggernaut = al_load_bitmap("images/Characters/Moloch.png");
	Images::Liniux = al_load_bitmap("images/Characters/Liniux.png");
	Images::MasterOfIllusion = al_load_bitmap("images/Characters/MistrzIluzji.png");
	Images::Mimic = al_load_bitmap("images/Characters/Mimik.png");
	Images::Mortar = al_load_bitmap("images/Characters/Mozdzierz.png");
	Images::Fang = al_load_bitmap("images/Characters/Kiel.png");
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
	Images::Terryfier = al_load_bitmap("images/Characters/Przeraza.png");
	Images::Zenon = al_load_bitmap("images/Characters/Zenon.png");
	//Deklaracja czêœci kart
	Images::CharacterFrame = al_load_bitmap("images/UI/CharacterFrame.png");
	Images::HeroCharacterFrame = al_load_bitmap("images/UI/CharacterFrameGold.png");
	Images::StatFrame = al_load_bitmap("images/UI/StatFrame.png");
	Images::NameFrame = al_load_bitmap("images/UI/textFrame.png");
	Images::DescrFrame = al_load_bitmap("images/UI/SkillDescr.png");
	Images::LongDescrFrame = al_load_bitmap("images/UI/LongDescr.png");
	Images::ReverseCard = al_load_bitmap("images/UI/ReverseCard.png");
	Images::RedReverseCard = al_load_bitmap("images/UI/RedReverseCard.png");
	Images::BlueReverseCard = al_load_bitmap("images/UI/BlueReverseCard.png");
	Images::StatCircle = al_load_bitmap("images/Skills/StatCircle.png");
	Images::MeleeCircle = al_load_bitmap("images/Skills/Melee Circle.png");
	Images::RangeCircle = al_load_bitmap("images/Skills/Range Circle.png");
	//Deklaracja czêœci interfejsu gry
	Images::Cursor = al_load_bitmap("images/UI/Cursor.png");
	Images::EmptyCrystal = al_load_bitmap("images/UI/Empty Crystal.png");
	Images::YellowCrystal = al_load_bitmap("images/UI/YellowCrystal.png");
	Images::PurpleCrystal = al_load_bitmap("images/UI/PurpleCrystal.png");
	Images::Tansparent = al_load_bitmap("images/UI/Transparent.png");
	Images::SmallButton = al_load_bitmap("images/UI/smallButton.png");
	//Deklaracja t³a
	Images::MenuBackground = al_load_bitmap("images/UI/Menu Background.png");
	Images::GameBeginBackground = al_load_bitmap("images/UI/begin Background.png");
	Images::RedGameBackground = al_load_bitmap("images/UI/RedGameBackground.png");
	Images::BlueGameBackground = al_load_bitmap("images/UI/BlueGameBackground.png");
	Images::GraveyardBackground = al_load_bitmap("images/UI/GraveyardBackground.png");
	//Deklaracja ikon umiejêtnoœci
	Images::None = al_load_bitmap("images/Skills/StatCircle.png");
	Images::Brotherhood = al_load_bitmap("images/Skills/BrotherhoodSkill.png");
	Images::Medic = al_load_bitmap("images/Skills/MedicSkill.png");
	Images::GoldenMedic = al_load_bitmap("images/Skills/MedicSkillG.png");
	Images::Spy = al_load_bitmap("images/Skills/SpySkill.png");
	Images::Executioner = al_load_bitmap("images/Skills/ExecutionSkill.png");
	Images::Archer = al_load_bitmap("images/Skills/ArcherSkill.png");
	Images::Horde = al_load_bitmap("images/Skills/HordeSkill.png");
	Images::Thief = al_load_bitmap("images/Skills/ThiefSkill.png");
	Images::Transport = al_load_bitmap("images/Skills/TransportSkill.png");
	Images::SummonerMortar = al_load_bitmap("images/Skills/MortarSkill.png");
	Images::DeadEater = al_load_bitmap("images/Skills/DeadEaterSkill.png");
	Images::GoldenDeadEater = al_load_bitmap("images/Skills/DeadEaterSkillG.png");
	Images::Slayer = al_load_bitmap("images/Skills/DeadSkill.png");
	Images::Banish = al_load_bitmap("images/Skills/BanishSkill.png");
}

