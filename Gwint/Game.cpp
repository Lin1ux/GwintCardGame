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
	lastUsedCardIndex = -1;
	lastUsedCardRow = -1;
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
	CardPos LastPlayedCard;

	float mouseX = 0;				//X myszy
	float  mouseY = 0;				//Y myszy
	bool GameOver = false;			//Pętla
	bool GameStart = true;			//Początek gry
	int CardsChanged = 0;			//Liczba odrzuconych kart
	//int LastUsedCardIndex = -1;	//Indeks ostatnio użytej karty
	//int skillId = 0;				//Do kontrolowania interfejsu dla specjalnych umiejętności
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
		//Umiejętność transport
		if (events.type == ALLEGRO_EVENT_TIMER && !GameStart && skillId == AllSkills::transport)
		{
			CardPos CardToTake;
			al_clear_to_color(Colors::darkGray);												//tło
			DrawOtherInfo(mouseX, mouseY);														//Rysowanie reszty informacji 
			CardToTake = DrawPlayersCards(mouseX, mouseY);										//Rysowanie kart gracza i zagranie karty
			if (Player.ReturnAmountOfCardOnTable() - Player.NumberOfCardsWithSkill(AllSkills::Transport) < 1)
			{
				skillId = 0;
				continue;
			}
			if (CardToTake.card.ReturnSkill() != AllSkills::Transport && CardToTake.card != Card() && mouseButton == 1)		
			{
				Player.TakeCard(CardToTake.card);											//Dodanie karty do ręki
				Player.RemoveCardFromTable(CardToTake.card.ReturnRow(), CardToTake.index);	//Usunięcie wskazanej karty z stołu
				if (CardToTake.card.ReturnSkill() == AllSkills::Brotherhood)				//Zaktualizowanie wartości braterstwa
				{
					AbilityManager(CardToTake.card);										//Używa umiejętności karty
				}
				skillId = 0;
				mouseButton = 0;
			}
			al_flip_display();
			continue;
		}
		//Umiejętność Trupojad
		if (events.type == ALLEGRO_EVENT_TIMER && !GameStart && skillId == AllSkills::deadEater)
		{
			CardPos SelectedCard;												//Zapamiętanie wybranej karty
			al_clear_to_color(Colors::darkGray);								//tło
			DrawOtherInfo(mouseX, mouseY);										//Rysowanie reszty informacji
			SelectedCard = DrawGraveyard(mouseX, mouseY, PlayersGraveyard);		//Rysowanie cmentarza
			DrawHand(mouseX, mouseY);											//Rysuje karty na ręce
			if (SelectedCard.card != Card())									//Nakładanie bonusowych punktów
			{
				skillId = AllSkills::none;
				GraveyardOn = false;
				//Dokończyć Miejsce na nałożenie bonusu karty
			}
			std::cout << "R="<< lastUsedCardRow<<"I=" << lastUsedCardIndex << "\n";
			al_flip_display();
		}
		//Partia 
		if (events.type == ALLEGRO_EVENT_TIMER && !GameStart && !GraveyardOn)
		{
			Enemy.SetRoundFinished(true);							//Dokończyć usunąć (do testów)

			al_clear_to_color(Colors::darkGray);					//tło
			DrawOtherInfo(mouseX, mouseY);							//Rysowanie reszty informacji 
			LastPlayedCard = DrawPlayersCards(mouseX, mouseY);		//Rysowanie kart gracza i zagranie karty
			while (LastPlayedCard.card != Card())						
			{
				LastPlayedCard.card = AbilityManager(LastPlayedCard.card);	//Używa umiejętności karty
			}
			RoundInfo(mouseX, mouseY);								//Przycisk końca rundy
			RoundResult();											//Koniec rundy
			al_flip_display();										//Wrzucenie na ekran
			continue;
		}
		//Cmentarz
		if (events.type == ALLEGRO_EVENT_TIMER && !GameStart && GraveyardOn)		
		{
			al_clear_to_color(Colors::darkGray);								//tło
			DrawOtherInfo(mouseX, mouseY);										//Rysowanie reszty informacji
			DrawGraveyard(mouseX, mouseY, PlayersGraveyard);					//Rysowanie cmentarza
			DrawHand(mouseX, mouseY);											//Rysuje karty na ręce
			al_flip_display();													//Wrzucenie na ekran
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
CardPos Game::DrawPlayersCards(float mouseX,float mouseY)
{
	std::vector<Card> PlayerHand = Player.ReturnPlayerHand();
	std::vector<Card> PFirst = Player.ReturnMeleeRow();
	std::vector<Card> PSecond = Player.ReturnRangeRow();
	CardPos PlayedCard = { Card(),-1 };
	ClearButtons();
	float StartDrawPointX;

	std::vector<Card> BrotherHoodCards = std::vector<Card>();
	//Umiejętności specjalne (Nwm czemu funkcja nie widzi zmian)
	//Szukanie specjalnych kart I Rząd
	for (int i = 0; i < PFirst.size(); i++)
	{
		if (PFirst[i].ReturnSkill() == AllSkills::Brotherhood && !CardInVector(BrotherHoodCards, PFirst[i]))
		{
			BrotherHoodCards.push_back(PFirst[i]);
		}
	}
	//Nakładanie zmian
	for (int i = 0; i < BrotherHoodCards.size(); i++)
	{
		int multiplayer = Player.NumberOfSpecificCards(BrotherHoodCards[i]);
		for (int j = 0; j<PFirst.size(); j++)
		{
			if (PFirst[j] == BrotherHoodCards[i])
			{
				PFirst[j].ChangeMultiplayer(multiplayer);
			}
		}
	}
	BrotherHoodCards = std::vector<Card>();	//Czyszczenie vectora
	//Szukanie specjalnych kart II rząd
	for (int i = 0; i < PSecond.size(); i++)
	{
		if (PSecond[i].ReturnSkill() == AllSkills::Brotherhood && !CardInVector(BrotherHoodCards, PSecond[i]))
		{
			BrotherHoodCards.push_back(PSecond[i]);
		}
	}
	//Nakładanie zmian
	for (int i = 0; i < BrotherHoodCards.size(); i++)
	{
		int multiplayer = Player.NumberOfSpecificCards(BrotherHoodCards[i]);
		for (int j = 0; j < PSecond.size(); j++)
		{
			if (PSecond[j] == BrotherHoodCards[i])
			{
				PSecond[j].ChangeMultiplayer(multiplayer);
			}
		}
	}
	//Rysowanie 1 rzędu gracza
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +PFirst.size() * 0.08f);
	for (int i = 0; i < PFirst.size(); i++)
	{
		MeleeButtons[i] = Button(PFirst[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.4f));
		//PFirst[i].ChangeMultiplayer(2);
		PFirst[i].DrawCard(StartDrawPointX + i * 0.08f, 0.4f);
		if (MeleeButtons[i].MouseOn(mouseX, mouseY))
		{
			if (skillId != 0)
			{
				PlayedCard.card = PFirst[i];
				PlayedCard.index = i;
			}
			PFirst[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}
	//Rysowanie 2 rzędu gracza
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +PSecond.size() * 0.08f);
	for (int i = 0; i < PSecond.size(); i++)
	{
		RangeButtons[i] = Button(PSecond[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.6f));
		PSecond[i].DrawCard(StartDrawPointX + i * 0.08f, 0.6f);
		if (RangeButtons[i].MouseOn(mouseX, mouseY))
		{
			if (skillId != 0)
			{
				PlayedCard.card = PSecond[i];
				PlayedCard.index = i;
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
			if (mouseButton == 1 && Player.CanPlay(PlayerHand[i]) && PlayerTurn && skillId == 0)
			{
				PlayedCard.card = PlayerHand[i];
				PlayedCard.index = i;
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
	if (PlayerTurn && UsedCard.ReturnSkill() == AllSkills::Brotherhood)	//Braterstwo
	{
		std::vector<Card> Table;
		if (UsedCard.ReturnRow() == CardList::front)
		{
			Table = Player.ReturnMeleeRow();
		}
		if (UsedCard.ReturnRow() == CardList::back)
		{
			Table = Player.ReturnRangeRow();
		}
		int multiplayer = Player.NumberOfSpecificCards(UsedCard);
		
		for (int i = 0; i < Table.size(); i++)
		{
			if (Table[i] == UsedCard)
			{
				Player.SetMultiplayerOfCard(UsedCard.ReturnRow(), i, multiplayer);
			}
		}
	}
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
	}
	if (PlayerTurn && UsedCard.ReturnSkill() == AllSkills::SummonerMortar)	//Przywołanie moździerza
	{
		NewCard = CardList::Mortar;
		if (Player.CanPlay(NewCard))
		{
			Player.PlayCard(NewCard);
		}
	}
	if (PlayerTurn && UsedCard.ReturnSkill() == AllSkills::DeadEater)	//Trupojad
	{
		GraveyardOn = true;
		PlayersGraveyard = true;
		skillId = AllSkills::deadEater;
		lastUsedCardIndex = Player.ReturnAmountOfCardOnTable(UsedCard.ReturnRow())-1;
		lastUsedCardRow = UsedCard.ReturnRow();
	}
	if (PlayerTurn && UsedCard.ReturnSkill() == AllSkills::Banish)	//Wygnanie
	{
		int PlayerHandCard = Player.AmountOfCardsInHand();
		//Usunięcie kart z ręki i wrzucenie ich do cmentarza
		for (int i = PlayerHandCard-1; i >= 0; i--)	
		{
			Card Card = Player.UseCard(i);
			Player.AddCardToGraveyard(Card);
		}
		//Dobranie nowych kart
		for (int i = 0; i < PlayerHandCard; i++)
		{
			Player.TakeCard();
		}
		PlayerHandCard = Enemy.AmountOfCardsInHand();
		//Usunięcie kart z ręki i wrzucenie ich do cmentarza
		for (int i = PlayerHandCard - 1; i >= 0; i--)
		{
			Card Card = Enemy.UseCard(i);
			Enemy.AddCardToGraveyard(Card);
		}
		//Dobranie nowych kart
		for (int i = 0; i < PlayerHandCard; i++)
		{
			Enemy.TakeCard();
		}
	}
	//Umiejętność kart przeciwnika
	return NewCard;
}
//Rysuje inne informacje takie jak ilość kart i liczba wygranych rund
//-------------------------------------------------------------------
void Game::DrawOtherInfo(float mouseX, float mouseY)
{
	Button GraveyardButton;
	//Wygrane gracza
	ALLEGRO_BITMAP* FirstCrystal;
	ALLEGRO_BITMAP* SecondCrystal;
	float ReverseCardSizeX = 0.07f;
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
	al_draw_scaled_bitmap(Images::ReverseCard, 0, 0, 330, 430, settings::PosX(0.865), settings::PosY(0.76), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.12) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Enemy.ReturnAmountOfCardStack()).c_str());
	al_draw_scaled_bitmap(Images::ReverseCard, 0, 0, 330, 430, settings::PosX(0.865), settings::PosY(0.06), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
	//Cmentarz
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.62) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player.ReturnAmountOfCardUsed()).c_str());
	al_draw_scaled_bitmap(Images::ReverseCard, 0, 0, 330, 430, settings::PosX(0.865), settings::PosY(0.56), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
	//Przycisk cmentarzu
	GraveyardButton = Button(settings::PosX(0.865), settings::PosY(0.56), settings::PosX(ReverseCardSizeX) + settings::PosX(0.865), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()) + settings::PosY(0.56));
	if (GraveyardButton.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		mouseButton == 0;
		GraveyardOn = true;
		PlayersGraveyard = true;
		GraveyardFirstCard = 0;
	}
	GraveyardButton.DrawHitbox();
	//Cmentarz przeciwnika
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.32) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Enemy.ReturnAmountOfCardUsed()).c_str());
	al_draw_scaled_bitmap(Images::ReverseCard, 0, 0, 330, 430, settings::PosX(0.865), settings::PosY(0.26), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
	//Przycisk cmentarzu
	GraveyardButton = Button(settings::PosX(0.865), settings::PosY(0.26), settings::PosX(ReverseCardSizeX) + settings::PosX(0.865), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()) + settings::PosY(0.26));
	if (GraveyardButton.MouseOn(mouseX, mouseY) && mouseButton == 1 && !IsEnemyGraveyardLocked())
	{
		mouseButton == 0;
		GraveyardOn = true;
		PlayersGraveyard = false;
		GraveyardFirstCard = 0;
	}
	GraveyardButton.DrawHitbox();
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
//Rysuje karty w cmentarzu
CardPos Game::DrawGraveyard(float mouseX, float mouseY,bool IsPlayerGraveyard)
{
	CardPos CardClicked = {Card(),-1};
	//Przycisk startu gry
	Button LeaveGraveyard(settings::PosX(0.865f), settings::PosY(0.47f), settings::PosX(0.945f), settings::PosY(0.515f));
	LeaveGraveyard.SetColor(Colors::white, Colors::lightGray);
	LeaveGraveyard.SetText("Wyjście");
	//Przycisk następnej strony kart
	Button PrevCard(settings::PosX(0.44f), settings::PosY(0.57f), settings::PosX(0.48f), settings::PosY(0.62f));
	PrevCard.SetColor(Colors::white, Colors::lightGray);
	PrevCard.SetText("<-");
	Button NextCard(settings::PosX(0.49), settings::PosY(0.57f), settings::PosX(0.53), settings::PosY(0.62f));
	NextCard.SetColor(Colors::white, Colors::lightGray);
	NextCard.SetText("->");

	std::vector<Card> PlayerGraveyard;
	if (IsPlayerGraveyard)
	{
		PlayerGraveyard = Player.ReturnCardUsed();
	}
	else
	{
		PlayerGraveyard = Enemy.ReturnCardUsed();
	}
	//Rysowanie instrukcji
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.45f), settings::PosY(0.09f), ALLEGRO_ALIGN_CENTER, "Cmentarz");
	//Rysowanie strony kart
	//Strona kart do wybrania
	if (PrevCard.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		GraveyardFirstCard -= 12;
		if (GraveyardFirstCard < 0)
		{
			for (int i = 0; i < PlayerGraveyard.size(); i += 12)
			{
				GraveyardFirstCard += 12;
			}
		}
		mouseButton = 0;
	}
	if (NextCard.MouseOn(mouseX, mouseY) && mouseButton == 1)
	{
		GraveyardFirstCard += 12;
		if (GraveyardFirstCard > PlayerGraveyard.size())
		{
			GraveyardFirstCard = 0;
		}
		mouseButton = 0;
	}
	int NumberOfCards = 12;
	//Rysowanie cmentarza gracza
	for (int i = 0; i < NumberOfCards; i++)
	{
		if (i + GraveyardFirstCard < PlayerGraveyard.size())
		{
			Card CurrentCard = PlayerGraveyard[i + GraveyardFirstCard];
			if (i < NumberOfCards/2)
			{
				CurrentCard.DrawCard(0.25f + i * 0.08f, 0.16f);
			}
			else
			{
				CurrentCard.DrawCard(0.25f + (i % (NumberOfCards/2)) * 0.08f, 0.36f);
			}
			HandButtons[i] = Button(CurrentCard.ReturnVertexesPosition());
			
			if (HandButtons[i].MouseOn(mouseX, mouseY))	//Rysowanie dużej karty
			{
				CurrentCard.DrawBigCardDescr(0.02f, 0.1f);
				if (mouseButton == 1)					//Zwrócenie narysowanej karty
				{
					CardClicked.card = CurrentCard;
					CardClicked.index = i + GraveyardFirstCard;
					mouseButton = 0;
				}
			}
		}
	}
	//Przyciski
	if (!IsEnemyGraveyardLocked())
	{
		if (LeaveGraveyard.MouseOn(mouseX, mouseY) && mouseButton == 3)	//Wyjście z cmentarza
		{
			GraveyardOn = false;
			mouseButton = 0;
			//Rysowanie przycisków
		}
		LeaveGraveyard.DrawImage();
		LeaveGraveyard.DrawText(Fonts::NameFont, settings::PosY(0.004f));
	}
	if (PlayerGraveyard.size() > NumberOfCards)
	{
		NextCard.DrawImage();
		NextCard.DrawText(Fonts::NameFont, settings::PosY(0.004f));
		PrevCard.DrawImage();
		PrevCard.DrawText(Fonts::NameFont, settings::PosY(0.004f));
	}
	return CardClicked;
}
//Rysuje rękę gracza (bez animacji)
//--------------------------------------------
void Game::DrawHand(float mouseX, float mouseY)
{
	std::vector<Card> PlayerHand = Player.ReturnPlayerHand();
	//Rysowanie ręki gracza
	float StartDrawPointX = OtherFunctions::AlignCenter(0.01f, 0.86f, +PlayerHand.size() * 0.08f);
	for (int i = 0; i < PlayerHand.size(); i++)
	{
		HandButtons[i] = Button(PlayerHand[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.8f));

		PlayerHand[i].DrawCard(StartDrawPointX + i * 0.08f, 0.8f);
		if (HandButtons[i].MouseOn(mouseX, mouseY))
		{
			PlayerHand[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}
}
//Sprawdza czy karta jest w vectorze
//--------------------------------------------------------------------
bool Game::CardInVector(std::vector<Card> CardVector ,Card CardToFind)
{
	bool CardFound = false;
	for (int i = 0; i < CardVector.size(); i++)
	{
		if (CardVector[i] == CardToFind)
		{
			return true;
		}
	}
	return false;
}
//Sprawdza czy włączona jest umiejętność blokująca cmentarz
//---------------------------------
bool Game::IsEnemyGraveyardLocked()
{
	if (skillId == AllSkills::deadEater || skillId == AllSkills::medic)
	{
		return true;
	}
	return false;
}
