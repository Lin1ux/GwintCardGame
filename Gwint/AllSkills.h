#include "Skills.h"
#include <vector>
#pragma once
class AllSkills
{
public:
	static int none;
	static int brotherhood;
	static int medic;
	static int spy;
	static int executioner;
	static int archer;
	static int horde;
	static int thief;
	static int transport;
	static int summonerMortar;
	static int deadEater;
	static int slayer;
	static int banish;
	static int goldDeadEater;
	static int goldMedic;

	static Skills None;
	static Skills Brotherhood;
	static Skills Medic;
	static Skills Spy;
	static Skills Executioner;
	static Skills Archer;
	static Skills Horde;
	static Skills Thief;
	static Skills Transport;
	static Skills SummonerMortar;
	static Skills DeadEater;
	static Skills Slayer;
	static Skills Banish;
	static Skills GoldDeadEater;
	static Skills GoldMedic;
	static void SetSkills();						//Ustawia warto�ci umiej�tno�ci
	static std::vector<Skills> ReturnSkillList();	//Zwraca vector z wszystkimi umiej�tno�ciami
	static int AmountOfSkillsAuto();				//Zwraca liczb� umiej�tno�ci na podstawie vectora (wolniejszy)
	static int AmountOfSkills();					//Zwraca liczb� umiej�tno�ci (nale�y r�cznie aktualizowa�)
};

