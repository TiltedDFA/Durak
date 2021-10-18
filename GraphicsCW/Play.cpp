#include "Play.hpp"

inline bool beatsTheCard(Card CardOne, Card CardTwo)
{
	auto ms = Deck::getMasterSuit();
	if (CardOne.Suit == CardTwo.Suit || CardOne.Suit == ms)
	{
		if (CardOne.Suit == ms && CardTwo.Suit != ms)
			return true;
		return (CardOne.Value > CardTwo.Value);
	}
	return false;
}

inline void switchPlayers(int& playerOne, int& playerTwo)
{
	playerOne = (playerOne + 1) % 2;
	playerTwo = (playerTwo+ 1) % 2;
}

