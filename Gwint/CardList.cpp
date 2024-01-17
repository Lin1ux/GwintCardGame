#include "CardList.h"

#include <vector>
#include <algorithm>

#include "Card.h"
#include "Images.h"
#include "AllSkills.h"

int CardList::front;
int CardList::back;
Card CardList::Bert;
Card CardList::BrotherOfBlood;
Card CardList::Carnotaur;
Card CardList::Crocolisk;
Card CardList::Fang;
Card CardList::FrozenChempion;
Card CardList::FrozenDog;
Card CardList::Golem;
Card CardList::Guts;
Card CardList::Juggernaut;
Card CardList::Liniux;
Card CardList::MasterOfIllusion;
Card CardList::Mimic;
Card CardList::Mortar;
Card CardList::Omobamidele;
Card CardList::Parasaurus;
Card CardList::Raptor;
Card CardList::Reptile;
Card CardList::Sarco;
Card CardList::Seraphin;
Card CardList::Shielder;
Card CardList::Terizino;
Card CardList::Terryffier;
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
	Bert = Card(false, back, 3,5, AllSkills::None, "Bert", Images::Bert);
	BrotherOfBlood = Card(false, front, 4,35, AllSkills::DeadEater, "Brat Krwi", Images::BrotherOfBlood);
	Carnotaur = Card(false, front, 5, 40, AllSkills::Brotherhood, "Karnotaur", Images::Carnothaurus);
	Crocolisk = Card(false, front, 12, 40, AllSkills::None, "Krokoliszek", Images::Crocolisk);
	FrozenChempion = Card(false, front, 5, 15, AllSkills::None, "Czempion", Images::FrozenChempion);
	FrozenDog = Card(false, front, 4, 30, AllSkills::Horde, "Ogar Mrozu", Images::FrozenDog);
	Golem = Card(false, front, 6, 20, AllSkills::None, "Golem", Images::Golem);
	Guts = Card(true, front, 6, 45, AllSkills::GoldDeadEater, "Jelito", Images::Guts);
	Juggernaut = Card(false, front, 10, 45, AllSkills::Executioner, "Moloch", Images::Juggernaut);
	Liniux = Card(true, front, 8, 50, AllSkills::Banish, "Liniux", Images::Liniux);
	MasterOfIllusion = Card(false, front, 8, 45, AllSkills::Spy, "Mistrz Iluzji", Images::Liniux);
	Mimic = Card(false, front, 2, 45, AllSkills::Thief, "Mimik", Images::Mimic);
	Mortar = Card(false, back, 4, 15, AllSkills::Archer, "Moździerz", Images::Mortar);
	Omobamidele = Card(true, back, 7, 35, AllSkills::Archer, "Omobamidele", Images::Omobamidele);
	Parasaurus = Card(true, front, 1, 50, AllSkills::Transport, "Andrzej", Images::Parasaurus);
	Raptor = Card(false, front, 2, 20, AllSkills::Brotherhood, "Raptor", Images::Raptor);
	Reptile = Card(false, back, 4, 30, AllSkills::Brotherhood, "Reptilian", Images::Reptile);
	Sarco = Card(false, front, 4, 10, AllSkills::None, "Sarcozuch", Images::Sarco);
	Seraphin = Card(false, front, 8, 45, AllSkills::Medic, "Serafin", Images::Seraphin);
	Shielder = Card(false, front, 3, 25, AllSkills::Brotherhood, "Tarczownik", Images::Shielder);
	Fang = Card(false, back, 5,30,AllSkills::Archer,"Kieł",Images::Fang);
	Terizino = Card(false, front, 10, 35, AllSkills::None, "Terizinozaur", Images::Terizino);
	Terryffier = Card(false, front, 10, 45, AllSkills::Slayer, "Przeraza", Images::Terryfier);
	Tytus = Card(true, back, 6, 30, AllSkills::SummonerMortar, "Tytus", Images::Tytus);
	Zenon = Card(true, back, 4, 40, AllSkills::GoldMedic, "Zenon", Images::Zenon);
}

//Zwraca vector z wszystkimi kartami
//------------------------------------------
std::vector<Card> CardList::ReturnAllCards()
{
	SetCards();							//Upewnienie, że wszystkie karty zostały ustawione
	std::vector<Card> AllCards;
	//Dodawanie kart
	AllCards.push_back(Bert);
	AllCards.push_back(BrotherOfBlood);
	AllCards.push_back(Carnotaur);
	AllCards.push_back(Crocolisk);
	AllCards.push_back(FrozenChempion);
	AllCards.push_back(Golem);
	AllCards.push_back(Guts);
	AllCards.push_back(Juggernaut);
	AllCards.push_back(Liniux);
	AllCards.push_back(Mimic);
	AllCards.push_back(Mortar);
	AllCards.push_back(FrozenDog);
	AllCards.push_back(Omobamidele);
	AllCards.push_back(Parasaurus);
	AllCards.push_back(Raptor);
	AllCards.push_back(Reptile);
	AllCards.push_back(Sarco);
	AllCards.push_back(Shielder);
	AllCards.push_back(Seraphin);
	AllCards.push_back(Terizino);
	AllCards.push_back(Tytus);
	AllCards.push_back(Zenon);
	AllCards.push_back(Fang);
	AllCards.push_back(Terryffier);
	AllCards.push_back(MasterOfIllusion);

	sort(AllCards.begin(), AllCards.end(), [](Card& a, Card& b) { return (a.ReturnCost() < b.ReturnCost()); });

	return AllCards;
}

/*std::vector<Card> CardList::ReturnAllCards();
{

	//reutrn 
}*/