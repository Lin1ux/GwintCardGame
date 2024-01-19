#include <iostream>
#include <allegro5/allegro.h>               //Biblioteka Allegro
#include <allegro5/allegro_native_dialog.h> //Do okienek błedu
#include <allegro5/allegro_primitives.h>	//Prymitywy (kwadraty, trójkąty itd.)
#include <allegro5/allegro_ttf.h>           //Wczytywanie czcionek .ttf
#include <allegro5/allegro_font.h>          //Czcionki


#include "Menu.h"                           //Menu
#include "Colors.h"                         //Kolory
#include "settings.h"                       //Ustawienia
#include "Images.h"                         //Obrazy
#include "OtherFunctions.h"                 //Inne funkcje
#include "MainMenu.h"                       //Menu główne

//#define ScreenWidth 1920
//#define ScreenHeight 1080

int main()
{
    srand(time(NULL));          //Ziarno losowania

    //Sprawdzenie czy biblioteka allegro się załadowała
    if (!al_init())
    {
        al_show_native_message_box(NULL, NULL, NULL, "Nie udalo się zaladować biblioteki Allegro", NULL, NULL);
        return -1;
    }

    //Ustawia tryb okna
    al_set_new_display_flags(ALLEGRO_FULLSCREEN); //ALLEGRO_FULLSCREEN - Fullscreen | ALLEGRO_WINDOWED - Tryb okienkowy
    //Ustawienie rozdzielczości okna
    ALLEGRO_DISPLAY* display;                                                       //Zmienna okna
    display = al_create_display(settings::ScrWidth(), settings::ScrHeight());       //Ustawia rozdzielczość okna
    al_set_window_position(display, 200, 50);                                       //Ustawia pozycje okna
    al_set_window_title(display, "Arok The Card Game");                             //Ustawia tytuł gry
    std::cout << "Gra zostala uruchomiona!\n";

    //Sprawdzenie czy okno istnieje
    if (!display)
    {
        al_show_native_message_box(display, "Tytuł", "Ustawienia Ekranu", "Okno nie zostalo utworzone", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_init_primitives_addon(); //Inicjalizacja Prymitywów
    al_init_image_addon();      //Inicjalizacja obrazków

    //Inicjalizacja Czcionek
    al_init_font_addon();
    al_init_ttf_addon();

    al_install_keyboard();		//Inicjalizacja klawiatury
    al_install_mouse();			//Inicjalizacja myszy

    Menu GameMenu(display, settings::ScrWidth(), settings::ScrHeight());
    MainMenu MainMenuWindow(display, settings::ScrWidth(), settings::ScrHeight());    //Obiekt menu głównego
    int State = 0;              //Stan gry
    while (true)                //Pętla gry
    {
        if (State == 0)
        {
            State = MainMenuWindow.MenuLoop();
        }
        if (State == 1)
        {
            std::cout << "Gra zostala zamknieta przez uzytkownika\n";
            return 0;
        }
        if (State == 2)
        {
            State = GameMenu.MenuLoopPVP();
        }
        if (State == -1)
        {
            std::cout << "Wystapil blad\n";
            return -1;
        }
    }
}