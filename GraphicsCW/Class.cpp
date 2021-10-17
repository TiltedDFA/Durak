#include "Class.hpp"
#include <array>

Card::Card() { Suit = cardSuit::CLUBS; Value = cardValue::TWO; }
Card::~Card() {}
Deck::Deck() { srand((unsigned)time(NULL));	masterSuit = (cardSuit)((rand() % 4) + 1); }
Player::Player() {}
Player::~Player() {}
Table::Table() {}
Table::~Table() {}
void Deck::addToDeck(Card card)
{
	_Deck.emplace_back(card);
}
Card Deck::getCardFromDeck(int cardIndex)
{
	return _Deck[cardIndex];
}
void Deck::printDeck()
{
	for (auto i : _Deck)
	{
		std::cout << i.Name << std::endl;
	}
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
	std::array<std::string, 4> suit = { "Spades", "Hearts", "Diamonds", "Clubs" };
	std::array<std::string, 14> value = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
	Card C;
	for (int i = 0; i < value.size(); i++)
	{
		for (int j = 0; j < suit.size(); j++)
		{
			
			C.Value = (cardValue)(i + 1);
			C.Suit = (cardSuit)(j + 1);
			C.Name = value.at(i) + " of " + suit.at(j);
			_Deck.emplace_back(C);
		}
	}
}
//worksassasas