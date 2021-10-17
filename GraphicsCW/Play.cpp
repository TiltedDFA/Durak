#include "Play.hpp"

inline bool beatsTheCard(cardSuit masterSuit, Card CardOne, Card CardTwo)
{
	if (CardOne.Suit == CardTwo.Suit || CardOne.Suit == masterSuit)
	{
		if (CardOne.Suit == masterSuit && CardTwo.Suit != masterSuit)
			return true;
		return (CardOne.Value > CardTwo.Value);
	}
	return false;
}