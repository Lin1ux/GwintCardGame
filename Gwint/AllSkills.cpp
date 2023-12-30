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

Skills AllSkills::None;
Skills AllSkills::Brotherhood;
Skills AllSkills::Medic;
Skills AllSkills::Spy;
Skills AllSkills::Executioner;
Skills AllSkills::Archer;
Skills AllSkills::Horde;
Skills AllSkills::Thief;
Skills AllSkills::Transport;

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
	//Umiejętności
	None = Skills(none, "Brak", "Brak Umięjętności", Images::StatCircle);
	Brotherhood = Skills(brotherhood, "Braterstwo", "Zwiększa dwukrotnie wartość karty jeśli w tym samy rzędzie znajduje się ta sama karta", Images::StatCircle);
	Medic = Skills(medic, "Medyk", "Wskrzesza ostatnią odrzuconą kartę", Images::StatCircle);
	Spy = Skills(spy, "Szpieg", "Dobiera 2 karty ale zagrywany jest po stronie przeciwnika", Images::StatCircle);
	Executioner = Skills(executioner, "Egzekutor", "Zabija najsilniejszego przeciwnika", Images::StatCircle);
	Archer = Skills(archer, "Strzelec", "Zmniejsza maksymalną siłę wrogiej karty o 2", Images::StatCircle);
	Horde = Skills(horde, "Wataha", "Przywołuje kartę o tego samego typu", Images::StatCircle);
	Thief = Skills(thief, "Złodziej", "Zabiera i zagrywa kartę z tali przeciwnika", Images::StatCircle);
	Transport = Skills(transport, "Wierzchowiec", "Pozwala usunąć własną kartę i dodać ją do ręki", Images::StatCircle);
}