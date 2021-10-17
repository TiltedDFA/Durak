#include "Class.hpp"
#include <array>
#include <random>
#include <algorithm>
#include <chrono>

Card::Card() { Suit = cardSuit::CLUBS; Value = cardValue::TWO; }
Card::~Card() {}
Deck::~Deck() {}
Player::Player() {}
Player::~Player() {}
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
Deck::Deck()
{
	std::array<std::string, 4> suit = { "Spades", "Hearts", "Diamonds", "Clubs" };
	std::array<std::string, 13> value = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
	Card C;
	for (int i = 0; i < value.size(); ++i)
	{
		for (int j = 0; j < suit.size(); ++j)
		{

			C.Value = (cardValue)(i + 1);
			C.Suit = (cardSuit)(j + 1);
			C.Name = value.at(i) + " of " + suit.at(j);
			_Deck.emplace_back(C);
		}
	}
	masterSuit = (cardSuit)(rand() % 5 + 1);
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(_Deck.begin(), _Deck.end(), std::default_random_engine(seed));
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

//worksassasas