#include <iostream>
#include <allegro5/allegro.h>				//Podstawowe komendy
#include "Colors.h"                         //Kolory


#pragma once
class Menu
{
private:
		ALLEGRO_DISPLAY* Display;
public:
	int MenuLoop();
	float ScreenWidth;
	float ScreenHeight;
	Menu(ALLEGRO_DISPLAY* Disp, float DisplayWidth, float DisplayHeight);
};

