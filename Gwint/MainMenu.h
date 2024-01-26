#include "Button.h"
#include <vector>

#pragma once
class MainMenu
{
private:
	int ChangeMenu;											//Czy będzie zmieniane menu
	int mouseButton;										//Stan myszki
	ALLEGRO_DISPLAY* Display;								//Ekran		
	Button ExitButton;										//Wyjście
	Button HowToPlay;										//Poradnik
	Button PVPGame;											//Przycisk startu gry
	int ExitButtonActivation(float mouseX,float mouseY);	//Przycisk wyjścia
	int HowToPlayActivation(float mouseX, float mouseY);	//Poradnik
	int PVPGameActivation(float mouseX, float mouseY);		//Start gry
public:
	MainMenu(ALLEGRO_DISPLAY* Disp, float DisplayWidth, float DisplayHeight);			//Konstruktor
	int MenuLoop();				//Pętla gry
};

