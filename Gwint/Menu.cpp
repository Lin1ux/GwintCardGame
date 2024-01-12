#include "Menu.h"
#include <allegro5/allegro_ttf.h>			//Wczytywanie czcionek .ttf
#include <allegro5/allegro_font.h>			//Czcionki
#include <allegro5/allegro_primitives.h>	//Prymitywy (kwadraty, trójkąty itd.)
#include <allegro5/allegro_image.h>			//Obrazki
#include <allegro5/allegro_native_dialog.h> //Do Errorów

#include "Card.h"
#include "settings.h"
#include "Images.h"
#include "Fonts.h"
#include "AllSkills.h"
#include "CardList.h"
#include "CardsToSelect.h"
#include "Button.h"
#include "DeckManager.h"
#include "Game.h"


Menu::Menu(ALLEGRO_DISPLAY* Disp, float DisplayWidth,float DisplayHeight)	//Konstruktor
{
	Display = Disp;
	ScreenWidth = DisplayWidth;
	ScreenHeight = DisplayHeight;
	mouseButton = 0;
	showInfo = false;
	infoButtonId = -1;
	
	//Ustawianie Statycznych obiektów
	Images::SetImages();
	Fonts::SetFonts();
	AllSkills::SetSkills();
	CardList::SetCards();
	
	//Przyciski Kart
	//Przycisk następnej strony
	PrevCards = Button(settings::PosX(0.3f), settings::PosY(0.85f), settings::PosX(0.39f), settings::PosY(0.95f));
	PrevCards.SetColor(Colors::white, Colors::lightGray);
	PrevCards.SetText("<-");
	//Przycisk poprzedniej strony
	NextCards = Button(settings::PosX(0.41f), settings::PosY(0.85f), settings::PosX(0.5f), settings::PosY(0.95f));
	NextCards.SetColor(Colors::white, Colors::lightGray);
	NextCards.SetText("->");
	//Przyciski talii gracza
	//Przycisk przewijania do góry tali
	UpDeck = Button(settings::PosX(0.87f), settings::PosY(0.93f), settings::PosX(0.9f), settings::PosY(0.98f));
	UpDeck.SetColor(Colors::white, Colors::lightGray);
	UpDeck.SetText("/\\");
	//Przycisk przewijania w dół tali
	DownDeck = Button(settings::PosX(0.83f), settings::PosY(0.93f), settings::PosX(0.86f), settings::PosY(0.98f));
	DownDeck.SetColor(Colors::white, Colors::lightGray);
	DownDeck.SetText("\\/");
	//Przycisk informacji
	InfoButton = Button();
	InfoButton.ChangeState(false);
	//Przycisk startu gry
	StartGame = Button(settings::PosX(0.91f), settings::PosY(0.93f), settings::PosX(0.98f), settings::PosY(0.98f));
	StartGame.SetColor(Colors::white, Colors::lightGray);
	StartGame.SetText("Start");
	StartGame.ChangeState(false);
	Deck = DeckManager(600, 20);
	MenuCards = CardsToSelect();
}
int Menu::MenuLoop()
{
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Nie udalo się zaladowac biblioteki Allegro", NULL, NULL);
		return -1;
	}
	//Timer
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / settings::FPS());

	//Załadowanie wszystkich kart dostępnych w grze
	MenuCards.SetCard(CardList::ReturnAllCards(),Deck.ReturnAmountOfCards());

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(Display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer); //inicjalizacja timera | Nie dawać do pętli gry
		//Obiekty
 
	Card test(CardList::FrozenDog);
	
	//Talia gracza
	
	//test = Images::FrozenDog;
	float mouseX = 0;												//X myszy
	float mouseY = 0;												//Y myszy
	bool ChangeMenu = false;										//Pętla
	bool StartNewGame = false;										//Rozpoczęcie partii
	int firstCard = 0;												//Pierwsza wyświetlana karta z vectora wszystkich kart
	int firstDeckCard = 0;											//Pierwsza wyświetlana karta z vectora tali gracza
	int AmountOfShowCard = sizeof(DeckButtons) / sizeof(Button);	//Liczba kart wyświetlana z talii
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
			float mouseX_percent = (float)events.mouse.x / ScreenWidth;
			float mouseY_percent = (float)events.mouse.y / ScreenHeight;
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
			float mouseX_percent = (float)events.mouse.x / ScreenWidth;
			float mouseY_percent = (float)events.mouse.y / ScreenHeight;
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
			Pages(mouseX, mouseY, &firstCard);							  //Przesuwa karty do wyboru
			MoveDeck(mouseX, mouseY, AmountOfShowCard, &firstDeckCard);   //Przesuwanie tali gracza
			StartCardGame(mouseX, mouseY, &ChangeMenu, &StartNewGame);	  //Start gry
			//Rysowanie
			al_clear_to_color(Colors::darkGray); //tło
			DrawCartToSelect(mouseX, mouseY, firstCard);				//Rysowanie kart do wyboru
			DrawDeck(AmountOfShowCard, firstDeckCard, mouseX, mouseY);  //Rysowanie talii
			//Rysowanie Przycisków
			NextCards.DrawImage();
			NextCards.DrawText(Fonts::BigFont, settings::PosY(0.014f));
			PrevCards.DrawImage();
			PrevCards.DrawText(Fonts::BigFont, settings::PosY(0.014f));
			//Przyciski talii
			UpDeck.DrawImage();
			UpDeck.DrawText(Fonts::NameFont, settings::PosY(0.004f));
			DownDeck.DrawImage();
			DownDeck.DrawText(Fonts::NameFont, settings::PosY(0.004f));
			if (StartGame.IsActive())
			{
				StartGame.DrawImage();
				StartGame.DrawText(Fonts::NameFont, settings::PosY(0.004f));
			}
			//Informacje o umiejętności karty
			if (showInfo)
			{
				DrawInfo(infoPosition.x, infoPosition.y);
			}
			al_flip_display();
		}
	}
	if (StartNewGame)
	{
		Game NewGame(Display, Deck.ReturnDeck(), std::vector<Card>());
		std::cout << "Rozpoczęto partię gry\n";
		return NewGame.GameLoopPvP();
	}
	else
	{
		return 1;
	}
}
//Zmienia stronę kart
//----------------------------------------------------------
void Menu::Pages(float mouseX, float mouseY, int* firstCard)
{
	//Strona kart do wybrania
	if (PrevCards.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		*firstCard -= 10;
		if (*firstCard < 0)
		{
			for (int i = 0; i < MenuCards.AmountOfCards(); i += 10)
			{
				*firstCard += 10;
			}
		}
		infoPosition = { 0 ,0 };
		showInfo = false;
		infoButtonId = -1;
		mouseButton = 0;
	}
	if (NextCards.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		*firstCard += 10;
		if (*firstCard > MenuCards.AmountOfCards())
		{
			*firstCard = 0;
		}
		infoPosition = { 0 ,0 };
		showInfo = false;
		infoButtonId = -1;
		mouseButton = 0;
	}
}
//Przesuwa widok kart
//-----------------------------------------------------------------
void Menu::MoveDeck(float mouseX, float mouseY,int AmountOfShowCard, int* firstDeckCard)
{
	if (UpDeck.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		if (*firstDeckCard > 0)
		{
			*firstDeckCard -= 1;
		}
		mouseButton = 0;
	}
	if (DownDeck.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		if (AmountOfShowCard < Deck.ReturnAmountOfCards() && Deck.ReturnAmountOfCards() - AmountOfShowCard > *firstDeckCard)
		{
			*firstDeckCard += 1;
		}
		mouseButton = 0;
	}
}
void Menu::StartCardGame(float mouseX, float mouseY, bool* ChangeMenu, bool* StartNewGame)
{
	if (StartGame.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		*ChangeMenu = true;
		*StartNewGame = true;
		mouseButton = 0;
	}
}
//Dodaje kartę do tali gracza
//------------------------------------------------------------------
void Menu::AddCard(float mouseX, float mouseY, int *firstCard,int i)
{
	if (CardButtons[i].MouseOn(mouseX, mouseY) && mouseButton == 3)
	{
		//Czy dostępne są jeszcze karty oraz czy można dodać ją do talii
		if (MenuCards.CardsLeftById(i + *firstCard) > 0 && Deck.CanAddCard(MenuCards.SelectCardById(i + *firstCard)))
		{
			Deck.AddCard(MenuCards.TakeCard(i + *firstCard, -1)); //Dodawanie karty
			std::cout << "Wybrano karte o id:" << i + *firstCard << " - " << MenuCards.SelectCardById(i + *firstCard).ReturnName() << std::endl;
		}
		mouseButton = 0;
	}
}
//Wyświetlanie informacji o karcie
//-------------------------------------------------------------------
void Menu::InfoCard(float mouseX, float mouseY, int* firstCard, int i)
{
	if (CardButtons[i].MouseOn(mouseX, mouseY))
	{
		if (mouseButton == 4)
		{
			InfoButton.ChangeState(true);
			infoPosition = { mouseX/ settings::ScrWidth() ,mouseY/ settings::ScrHeight() };
			showInfo = true;
			infoButtonId = *firstCard + i;
			mouseButton = 0;
		}
	}
	//Dokończyć znikanie okienka
	if (!InfoButton.MouseOn(mouseX,mouseY) && !CardButtons[i].MouseOn(mouseX, mouseY) && showInfo && infoButtonId == i + *firstCard)
	{
		InfoButton = Button();
		InfoButton.ChangeState(false);
		infoPosition = { 0 ,0 };
		showInfo = false;
		infoButtonId = -1;
	}
}
//Rysuje informacje o karcie
//-------------------------------------------------------------------
void Menu::DrawInfo(float x, float y)
{
	//al_draw_scaled_bitmap(Images::Crocolisk, 0, 0, 300, 300, settings::PosX(x), settings::PosY(y), settings::PosX(0.5), settings::PosY(0.5), NULL);
	Skills cardSkill = MenuCards.SelectCardById(infoButtonId).ReturnSkill();
	float ImgSizeX = (settings::PosX(x + 0.12) - settings::PosX(x)) / settings::ScrWidth();															//Dolna krawędź karty (współrzędna y)
	al_draw_scaled_bitmap(Images::DescrFrame, 0, 0, 330, 400, settings::PosX(x), settings::PosY(y), settings::PosX(ImgSizeX * 1.1), settings::PosY(ImgSizeX * 1.21f * settings::ProportionScreenWH()), NULL); //ALLEGRO_ALIGN_CENTER
	al_draw_multiline_text(Fonts::NameFont, Colors::white, (settings::PosX(x) + settings::PosX(ImgSizeX * 1.1 + x)) / 2, settings::PosY(y+0.01), settings::PosX(ImgSizeX), settings::PosY(ImgSizeX * 0.1f * settings::ProportionScreenWH()), ALLEGRO_ALIGN_CENTER, (cardSkill.ReturnName() + ":\n" + cardSkill.ReturnDescr()).c_str());
	InfoButton = Button(settings::PosX(x-0.01), settings::PosY(y-0.01), settings::PosX(x) + settings::PosX(ImgSizeX * 1.1) + settings::PosX(0.01), settings::PosY(y) + settings::PosY(ImgSizeX * 1.21f * settings::ProportionScreenWH())+ settings::PosY(0.01));
}
//Rysuje karty do wyboru oraz dodaje wskazaną kartę do talii
//------------------------------------------------------------------
void Menu::DrawCartToSelect(float mouseX, float mouseY,int firstCard)
{
	int NumberOfCards = 10;
	for (int i = 0; i < NumberOfCards; i++)
	{
		if (i + firstCard < MenuCards.AmountOfCards())
		{
			Card CurrentCard = MenuCards.SelectCardById(i + firstCard);
			if (i < (NumberOfCards) / 2)
			{
				CurrentCard.DrawBigCard(0.05f + i * 0.15f, 0.05f);
			}
			else
			{
				CurrentCard.DrawBigCard(0.05f + (i % (NumberOfCards / 2)) * 0.15f, 0.45f);
			}
			std::string Amount = std::to_string(MenuCards.CardsLeftById(i + firstCard));
			if (CurrentCard.ReturnIsHero())
			{
				Amount += "/1";
			}
			else
			{
				Amount += "/3";
			}
			OtherFunctions::DrawTextImage(Images::StatCircle, { CurrentCard.ReturnVertexesPosition().P2.x - settings::PosX(0.015),CurrentCard.ReturnVertexesPosition().P2.y - settings::PosY(0.015) }
			, { 100,100 }, { settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, Amount);
			//Przyciski do wybierania kart
			CardButtons[i] = Button(CurrentCard.ReturnVertexesPosition());
			AddCard(mouseX, mouseY, &firstCard, i);				//Dodanie karty
			InfoCard(mouseX, mouseY, &firstCard, i);			//Włączanie dodatkowych informacji
		}
	}
}
//Rysuje talię gry
//-----------------------------------------------------------------------------------
void Menu::DrawDeck(int AmountOfShowCard,int firstDeckCard,float mouseX,float mouseY)
{
	//Wydane złoto
	al_draw_text(Fonts::SmallValueFont, Colors::white, settings::PosX(0.83f), settings::PosY(0.05f), ALLEGRO_ALIGN_LEFT, Deck.GoldText().c_str());
	//Liczba kart
	if (Deck.CanStartGame())
	{
		al_draw_text(Fonts::SmallValueFont, Colors::lightGreen, settings::PosX(0.98f), settings::PosY(0.05f), ALLEGRO_ALIGN_RIGHT, std::to_string(Deck.ReturnAmountOfCards()).c_str());
		StartGame.ChangeState(true);
	}
	else
	{
		al_draw_text(Fonts::SmallValueFont, Colors::lightRed, settings::PosX(0.98f), settings::PosY(0.05f), ALLEGRO_ALIGN_RIGHT, std::to_string(Deck.ReturnAmountOfCards()).c_str());
		StartGame.ChangeState(false);
	}
	//Karty do wybrania
	for (int i = 0; i < AmountOfShowCard; i++)
	{
		Card CurrentCard = Deck.ReturnCardById(i + firstDeckCard);
		if (Deck.ReturnAmountOfCards() > i + firstDeckCard)
		{
			CurrentCard.DrawSmallCard(0.82f, 0.1f + i * 0.06f);
		}
		//Przyciski do usuwania kart z talii
		DeckButtons[i] = Button(CurrentCard.ReturnVertexesPosition());
		if (DeckButtons[i].MouseOn(mouseX, mouseY) && mouseButton == 1)
		{
			Card RemovedCard(Deck.RemoveCard(i + firstDeckCard));			//Usunięcie karty z talii
			std::cout << "Usunieto karte o id: " << i + firstDeckCard << " - " << RemovedCard.ReturnName() << std::endl;
			MenuCards.TakeCard(MenuCards.ReturnIdOfCard(RemovedCard), 1);	//Oddawanie karty
			mouseButton = 0;
			//Przesunięcie pierwszej wyświetlanej karty z talii
			firstDeckCard -= 1;
			if (firstDeckCard < 0)
			{
				firstDeckCard = 0;
			}
			//CardButtons[i].DrawHitbox();
		}
	}
}



