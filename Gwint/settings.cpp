#include "settings.h"
#include "json.hpp"
#include<iostream>
#include<fstream>

using json = nlohmann::json;

float settings::screenWidth; //1920
float settings::screenHeight; //1080
bool settings::windowed;
std::string settings::settingsFileName = "settings.json";
int settings::framePerSecond = 30;
//Ustawia wartoœci ekranu zgodnie z plikiem konfiguracyjnym
//---------------------------------------------------------
void settings::SetSettings()
{
	json data;
	json readData;
	std::ifstream reader;
	reader.open(settingsFileName,std::ios::in);
	if (!reader.good())
	{
		reader.close();
		//Tworzenie pliku jeœli nie istnieje
		std::ofstream writer;
		data = {
			{ "screenWidth",1920},
			{ "screenHeight",1080},
			{ "framePerSecond",30},
			{ "windowed",false }
		};
		writer.open(settingsFileName);
		writer << data.dump(4);
		writer.close();
	}
	//Odczyt
	reader.open(settingsFileName);
	reader >> readData;
	screenWidth = readData["screenWidth"];
	screenHeight = readData["screenHeight"];
	framePerSecond = readData["framePerSecond"];
	windowed = readData["windowed"];
	reader.close();
	std::cout << screenWidth<<"x"<< screenHeight << "\n";

	//Tworzenie
}
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
bool settings::IsWindowed()
{
	return windowed;
}
