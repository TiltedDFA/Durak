#include "Class.hpp"
#include <array>
#include <algorithm>
#include <random>
//-------------------------------------------------------------------------------------------------------------

Card::Card() { Suit = cardSuit::CLUBS; Value = cardValue::TWO; }

Card::~Card() {}

//-------------------------------------------------------------------------------------------------------------
Deck::Deck()
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

	masterSuit = (cardSuit)(rand() % 5 + 1);

	auto rng = std::default_random_engine{};

	std::shuffle(_Deck.begin(), _Deck.begin(), rng);
}
Deck::~Deck() {}
void Deck::addToDeck(Card card)
{
	_Deck.emplace_back(card);
}
Card Deck::dealCard()
{
	auto holder = _Deck[0];
	_Deck.erase(_Deck.begin());
	return holder;
}
void Deck::printDeck()
{
	for (const auto i : _Deck)
	{
		std::cout << i.Name << std::endl;
	}
}
cardSuit Deck::getMasterSuit()
{
	return masterSuit;
}
//-------------------------------------------------------------------------------------------------------------

Player::Player() {}
Player::~Player() {}

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
void Player::addToPlayerHand(Card card)
{
	PlayerHand.emplace_back(card);
}

//-------------------------------------------------------------------------------------------------------------

Table::Table() {}
Table::~Table() {}
// for the cards on table embedded arrays, it would seem cardsOnTable.$command() accesses the vector while cardsOnTable[index].$command() accesses the array
// This is to say that it accesses it in a array.$command type of way. It doesn't actually access the data held within the array
void Table::addCardToTableAtk(Card card)
{
	std::array<Card, 2> tempArry;
	switch (movesThisTurnAtk)
	{
	case 0 - 5:
		tempArry[0] = card;
		cardsOnTable.push_back(tempArry);
		++movesThisTurnAtk;
		break;
	default:
		break;
	}
}
void Table::clearTable()
{
	//cardsOnTable.clear();
}
void Table::setMovesMadeThisRound(int played)
{
	movesThisTurnAtk = played;
}
int Table::getMovesMadeThisRound()
{
	return movesThisTurnAtk;
}
void Table::resetMovesMade()
{
	//Table::movesThisTurnAtk = 0;
}
//-------------------------------------------------------------------------------------------------------------

//worksassasas