#include "Fonts.h"
#include <allegro5/allegro_ttf.h> //Wczytywanie czcionek .ttf
#include <allegro5/allegro_font.h> //Czcionki
#include "settings.h"

ALLEGRO_FONT* Fonts::NameFont;
ALLEGRO_FONT* Fonts::ValueFont;
ALLEGRO_FONT* Fonts::SmallValueFont;

void Fonts::SetFonts()
{
	Fonts::NameFont = al_load_font("fonts/Baloo-Regular.ttf", settings::ScrWidth() * 0.015, NULL);
	Fonts::ValueFont = al_load_font("fonts/Baloo-Regular.ttf", settings::ScrWidth() * 0.018, NULL);
	Fonts::SmallValueFont = al_load_font("fonts/Baloo-Regular.ttf", settings::ScrWidth() * 0.014, NULL);
}
