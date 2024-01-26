#include <iostream>
#include <vector>
#include <allegro5/allegro.h>              
#include <allegro5/allegro_image.h>	
#include "Button.h"
#include "Skills.h"


#pragma once
class HowToPlay
{
private:
	ALLEGRO_DISPLAY* Display;
	int PressedButton;
	bool ChangeMenu;
	int mouseButton;
	//Przyciski
	Button MenuButton;
	Button CardButton;
	Button SkillButton;
	Button RulesButton;
	Button GameButton;
	Button ExitButton;
	Button NextPage;
	Button PrevPage;
	//Strona
	std::string Title;
	int LastPage;			//Ostatnia Podstrona
	int CurrentPage;		//Obecna Podstrona
	int Page;				//Strona
	int Category;			//Kategoria

	std::vector<Skills> SkillList;
public:
	enum Section {menu,card,skill,rules,game};
	HowToPlay(ALLEGRO_DISPLAY* Disp);				//Konstruktor
	int Loop();										//Pętla poradnika
	void Next(float mouseX, float mouseY);			//Następna strona
	void Prev(float mouseX, float mouseY);			//Poprzednia strona
	void MenuTutorial(float mouseX, float mouseY);	//Poradnik Menu
	void CardTutorial(float mouseX, float mouseY);	//Opis karty
	void SkillTutorial(float mouseX, float mouseY);	//Opis umiejetności kart
	void RulesTutorial(float mouseX, float mouseY);	//Zasady gry
	void GameTutorial(float mouseX, float mouseY);	//Poradnik gry
	int ExitTutorial(float mouseX, float mouseY);	//Wyjscie
	void Skill();									//Rysuje Dane umiejętności
};

