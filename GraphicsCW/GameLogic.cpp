#include "GameLogic.hpp"
/*
void switchPlayerTurns(std::array<Player, 2>&players)
{
	bool invPlayerOne = !players[0].getPTurn();
	bool invPlayerTwo = !players[1].getPTurn();
	players[0].setPTurn(invPlayerOne);
	players[1].setPTurn(invPlayerTwo);
}
*/
void GameLogic::swapPlayerTurns()
{
	playerTurn = (playerTurn + 1) % 2;
}
int GameLogic::getPlayerTurn()
{
	return playerTurn;
}

GameLogic::GameLogic()
{	
}
GameLogic::~GameLogic()
{
}