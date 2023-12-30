#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //obrazki
#include <string>

#pragma once
class Skills
{
private:
	int id;
	std::string name;
	std::string descr;
	ALLEGRO_BITMAP* Icon;
public:
	Skills(int newId, std::string newName, std::string newDescr, ALLEGRO_BITMAP* NewIcon);
	Skills();
	int ReturnId();
	std::string ReturnName();
	std::string ReturnDescr();
	ALLEGRO_BITMAP* ReturnIcon();
	bool operator == (const Skills& s);
	bool operator != (const Skills& s);
};

