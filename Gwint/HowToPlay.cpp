#include <allegro5/allegro_native_dialog.h>
#include "HowToPlay.h"
#include "Colors.h"
#include "Fonts.h"
#include "Images.h";
#include "Button.h"
#include "settings.h"
#include "Skills.h"
#include "AllSkills.h"

HowToPlay::HowToPlay(ALLEGRO_DISPLAY* Disp)
{
	Display = Disp;
	PressedButton = 0;
	mouseButton = 0;
	ChangeMenu = false;
}

int HowToPlay::Loop()
{
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Nie udalo się zaladowac biblioteki Allegro", NULL, NULL);
		return -1;
	}
	ChangeMenu = false;
	Category = 0;
	Title = "Wybieranie Tali";
	//Timer
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / settings::FPS());

	//Wydarzenia allegro
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(Display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer); //inicjalizacja timera | Nie dawać do pętli gry

	AllSkills::SetSkills();	//Wczytanie wszystkich umiejętności

	//Przyciski
	MenuButton = Button(settings::PosX(0.05), settings::PosY(0.05), settings::PosX(0.2), settings::PosY(0.15));
	MenuButton.SetText("Wybieranie Tali");
	MenuButton.SetColor(Colors::white, Colors::lightGray);
	//Dane karty
	CardButton = Button(settings::PosX(0.05), settings::PosY(0.16), settings::PosX(0.2), settings::PosY(0.26));
	CardButton.SetText("Statystyki Karty");
	CardButton.SetColor(Colors::white, Colors::lightGray);
	//Zasady gry
	RulesButton = Button(settings::PosX(0.05), settings::PosY(0.27), settings::PosX(0.2), settings::PosY(0.37));
	RulesButton.SetText("Zasady gry");
	RulesButton.SetColor(Colors::white, Colors::lightGray);
	//Umiejetnosci
	SkillButton = Button(settings::PosX(0.05), settings::PosY(0.38), settings::PosX(0.2), settings::PosY(0.48));
	SkillButton.SetText("Umiejętnosci kart");
	SkillButton.SetColor(Colors::white, Colors::lightGray);
	//Opis interfejsu gry
	GameButton = Button(settings::PosX(0.05), settings::PosY(0.49), settings::PosX(0.2), settings::PosY(0.59));
	GameButton.SetText("Interfejs gry");
	GameButton.SetColor(Colors::white, Colors::lightGray);
	//Wyjscie
	ExitButton = Button(settings::PosX(0.05), settings::PosY(0.60), settings::PosX(0.2), settings::PosY(0.70));
	ExitButton.SetText("Wyjście");
	ExitButton.SetColor(Colors::white, Colors::lightGray);
	//Następna strona
	NextPage = Button(settings::PosX(0.61), settings::PosY(0.85), settings::PosX(0.70), settings::PosY(0.95));
	NextPage.SetText(">");
	NextPage.SetColor(Colors::white, Colors::lightGray);
	//Poprzednia strona
	PrevPage = Button(settings::PosX(0.51), settings::PosY(0.85), settings::PosX(0.60), settings::PosY(0.95));
	PrevPage.SetText("<");
	PrevPage.SetColor(Colors::white, Colors::lightGray);

	float mouseX = 0;												//X myszy
	float mouseY = 0;												//Y myszy
	int ReturnValue = 0;											//Zwracana wartość

	while (!ChangeMenu)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events); //Czeka do wciśnięcia przycisku		
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
			al_clear_to_color(Colors::darkGray); //tło
			MenuButton.DrawImage();
			MenuButton.DrawText(Fonts::NameFont, settings::PosY(0.03));
			CardButton.DrawImage();
			CardButton.DrawText(Fonts::NameFont, settings::PosY(0.03));
			RulesButton.DrawImage();
			RulesButton.DrawText(Fonts::NameFont, settings::PosY(0.03));
			SkillButton.DrawImage();
			SkillButton.DrawText(Fonts::NameFont, settings::PosY(0.03));
			GameButton.DrawImage();
			GameButton.DrawText(Fonts::NameFont, settings::PosY(0.03));
			ExitButton.DrawImage();
			ExitButton.DrawText(Fonts::NameFont, settings::PosY(0.03));
			NextPage.DrawImage();
			NextPage.DrawText(Fonts::BigFont, settings::PosY(0.015));
			PrevPage.DrawImage();
			PrevPage.DrawText(Fonts::BigFont, settings::PosY(0.015));
			//Tytuł
			al_draw_text(Fonts::TitleFont, Colors::white, settings::PosX(0.60), settings::PosY(0.01), ALLEGRO_ALIGN_CENTER, Title.c_str());
			//Wykrywanie myszy na przycisku
			Next(mouseX, mouseY);
			Prev(mouseX, mouseY);
			MenuTutorial(mouseX, mouseY);
			CardTutorial(mouseX, mouseY);
			SkillTutorial(mouseX, mouseY);
			RulesTutorial(mouseX, mouseY);
			GameTutorial(mouseX, mouseY);
			ExitTutorial(mouseX, mouseY);
			//Sekcje
			//Sekcja Umiejętności
			if (Category == HowToPlay::skill)
			{
				Skill();
			}
			OtherFunctions::DrawMouseCursor(mouseX, mouseY); //Kursor myszy
			al_flip_display();
		}
	}
	return ReturnValue;
}
//Następna strona
//----------------------------------------------
void HowToPlay::Next(float mouseX, float mouseY)
{
	if (NextPage.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		Page += 1;
		if (Page > LastPage)
		{
			Page = 0;
		}
	}
}
//Poprzednia strona
//----------------------------------------------
void HowToPlay::Prev(float mouseX, float mouseY)
{
	if (PrevPage.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		Page -= 1;
		if (Page < 0)
		{
			Page = LastPage;
		}
	}
}
//Poradnik Menu
//------------------------------------------------------
void HowToPlay::MenuTutorial(float mouseX, float mouseY)
{
	if (MenuButton.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		Page = 0;
		LastPage = 0;
		Title = "Wybieranie Tali";
		Category = HowToPlay::menu;
	}
}
//Opis Karty
//-----------------------------------------------------
void HowToPlay::CardTutorial(float mouseX, float mouseY)
{
	if (CardButton.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		Page = 0;
		LastPage = 0;
		Title = "Statystyki Karty";
		Category = HowToPlay::card;
	}
}
//Opis Umiejętności
//-------------------------------------------------------
void HowToPlay::SkillTutorial(float mouseX, float mouseY)
{
	if (SkillButton.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		Page = 0;
		LastPage = (AllSkills::AmountOfSkills()%5)-1;
		std::cout << LastPage << " LP\n";
		Title = "Umiejetności Kart";
		Category = HowToPlay::skill;
	}
}
//Zasady gry
//-------------------------------------------------------
void HowToPlay::RulesTutorial(float mouseX, float mouseY)
{
	if (RulesButton.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		Page = 0;
		LastPage = 0;
		Title = "Zasady Gry";
		Category = HowToPlay::rules;
	}
}
//Poradnik interfejsu gry
void HowToPlay::GameTutorial(float mouseX, float mouseY)
{
	if (GameButton.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		Page = 0;
		LastPage = 0;
		Title = "Interfejs gry";
		Category = HowToPlay::game;
	}
}
//Wyjscie
//-----------------------------------------------------
int HowToPlay::ExitTutorial(float mouseX, float mouseY)
{
	if (ExitButton.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		Page = 0;
		ChangeMenu = true;
	}
	return 0;
}
//Rysuje Dane umiejętności
//---------------------
void HowToPlay::Skill()
{
	std::vector<Skills> AllSkills = AllSkills::ReturnSkillList();
	int AmountOfSkills = AllSkills.size();
	for (int i = 0; i < 5; i++)
	{
		if (i + Page * 5 < AmountOfSkills)
		{	
			Skills Skill = AllSkills[i + Page * 5];
			al_draw_scaled_bitmap(Skill.ReturnIcon(),0,0,100,100,settings::PosX(0.3),settings::PosY(0.2 + 0.1 * i),settings::PosX(0.05),settings::PosY(0.05 * settings::ProportionScreenWH()),NULL);
			al_draw_scaled_bitmap(Images::LongDescrFrame, 0, 0, 800, 100, settings::PosX(0.38), settings::PosY(0.2 + 0.1 * i), settings::PosX(0.6), settings::PosY(0.09), NULL);
			al_draw_multiline_text(Fonts::SmallValueFont, Colors::white, settings::PosX(0.4), settings::PosY(0.215 + 0.1 * i), settings::PosX(0.58), settings::PosY(0.02), ALLEGRO_ALIGN_LEFT, (Skill.ReturnName()+": " + Skill.ReturnDescr()).c_str());
			
		}	
	}
}
