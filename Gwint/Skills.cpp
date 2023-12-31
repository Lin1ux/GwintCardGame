#include "Skills.h"
#include "Images.h"

Skills::Skills(int newId, std::string newName, std::string newDescr, ALLEGRO_BITMAP* NewIcon)
{
	id = newId;
	name = newName;
	descr = newDescr;
	Icon = NewIcon;
}
Skills::Skills()
{
	id = 0;
	name = "Brak";
	descr = "";
	Icon = Images::StatCircle;
}
int Skills::ReturnId()
{
	return id;
}
std::string Skills::ReturnName()
{
	return name;
}
std::string Skills::ReturnDescr()
{
	return descr;
}
ALLEGRO_BITMAP* Skills::ReturnIcon()
{
	return Icon;
}

bool Skills::operator==(const Skills& s)
{
	if (this->id == s.id)
	{
		return true;
	}
	return false;
}
bool Skills::operator!=(const Skills& s)
{
	if (this->id != s.id)
	{
		return true;
	}
	return false;
}

