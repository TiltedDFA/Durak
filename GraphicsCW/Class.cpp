#include "Class.hpp"

Card::Card() { Suit = cardSuit::CLUBS; Value = cardValue::TWO; }
Card::~Card() {}
Deck::Deck() { srand((unsigned)time(NULL));	masterSuit = (cardSuit)((rand() % 4) + 1); }
Player::Player() {}
Player::~Player() {}
Players::Players() {}
Players::~Players() {}
Table::Table() {}
Table::~Table() {}
void Deck::addToDeck(Card card)
{
	_Deck.push_back(card);
}
Card Deck::getCardFromDeck(int cardIndex)
{
	return _Deck[cardIndex];
}
cardSuit Deck::getMasterSuit()
{
	return masterSuit;
}
Card Player::getPlayerHand(int index)
{
	return PlayerHand[index];
}
void Player::setPlayerHand(int index, Card input)
{
	PlayerHand[index] = input;
}
std::string Player::getPlayerName()
{
	return PlayerName;
}
void Player::setPlayerName(std::string input)
{
	PlayerName = input;
}
Deck::~Deck()
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 4; j++)
		{

		}
	}
}
//worksassasas