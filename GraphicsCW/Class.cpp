#include "Class.hpp"
#include <array>
#include <algorithm>
#include <random>

void swap(Card* var1, Card* var2)
{
	Card temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}
//-------------------------------------------------------------------------------------------------------------

Card::Card() { Suit = cardSuit::CLUBS; Value = cardValue::TWO; xPos = 0; yPos = 0; }
Card::~Card(){}

//-------------------------------------------------------------------------------------------------------------
Deck::~Deck() {}
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

	auto rng = std::default_random_engine{};

	std::shuffle(_Deck.begin(), _Deck.begin(), rng);
}
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
	for (auto const  i : _Deck)
	{		
		std::cout << i.Name << std::endl;
	}
}
cardSuit Deck::getMasterSuit()
{
	return masterSuit;
}
Card Deck::lookAtTopCard()
{
	Card topCard;
	if (!_Deck.empty())
		topCard = _Deck[(_Deck.size() - 1)];
	return topCard;
}
Card Deck::removeTopCard()
{
	Card topCard = _Deck[(_Deck.size() - 1)];
	_Deck.erase(_Deck.begin() + (_Deck.size() - 1));
	return topCard;
}
//-------------------------------------------------------------------------------------------------------------

Player::Player() {}
Player::~Player() {}

Card Player::getCardFromPH(int index)
{
	return PlayerHand[index];
}
std::string Player::getPlayerName()
{
	return PlayerName;
}
void Player::setPlayerName(std::string input)
{
	PlayerName = input;
}
void Player::addToPlayerHand(int index, Card card)
{
	PlayerHand[index] = card;
}
void Player::addNeededCardsToPlayerHand(Deck deck)
{
	if (PlayerHand.size() != 6)
	{
		for (auto i = PlayerHand.size(); i < 6; ++i)
		{
			std::size_t amtOfCNeeded = (6 - PlayerHand.size());
			for (std::size_t i = 0; i < amtOfCNeeded; ++i)
			{
				PlayerHand[i] = deck.removeTopCard();
			}
		}
	}
}
void Player::clearIndexHand(int index)
{
	Card card;
	PlayerHand[index] = card;
}
void Player::setCardPos(Vector2 pos, int index)
{
	PlayerHand[index].xPos = pos.x;
	PlayerHand[index].yPos = pos.y;
}
Card* Player::getCardPtr(int index)
{
	Card* ptr = &PlayerHand[index];
	return ptr;
}
void Player::sortHand()
{	
	int i, j;
	for (i = 0; i < PlayerHand.size() - 1; ++i)
	{
		for (j = 0; j < PlayerHand.size() - i - 1; ++j)
		{
			if ((int)PlayerHand[j].Suit > (int)PlayerHand[(j + 1)].Suit)
			{
				swap(&PlayerHand[j], &PlayerHand[(j + 1)]);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------

Table::Table() {}
Table::~Table() {}
// for the cards on table embedded arrays, it would seem cardsOnTable.$command() accesses the vector while cardsOnTable[index].$command() accesses the array
// This is to say that it accesses it in a array.$command type of way. It doesn't actually access the data held within the array
void Table::addCardToTableAtk(Card card, int pNum)
{
	cardsOnTable[pNum][0] = card;
}
void Table::addCardToTableDef(Card card, int cardPile)
{
	cardsOnTable[cardPile][1] = card;
}
void Table::clearTable()
{
	Card card;
	for (int i = 0;i < 6 ;++i)
	{
		for (int j = 0; j < 2; ++j)
			cardsOnTable[i][j] = card;
	}
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
	movesThisTurnAtk = 0;
}
void Table::displayCardsOnTable()
{
	
}
Card Table::getCardFromTableDef(int index)
{
	return cardsOnTable[index][1];
}
Card Table::getCardFromTableAtk(int index)
{
	return cardsOnTable[index][0];
}
Card* Table::getPtrCardAtk(int index)
{
	Card* cPtr = &cardsOnTable[index][0];
	return cPtr;
}
Card* Table::getPtrCardDef(int index)
{
	Card* cPtr = &cardsOnTable[index][1];
	return cPtr;
}

//-------------------------------------------------------------------------------------------------------------

//worksassasas