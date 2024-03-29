﻿#include <allegro5/allegro_native_dialog.h>
#include "MainMenu.h"
#include "settings.h"
#include "OtherFunctions.h"
#include "Colors.h"
#include "Fonts.h"
#include "Menu.h"


MainMenu::MainMenu(ALLEGRO_DISPLAY* Disp, float DisplayWidth, float DisplayHeight)
{
	Display = Disp;
	ChangeMenu = false;
	PVPGame = Button(settings::PosX(0.4), settings::PosY(0.3), settings::PosX(0.6), settings::PosY(0.45));
	PVPGame.SetText("Rozpocznij");
	PVPGame.SetColor(Colors::white, Colors::lightGray);
	HowToPlay = Button(settings::PosX(0.4), settings::PosY(0.5), settings::PosX(0.6), settings::PosY(0.65));
	HowToPlay.SetText("Jak Grać");
	HowToPlay.SetColor(Colors::white, Colors::lightGray);
	ExitButton = Button(settings::PosX(0.4), settings::PosY(0.7), settings::PosX(0.6), settings::PosY(0.85));
	ExitButton.SetText("Wyjście");
	ExitButton.SetColor(Colors::white, Colors::lightGray);
}
//Pętla gry
//-----------------------
int MainMenu::MenuLoop()
{
	ChangeMenu = false;
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Nie udalo się zaladowac biblioteki Allegro", NULL, NULL);
		return -1;
	}
	//Timer
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / settings::FPS());

	//Wydarzenia allegro
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(Display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer); //inicjalizacja timera | Nie dawać do pętli gry

	float mouseX = 0;												//X myszy
	float mouseY = 0;												//Y myszy
	bool StartNewGame = false;										//Rozpoczęcie partii
	int ReturnValue = 0;											//Zwracana wartość

	while (!ChangeMenu)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events); //Czeka do wciśnięcia przycisku		
		//Zamykanie okna
		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			ChangeMenu = true;
			ReturnValue = 1;
		}
		if (events.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE: //wciśniecie Escape
				ChangeMenu = true;
				std::cout << "Wcisnieto ESC\n";
				ReturnValue = 1;
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
			float mouseX_percent = (float)events.mouse.x / settings::ScrWidth();
			float mouseY_percent = (float)events.mouse.y / settings::ScrHeight();
			//printf("X - %d (%.3f)\nY - %d (%.3f)\n\n", events.mouse.x, mouseX_percent, events.mouse.y, mouseY_percent);
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
			float mouseX_percent = (float)events.mouse.x / settings::ScrWidth();
			float mouseY_percent = (float)events.mouse.y / settings::ScrHeight();
			//printf("X - %d (%.3f)\nY - %d (%.3f)\n\n", events.mouse.x, mouseX_percent, events.mouse.y, mouseY_percent);
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
			
			//tło
			al_clear_to_color(Colors::darkGray);
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					al_draw_scaled_bitmap(Images::ReverseCard, 0, 0, 330, 430, settings::PosX(i * 0.1), settings::PosY(j*0.1 * settings::ProportionScreenWH()), settings::PosX(0.1), settings::PosY(0.1 * settings::ProportionScreenWH()), NULL);
				}
			}
			al_draw_scaled_bitmap(Images::Tansparent, 0, 0, 1, 1, 0, 0, settings::PosX(1), settings::PosY(1), NULL);
			al_draw_text(Fonts::TitleFont, Colors::white, settings::PosX(0.5), settings::PosY(0.15), ALLEGRO_ALIGN_CENTER, "Projekt Gwint");
			//Rysowanie przycisków
			PVPGame.DrawImage();
			PVPGame.DrawText(Fonts::BigFont, settings::PosY(0.04f));
			HowToPlay.DrawImage();
			HowToPlay.DrawText(Fonts::BigFont, settings::PosY(0.04f));
			ExitButton.DrawImage();
			ExitButton.DrawText(Fonts::BigFont, settings::PosY(0.04f));
			al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.99), settings::PosY(0.95), ALLEGRO_ALIGN_RIGHT, "Wersja 1.0");
			//obsługa przycisków
			ReturnValue = ExitButtonActivation(mouseX,mouseY);
			//Start gry
			if (ReturnValue == 0)
			{
				ReturnValue = PVPGameActivation(mouseX,mouseY);
			}
			//Start poradnika
			if (ReturnValue == 0)
			{
				ReturnValue = HowToPlayActivation(mouseX, mouseY);
			}
			OtherFunctions::DrawMouseCursor(mouseX, mouseY);
			al_flip_display();
		}
	}
	return ReturnValue;
}
//Przycisk wyjścia
int MainMenu::ExitButtonActivation(float mouseX, float mouseY)
{
	if (ExitButton.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		ChangeMenu = true;
		return 1;
	}
	return 0;
}
//Poradnik
int MainMenu::HowToPlayActivation(float mouseX, float mouseY)
{
	if (HowToPlay.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		ChangeMenu = true;
		return 3;
	}
	return 0;
}
//Start gry
//----------------------------------------------------------
int MainMenu::PVPGameActivation(float mouseX, float mouseY)
{
	if (PVPGame.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		ChangeMenu = true;
		return 2;
	}
	return 0;
}
