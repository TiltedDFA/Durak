#pragma once
#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP
#include "Display.hpp"

class GameLogic
{
private:
	int roundNum;
	int playerTurn;
public:
	GameLogic();
	~GameLogic();

	void swapPlayerTurns();
	int getPlayerTurn();

};

#endif // !GAMELOGIC_HPP

