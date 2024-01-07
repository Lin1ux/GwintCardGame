#include "CardList.h"

#include <vector>

#include "Card.h"
#include "Images.h"
#include "AllSkills.h"

int CardList::front;
int CardList::back;
Card CardList::Bert;
Card CardList::BrotherOfBlood;
Card CardList::FrozenChempion;
Card CardList::Golem;
Card CardList::Guts;
Card CardList::Liniux;
Card CardList::Mimic;
Card CardList::Mortar;
Card CardList::FrozenDog;
Card CardList::Omobamidele;
Card CardList::Parasaurus;
Card CardList::Raptor;
Card CardList::Reptile;
Card CardList::Sarco;
Card CardList::Terizino;
Card CardList::Tytus;
Card CardList::Zenon;

//Ustawia wartości dla wszystkich kart
//------------------------------------
void CardList::SetCards()
{
	front = 1;
	back = 2;
	AllSkills::SetSkills();			//Upewnienie, że wszystkie umiejętności zostały ustawione
	//Ustawianie danych kart
	Bert = Card(false, 2, 3,10, AllSkills::None, "Bert", Images::Bert);
	BrotherOfBlood = Card(false, 1, 8,30, AllSkills::None, "Brat Krwi", Images::BrotherOfBlood);
	FrozenChempion = Card(false, 1, 5, 20, AllSkills::None, "Czempion", Images::FrozenChempion);
	Golem = Card(false, 1, 4, 15, AllSkills::None, "Golem", Images::Golem);
	Guts = Card(true, 1, 9, 50, AllSkills::Executioner, "Jelito", Images::Guts);
	Liniux = Card(true, 1, 8, 50, AllSkills::Thief, "Liniux", Images::Liniux);
	Mimic = Card(false, 1, 2, 30, AllSkills::Thief, "Mimik", Images::Mimic);
	Mortar = Card(false, 2, 4, 20, AllSkills::Archer, "Moździerz", Images::Mortar);
	FrozenDog = Card(false, 1, 4, 30, AllSkills::Horde, "Ogar Mrozu", Images::FrozenDog);
	Omobamidele = Card(true, 2, 7, 40, AllSkills::Archer, "Omobamidele", Images::Omobamidele);
	Parasaurus = Card(false, 1, 1, 20, AllSkills::Transport, "Parazaur", Images::Parasaurus);
	Raptor = Card(false, 1, 3, 25, AllSkills::Brotherhood, "Raptor", Images::Raptor);
	Reptile = Card(false, 2, 4, 35, AllSkills::Brotherhood, "Reptilian", Images::Reptile);
	Sarco = Card(false, 1, 7, 35, AllSkills::None, "Sarcozuch", Images::Sarco);
	Terizino = Card(false, 1, 10, 45, AllSkills::None, "Terizinozaur", Images::Terizino);
	Tytus = Card(true, 2, 6, 30, AllSkills::SummonerMortar, "Tytus", Images::Tytus);
	Zenon = Card(true, 1, 4, 35, AllSkills::Medic, "Zenon", Images::Zenon);
}

//Zwraca vector z wszystkimi kartami
//------------------------------------------
std::vector<Card> CardList::ReturnAllCards()
{
	SetCards();							//Upewnienie, że wszystkie karty zostały ustawione
	std::vector<Card> AllCards;
	//Dodawanie kart
	AllCards.push_back(Bert);
	AllCards.push_back(Golem);
	AllCards.push_back(FrozenChempion);
	AllCards.push_back(Mortar);
	AllCards.push_back(Parasaurus);
	AllCards.push_back(Raptor);
	AllCards.push_back(BrotherOfBlood);
	AllCards.push_back(Mimic);
	AllCards.push_back(FrozenDog);
	AllCards.push_back(Tytus);
	AllCards.push_back(Reptile);
	AllCards.push_back(Sarco);
	AllCards.push_back(Zenon);
	AllCards.push_back(Omobamidele);
	AllCards.push_back(Terizino);
	AllCards.push_back(Guts);
	AllCards.push_back(Liniux);

	return AllCards;
}

/*std::vector<Card> CardList::ReturnAllCards();
{

	//reutrn 
}*/