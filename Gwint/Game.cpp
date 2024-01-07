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
	//Enemy = PlayerInfo(EnemyDeck);
	Enemy = PlayerInfo(PlayerDeck);	//Dokończyć zmienić później na talię przeciwnika 
	mouseButton = 0;
	ClearButtons();
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

	//Obiekty
	std::vector<Card> PlayerHand;
	std::vector<Card> PFirst;
	std::vector<Card> PSecond;
	Card LastPlayedCard;

	float mouseX = 0;			//X myszy
	float  mouseY = 0;			//Y myszy
	bool GameOver = false;		//Pętla
	bool GameStart = true;		//Początek gry
	int CardsChanged = 0;		//Liczba odrzuconych kart
	//int skillId = 0;			//Do kontrolowania interfejsu dla specjalnych umiejętności
	while (!GameOver)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);	//Czeka do wciśnięcia przycisku

		if (events.type == ALLEGRO_EVENT_KEY_UP)	//Puszczenie klawisza klawiatury
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE: //wciśniecie Escape
				GameOver = true;
				std::cout << "Wcisnieto ESC\n";
				break;
			}
		}
		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)	//Puszczemie przycisku myszy
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
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)	//Wciśnięcie przycisku myszy
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
			printf("X - %d (%.3f)\nY - %d (%.3f)\n\n", events.mouse.x, mouseX_percent, events.mouse.y, mouseY_percent);
		}
		if (events.type == ALLEGRO_EVENT_MOUSE_AXES)				//Pozycja kursora
		{
			mouseX = events.mouse.x;
			mouseY = events.mouse.y;
			mouseButton = 0;
		}
		if (events.type == ALLEGRO_EVENT_TIMER && GameStart)		//Początek gry
		{
			al_clear_to_color(Colors::darkGray);					//tło
			GameStart = GameBegin(mouseX, mouseY,&CardsChanged);	//Wymiana kart 
			al_flip_display();										//Wrzucenie na ekran
			continue;
		}
		if (events.type == ALLEGRO_EVENT_TIMER && !GameStart && skillId == AllSkills::transport)	//Transport
		{
			Card CardToTake;
			al_clear_to_color(Colors::darkGray);												//tło
			DrawOtherInfo();																	//Rysowanie reszty informacji 
			CardToTake = DrawPlayersCards(mouseX, mouseY);										//Rysowanie kart gracza i zagranie karty
			if (Player.ReturnAmountOfCardOnTable() - Player.NumberOfCardsWithSkill(AllSkills::Transport) < 1)
			{
				skillId = 0;
				continue;
			}
			if (CardToTake.ReturnSkill() != AllSkills::Transport && CardToTake != Card() && mouseButton == 1)		
			{
				Player.TakeCard(CardToTake);
				Player.RemoveCardFromTable(CardToTake);
				//Player.TakeCard(Player.RemoveCardFromTable(CardToTake));						//Wymiana karty
				skillId = 0;
				mouseButton = 0;
			}
			al_flip_display();
			continue;
		}
		if (events.type == ALLEGRO_EVENT_TIMER && !GameStart)		//Partia
		{
			Enemy.SetRoundFinished(true);							//Dokończyć usunąć (do testów)
			
			al_clear_to_color(Colors::darkGray);					//tło
			DrawOtherInfo();										//Rysowanie reszty informacji 
			LastPlayedCard = DrawPlayersCards(mouseX, mouseY);		//Rysowanie kart gracza i zagranie karty
			while (LastPlayedCard != Card())						
			{
				LastPlayedCard = AbilityManager(LastPlayedCard);	//Używa umiejętności karty
			}
			//LastPlayedCard = Card();								//Wyczyszczenie użytej karty
			RoundInfo(mouseX, mouseY);								//Przycisk końca rundy
			RoundResult();											//Koniec rundy
			al_flip_display();										//Wrzucenie na ekran
		}
	}
	return 0;
}
//Możliwość wymiany kart w ręce gracza
//Zwraca czy można zacząć grę
//Oraz zmienia wartość liczby zmienionych kart (argument funkjcji)
//----------------------------------------------------------------
bool Game::GameBegin(float mouseX,float mouseY,int *CardsChanged)
{
	//Przycisk startu gry
	Button StartGame(settings::PosX(0.7f), settings::PosY(0.5f), settings::PosX(0.8f), settings::PosY(0.55f));
	StartGame.SetColor(Colors::white, Colors::lightGray);
	StartGame.SetText("Rozpocznij");
	std::vector<Card> PlayerHand = Player.ReturnPlayerHand();
	//Rysowanie instrukcji
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.45f), settings::PosY(0.24f), ALLEGRO_ALIGN_CENTER, "Wybierz kartę którą chcesz odrzucić");
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.45f), settings::PosY(0.29f), ALLEGRO_ALIGN_CENTER, ("Liczba dostępnych przelosowań:  " + std::to_string(2 - *CardsChanged)).c_str());
	//Rysowanie ręki gracza
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
		return false;
	}
	for (int i = 0; i < PlayerHand.size(); i++)
	{
		if (HandButtons[i].MouseOn(mouseX, mouseY) && mouseButton == 1)	//Rysowanie dużej karty
		{
			Player.PutToStack(Player.UseCard(i));	//Usuwa kartę z ręki i dodaje do nie używanych kart
			Player.TakeCard();
			*CardsChanged += 1;
			mouseButton = 0;
		}
	}
	if (*CardsChanged >= 2)	//Osiągnięcie limitu przelosowań kart
	{
		return false;
	}
	StartGame.DrawImage();
	StartGame.DrawText(Fonts::NameFont, settings::PosY(0.005f));
	//StartGame.DrawHitbox();
	return true;
}
//Rysuje karty należące do gracza oraz sprawdza przyciski
//----------------------------------------------------
Card Game::DrawPlayersCards(float mouseX,float mouseY)
{
	std::vector<Card> PlayerHand = Player.ReturnPlayerHand();
	std::vector<Card> PFirst = Player.ReturnMeleeRow();
	std::vector<Card> PSecond = Player.ReturnRangeRow();
	Card PlayedCard = Card();
	ClearButtons();
	float StartDrawPointX;

	//Rysowanie 1 rzędu gracza
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +PFirst.size() * 0.08f);
	for (int i = 0; i < PFirst.size(); i++)
	{
		MeleeButtons[i] = Button(PFirst[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.4f));
		PFirst[i].DrawCard(StartDrawPointX + i * 0.08f, 0.4f);
		if (MeleeButtons[i].MouseOn(mouseX, mouseY))
		{
			if (skillId != 0)
			{
				PlayedCard = PFirst[i];
			}
			PFirst[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}
	//Rysowanie 2 rzędu gracza
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.8f, +PSecond.size() * 0.08f);
	for (int i = 0; i < PSecond.size(); i++)
	{
		RangeButtons[i] = Button(PSecond[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.6f));
		PSecond[i].DrawCard(StartDrawPointX + i * 0.08f, 0.6f);
		if (RangeButtons[i].MouseOn(mouseX, mouseY))
		{
			if (skillId != 0)
			{
				PlayedCard = PSecond[i];
			}
			PSecond[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}

	//Rysowanie ręki gracza
	StartDrawPointX = OtherFunctions::AlignCenter(0.01f, 0.86f, +PlayerHand.size() * 0.08f);
	for (int i = 0; i < PlayerHand.size(); i++)
	{
		HandButtons[i] = Button(PlayerHand[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.8f));

		if (HandButtons[i].MouseOn(mouseX, mouseY))
		{
			PlayerHand[i].DrawBigCardDescr(0.02, 0.1f);
			PlayerHand[i].DrawCard(StartDrawPointX + i * 0.08f, 0.76f);
			if (mouseButton == 1 && Player.CanPlay(PlayerHand[i]) && PlayerTurn)
			{
				PlayedCard = PlayerHand[i];
				Player.PlayCard(Player.UseCard(i));		//Zagranie karty i usunięcie jej z ręki
				mouseButton = 0;
			}
		}
		else
		{
			PlayerHand[i].DrawCard(StartDrawPointX + i * 0.08f, 0.8f);
		}
	}
	return PlayedCard;
}
//Sprawdza i używa odpowiedniej umiejętności
//------------------------------------------
Card Game::AbilityManager(Card UsedCard)
{
	Card NewCard = Card();
	//Umiejętność kart gracza
	if (PlayerTurn && UsedCard.ReturnSkill() == AllSkills::Horde)	//Horda
	{
		NewCard = Player.UseCard(UsedCard);	
		if (NewCard != Card())
		{
			Player.PlayCard(NewCard);
			return NewCard;
		}
		NewCard = Player.UseStackCard(UsedCard);
		std::cout << NewCard.ReturnName()<<":"<<NewCard.ReturnCost() << "\n";
		if (NewCard != Card())
		{
			Player.PlayCard(NewCard);
			return NewCard;
		}
	}
	if (PlayerTurn && UsedCard.ReturnSkill() == AllSkills::Thief)	//Złodziej
	{
		NewCard = Enemy.TakeCardFromStack();
		if (Player.CanPlay(NewCard))
		{
			Player.PlayCard(NewCard);
		}
		//Player.TakeCard(Enemy.TakeCardFromStack());
	}
	if (PlayerTurn && UsedCard.ReturnSkill() == AllSkills::Transport)	//Transport
	{
		skillId = AllSkills::transport;
		//TakeCard
	}
	if (PlayerTurn && UsedCard.ReturnSkill() == AllSkills::SummonerMortar)	//Przywoływacz moździerz
	{
		NewCard = CardList::Mortar;
		if (Player.CanPlay(NewCard))
		{
			Player.PlayCard(NewCard);
		}
	}
	//Umiejętność kart przeciwnika
	return NewCard;
}
//Rysuje inne informacje takie jak ilość kart i liczba wygranych rund
//------------------------
void Game::DrawOtherInfo()
{
	//Wygrane gracza
	ALLEGRO_BITMAP* FirstCrystal;
	ALLEGRO_BITMAP* SecondCrystal;
	if (Enemy.ReturnRoundsWon() == 0)
	{
		FirstCrystal = Images::YellowCrystal;
		SecondCrystal = Images::PurpleCrystal;
	}
	else if (Enemy.ReturnRoundsWon() == 1)
	{
		FirstCrystal = Images::EmptyCrystal;
		SecondCrystal = Images::PurpleCrystal;
	}
	else
	{
		FirstCrystal = Images::EmptyCrystal;
		SecondCrystal = Images::EmptyCrystal;
	}
	//Kryształy gracz
	al_draw_scaled_bitmap(FirstCrystal, 0, 0, 100, 100, settings::PosX(0.17), settings::PosY(0.39), settings::PosX(0.015), settings::PosY(0.015 * settings::ProportionScreenWH()), NULL);
	al_draw_scaled_bitmap(SecondCrystal, 0, 0, 100, 100, settings::PosX(0.19), settings::PosY(0.39), settings::PosX(0.015), settings::PosY(0.015 * settings::ProportionScreenWH()), NULL);
	//Kryształy przeciwnika
	if (Player.ReturnRoundsWon() == 0)
	{
		FirstCrystal = Images::YellowCrystal;
		SecondCrystal = Images::PurpleCrystal;
	}
	else if (Player.ReturnRoundsWon() == 1)
	{
		FirstCrystal = Images::EmptyCrystal;
		SecondCrystal = Images::PurpleCrystal;
	}
	else
	{
		FirstCrystal = Images::EmptyCrystal;
		SecondCrystal = Images::EmptyCrystal;
	}
	al_draw_scaled_bitmap(FirstCrystal, 0, 0, 100, 100, settings::PosX(0.17), settings::PosY(0.34), settings::PosX(0.015), settings::PosY(0.015 * settings::ProportionScreenWH()), NULL);
	al_draw_scaled_bitmap(SecondCrystal, 0, 0, 100, 100, settings::PosX(0.19), settings::PosY(0.34), settings::PosX(0.015), settings::PosY(0.015 * settings::ProportionScreenWH()), NULL);
	//Rzędy gracza
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.783),settings::PosY(0.45) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player.ReturnMeleePoints()).c_str());
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.783),settings::PosY(0.65) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player.ReturnRangePoints()).c_str());
	//Rzędy przeciwnika
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.783),settings::PosY(0.25) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Enemy.ReturnMeleePoints()).c_str());
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.783),settings::PosY(0.05) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Enemy.ReturnRangePoints()).c_str());
	//Suma punktów rzędów
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.165),settings::PosY(0.25) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Enemy.CountPoints()).c_str());
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.165),settings::PosY(0.45) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player.CountPoints()).c_str());
	//Nie dobrane karty
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.82) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player.ReturnAmountOfCardStack()).c_str());
	CardList::BrotherOfBlood.DrawCard(0.865, 0.76);
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.12) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Enemy.ReturnAmountOfCardStack()).c_str());
	CardList::BrotherOfBlood.DrawCard(0.865, 0.06);
	//Talia użytych kart
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.62) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player.ReturnAmountOfCardUsed()).c_str());
	CardList::BrotherOfBlood.DrawCard(0.865, 0.56);
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.32) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Enemy.ReturnAmountOfCardUsed()).c_str());
	CardList::BrotherOfBlood.DrawCard(0.865, 0.26);
}
//Odpowiada za koniec rundy
//--------------------------------------------
void Game::RoundInfo(float mouseX,float mouseY)
{
	Button EndRound(settings::PosX(0.865f), settings::PosY(0.47f), settings::PosX(0.945f), settings::PosY(0.515f));
	EndRound.SetColor(Colors::white, Colors::lightGray);
	EndRound.SetText("Koniec tury");

	if (EndRound.MouseOn(mouseX,mouseY) && mouseButton == 1)
	{
		Player.SetRoundFinished(true);
		mouseButton = 0;	
	}
	EndRound.DrawImage();
	//EndRound.DrawHitbox();
	EndRound.DrawText(Fonts::SmallValueFont,settings::PosY(0.004) );
}
//Oblicza wynik rundy i czyści stół, zwraca true jeśli runda się zakończyła
//-------------------------------------------------------------------------
bool Game::RoundResult()
{
	if (!Player.IsFinishedRound() || !Enemy.IsFinishedRound())
	{
		return false;
	}
	int playerPoints = Player.CountPoints();
	int enemyPoints = Enemy.CountPoints();
	//Sprawdzanie kto wygrał rundę
	if (playerPoints > enemyPoints)
	{
		Player.RoundWon();
	}
	else if (playerPoints < enemyPoints)
	{
		Enemy.RoundWon();
	}
	else
	{
		Player.RoundWon();
		Enemy.RoundWon();
	}
	//Przygotowanie do następnej rundy
	Player.SetRoundFinished(false);
	Enemy.SetRoundFinished(false);
	Player.EndRound();
	Enemy.EndRound();
	return true;
}
//Czyści zawartość przycisków
//---------------------------
void Game::ClearButtons()
{
	for (int i = 0; i < 10; i++)
	{
		HandButtons[i] = Button();
	}
	for (int i = 0; i < 6; i++)
	{
		MeleeButtons[i] = Button();
		RangeButtons[i] = Button();
	}

}