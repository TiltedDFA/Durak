#pragma once
#include "Discardedcards.hpp"

class MainGame
{
	int  pTurn = 1;
	unsigned short int cardsPlayedThisPass = 0;
public:

	void incramentRound();

	void setPTurn(const int player);
	void switchPTurn();
	const int getPTurn()noexcept;

	const unsigned short int getCardsPlayed()noexcept;
	void setCardsPlayed(const unsigned short int played);
	void resetCardsPlayed();
	void incramentCardsPlayed();

	MainGame();
	~MainGame();
};
