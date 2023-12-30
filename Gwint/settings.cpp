#include "settings.h"
#include<iostream>

float settings::screenWidth = 1920;
float settings::screenHeight = 1080;
int settings::framePerSecond = 30;
//Zwraca szeroko�� okna
//------------------------
float settings::ScrWidth()
{
	return screenWidth;
}
//Zwraca wysoko�� okna
//-------------------------
float settings::ScrHeight()
{
	return screenHeight;
}
//Zwraca liczb� klatek na sekund�
//-------------------------------
int settings::FPS()
{
	return framePerSecond;
}
//Zwraca proporcj� ekranu szeroko��/wysoko��
//------------------------------------------
float settings::ProportionScreenWH()
{
	return screenWidth / screenHeight;
}
//Zwraca pozycj� X z wzgl�du na procent
//-------------------------------------
float settings::PosX(float x)
{
	return (screenWidth * x);
}
//Zwraca pozycj� Y z wzgl�du na procent
//-------------------------------------
float settings::PosY(float y)
{
	return (screenHeight * y);
}
