#include <allegro5/allegro.h> //Podstawowe komendy
#include <allegro5/allegro_ttf.h> //Wczytywanie czcionek .ttf
#include <allegro5/allegro_font.h> //Czcionki

#pragma once
class Fonts
{
public:
	static ALLEGRO_FONT* NameFont;
	static ALLEGRO_FONT* ValueFont;
	static ALLEGRO_FONT* SmallValueFont;
	static void SetFonts();
};

