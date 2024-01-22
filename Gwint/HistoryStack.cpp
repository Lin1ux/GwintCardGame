#include "HistoryStack.h"
#include "settings.h"
#include "Colors.h"
#include "Fonts.h"

HistoryStack::HistoryStack()
{
	History = std::vector<Action>();
}
//Dodanie akcji
//--------------------------------------------
void HistoryStack::AddAction(Action NewAction)
{
	History.push_back(NewAction);
}
//Usuwa ostanio dodan¹ akcje
void HistoryStack::RemoveAction()
{
	if (History.size() > 0)
	{
		History.pop_back();
	}
}
//Usuwa akcjê licz¹c od koñca
void HistoryStack::RemoveActionEnd(int diff)
{
	if (diff+1 < History.size())
	{
		History.erase(History.end() - diff-1);
	}
}
//Rysowanie histori
//-----------------------------------------------------------
void HistoryStack::DrawHistory(float x1, float y1, int amount)
{
	//Ostatni wyœwietlany index
	int LastIndex;
	int MaxActions = amount;
	if (amount >= History.size())
	{
		LastIndex = History.size();
		MaxActions = History.size();
	}
	else
	{				
		LastIndex = History.size();
	}
	//Rysowanie histori 
	for(int i = 0;i	< MaxActions;i++)
	{
		al_draw_text(Fonts::ValueFont, Colors::white, settings::PosX(x1 - 0.01 ), settings::PosY(y1+0.01 + i*0.08), ALLEGRO_ALIGN_CENTER, std::to_string(History[LastIndex - i - 1].PlayerNumber).c_str());
		History[LastIndex-i-1].PlayedCard.DrawPicture(x1,y1+i*0.08);
		al_draw_scaled_bitmap(History[LastIndex - i - 1].UsedSkill.ReturnIcon(), 0, 0, 100, 100, settings::PosX(x1 + 0.0485), settings::PosY(y1+ 0.015 + i * 0.08), settings::PosX(0.025), settings::PosY(0.025 * settings::ProportionScreenWH()), NULL);
		if (History[LastIndex - i - 1].TargetCard != Card())
		{
			History[LastIndex - i - 1].TargetCard.DrawPicture(x1 + 0.08, y1 + i * 0.08);
		}
	}
}
//Dodaje cel do ostatniego wydarzenia
//------------------------------------------
void HistoryStack::UpdateTarget(Card Target)
{
	if (History.size() < 0)
	{
		return;
	}
	History[History.size() - 1].TargetCard = Target;
}
//Aktualizuje wykonawce czynnoœci
//-----------------------------------------
void HistoryStack::UpdatePlayer(int Player)
{
	if (History.size() < 0)
	{
		return;
	}
	History[History.size() - 1].PlayerNumber = Player;
}
