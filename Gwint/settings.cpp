#include "settings.h"
#include<iostream>

float settings::screenWidth = 1920;
float settings::screenHeight = 1080;
int settings::framePerSecond = 30;
//Zwraca szerokoœæ okna
//------------------------
float settings::ScrWidth()
{
	return screenWidth;
}
//Zwraca wysokoœæ okna
//-------------------------
float settings::ScrHeight()
{
	return screenHeight;
}
//Zwraca liczbê klatek na sekundê
//-------------------------------
int settings::FPS()
{
	return framePerSecond;
}
//Zwraca proporcjê ekranu szerokoœæ/wysokoœæ
//------------------------------------------
float settings::ProportionScreenWH()
{
	return screenWidth / screenHeight;
}
//Zwraca pozycjê X z wzglêdu na procent
//-------------------------------------
float settings::PosX(float x)
{
	return (screenWidth * x);
}
//Zwraca pozycjê Y z wzglêdu na procent
//-------------------------------------
float settings::PosY(float y)
{
	return (screenHeight * y);
}
