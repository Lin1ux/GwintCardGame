#include <iostream>
#include<vector>
#include <allegro5/allegro.h>              
#include <allegro5/allegro_image.h>	


#pragma once
class HowToPlay
{
private:
	ALLEGRO_DISPLAY* Display;
	int PressedButton;
	bool ChangeMenu;
	int mouseButton;
public:
	HowToPlay(ALLEGRO_DISPLAY* Disp);
	int Loop();
};

