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
	bool GameBegin(float mouseX, float mouseY,int *CardsChanged);			//Mo¿liwoœæ wymiany kart w rêce gracza
	Card DrawPlayersCards(float mouseX, float mouseY);						//Rysuje karty nale¿¹ce do gracza oraz sprawdza przyciski pozwala na zagranie karty i zwraca zagran¹ kartê
	Card AbilityManager(Card UsedCard);										//Sprawdza i u¿ywa odpowiedniej umiejêtnoœci i zwraca nowo zagran¹ kartê jeœli umiejêtnoœæ zagrywa dodatkowe karty
	void DrawOtherInfo();													//Rysuje inne informacje takie jak iloœæ kart i liczba wygranych rund
	void RoundInfo(float mouseX, float mouseY);								//Odpowiada za koniec rundy
	bool RoundResult();														//Oblicza wynik rundy i czyœci stó³, zwraca true jeœli runda siê zakoñczy³a
	void ClearButtons();													//Czyœci zawartoœæ przycisków
	void BrotherhoodSkill(std::vector<Card> VectorCard, Card CardToFind);	//Nak³ada efekt Braterstwa
	bool CardInVector(std::vector<Card> CardVector,Card CardToFind);										//Sprawdza czy karta jest w vectorze
public:
	Game(ALLEGRO_DISPLAY* Disp,std::vector<Card> PlayerDeck, std::vector<Card> EnemyDeck);
	int GameLoop();			//Pêtla gry
};

