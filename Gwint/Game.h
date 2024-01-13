#include<vector>
#include"Card.h"
#include"PlayerInfo.h"
#include"Button.h"
#include"CardValues.h"

#pragma once

class Game
{
private:
	ALLEGRO_DISPLAY* Display;		//Ekran								
	int mouseButton;				//Nazwa akcji myszy
	int skillId;					//Id u�ywanej umiej�tno�ci (do rysowania specjalnego interfejsu)
	int lastUsedCardIndex;			//Id ostatniej u�ytej karty (do zapami�tywania wybranej karty)
	int lastUsedCardRow;			//rz�d ostatniej u�ytej karty
	int GraveyardFirstCard;			//Pierwsza wy�wietlana karta w cmentarzu
	bool PlayerTurn;				//Tura 1 gracza
	bool GraveyardOn;				//Czy cmentarz jest w��czony
	bool PlayersGraveyard;			//Czy wy�wietlany jest cmentarz gracza 1 gracza
	bool TurnBegin;					//Pocz�tek tury gracza (ukrywanie kart)
	PlayerInfo Player;				//Dane 1 gracza
	PlayerInfo Enemy;				//Dane 2 gracza
	Button HandButtons[10];			//Przyciski r�ki
	Button MeleeButtons[6];			//Przyciski 1 rz�du
	Button RangeButtons[6];			//Przyciski 2 rz�du

	bool GameBegin(float mouseX, float mouseY,int *CardsChanged);							//Mo�liwo�� wymiany kart w r�ce gracza
	void HiddenGameBegin(float mouseX, float mouseY);										//Zas�oni�te karty do wymiany
	CardPos DrawPlayersCards(float mouseX, float mouseY);									//Rysuje karty nale��ce do gracza oraz sprawdza przyciski pozwala na zagranie karty i zwraca zagran� kart�
	Card AbilityManager(Card UsedCard);														//Sprawdza i u�ywa odpowiedniej umiej�tno�ci i zwraca nowo zagran� kart� je�li umiej�tno�� zagrywa dodatkowe karty
	void DrawOtherInfo(float mouseX, float mouseY);											//Rysuje inne informacje takie jak ilo�� kart i liczba wygranych rund
	void EndRoundButton(float mouseX, float mouseY);										//Przycisk Ko�ca tury
	bool RoundResult();																		//Oblicza wynik rundy i czy�ci st�, zwraca true je�li runda si� zako�czy�a
	void ClearButtons();																	//Czy�ci zawarto�� przycisk�w
	CardPos DrawGraveyard(float mouseX, float mouseY, bool IsPlayerGraveyard,bool CanHero);	//Rysuje karty w cmentarzu
	void DrawHand(float mouseX, float mouseY);												//Rysuje r�k� gracza (bez animacji)
	void DrawHiddenHand(float mouseX, float mouseY);						//Rysuje r�ke z odwr�conymi kartami
	bool CardInVector(std::vector<Card> CardVector,Card CardToFind);						//Sprawdza czy karta jest w vectorze
	bool IsEnemyGraveyardLocked();															//Sprawdza czy w��czona jest umiej�tno�� blokuj�ca cmentarz
public:
	Game(ALLEGRO_DISPLAY* Disp,std::vector<Card> PlayerDeck, std::vector<Card> EnemyDeck);
	int GameLoopPvP();																		//P�tla gry
};