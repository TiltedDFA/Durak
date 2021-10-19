#include "Play.hpp"

inline bool beatsTheCard(Deck deck, Card CardOne, Card CardTwo)
{
	auto ms = deck.getMasterSuit();
	if (CardOne.Suit == CardTwo.Suit || CardOne.Suit == ms)
	{
		if (CardOne.Suit == ms && CardTwo.Suit != ms)
			return true;
		return (CardOne.Value > CardTwo.Value);
	}
	return false;
}

inline void switchPlayers(int& playerOne, int& playerTwo)
{//players will be stored as either 0 or 1 so this works pretty neetly
	playerOne = (playerOne + 1) % 2;
	playerTwo = (playerTwo + 1) % 2;
}

