#include<iostream>
#pragma once
class settings
{
private:
	static float screenWidth;
	static float screenHeight;
	static int framePerSecond;
	static bool windowed;
	static std::string settingsFileName;
public:
	static void SetSettings();
	static float ScrWidth();
	static float ScrHeight();
	static int FPS();
	static float ProportionScreenWH();
	static float PosX(float x);			
	static float PosY(float y);
	static bool IsWindowed();
};

