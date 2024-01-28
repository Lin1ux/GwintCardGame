#include<vector>
#include"Card.h"
#include"PlayerInfo.h"
#include"Button.h"
#include"CardValues.h"
#include"HistoryStack.h"

#pragma once

class Game
{
private:
	ALLEGRO_DISPLAY* Display;		//Ekran								
	int mouseButton;				//Nazwa akcji myszy
	int skillId;					//Id używanej umiejętności (do rysowania specjalnego interfejsu)
	int lastUsedCardIndex;			//Id ostatniej użytej karty (do zapamiętywania wybranej karty)
	int lastUsedCardRow;			//rząd ostatniej użytej karty
	int GraveyardFirstCard;			//Pierwsza wyświetlana karta w cmentarzu
	bool player1Turn;				//Tura 1 gracza
	bool gameEnd;					//Koniec gry
	bool cardPlayed;				//Czy karta zostałą zagrana
	bool GraveyardOn;				//Czy cmentarz jest włączony
	bool PlayersGraveyard;			//Czy wyświetlany jest cmentarz gracza 1 gracza
	bool TurnBegin;					//Początek tury gracza (ukrywanie kart)
	PlayerInfo Player;				//Dane 1 gracza
	PlayerInfo Enemy;				//Dane 2 gracza
	PlayerInfo* Player1;			//Wskaźnik na aktualnego gracza
	PlayerInfo* Player2;			//Wskaźnik na biernego gracza  
	Button HandButtons[10];			//Przyciski ręki
	Button MeleeButtons[6];			//Przyciski 1 rzędu gracza
	Button RangeButtons[6];			//Przyciski 2 rzędu gracza
	Button EMeleeButtons[6];		//Przyciski 1 rzędu przeciwnika
	Button ERangeButtons[6];		//Przyciski 2 rzędu przeciwnika
	HistoryStack History;			//Historia gry

	bool GameBegin(float mouseX, float mouseY,int *CardsChanged);							//Możliwość wymiany kart w ręce gracza
	void HiddenGameBegin(float mouseX, float mouseY);										//Zasłonięte karty do wymiany
	CardPos DrawPlayersCards(float mouseX, float mouseY);									//Rysuje karty należące do gracza oraz sprawdza przyciski pozwala na zagranie karty i zwraca zagraną kartę
	Card AbilityManager(Card UsedCard,bool otherPlayer);									//Sprawdza i używa odpowiedniej umiejętności i zwraca nowo zagraną kartę jeśli umiejętność zagrywa dodatkowe karty
	void DrawOtherInfo(float mouseX, float mouseY);											//Rysuje inne informacje takie jak ilość kart i liczba wygranych rund
	void DrawHistory();																		//Rysuje historię
	void EndRoundButton(float mouseX, float mouseY);										//Przycisk Końca tury
	bool RoundResult(int *RoundNumber);														//Oblicza wynik rundy i czyści stół, zwraca true jeśli runda się zakończyła oraz zwiększa wartość argumentu o 1
	bool DrawSummary(float mouseX, float mouseY);											//Rysuje podsumowanie gry zwraca true jeśli naciśnięto przycisk
	void ClearButtons();																	//Czyści zawartość przycisków
	CardPos DrawGraveyard(float mouseX, float mouseY, bool IsPlayerGraveyard,bool CanHero);	//Rysuje karty w cmentarzu
	void DrawHand(float mouseX, float mouseY,bool hide);									//Rysuje rękę gracza (bez animacji)
	void DrawHiddenHand(float mouseX, float mouseY);										//Rysuje ręke z odwróconymi kartami
	void DrawTable(float mouseX, float mouseY);												//Rysuje stół
	void DrawTip(std::string text);															//Rysuje poradę w lewym głównym rogu
	bool CardInVector(std::vector<Card> CardVector,Card CardToFind);						//Sprawdza czy karta jest w vectorze
	bool IsEnemyGraveyardLocked();															//Sprawdza czy włączona jest umiejętność blokująca cmentarz przeciwnika
	bool IsGraveyardLocked();																//Sprawdza czy włączona jest umiejętność blokująca cmentarz gracza
	void NextPlayer();																		//Odpowiada za zmianę gracza
public:
	Game(ALLEGRO_DISPLAY* Disp,std::vector<Card> PlayerDeck, std::vector<Card> EnemyDeck);
	int GameLoopPvP();																		//Pętla gry
};