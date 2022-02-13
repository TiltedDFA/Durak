#include "Maingame.hpp"

MainGame::MainGame() {}
MainGame::~MainGame() {}

void MainGame::switchPTurn()
{
	pTurn = (pTurn) ? 0 : 1;
	cardsPlayedThisPass = 0;
}
void MainGame::setPTurn(int player)
{
	pTurn = player;
}
const unsigned short int MainGame::getCardsPlayed() noexcept {

	return cardsPlayedThisPass;
}
void MainGame::setCardsPlayed(unsigned short int played)
{
	cardsPlayedThisPass = played;
}
void MainGame::resetCardsPlayed()
{
	cardsPlayedThisPass = 0;
}
void MainGame::incramentCardsPlayed()
{
	++cardsPlayedThisPass;
}
const int MainGame::getPTurn() noexcept {

	return pTurn;
}
