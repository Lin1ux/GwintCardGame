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
	int skillId;
	bool PlayerTurn;
	PlayerInfo Player;
	PlayerInfo Enemy;
	Button HandButtons[10];
	Button MeleeButtons[6];
	Button RangeButtons[6];
	bool GameBegin(float mouseX, float mouseY,int *CardsChanged);			//Mo�liwo�� wymiany kart w r�ce gracza
	Card DrawPlayersCards(float mouseX, float mouseY);						//Rysuje karty nale��ce do gracza oraz sprawdza przyciski pozwala na zagranie karty i zwraca zagran� kart�
	Card AbilityManager(Card UsedCard);										//Sprawdza i u�ywa odpowiedniej umiej�tno�ci i zwraca nowo zagran� kart� je�li umiej�tno�� zagrywa dodatkowe karty
	void DrawOtherInfo();													//Rysuje inne informacje takie jak ilo�� kart i liczba wygranych rund
	void RoundInfo(float mouseX, float mouseY);								//Odpowiada za koniec rundy
	bool RoundResult();														//Oblicza wynik rundy i czy�ci st�, zwraca true je�li runda si� zako�czy�a
	void ClearButtons();													//Czy�ci zawarto�� przycisk�w
	void BrotherhoodSkill(std::vector<Card> VectorCard, Card CardToFind);	//Nak�ada efekt Braterstwa
	bool CardInVector(std::vector<Card> CardVector,Card CardToFind);										//Sprawdza czy karta jest w vectorze
public:
	Game(ALLEGRO_DISPLAY* Disp,std::vector<Card> PlayerDeck, std::vector<Card> EnemyDeck);
	int GameLoop();			//P�tla gry
};

