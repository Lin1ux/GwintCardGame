#include "Game.h"			
#include<iostream>
//#include<vector>
#include <allegro5/allegro_ttf.h>				//Wczytywanie czcionek .ttf
#include <allegro5/allegro_font.h>				//Czcionki
#include <allegro5/allegro_primitives.h>		//Prymitywy (kwadraty, tr�jk�ty itd.)
#include <allegro5/allegro_image.h>				//Obrazki
#include <allegro5/allegro_native_dialog.h>		//Do Error�w

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

//G��wna cz�� gry 
int Game::GameLoop()
{
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Nie udalo si� zaladowac biblioteki Allegro", NULL, NULL);
		return -1;
	}
	//Timer
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / settings::FPS());

	//Ustawianie Statycznych obiekt�w
	Images::SetImages();
	Fonts::SetFonts();
	AllSkills::SetSkills();
	CardList::SetCards();

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(Display));
	al_register_event_source(event_queue, al_get_mouse_event_source());


	al_start_timer(timer); //inicjalizacja timera | Nie dawa� do p�tli gry

	//Przyciski
	Button HandButtons[10];
	//Obiekty
	std::vector<Card> PlayerHand;

	float mouseX = 0;			//X myszy
	float  mouseY = 0;			//Y myszy
	int mouseButton = 0;		//Wci�ni�ty przycisk myszy
	bool GameOver = false;		//P�tla
	while (!GameOver)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events); //Czeka do wci�ni�cia przycisku

		if (events.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE: //wci�niecie Escape
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
			//Rysowanie
			al_clear_to_color(Colors::darkGray); //t�o
			PlayerHand = Player.ReturnPlayerHand();
			for (int i = 0; i < PlayerHand.size(); i++)
			{
				HandButtons[i] = Button(PlayerHand[i].NormalCardVertexesPosition(0.05f + i * 0.08f, 0.8f));
				
				if (HandButtons[i].MouseOn(mouseX, mouseY))
				{
					PlayerHand[i].DrawBigCard(0.02, 0.2);
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
			al_flip_display();
		}
	}
	return 0;
}
