#include "Game.h"			
#include<iostream>
//#include<vector>
#include <allegro5/allegro_ttf.h>				//Wczytywanie czcionek .ttf
#include <allegro5/allegro_font.h>				//Czcionki
#include <allegro5/allegro_primitives.h>		//Prymitywy (kwadraty, trójkąty itd.)
#include <allegro5/allegro_image.h>				//Obrazki
#include <allegro5/allegro_native_dialog.h>		//Do Errorów

#include "PlayerInfo.h"
#include "Colors.h"
#include "Images.h"
#include "AllSkills.h"
#include "CardList.h"
#include "settings.h"
#include "OtherFunctions.h"
#include "Card.h"
#include "Fonts.h"
#include "Button.h"

//Konstruktor
Game::Game(ALLEGRO_DISPLAY* Disp,std::vector<Card> PlayerDeck, std::vector<Card> EnemyDeck)
{
	Display = Disp;
	PlayerTurn = true;
	Player = PlayerInfo(PlayerDeck);
	Enemy = PlayerInfo(EnemyDeck);
}

//Główna część gry 
int Game::GameLoop()
{
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Nie udalo się zaladowac biblioteki Allegro", NULL, NULL);
		return -1;
	}
	//Timer
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / settings::FPS());

	//Ustawianie Statycznych obiektów
	Images::SetImages();
	Fonts::SetFonts();
	AllSkills::SetSkills();
	CardList::SetCards();

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(Display));
	al_register_event_source(event_queue, al_get_mouse_event_source());


	al_start_timer(timer); //inicjalizacja timera | Nie dawać do pętli gry

	//Przyciski
	Button StartGame(settings::PosX(0.7f), settings::PosY(0.5f), settings::PosX(0.8f), settings::PosY(0.55f));
	Button HandButtons[10];
	//Obiekty
	std::vector<Card> PlayerHand;

	float mouseX = 0;			//X myszy
	float  mouseY = 0;			//Y myszy
	int mouseButton = 0;		//Wciśnięty przycisk myszy
	bool GameOver = false;		//Pętla
	bool GameBegin = true;		//Początek gry
	int CardsChanged = 0;		//Liczba odrzuconych kart
	while (!GameOver)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events); //Czeka do wciśnięcia przycisku

		if (events.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE: //wciśniecie Escape
				GameOver = true;
				std::cout << "Wcisnieto ESC\n";
				break;
			}
		}
		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (events.mouse.button & 1)
			{
				mouseButton = 3;
			}
			else if (events.mouse.button & 2)
			{
				mouseButton = 4;
			}
			else
			{
				mouseButton = 0;
			}
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (events.mouse.button & 1)
			{
				mouseButton = 1;
			}
			else if (events.mouse.button & 2)
			{
				mouseButton = 2;
			}
			else
			{
				mouseButton = 0;
			}
		}
		if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouseX = events.mouse.x;
			mouseY = events.mouse.y;
			mouseButton = 0;
		}
		if (events.type == ALLEGRO_EVENT_TIMER)
		{
			
			al_clear_to_color(Colors::darkGray); //tło
			PlayerHand = Player.ReturnPlayerHand();
			if (GameBegin) //Początek gry --> odrzucanie kart
			{	
				//Rysowanie
				al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.45f), settings::PosY(0.24f), ALLEGRO_ALIGN_CENTER, "Wybierz kartę którą chcesz odrzucić");
				al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.45f), settings::PosY(0.29f), ALLEGRO_ALIGN_CENTER, ("Liczba dostępnych przelosowań:  "+std::to_string(2 - CardsChanged)).c_str());
				for (int i = 0; i < PlayerHand.size(); i++)
				{
					if (i < 5)
					{
						PlayerHand[i].DrawCard(0.25f + i * 0.08f, 0.36f);
					}
					else
					{
						PlayerHand[i].DrawCard(0.25f + (i % (5)) * 0.08f, 0.56f);
					}
					HandButtons[i] = Button(PlayerHand[i].ReturnVertexesPosition());
					if (HandButtons[i].MouseOn(mouseX, mouseY))	//Rysowanie dużej karty
					{
						PlayerHand[i].DrawBigCardDescr(0.02f, 0.1f);
					}
				}
				//Przyciski
				if (StartGame.MouseOn(mouseX, mouseY) && mouseButton == 1)	//Rozpoczęcie gracza nie wykorzystując wszystkich przelosowań
				{
					GameBegin = false;
				}
				for (int i = 0; i < PlayerHand.size();i++)
				{
					if (HandButtons[i].MouseOn(mouseX, mouseY) && mouseButton == 1)	//Rysowanie dużej karty
					{
						Player.PutToStack(Player.UseCard(i));	//Usuwa kartę z ręki i dodaje do nie używanych kart
						Player.TakeCard();
						CardsChanged += 1;
						mouseButton = 0;
					}
				}
				if (CardsChanged >= 2)	//Osiągnięcie limitu przelosowań kart
				{
					GameBegin = false;
				}
				StartGame.DrawHitbox();
			}
			else
			{
				
				for (int i = 0; i < PlayerHand.size(); i++)
				{
					HandButtons[i] = Button(PlayerHand[i].NormalCardVertexesPosition(0.05f + i * 0.08f, 0.8f));
				
					if (HandButtons[i].MouseOn(mouseX, mouseY))
					{
						PlayerHand[i].DrawBigCardDescr(0.02, 0.1f);
						PlayerHand[i].DrawCard(0.05f + i * 0.08f, 0.76f);

					}
					else
					{
						PlayerHand[i].DrawCard(0.05f + i * 0.08f, 0.8f);
					}
					//HandButtons[i].DrawHitbox();
				}
				OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.92),settings::PosY(0.93) }, { 100,100 },
					{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player.ReturnAmountOfCardStack()).c_str());
				CardList::BrotherOfBlood.DrawCard(0.895, 0.75);
				//Player.DrawHand();
			}
			al_flip_display();
		}
	}
	return 0;
}
