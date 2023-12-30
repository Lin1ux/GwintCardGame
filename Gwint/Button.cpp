#include "Button.h"

#include <allegro5/allegro_primitives.h>

#include "Colors.h"
#include "OtherFunctions.h"

Button::Button()
{
	active = true;
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	Color = Colors::red;
}

Button::Button(float X1, float Y1, float X2, float Y2)
{
	active = true;
	x1 = X1;
	y1 = Y1;
	x2 = X2;
	y2 = Y2;
	Color = Colors::red;
}

Button::Button(Point P1, Point P2)
{
	active = true;
	x1 = P1.x;
	y1 = P1.y;
	x2 = P2.x;
	y2 = P2.y;
	Color = Colors::red;
}

Button::Button(RectanglePoints Points)
{
	active = true;
	x1 = Points.P1.x;
	y1 = Points.P1.y;
	x2 = Points.P4.x;
	y2 = Points.P4.y;
	Color = Colors::red;
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

//Rysuje wizualizacje hitboxa przycisku
//--------------------------------------
void Button::DrawHitbox()
{
	al_draw_rectangle(x1, y1, x2, y2, Color, 10);
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
		else
		{
			Color = Colors::red;
			return false;
		}
	}
}
