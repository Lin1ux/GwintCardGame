#include "OtherFunctions.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>			
#include <allegro5/allegro_font.h>			

#include "Fonts.h"
#include "Colors.h"

//Rysuje prostok¹t u¿ywaj¹c struktury "RectanglePoints"
//------------------------------------------------------------------------------------
void OtherFunctions::DrawRectangle(RectanglePoints Points, ALLEGRO_COLOR color, int t)
{
	al_draw_rectangle(Points.P1.x, Points.P1.y, Points.P4.x, Points.P4.y, color, t);
}
//Rysuje obraz u¿ywaj¹c struktur "Point"
//--------------------------------------------------------------------------------------------------------
void OtherFunctions::DrawImage(ALLEGRO_BITMAP* Image, Point Position, Point ImgSize, Point(ImgScaledSize))
{
	al_draw_scaled_bitmap(Image, 0, 0, ImgSize.x, ImgSize.y, Position.x, Position.y, ImgScaledSize.x, ImgScaledSize.y, NULL);
}
//Rysuje tekst na ramce
//------------------------------------------------------
void OtherFunctions::DrawTextImage(ALLEGRO_BITMAP* Image, Point Position, Point ImgSize, Point(ImgScaledSize), std::string text)
{
	DrawImage(Image, Position, ImgSize, ImgScaledSize);
	al_draw_text(Fonts::SmallValueFont, Colors::white, Position.x+ImgScaledSize.x/2, Position.y+ ImgScaledSize.y / 7, ALLEGRO_ALIGN_CENTER, text.c_str());
}
//Losuje liczbê z przedzia³u <min,max>
//---------------------------------------
int OtherFunctions::Random(int min, int max)
{
	max += 1;
	return rand() % (max - min) + min;
}
//Zwraca miejsce, w którym nale¿y wstawiæ obiekt aby by³ wyœrodkowany
//-------------------------------------------------------------------
float OtherFunctions::AlignCenter(float start, float end, float size)
{
	float realSize = end - start;
	float emptySpace = realSize - size;
	return start+emptySpace/2;
}



//al_draw_scaled_bitmap(Images::StatFrame, 0, 0, 330, 100, PosX(x1), PosY(DownEdgePos), PosX(ImgSizeX * 1.1), PosY(ImgSizeX * 0.3 * settings::ProportionScreenWH()), NULL);
