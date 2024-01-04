#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h> 
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
	ALLEGRO_BITMAP* Image;
	int sizeX;
	int sizeY;
	std::string text;
public:
	Button();
	Button(float X1, float Y1, float X2, float Y2);
	Button(Point P1, Point P2);
	Button(RectanglePoints Points);
	bool IsActive();
	bool ChangeState(bool newState);
	void SetImage(ALLEGRO_BITMAP* Newimage,int sx,int sy);
	void SetText(std::string newText);
	void DrawHitbox();
	void DrawImage();
	void DrawText(ALLEGRO_FONT* Font, float moveY);
	bool MouseOn(float mouseX,float mouseY);
};

