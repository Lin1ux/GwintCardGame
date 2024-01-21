#include <allegro5/allegro_native_dialog.h>
#include "HowToPlay.h"
#include "Colors.h"
#include "Button.h"
#include "settings.h"

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
		al_show_native_message_box(NULL, NULL, NULL, "Nie udalo siê zaladowac biblioteki Allegro", NULL, NULL);
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

	al_start_timer(timer); //inicjalizacja timera | Nie dawaæ do pêtli gry

	float mouseX = 0;												//X myszy
	float mouseY = 0;												//Y myszy
	int ReturnValue = 0;											//Zwracana wartoœæ

	while (!ChangeMenu)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events); //Czeka do wciœniêcia przycisku		
		if (events.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE: //wciœniecie Escape
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
			al_clear_to_color(Colors::darkGray); //t³o
			al_flip_display();
		}
	}
	return ReturnValue;
}

