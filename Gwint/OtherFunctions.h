#include <allegro5/allegro.h>               //Biblioteka Allegro
#include <iostream>

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
	static void DrawRectangle(RectanglePoints Points, ALLEGRO_COLOR color,int t);
    static void DrawImage(ALLEGRO_BITMAP* Image, Point Position, Point ImgSize, Point(ImgScaledSize));
    static void DrawTextImage(ALLEGRO_BITMAP* Image, Point Position, Point ImgSize, Point(ImgScaledSize),std::string text);
};

