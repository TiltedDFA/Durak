#pragma once
#include "Discardedcards.hpp"

class MainGame
{
	int  pTurn = 1;
	unsigned int _round = 0;
	unsigned short int cardsPlayedThisPass = 0;
public:
	int getRound()noexcept;


	void incramentRound();
	void setRound(const int num);

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
