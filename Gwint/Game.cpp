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
#include "CardValues.h"
#include "HistoryStack.h"

//Konstruktor
Game::Game(ALLEGRO_DISPLAY* Disp,std::vector<Card> PlayerDeck, std::vector<Card> EnemyDeck)
{
	Display = Disp;
	player1Turn = true;							//Tura 1 gracza
	Player = PlayerInfo(PlayerDeck);			
	Enemy = PlayerInfo(EnemyDeck);
	Player.SetReverse(Images::RedReverseCard);
	Enemy.SetReverse(Images::BlueReverseCard);
	mouseButton = 0;
	lastUsedCardIndex = -1;
	lastUsedCardRow = -1;
	cardPlayed = false;
	gameEnd = false;
	TurnBegin = true;
	Player1 = &Player;
	Player2 = &Enemy;
	ClearButtons();
}

//Pętla gry gracz vs gracz
//-------------------------------
int Game::GameLoopPvP()
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
	int RoundNumber = 0;			//Numer rundy

	bool timerEvent = false;
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
		timerEvent = events.type == ALLEGRO_EVENT_TIMER;
		al_clear_to_color(Colors::darkGray);						//tło
		//Wymiana kart na początku gry
		if (timerEvent && GameStart && !TurnBegin)
		{
			GameStart = GameBegin(mouseX, mouseY,&CardsChanged);	//Wymiana kart 
			al_flip_display();										//Wrzucenie na ekran
			continue;
		}
		//Ukrycie kart do wymiany
		if (timerEvent && GameStart && TurnBegin)
		{
			HiddenGameBegin(mouseX, mouseY);						//Początek wymiany kart kart 
			al_flip_display();										//Wrzucenie na ekran
			continue;
		}
		//Podsumowanie gry
		if (gameEnd)
		{
			GameOver = DrawSummary(mouseX, mouseY);
			al_flip_display();
			continue;
		}
		//Umiejętność transport
		if (timerEvent && !GameStart && skillId == AllSkills::transport)
		{
			CardPos CardToTake;
			DrawTip("Kliknij na swoją kartę na stole");											//Rysuje wskazówkę
			DrawOtherInfo(mouseX, mouseY);														//Rysowanie reszty informacji 
			CardToTake = DrawPlayersCards(mouseX, mouseY);										//Rysowanie kart gracza i zagranie karty
			//Czy występują inne karty oprócz Transportu
			if (Player1->ReturnAmountOfCardOnTable() - Player1->NumberOfCardsWithSkill(AllSkills::Transport) < 1)
			{
				skillId = 0;
				continue;
			}
			//Czy są zwykłe karty
			if (Player1->ReturnAmountOfCardOnTable(true) < 1)
			{
				skillId = 0;
				continue;
			}
			if (CardToTake.card.ReturnSkill() != AllSkills::Transport && CardToTake.card != Card() && !CardToTake.card.ReturnIsHero() && mouseButton == 1 && CardToTake.isPlayerCard)
			{
				Player1->TakeCard(CardToTake.card);												//Dodanie karty do ręki
				Player1->RemoveCardFromTable(CardToTake.card.ReturnRow(), CardToTake.index);	//Usunięcie wskazanej karty z stołu
				History.UpdateTarget(CardToTake.card);
				if (CardToTake.card.ReturnSkill() == AllSkills::Brotherhood)					//Zaktualizowanie wartości braterstwa
				{
					AbilityManager(CardToTake.card);											//Używa umiejętności karty
				}
				skillId = 0;
				mouseButton = 0;
			}
			al_flip_display();
			continue;
		}
		//Umiejętność Strzelec
		if (timerEvent && !GameStart && skillId == AllSkills::archer)
		{
			CardPos TargetCard;
			DrawTip("Kliknij na kartę przeciwnika");											//Rysuje wskazówkę
			DrawOtherInfo(mouseX, mouseY);														//Rysowanie reszty informacji 
			TargetCard = DrawPlayersCards(mouseX, mouseY);										//Rysowanie kart gracza i zagranie karty
			if (Player2->ReturnAmountOfCardOnTable(true) <= 0)
			{
				skillId = 0;
				continue;
			}
			if (mouseButton == 1 && TargetCard.card != Card() && !TargetCard.isPlayerCard && !TargetCard.card.ReturnIsHero())
			{
				//Miejsce na zadanie obrażeń
				History.UpdateTarget(TargetCard.card);
				Player2->AddDiffrenceOfCard(TargetCard.card.ReturnRow(), TargetCard.index, -3);
				skillId = 0;
				mouseButton = 0;
			}
			al_flip_display();
			continue;
		}
		//Umiejętność Trupojad
		if (timerEvent && !GameStart && (skillId == AllSkills::deadEater || skillId == AllSkills::goldDeadEater))
		{
			CardPos SelectedCard;												//Zapamiętanie wybranej karty
			if (Player1->ReturnAmountOfCardUsed() < 1)							//Jeśli nie ma kart w cmentarzu
			{
				skillId = AllSkills::none;
				GraveyardOn = false;
				continue;
			}
			DrawOtherInfo(mouseX, mouseY);												//Rysowanie reszty informacji
			if (skillId == AllSkills::deadEater)
			{
				SelectedCard = DrawGraveyard(mouseX, mouseY, PlayersGraveyard,false);		//Rysowanie cmentarza
			}
			if (skillId == AllSkills::goldDeadEater)
			{
				SelectedCard = DrawGraveyard(mouseX, mouseY, PlayersGraveyard, true);		//Rysowanie cmentarza
			}
			DrawHand(mouseX, mouseY);													//Rysuje karty na ręce
			if (SelectedCard.card != Card())											//Nakładanie bonusowych punktów
			{
				skillId = AllSkills::none;
				GraveyardOn = false;
				History.UpdateTarget(SelectedCard.card);
				Player1->SetDiffrenceOfCard(lastUsedCardRow, lastUsedCardIndex, SelectedCard.card.ReturnValue());	//Nakładanie bonusowych wartości
				Player1->RemoveCardFromGraveyard(SelectedCard.card);												//Usunięcie karty z cmentarza
			}
			al_flip_display();
			continue;
		}
		//Umiejętność Medyk
		if (timerEvent && !GameStart && (skillId == AllSkills::medic || skillId == AllSkills::goldMedic))
		{
			CardPos SelectedCard;	
			if (Player1->ReturnAmountOfCardUsed() < 1)							//Jeśli nie ma kart w cmentarzu
			{
				skillId = AllSkills::none;
				GraveyardOn = false;
				continue;
			}
			int frontCard = Player1->ReturnAmountOfCardsByRow(CardList::front);
			int backCard = Player1->ReturnAmountOfCardsByRow(CardList::back);
			//Brak kart II rzędu i brak miejsca w I rzędzie 
			if(frontCard > 1 && backCard == 0 && !Player1->CanPlay(CardList::front))
			{
				skillId = AllSkills::none;
				GraveyardOn = false;
				continue;
			}
			//Brak kart I rzędu i brak miejsca w II rzędzie 
			if (backCard > 1 && frontCard == 0 && !Player1->CanPlay(CardList::back))
			{
				skillId = AllSkills::none;
				GraveyardOn = false;
				continue;
			}
			//Brak Miejsca w obu rzędach
			if (!Player1->CanPlay(CardList::front) && !Player1->CanPlay(CardList::back))
			{
				skillId = AllSkills::none;
				GraveyardOn = false;
				continue;
			}
			//Zapamiętanie wybranej karty
			DrawOtherInfo(mouseX, mouseY);												//Rysowanie reszty informacji
			if (skillId == AllSkills::medic)
			{
				SelectedCard = DrawGraveyard(mouseX, mouseY, PlayersGraveyard,false);		//Rysowanie cmentarza
			}
			if (skillId == AllSkills::goldMedic)
			{
				SelectedCard = DrawGraveyard(mouseX, mouseY, PlayersGraveyard, true);		//Rysowanie cmentarza
			}
			DrawHand(mouseX, mouseY);													//Rysuje karty na ręce
			if (SelectedCard.card != Card())	//Nakładanie bonusowych punktów
			{
				skillId = AllSkills::none;
				GraveyardOn = false;
				//Zagranie karty
				History.UpdateTarget(SelectedCard.card);
				Player1->PlayCard(SelectedCard.card);
				Player1->RemoveCardFromGraveyard(SelectedCard.card);
				while (SelectedCard.card != Card())
				{
					SelectedCard.card = AbilityManager(SelectedCard.card);		//Używa umiejętności karty
				}
			}
			al_flip_display();
			continue;
		}
		//Początek tury gracza
		if (timerEvent && !GameStart && !GraveyardOn && TurnBegin)
		{
			//Automatyczna zmiana gracza
			if (Player1->IsFinishedRound() || Player1->ReturnAmountOfCardInHand() <= 0)
			{
				Player1->SetRoundFinished(true);
				NextPlayer();
				TurnBegin = false;
				continue;
			}
			TurnBegin = true;
			DrawOtherInfo(mouseX, mouseY);									//Rysowanie reszty informacji 
			DrawHiddenHand(mouseX, mouseY);									//Rysowanie ukrytej ręki
			EndRoundButton(mouseX, mouseY);									//Przycisk końca rundy
			RoundResult(&RoundNumber);										//Koniec rundy
			al_flip_display();												//Wrzucenie na ekran
			continue;
		}
		//Partia 
		if (timerEvent && !GameStart && !GraveyardOn && !TurnBegin)
		{
			DrawOtherInfo(mouseX, mouseY);									//Rysowanie reszty informacji 
			LastPlayedCard = DrawPlayersCards(mouseX, mouseY);				//Rysowanie kart gracza i zagranie karty
			while (LastPlayedCard.card != Card())						
			{
				LastPlayedCard.card = AbilityManager(LastPlayedCard.card);	//Używa umiejętności karty
			}
			//Zagranie karty i przekazanie ruchu następnemu graczowi
			if (cardPlayed && skillId == 0)
			{
				NextPlayer();
				TurnBegin = true;
				cardPlayed = false;
			}
			EndRoundButton(mouseX, mouseY);									//Przycisk końca rundy
			RoundResult(&RoundNumber);										//Koniec rundy
			al_flip_display();												//Wrzucenie na ekran
			continue;
		}
		//Cmentarz
		if (timerEvent && !GameStart && GraveyardOn)
		{
			DrawOtherInfo(mouseX, mouseY);									//Rysowanie reszty informacji
			DrawGraveyard(mouseX, mouseY, PlayersGraveyard,true);			//Rysowanie cmentarza
			DrawHand(mouseX, mouseY);										//Rysuje karty na ręce
			al_flip_display();												//Wrzucenie na ekran
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
	std::vector<Card> PlayerHand = Player1->ReturnPlayerHand();
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
		mouseButton = 0;
		if (player1Turn)
		{
			*CardsChanged = 0;
			NextPlayer();
			TurnBegin = true;
			return true;
		}
		NextPlayer();
		TurnBegin = true;
		return false;
	}
	for (int i = 0; i < PlayerHand.size(); i++)
	{
		if (HandButtons[i].MouseOn(mouseX, mouseY) && mouseButton == 1)	//Rysowanie dużej karty
		{
			Player1->PutToStack(Player1->UseCard(i));	//Usuwa kartę z ręki i dodaje do nie używanych kart
			Player1->TakeCard();
			*CardsChanged += 1;
			mouseButton = 0;
		}
	}
	if (*CardsChanged >= 2)	//Osiągnięcie limitu przelosowań kart
	{
		if (player1Turn)
		{
			*CardsChanged = 0;
			NextPlayer();
			TurnBegin = true;
			return true;
		}
		NextPlayer();
		TurnBegin = true;
		return false;
	}
	StartGame.DrawImage();
	StartGame.DrawText(Fonts::NameFont, settings::PosY(0.005f));
	return true;
}
//Zasłonięte karty do wymiany
//----------------------------------------------------
void Game::HiddenGameBegin(float mouseX, float mouseY)
{
	std::vector<Card> PlayerHand = Player1->ReturnPlayerHand();
	float ReverseCardSizeX = 0.077f;
	//Rysowanie instrukcji
	if (player1Turn)
	{
		al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.45f), settings::PosY(0.24f), ALLEGRO_ALIGN_CENTER, "Gracz 1");
	}
	else
	{
		al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.45f), settings::PosY(0.24f), ALLEGRO_ALIGN_CENTER, "Gracz 2");
	}
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.45f), settings::PosY(0.29f), ALLEGRO_ALIGN_CENTER, "Kliknij na dowolną kartę aby odkryć pozostałe");
	//Rysowanie ręki gracza
	for (int i = 0; i < PlayerHand.size(); i++)
	{
		if (i < 5)
		{
			HandButtons[i] = Button(PlayerHand[i].NormalCardVertexesPosition(0.25f + i * 0.08f, 0.36f));
			al_draw_scaled_bitmap(Player1->ReturnReverse(), 0, 0, 330, 430, settings::PosX(0.25f + i * 0.08f), settings::PosY(0.36f), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
		}
		else
		{
			HandButtons[i] = Button(PlayerHand[i].NormalCardVertexesPosition(0.25f + (i % (5)) * 0.08f, 0.56f));
			al_draw_scaled_bitmap(Player1->ReturnReverse(), 0, 0, 330, 430, settings::PosX(0.25f + (i % (5)) * 0.08f), settings::PosY(0.56f), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
		}
		if (HandButtons[i].MouseOn(mouseX, mouseY) && mouseButton == 1)	//Rysowanie dużej karty
		{
			TurnBegin = false;
			mouseButton = 0;
		}
	}
}
//Rysuje karty należące do gracza oraz sprawdza przyciski
//----------------------------------------------------
CardPos Game::DrawPlayersCards(float mouseX,float mouseY)
{
	std::vector<Card> PlayerHand = Player1->ReturnPlayerHand();
	std::vector<Card> PFirst = Player1->ReturnMeleeRow();
	std::vector<Card> PSecond = Player1->ReturnRangeRow();
	std::vector<Card> EFirst = Player2->ReturnMeleeRow();
	std::vector<Card> ESecond = Player2->ReturnRangeRow();
	CardPos PlayedCard = { Card(),-1 };
	ClearButtons();
	float StartDrawPointX;

	//Rysowanie 1 rzędu gracza
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +PFirst.size() * 0.08f);
	for (int i = 0; i < PFirst.size(); i++)
	{
		MeleeButtons[i] = Button(PFirst[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.41f));
		PFirst[i].DrawCard(StartDrawPointX + i * 0.08f, 0.41f,Player1->ReturnCurrentValueOfCard(CardList::front, i));
		if (MeleeButtons[i].MouseOn(mouseX, mouseY))
		{
			if (skillId != 0)
			{
				PlayedCard.card = PFirst[i];
				PlayedCard.index = i;
				PlayedCard.isPlayerCard = true;
			}
			PFirst[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}
	//Rysowanie 1 rzędu przeciwnika
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +EFirst.size() * 0.08f);
	for (int i = 0; i < EFirst.size(); i++)
	{
		EMeleeButtons[i] = Button(EFirst[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.21f));
		EFirst[i].DrawCard(StartDrawPointX + i * 0.08f, 0.21f, Player2->ReturnCurrentValueOfCard(CardList::front, i));
		if (EMeleeButtons[i].MouseOn(mouseX, mouseY))
		{
			if (skillId != 0)
			{
				PlayedCard.card = EFirst[i];
				PlayedCard.index = i;
				PlayedCard.isPlayerCard = false;
			}
			EFirst[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}
	//Rysowanie 2 rzędu gracza
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +PSecond.size() * 0.08f);
	for (int i = 0; i < PSecond.size(); i++)
	{
		RangeButtons[i] = Button(PSecond[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.61f));
		PSecond[i].DrawCard(StartDrawPointX + i * 0.08f, 0.61f,Player1->ReturnCurrentValueOfCard(CardList::back, i));
		if (RangeButtons[i].MouseOn(mouseX, mouseY))
		{
			if (skillId != 0)
			{
				PlayedCard.card = PSecond[i];
				PlayedCard.index = i;
				PlayedCard.isPlayerCard = true;
			}
			PSecond[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}
	//Rysowanie 2 rzędu przeciwnika
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +ESecond.size() * 0.08f);
	for (int i = 0; i < ESecond.size(); i++)
	{
		ERangeButtons[i] = Button(ESecond[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.01f));
		ESecond[i].DrawCard(StartDrawPointX + i * 0.08f, 0.01f, Player2->ReturnCurrentValueOfCard(CardList::back, i));
		if (ERangeButtons[i].MouseOn(mouseX, mouseY))
		{
			if (skillId != 0)
			{
				PlayedCard.card = ESecond[i];
				PlayedCard.index = i;
				PlayedCard.isPlayerCard = false;
			}
			ESecond[i].DrawBigCardDescr(0.02, 0.1f);
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
			if (mouseButton == 1 && Player1->CanPlay(PlayerHand[i]) && skillId == 0)
			{
				PlayedCard.card = PlayerHand[i];
				PlayedCard.index = i;
				PlayedCard.isPlayerCard = true;
				Card NewCard = Player1->UseCard(i);
				if (NewCard.ReturnSkill() == AllSkills::Spy)
				{
					Player2->PlayCard(NewCard);		//Zagranie karty i usunięcie jej z ręki
				}
				else
				{
					Player1->PlayCard(NewCard);		//Zagranie karty i usunięcie jej z ręki
				}
				//Zagranie karty
				cardPlayed = true;
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
	int PlayerNumber;
	bool CanAddAction = true;
	//History.AddAction({ UsedCard, Card(),UsedCard.ReturnSkill() });
	if (player1Turn)
	{
		PlayerNumber = 1;
	}
	else
	{
		PlayerNumber = 2;
	}
	History.AddAction({ PlayerNumber, UsedCard, Card(),UsedCard.ReturnSkill()});
	Card NewCard = Card();
	//Umiejętność kart gracza
	if (UsedCard.ReturnSkill() == AllSkills::Brotherhood)	//Braterstwo
	{
		std::vector<Card> Table;
		if (UsedCard.ReturnRow() == CardList::front)
		{
			Table = Player1->ReturnMeleeRow();
		}
		if (UsedCard.ReturnRow() == CardList::back)
		{
			Table = Player1->ReturnRangeRow();
		}
		int multiplayer = Player1->NumberOfSpecificCards(UsedCard);
		
		for (int i = 0; i < Table.size(); i++)
		{
			if (Table[i] == UsedCard)
			{
				Player1->SetMultiplayerOfCard(UsedCard.ReturnRow(), i, multiplayer);
			}
		}
		//Zapisanie w histori efektu braterstwa na drugą taką kartę
		if (multiplayer > 1)
		{
			History.UpdateTarget(UsedCard);
		}
	}
	if (UsedCard.ReturnSkill() == AllSkills::Medic)	//Medyk
	{
		GraveyardOn = true;
		PlayersGraveyard = true;
		skillId = AllSkills::medic;
	}
	if (UsedCard.ReturnSkill() == AllSkills::GoldMedic)	//Złoty Medyk
	{
		GraveyardOn = true;
		PlayersGraveyard = true;
		skillId = AllSkills::goldMedic;
	}
	if (UsedCard.ReturnSkill() == AllSkills::Spy)		//Szpieg
	{
		Player1->TakeCard();
		History.UpdateTarget(Player1->LastCardInHand());
	}
	if (UsedCard.ReturnSkill() == AllSkills::Executioner)	//Egzekutor
	{
		int numRemovedCard = 0;
		numRemovedCard = Player2->RemoveAllCardsWithValue(Player2->MinValue(),true, &History, UsedCard, PlayerNumber);
		std::cout << numRemovedCard << "\n";
		if (numRemovedCard > 0)
		{
			History.RemoveActionEnd(numRemovedCard);
		}
	}
	if (UsedCard.ReturnSkill() == AllSkills::Archer)	//Strzelec
	{
		skillId = AllSkills::archer;
	}
	if (UsedCard.ReturnSkill() == AllSkills::Horde)	//Horda
	{
		if (Player1->CanPlay(UsedCard))
		{
			NewCard = Player1->UseStackCard(UsedCard);
			//std::cout << NewCard.ReturnName()<<":"<<NewCard.ReturnCost() << "\n";
			if (NewCard != Card())
			{
				Player1->PlayCard(NewCard);
				History.UpdateTarget(NewCard);
				return NewCard;
			}
		}
	}
	if (UsedCard.ReturnSkill() == AllSkills::Thief)	//Złodziej
	{
		NewCard = Player2->TakeCardFromStack();
		if (Player1->CanPlay(NewCard))
		{
			Player1->PlayCard(NewCard);
			History.UpdateTarget(NewCard);
		}
	}
	if (UsedCard.ReturnSkill() == AllSkills::Transport)	//Transport
	{
		skillId = AllSkills::transport;
	}
	if (UsedCard.ReturnSkill() == AllSkills::SummonerMortar)	//Przywołanie moździerza
	{
		NewCard = CardList::Mortar;
		if (Player1->CanPlay(NewCard))
		{
			Player1->PlayCard(NewCard);
			History.UpdateTarget(NewCard);
		}
	}
	if ((UsedCard.ReturnSkill() == AllSkills::DeadEater || UsedCard.ReturnSkill() == AllSkills::GoldDeadEater))	//Trupojad
	{
		GraveyardOn = true;
		PlayersGraveyard = true;
		if (UsedCard.ReturnSkill() == AllSkills::DeadEater)
		{
			skillId = AllSkills::deadEater;
		}
		if (UsedCard.ReturnSkill() == AllSkills::GoldDeadEater)
		{
			skillId = AllSkills::goldDeadEater;
		}
		lastUsedCardIndex = Player1->ReturnAmountOfCardOnTable(UsedCard.ReturnRow())-1;
		lastUsedCardRow = UsedCard.ReturnRow();
	}
	if (UsedCard.ReturnSkill() == AllSkills::Slayer) //Pogromca
	{
		int AmountOfRemovedCard = 0;
		int CardIndex = Player1->ReturnAmountOfCardOnTable(UsedCard.ReturnRow()) - 1;	//Indeks zagranej karty
		int CardRow = UsedCard.ReturnRow();											
		
		int Max;
		if (Player1->MaxValue(CardRow, CardIndex) >= Player2->MaxValue())
		{
			Max = Player1->MaxValue(CardRow, CardIndex);
			//Usuwanie kart
			AmountOfRemovedCard += Player1->RemoveAllCardsWithValue(CardRow, CardIndex, Max,true,&History,UsedCard, PlayerNumber);
			AmountOfRemovedCard += Player2->RemoveAllCardsWithValue(Max, true, &History, UsedCard, PlayerNumber);
		}
		else if (Player1->MaxValue(CardRow, CardIndex) < Player2->MaxValue());
		{
			Max = Player2->MaxValue();
			//Usuwanie kart
			AmountOfRemovedCard += Player1->RemoveAllCardsWithValue(CardRow, CardIndex,Max, true, &History, UsedCard, PlayerNumber);
			AmountOfRemovedCard += Player2->RemoveAllCardsWithValue(Max, true, &History, UsedCard, PlayerNumber);
		}
		if (AmountOfRemovedCard > 0)
		{
			History.RemoveActionEnd(AmountOfRemovedCard);
		}
	}
	if (UsedCard.ReturnSkill() == AllSkills::Banish)	//Wygnanie
	{
		int PlayerHandCard = Player1->AmountOfCardsInHand();
		//Usunięcie kart z ręki i wrzucenie ich do cmentarza
		for (int i = PlayerHandCard-1; i >= 0; i--)	
		{
			Card Card = Player1->UseCard(i);
			Player1->AddCardToGraveyard(Card);
		}
		//Dobranie nowych kart
		for (int i = 0; i < PlayerHandCard; i++)
		{
			Player1->TakeCard();
		}
	}
	return NewCard;
}
//Rysuje inne informacje takie jak ilość kart i liczba wygranych rund
//-------------------------------------------------------------------
void Game::DrawOtherInfo(float mouseX, float mouseY)
{
	Button GraveyardButton;
	//Tura gracza
	if (player1Turn)
	{
		al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.01f), settings::PosY(0.01f), ALLEGRO_ALIGN_LEFT, "Tura gracza 1");
	}
	else
	{
		al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.01f), settings::PosY(0.01f), ALLEGRO_ALIGN_LEFT, "Tura gracza 2");
	}
	//Wygrane gracza
	ALLEGRO_BITMAP* FirstCrystal;
	ALLEGRO_BITMAP* SecondCrystal;
	float ReverseCardSizeX = 0.07f;
	if (Player2->ReturnRoundsWon() == 0)
	{
		FirstCrystal = Images::YellowCrystal;
		SecondCrystal = Images::PurpleCrystal;
	}
	else if (Player2->ReturnRoundsWon() == 1)
	{
		FirstCrystal = Images::EmptyCrystal;
		SecondCrystal = Images::PurpleCrystal;
	}
	else
	{
		FirstCrystal = Images::EmptyCrystal;
		SecondCrystal = Images::EmptyCrystal;
	}
	//Kryształy graczy
	al_draw_scaled_bitmap(FirstCrystal, 0, 0, 100, 100, settings::PosX(0.17), settings::PosY(0.39), settings::PosX(0.015), settings::PosY(0.015 * settings::ProportionScreenWH()), NULL);
	al_draw_scaled_bitmap(SecondCrystal, 0, 0, 100, 100, settings::PosX(0.19), settings::PosY(0.39), settings::PosX(0.015), settings::PosY(0.015 * settings::ProportionScreenWH()), NULL);
	//Kryształy przeciwnika
	if (Player1->ReturnRoundsWon() == 0)
	{
		FirstCrystal = Images::YellowCrystal;
		SecondCrystal = Images::PurpleCrystal;
	}
	else if (Player1->ReturnRoundsWon() == 1)
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
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player1->ReturnMeleePoints()).c_str());
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.783),settings::PosY(0.65) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player1->ReturnRangePoints()).c_str());
	//Rzędy przeciwnika
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.783),settings::PosY(0.25) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player2->ReturnMeleePoints()).c_str());
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.783),settings::PosY(0.05) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player2->ReturnRangePoints()).c_str());
	//Suma punktów rzędów
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.165),settings::PosY(0.25) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player2->CountPoints()).c_str());
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.165),settings::PosY(0.45) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player1->CountPoints()).c_str());
	//Nie dobrane karty
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.82) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player1->ReturnAmountOfCardStack()).c_str());

	al_draw_scaled_bitmap(Player1->ReturnReverse(), 0, 0, 330, 430, settings::PosX(0.865), settings::PosY(0.76), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.12) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player2->ReturnAmountOfCardStack()).c_str());
	al_draw_scaled_bitmap(Player2->ReturnReverse(), 0, 0, 330, 430, settings::PosX(0.865), settings::PosY(0.06), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
	//Cmentarz
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.62) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player1->ReturnAmountOfCardUsed()).c_str());
	al_draw_scaled_bitmap(Player1->ReturnReverse(), 0, 0, 330, 430, settings::PosX(0.865), settings::PosY(0.56), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
	//Przycisk cmentarzu
	GraveyardButton = Button(settings::PosX(0.865), settings::PosY(0.56), settings::PosX(ReverseCardSizeX) + settings::PosX(0.865), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()) + settings::PosY(0.56));
	if (GraveyardButton.MouseOn(mouseX, mouseY) && mouseButton == 1 && !IsGraveyardLocked())
	{
		mouseButton == 0;
		GraveyardOn = true;
		PlayersGraveyard = true;
		GraveyardFirstCard = 0;
	}
	//GraveyardButton.DrawHitbox();
	//Cmentarz przeciwnika
	OtherFunctions::DrawTextImage(Images::StatCircle, { settings::PosX(0.96),settings::PosY(0.32) }, { 100,100 },
		{ settings::PosX(0.03),settings::PosY(0.03 * settings::ProportionScreenWH()) }, std::to_string(Player2->ReturnAmountOfCardUsed()).c_str());
	al_draw_scaled_bitmap(Player2->ReturnReverse(), 0, 0, 330, 430, settings::PosX(0.865), settings::PosY(0.26), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
	//Przycisk cmentarzu
	GraveyardButton = Button(settings::PosX(0.865), settings::PosY(0.26), settings::PosX(ReverseCardSizeX) + settings::PosX(0.865), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()) + settings::PosY(0.26));
	if (GraveyardButton.MouseOn(mouseX, mouseY) && mouseButton == 1 && !IsEnemyGraveyardLocked())
	{
		mouseButton == 0;
		GraveyardOn = true;
		PlayersGraveyard = false;
		GraveyardFirstCard = 0;
	}
	DrawHistory();
	//GraveyardButton.DrawHitbox();
}
void Game::DrawHistory()
{
	History.DrawHistory(0.03,0.12,8);
}
//Przycisk Końca tury
//--------------------------------------------
void Game::EndRoundButton(float mouseX,float mouseY)
{
	if (!TurnBegin)
	{
		//Przycisk końca tury
		Button EndRound(settings::PosX(0.865f), settings::PosY(0.47f), settings::PosX(0.945f), settings::PosY(0.515f));
		EndRound.SetColor(Colors::white, Colors::lightGray);
		EndRound.SetText("Koniec tury");
		//Kliknięcie przycisku
		if (EndRound.MouseOn(mouseX,mouseY) && mouseButton == 1 && !TurnBegin)
		{
			Player1->SetRoundFinished(true);
			NextPlayer();
			TurnBegin = true;
			mouseButton = 0;	
		}
		//Rysowanie przycisku
		EndRound.DrawImage();
		EndRound.DrawText(Fonts::SmallValueFont,settings::PosY(0.004) );
	}
}
//Oblicza wynik rundy i czyści stół, zwraca true jeśli runda się zakończyła oraz zwiększa wartość argumentu o 1
//--------------------------------------
bool Game::RoundResult(int* RoundNumber)
{
	if (!Player1->IsFinishedRound() || !Player2->IsFinishedRound())
	{
		return false;
	}
	int playerPoints = Player1->CountPoints();
	int enemyPoints = Player2->CountPoints();
	//Zapisanie wyniku rundy
	Player.SetRound(*RoundNumber);
	Enemy.SetRound(*RoundNumber);
	//Sprawdzanie kto wygrał rundę
	if (playerPoints > enemyPoints)
	{
		Player1->RoundWon();
	}
	else if (playerPoints < enemyPoints)
	{
		Player2->RoundWon();
	}
	else
	{
		Player1->RoundWon();
		Player2->RoundWon();
	}
	*RoundNumber += 1; //Następna runda
	if (Player1->ReturnRoundsWon() >= 2 || Player2->ReturnRoundsWon() >= 2)
	{
		gameEnd = true;
		return true;
	}
	//Przygotowanie do następnej rundy
	Player1->SetRoundFinished(false);
	Player2->SetRoundFinished(false);
	Player1->EndRound();
	Player2->EndRound();
	return true;
}
//Rysuje podsumowanie gry zwraca true jeśli naciśnięto przycisk
//------------------------------------------------
bool Game::DrawSummary(float mouseX, float mouseY)
{
	Button NextButton(settings::PosX(0.45), settings::PosY(0.65), settings::PosX(0.55), settings::PosY(0.75));
	NextButton.SetText("Dalej");
	NextButton.SetColor(Colors::white, Colors::lightGray);
	//Rysowanie instrukcji
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.5f), settings::PosY(0.09f), ALLEGRO_ALIGN_CENTER, "Podsumowanie");
	if (Player.ReturnRoundsWon() == 2 && Enemy.ReturnRoundsWon() == 2)
	{
		al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.5f), settings::PosY(0.14f), ALLEGRO_ALIGN_CENTER, "Remis!");
	}
	else if (Player.ReturnRoundsWon() == 2)
	{
		al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.5f), settings::PosY(0.14f), ALLEGRO_ALIGN_CENTER, "Gracz 1 zwycięża!");
	}
	else if (Enemy.ReturnRoundsWon() == 2)
	{
		al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.5f), settings::PosY(0.14f), ALLEGRO_ALIGN_CENTER, "Gracz 2 zwycięża!");
	}
	//Wyniki rund
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.5f), settings::PosY(0.29f), ALLEGRO_ALIGN_CENTER, "Runda 1");
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.5f), settings::PosY(0.34f), ALLEGRO_ALIGN_CENTER, (std::to_string(Player.ReturnRoundPoints(0))+ " vs " + std::to_string(Enemy.ReturnRoundPoints(0))).c_str());
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.5f), settings::PosY(0.39f), ALLEGRO_ALIGN_CENTER, "Runda 2");
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.5f), settings::PosY(0.44f), ALLEGRO_ALIGN_CENTER, (std::to_string(Player.ReturnRoundPoints(1)) + " vs " + std::to_string(Enemy.ReturnRoundPoints(1))).c_str());
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.5f), settings::PosY(0.49f), ALLEGRO_ALIGN_CENTER, "Runda 3");
	al_draw_text(Fonts::BigFont, Colors::white, settings::PosX(0.5f), settings::PosY(0.54f), ALLEGRO_ALIGN_CENTER, (std::to_string(Player.ReturnRoundPoints(2)) + " vs " + std::to_string(Enemy.ReturnRoundPoints(2))).c_str());
	if (NextButton.MouseOn(mouseX,mouseY) && mouseButton == 1)
	{
		mouseButton = 0;
		return true;
	}
	NextButton.DrawImage();
	NextButton.DrawText(Fonts::ValueFont, settings::PosY(0.025));
	
	return false;
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
CardPos Game::DrawGraveyard(float mouseX, float mouseY,bool IsPlayerGraveyard,bool CanHero)
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
		PlayerGraveyard = Player1->ReturnCardUsed();
	}
	else
	{
		PlayerGraveyard = Player2->ReturnCardUsed();
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
			
			if (HandButtons[i].MouseOn(mouseX, mouseY))		//Rysowanie dużej karty
			{
				CurrentCard.DrawBigCardDescr(0.02f, 0.1f);
				if (mouseButton == 1)						//Zwrócenie narysowanej karty
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
	//Sprawdzenie czy zwrócono złotą kartę
	if (CardClicked.card.ReturnIsHero() && !CanHero)
	{
		CardClicked.card = Card();
	}
	return CardClicked;
}
//Rysuje rękę gracza (bez animacji)
//--------------------------------------------
void Game::DrawHand(float mouseX, float mouseY)
{
	std::vector<Card> PlayerHand = Player1->ReturnPlayerHand();
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
//Rysuje ręke z odwróconymi kartami
//---------------------------------------------------
void Game::DrawHiddenHand(float mouseX, float mouseY)
{
	std::vector<Card> PlayerHand = Player1->ReturnPlayerHand();
	//Rysowanie podpowiedzi
	DrawTip("Kliknij na kartę w ręce");
	//Rysowanie stołu
	DrawTable(mouseX, mouseY);
	//Rysowanie ręki gracza
	float StartDrawPointX = OtherFunctions::AlignCenter(0.01f, 0.86f, +PlayerHand.size() * 0.08f);
	float ReverseCardSizeX = 0.077f;
	for (int i = 0; i < PlayerHand.size(); i++)
	{
		HandButtons[i] = Button(PlayerHand[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.8f));
		al_draw_scaled_bitmap(Player1->ReturnReverse(), 0, 0, 330, 430, settings::PosX(StartDrawPointX + i * 0.08f), settings::PosY(0.8f), settings::PosX(ReverseCardSizeX), settings::PosY(ReverseCardSizeX * 1.31 * settings::ProportionScreenWH()), NULL);
		//Kliknięcie na kartę (przycisk)
		if (HandButtons[i].MouseOn(mouseX, mouseY) && mouseButton == 1)
		{
			mouseButton = 0;
			TurnBegin = false;
		}
	}
}
//Rysuje stół
void Game::DrawTable(float mouseX, float mouseY)
{
	std::vector<Card> PFirst = Player1->ReturnMeleeRow();
	std::vector<Card> PSecond = Player1->ReturnRangeRow();
	std::vector<Card> EFirst = Player2->ReturnMeleeRow();
	std::vector<Card> ESecond = Player2->ReturnRangeRow();
	float StartDrawPointX;

	//Rysowanie 1 rzędu gracza
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +PFirst.size() * 0.08f);
	for (int i = 0; i < PFirst.size(); i++)
	{
		MeleeButtons[i] = Button(PFirst[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.41f));
		PFirst[i].DrawCard(StartDrawPointX + i * 0.08f, 0.41f, Player1->ReturnCurrentValueOfCard(CardList::front, i));
		if (MeleeButtons[i].MouseOn(mouseX, mouseY))
		{
			PFirst[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}
	//Rysowanie 1 rzędu przeciwnika
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +EFirst.size() * 0.08f);
	for (int i = 0; i < EFirst.size(); i++)
	{
		EMeleeButtons[i] = Button(EFirst[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.21f));
		EFirst[i].DrawCard(StartDrawPointX + i * 0.08f, 0.21f, Player2->ReturnCurrentValueOfCard(CardList::front, i));
		if (EMeleeButtons[i].MouseOn(mouseX, mouseY))
		{
			EFirst[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}
	//Rysowanie 2 rzędu gracza
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +PSecond.size() * 0.08f);
	for (int i = 0; i < PSecond.size(); i++)
	{
		RangeButtons[i] = Button(PSecond[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.61f));
		PSecond[i].DrawCard(StartDrawPointX + i * 0.08f, 0.61f, Player1->ReturnCurrentValueOfCard(CardList::back, i));
		if (RangeButtons[i].MouseOn(mouseX, mouseY))
		{
			PSecond[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}
	//Rysowanie 2 rzędu przeciwnika
	StartDrawPointX = OtherFunctions::AlignCenter(0.2f, 0.86f, +ESecond.size() * 0.08f);
	for (int i = 0; i < ESecond.size(); i++)
	{
		ERangeButtons[i] = Button(ESecond[i].NormalCardVertexesPosition(StartDrawPointX + i * 0.08f, 0.01f));
		ESecond[i].DrawCard(StartDrawPointX + i * 0.08f, 0.01f, Player2->ReturnCurrentValueOfCard(CardList::back, i));
		if (ERangeButtons[i].MouseOn(mouseX, mouseY))
		{
			ESecond[i].DrawBigCardDescr(0.02, 0.1f);
		}
	}

}
//Rysuje poradę w lewym głównym rogu
//----------------------------------
void Game::DrawTip(std::string text)
{
	//Rysowanie podpowiedzi
	al_draw_text(Fonts::NameFont, Colors::white, settings::PosX(0.01f), settings::PosY(0.06f), ALLEGRO_ALIGN_LEFT, text.c_str());
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
	if (skillId == AllSkills::deadEater || skillId == AllSkills::medic || skillId == AllSkills::archer)
	{
		return true;
	}
	return false;
}
//Sprawdza czy włączona jest umiejętność blokująca cmentarz gracza
//----------------------------
bool Game::IsGraveyardLocked()
{
	if (skillId == AllSkills::transport || skillId == AllSkills::archer)
	{
		return true;
	}
	return false;
}
//Odpowiada za zmianę gracza
//--------------------------
void Game::NextPlayer()
{
	player1Turn = !player1Turn;
	if (player1Turn)
	{
		Player1 = &Player;
		Player2 = &Enemy;
		return;
	}
	Player1 = &Enemy;
	Player2 = &Player;
	return;
}
