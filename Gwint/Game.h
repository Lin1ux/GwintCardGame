#include<vector>
#include"Card.h"
#include"PlayerInfo.h"

#pragma once
class Game
{
private:
	ALLEGRO_DISPLAY* Display;
	bool PlayerTurn;
	PlayerInfo Player;
	PlayerInfo Enemy;
public:
	Game(ALLEGRO_DISPLAY* Disp,std::vector<Card> PlayerDeck, std::vector<Card> EnemyDeck);
	int GameLoop();
};

