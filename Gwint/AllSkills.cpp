#include "AllSkills.h"
#include "Images.h"

int AllSkills::none;
int AllSkills::brotherhood;
int AllSkills::medic;
int AllSkills::spy;
int AllSkills::executioner;
int AllSkills::archer;
int AllSkills::horde;
int AllSkills::thief;
int AllSkills::transport;
int AllSkills::summonerMortar;
int AllSkills::deadEater;
int AllSkills::conflagration;
int AllSkills::banish;
int AllSkills::goldDeadEater;
int AllSkills::goldMedic;

Skills AllSkills::None;
Skills AllSkills::Brotherhood;
Skills AllSkills::Medic;
Skills AllSkills::Spy;
Skills AllSkills::Executioner;
Skills AllSkills::Archer;
Skills AllSkills::Horde;
Skills AllSkills::Thief;
Skills AllSkills::Transport;
Skills AllSkills::SummonerMortar;
Skills AllSkills::DeadEater;
Skills AllSkills::Conflagration;
Skills AllSkills::Banish;
Skills AllSkills::GoldDeadEater;
Skills AllSkills::GoldMedic;

void AllSkills::SetSkills()
{
	//Id umiejętności
	AllSkills::none = 0;
	AllSkills::brotherhood = 1;
	AllSkills::medic = 2;
	AllSkills::spy = 3;
	AllSkills::executioner = 4;
	AllSkills::archer = 5;
	AllSkills::horde = 6;
	AllSkills::thief = 7;
	AllSkills::transport = 8;
	AllSkills::summonerMortar = 9;
	AllSkills::deadEater = 10;
	AllSkills::conflagration = 11;
	AllSkills::banish = 12;
	AllSkills::goldDeadEater = 13;
	AllSkills::goldMedic = 14;
	//Umiejętności
	None = Skills(none, "Brak", "", Images::None);
	Brotherhood = Skills(brotherhood, "Braterstwo", "Zwiększa dwukrotnie wartość karty jeśli w tym samy rzędzie znajduje się ta sama karta", Images::Brotherhood);
	Medic = Skills(medic, "Medyk", "Wskrzesza wybraną kartę z cmentarza (nie działa na złote karty)", Images::Medic);
	Spy = Skills(spy, "Szpieg", "Dobiera 2 karty ale zagrywany jest po stronie przeciwnika", Images::Spy);
	Executioner = Skills(executioner, "Egzekutor", "Zabija najsilniejszego przeciwnika", Images::Executioner);
	Archer = Skills(archer, "Strzelec", "Zmniejsza maksymalną siłę wrogiej karty o 2", Images::Archer);
	Horde = Skills(horde, "Wataha", "Przywołuje kartę tego samego typu", Images::Horde);
	Thief = Skills(thief, "Złodziej", "Zabiera i zagrywa kartę z tali przeciwnika", Images::Thief);
	Transport = Skills(transport, "Wierzchowiec", "Pozwala usunąć własną kartę i dodać ją do ręki", Images::Transport);
	SummonerMortar = Skills(summonerMortar, "Przywoływacz", "Przywołuje Moździerz", Images::SummonerMortar);
	DeadEater = Skills(deadEater, "Trupojad", "Pożera kartę z cmentarza i dodaje wartość pożartej karty do siebie (nie działa  na złote karty)", Images::DeadEater);
	Conflagration = Skills(conflagration, "Pożoga", "Niszczy najsilniejsze karty na stole (karta nie niszczy siebie samej)", Images::Conflagration);
	Banish = Skills(banish, "Wygnanie", "Przenosi wszystkie karty z rąk graczy do cmentarza i dobiera tyle samo kart ile zostało przeniesionych", Images::Banish);
	GoldDeadEater = Skills(goldDeadEater, "Trupojad", "Pożera kartę z cmentarza i dodaje wartość pożartej karty do siebie (działa również na złote karty)", Images::GoldenDeadEater);
	GoldMedic = Skills(goldMedic, "Medyk", "Wskrzesza wybraną kartę z cmentarza (działa również na złote karty)", Images::GoldenMedic);
}