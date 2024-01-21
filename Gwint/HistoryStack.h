#include "Card.h"
#include "Skills.h"
#include <vector>

#pragma once

typedef struct Action
{
	int PlayerNumber;
	Card PlayedCard;
	Card TargetCard;
	Skills UsedSkill;
}Action
;

class HistoryStack
{
private:
	std::vector<Action> History;

public:
	HistoryStack();										//Konstruktor
	void AddAction(Action NewAction);					//Dodanie akcji
	void RemoveAction();								//Usuwa ostanio dodan¹ akcje
	void RemoveActionEnd(int diff);						//Usuwa akcjê licz¹c od koñca 
	void DrawHistory(float x1, float y1, int amount);	//Rysowanie histori
	void UpdateTarget(Card Target);						//Dodaje cel do ostatniego wydarzenia
	void UpdatePlayer(int Player);						//Aktualizuje wykonawce czynnoœci
};

