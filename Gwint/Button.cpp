#include "Button.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h> 

#include "settings.h"
#include "Colors.h"
#include "Images.h"
#include "Fonts.h"
#include "OtherFunctions.h"

//Pusty Konstruktor
//--------------
Button::Button()
{
	active = true;
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	Color = Colors::red;
	Image = Images::NameFrame;
	sizeX = 330;
	sizeY = 100;
	text = "";
}
//Konstruktor z punktami
//----------------------------------------------------
Button::Button(float X1, float Y1, float X2, float Y2)
{
	active = true;
	x1 = X1;
	y1 = Y1;
	x2 = X2;
	y2 = Y2;
	Color = Colors::red;
	Image = Images::NameFrame;
	sizeX = 330;
	sizeY = 100;
	text = "";
}
Button::Button(Point P1, Point P2)
{
	active = true;
	x1 = P1.x;
	y1 = P1.y;
	x2 = P2.x;
	y2 = P2.y;
	Color = Colors::red;
	Image = Images::NameFrame;
	sizeX = 330;
	sizeY = 100;
	text = "";
}

Button::Button(RectanglePoints Points)
{
	active = true;
	x1 = Points.P1.x;
	y1 = Points.P1.y;
	x2 = Points.P4.x;
	y2 = Points.P4.y;
	Color = Colors::red;
	Image = Images::NameFrame;
	sizeX = 330;
	sizeY = 100;
	text = "";
}
//Czy przycisk jest aktywny
//-------------------------
bool Button::IsActive()
{
	return active;
}
//Zmienia stan przycisku i zwraca nowy stan

bool Button::ChangeState(bool newState)
{
	active = newState;
	return active;
}
//Ustawia Obraz
//---------------------------------------------
void Button::SetImage(ALLEGRO_BITMAP* Newimage, int sx, int sy)
{
	Image = Newimage;
	sizeX = sx;
	sizeY = sy;
}
//Ustawia nowy tekst
void Button::SetText(std::string newText)
{
	text = newText;
}
//Rysuje wizualizacje hitboxa przycisku
//--------------------------------------
void Button::DrawHitbox()
{
	al_draw_rectangle(x1, y1, x2, y2, Color, 10);
}
//Rysuje obraz
//----------------------
void Button::DrawImage()
{
	al_draw_scaled_bitmap(Image, 0, 0, sizeX, sizeY, x1, y1, x2 - x1, y2 - y1, NULL);
}
//Rysuje tekst na przycisku
//--------------------------------------
void Button::DrawText(ALLEGRO_FONT* Font,float moveY)
{
	al_draw_text(Font, Colors::white, x1+(x2 - x1) / 2, y1+ moveY, ALLEGRO_ALIGN_CENTER, text.c_str());
}
//Sprawdza czy podany punkt znajduje siê na aktywnym przycisku
//------------------------------------------------------------
bool Button::MouseOn(float mouseX, float mouseY)
{
	if (active)
	{
		if (mouseX > x1 && mouseY > y1 && mouseX < x2 && mouseY < y2)
		{
			Color = Colors::green;
			return true;
		}
		Color = Colors::red;
		return false;
	}
	Color = Colors::yellow;
	return false;
}
