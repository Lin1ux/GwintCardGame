#include <iostream>
#include <allegro5/allegro.h>				//Podstawowe komendy
#include "Colors.h"                         //Kolory
#include "Button.h"							//Przyciski
#include "CardsToSelect.h"					//Kardy do wybrania
#include "DeckManager.h"					//Menadżer tali


#pragma once
class Menu
{
private:
		ALLEGRO_DISPLAY* Display;
		bool showInfo;
		bool IsPlayer1Selecting;	//Czy 1 gracz wybiera
		int mouseButton;
		int infoButtonId;
		Point infoPosition;
		CardsToSelect MenuCards1;	//Karty do wyboru 1 gracza
		CardsToSelect MenuCards2;	//Karty do wyboru 2 gracza
		DeckManager Deck1;			//Talia 1 gracza
		DeckManager Deck2;			//Talia 2 gracza

		CardsToSelect* MenuCards;
		DeckManager* Deck;

		Button PrevCards;			
		Button NextCards;
		Button UpDeck;
		Button DownDeck;
		Button StartGame;
		Button InfoButton;
		Button DeckButtons[13];
		Button CardButtons[10];
		void Pages(float mouseX, float mouseY, int* firstCard);									//Zmienia stronę kart
		void MoveDeck(float mouseX, float mouseY, int AmountOfShowCard, int* firstDeckCard);	//Przesuwa widok kart w talii
		void StartCardGame(float mouseX, float mouseY, bool* ChangeMenu, bool* StartNewGame);	//Rozpoczęcie partii
		void DrawCartToSelect(float mouseX, float mouseY, int firstCard);						//Rysuje karty do wyboru oraz dodaje wskazaną kartę do talii
		void DrawDeck(int AmountOfShowCard, int firstDeckCard, float mouseX, float mouseY);		//Rysuje talię gracza
		void DrawInfo(float mouseX, float mouseY);												//Rysuje informacje o karcie
		void InfoCard(float mouseX, float mouseY, int* firstCard, int i);						//Aktywuje informacje o karcie
		void AddCard(float mouseX, float mouseY, int* firstCard, int i);						//Dodanie kart
		void PreviousButton(float mouseX, float mouseY,bool* changeMenu);						//Przycisk cofania
		void ClearDeckButton(float mouseX, float mouseY,int *firstDeckCard);												//Przycisk usuwania talii			
		void DeleteDeck(int* firstDeckCard);													//Usuwa wszystkie karty z talii
		void ChangePlayer();																	//Zmiana gracza
public:
	int MenuLoopPVP();																			//Pętla menu wyboru
	void ResetDeck(int mode);																	//Usuwanie tali mode=1 gracz1, mode=2 gracz2, mode=3 obaj gracze
	float ScreenWidth;		
	float ScreenHeight;
	Menu(ALLEGRO_DISPLAY* Disp, float DisplayWidth, float DisplayHeight);
};

