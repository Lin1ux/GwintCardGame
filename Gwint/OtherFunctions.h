#include <allegro5/allegro.h>               //Biblioteka Allegro
#include <iostream>
#include <vector>

typedef struct Point
{
    float x;
    float y;
}Point;

typedef struct RectanglePoints
{
    Point P1;   //Left up point
    Point P2;   //Right up point
    Point P3;   //Left down point
    Point P4;   //Right down point
}RectanglePoints;

#pragma once



class OtherFunctions
{
public:
	static void DrawRectangle(RectanglePoints Points, ALLEGRO_COLOR color,int t);                                           //Rysuje prostok¹t u¿ywaj¹c struktury "RectanglePoints"
    static void DrawImage(ALLEGRO_BITMAP* Image, Point Position, Point ImgSize, Point(ImgScaledSize));                      //Rysuje obraz u¿ywaj¹c struktur "Point"
    static void DrawTextImage(ALLEGRO_BITMAP* Image, Point Position, Point ImgSize, Point(ImgScaledSize),std::string text); //Rysuje tekst na ramce
    static int Random(int min, int max);                                                                //Losuje liczbê z przedzia³u <min,max>
    static float AlignCenter(float start, float end,float size);                                        //Zwraca miejsce, w którym nale¿y wstawiæ obiekt aby by³ wyœrodkowany
    static void DrawMouseCursor(float mouseX, float mouseY);                                                                      //Rysuje kursor myszy
};

