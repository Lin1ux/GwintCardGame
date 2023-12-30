#include <allegro5/allegro.h>
#include "OtherFunctions.h"
#pragma once
class Button
{
private:
	bool active;
	float x1;
	float y1;
	float x2;
	float y2;
	ALLEGRO_COLOR Color;
public:
	Button();
	Button(float X1, float Y1, float X2, float Y2);
	Button(Point P1, Point P2);
	Button(RectanglePoints Points);
	bool IsActive();
	bool ChangeState(bool newState);
	void DrawHitbox();
	bool MouseOn(float mouseX,float mouseY);
};

