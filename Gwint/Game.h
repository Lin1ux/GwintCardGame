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
	int skillId;					//Id u¿ywanej umiejêtnoœci (do rysowania specjalnego interfejsu)
	int lastUsedCardIndex;			//Id ostatniej u¿ytej karty (do zapamiêtywania wybranej karty)
	int lastUsedCardRow;			//rz¹d ostatniej u¿ytej karty
	int GraveyardFirstCard;			//Pierwsza wyœwietlana karta w cmentarzu
	bool PlayerTurn;				//Tura 1 gracza
	bool GraveyardOn;				//Czy cmentarz jest w³¹czony
	bool PlayersGraveyard;			//Czy wyœwietlany jest cmentarz gracza 1 gracza
	bool TurnBegin;					//Pocz¹tek tury gracza (ukrywanie kart)
	PlayerInfo Player;				//Dane 1 gracza
	PlayerInfo Enemy;				//Dane 2 gracza
	Button HandButtons[10];			//Przyciski rêki
	Button MeleeButtons[6];			//Przyciski 1 rzêdu
	Button RangeButtons[6];			//Przyciski 2 rzêdu

	bool GameBegin(float mouseX, float mouseY,int *CardsChanged);							//Mo¿liwoœæ wymiany kart w rêce gracza
	void HiddenGameBegin(float mouseX, float mouseY);										//Zas³oniête karty do wymiany
	CardPos DrawPlayersCards(float mouseX, float mouseY);									//Rysuje karty nale¿¹ce do gracza oraz sprawdza przyciski pozwala na zagranie karty i zwraca zagran¹ kartê
	Card AbilityManager(Card UsedCard);														//Sprawdza i u¿ywa odpowiedniej umiejêtnoœci i zwraca nowo zagran¹ kartê jeœli umiejêtnoœæ zagrywa dodatkowe karty
	void DrawOtherInfo(float mouseX, float mouseY);											//Rysuje inne informacje takie jak iloœæ kart i liczba wygranych rund
	void EndRoundButton(float mouseX, float mouseY);										//Przycisk Koñca tury
	bool RoundResult();																		//Oblicza wynik rundy i czyœci stó³, zwraca true jeœli runda siê zakoñczy³a
	void ClearButtons();																	//Czyœci zawartoœæ przycisków
	CardPos DrawGraveyard(float mouseX, float mouseY, bool IsPlayerGraveyard,bool CanHero);	//Rysuje karty w cmentarzu
	void DrawHand(float mouseX, float mouseY);												//Rysuje rêkê gracza (bez animacji)
	void DrawHiddenHand(float mouseX, float mouseY);						//Rysuje rêke z odwróconymi kartami
	bool CardInVector(std::vector<Card> CardVector,Card CardToFind);						//Sprawdza czy karta jest w vectorze
	bool IsEnemyGraveyardLocked();															//Sprawdza czy w³¹czona jest umiejêtnoœæ blokuj¹ca cmentarz
public:
	Game(ALLEGRO_DISPLAY* Disp,std::vector<Card> PlayerDeck, std::vector<Card> EnemyDeck);
	int GameLoopPvP();																		//Pêtla gry
};