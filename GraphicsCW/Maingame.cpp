#include "Maingame.hpp"

MainGame::MainGame() {}
MainGame::~MainGame() {}

int MainGame::getRound() noexcept {
	return _round;
}
void MainGame::incramentRound()
{
	++_round;
}
void MainGame::setRound(const int num)
{
	_round = num;
}
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
