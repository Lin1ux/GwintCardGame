#include<vector>
#include"Card.h"
#include"PlayerInfo.h"
#include"Button.h"
#include"CardValues.h"

#pragma once

class Game
{
private:
	ALLEGRO_DISPLAY* Display;
	int mouseButton;
	int skillId;
	int lastUsedCardIndex;
	int lastUsedCardRow;
	int GraveyardFirstCard;
	bool PlayerTurn;
	bool GraveyardOn;
	bool PlayersGraveyard;
	PlayerInfo Player;
	PlayerInfo Enemy;
	Button HandButtons[10];
	Button MeleeButtons[6];
	Button RangeButtons[6];
	bool GameBegin(float mouseX, float mouseY,int *CardsChanged);							//Mo�liwo�� wymiany kart w r�ce gracza
	CardPos DrawPlayersCards(float mouseX, float mouseY);									//Rysuje karty nale��ce do gracza oraz sprawdza przyciski pozwala na zagranie karty i zwraca zagran� kart�
	Card AbilityManager(Card UsedCard);														//Sprawdza i u�ywa odpowiedniej umiej�tno�ci i zwraca nowo zagran� kart� je�li umiej�tno�� zagrywa dodatkowe karty
	void DrawOtherInfo(float mouseX, float mouseY);											//Rysuje inne informacje takie jak ilo�� kart i liczba wygranych rund
	void RoundInfo(float mouseX, float mouseY);												//Odpowiada za koniec rundy
	bool RoundResult();																		//Oblicza wynik rundy i czy�ci st�, zwraca true je�li runda si� zako�czy�a
	void ClearButtons();																	//Czy�ci zawarto�� przycisk�w
	CardPos DrawGraveyard(float mouseX, float mouseY, bool IsPlayerGraveyard,bool CanHero);	//Rysuje karty w cmentarzu
	void DrawHand(float mouseX, float mouseY);												//Rysuje r�k� gracza (bez animacji)
	bool CardInVector(std::vector<Card> CardVector,Card CardToFind);						//Sprawdza czy karta jest w vectorze
	bool IsEnemyGraveyardLocked();															//Sprawdza czy w��czona jest umiej�tno�� blokuj�ca cmentarz
public:
	Game(ALLEGRO_DISPLAY* Disp,std::vector<Card> PlayerDeck, std::vector<Card> EnemyDeck);
	int GameLoopPvP();			//P�tla gry
};

