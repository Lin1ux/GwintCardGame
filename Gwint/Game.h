#include<vector>
#include"Card.h"
#include"PlayerInfo.h"
#include"Button.h"

#pragma once
class Game
{
private:
	ALLEGRO_DISPLAY* Display;
	int mouseButton;
	bool PlayerTurn;
	PlayerInfo Player;
	PlayerInfo Enemy;
	Button HandButtons[10];
	Button MeleeButtons[6];
	Button RangeButtons[6];
	bool GameBegin(float mouseX, float mouseY,int *CardsChanged);	//Mo�liwo�� wymiany kart w r�ce gracza
	void DrawPlayersCards(float mouseX, float mouseY);				//Rysuje karty nale��ce do gracza oraz sprawdza przyciski
	void DrawOtherInfo();											//Rysuje inne informacje takie jak ilo�� kart i liczba wygranych rund
	void RoundInfo(float mouseX, float mouseY);						//Odpowiada za koniec rundy
	bool RoundResult();												//Oblicza wynik rundy i czy�ci st�, zwraca true je�li runda si� zako�czy�a
	void ClearButtons();											//Czy�ci zawarto�� przycisk�w
public:
	Game(ALLEGRO_DISPLAY* Disp,std::vector<Card> PlayerDeck, std::vector<Card> EnemyDeck);
	int GameLoop();			//P�tla gry
};

