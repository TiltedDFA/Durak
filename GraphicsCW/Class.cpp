#include "Class.hpp"


//-------------------------------------------------------------------------------------------------------------

Card::Card() { Suit = cardSuit::CLUBS; Value = cardValue::TWO; Pos = { 0, 0 }; }
Card::~Card(){}
std::string Card::suitToString(cardSuit suit)
{
	switch (suit)
	{
	case cardSuit::SPADES:
		return "Spades";		
	case cardSuit::HEARTS:
		return "Hearts";		
	case cardSuit::DIAMONDS:
		return "Diamonds";
	case cardSuit::CLUBS:
		return "Clubs";
	default:
		break;
	}
	return "Error";
}

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
	
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(std::begin(_Deck), std::end(_Deck), rng);
}
void Deck::addToDeck(const Card card)
{
	_Deck.emplace_back(card);
}
Card Deck::dealCard()
{	
	auto holder = _Deck[0];	
	_Deck.erase(_Deck.begin());
	return holder;
}
cardSuit Deck::getMasterSuit()
{
	return masterSuit;
}

void Deck::setVCard(const Card card)
{
	visibleCard = card;
}
Card Deck::getVCard()
{
	return visibleCard;
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
void Deck::setUpTwoDeckCards()
{
	if (nextTwoDeckCards[0].Pos.x != 153)
	{
		nextTwoDeckCards[0] = removeTopCard();
		nextTwoDeckCards[0].canBeTouched = false;
		nextTwoDeckCards[0].Pos.x = deckPos.x;
		nextTwoDeckCards[0].Pos.y = deckPos.y;
	}
	if (nextTwoDeckCards[1].Pos.x != 153)
	{
		nextTwoDeckCards[1] = removeTopCard();
		nextTwoDeckCards[1].canBeTouched = false;
		nextTwoDeckCards[1].Pos.x = deckPos.x;
		nextTwoDeckCards[1].Pos.y = deckPos.y;
	}
}
Card Deck::getCardFromTwoCards(const int index)
{
	return nextTwoDeckCards[index];
}
Card Deck::removeCardFromTwoCards(const int index)
{	
	Card reset;
	Card temp = nextTwoDeckCards[index];
	nextTwoDeckCards[index] = reset;
	return temp;
}
void Deck::displayDeck(const Texture2D flippedCard, const Texture2D backOfCard)
{
	//display the flipped card first 
	// void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);
	// {206, 503} is the co ords for the top right of the place to draw the flippedCard
	// is the co ords for the deck pos
	Vector2 flippedCardPos = { 376, 503 };
	Card card;
	/*
	Card topDeckCard = _Deck[(_Deck.size() - 1)];
	Card secondFromTopCard = _Deck[(_Deck.size() - 2)];
	*/
	//Rotating a card seems to also rotate the point from which it's drawn 
	std::string cValStr = std::to_string((int)visibleCard.Value);
	std::string cSuitStr = card.suitToString(visibleCard.Suit);
	DrawTextureEx(flippedCard, flippedCardPos, 90, 1, WHITE);
	DrawText(cValStr.c_str(), ((int)flippedCardPos.x - 110), (int)flippedCardPos.y, 40, BLACK);
	DrawText(cSuitStr.c_str(), ((int)flippedCardPos.x - 110), ((int)flippedCardPos.y+ 30), 40, BLACK);
	DrawTexture(backOfCard, (int)nextTwoDeckCards[0].Pos.x, (int)nextTwoDeckCards[0].Pos.y, WHITE);
	DrawTexture(backOfCard, (int)nextTwoDeckCards[1].Pos.x, (int)nextTwoDeckCards[1].Pos.y, WHITE);
}
//878 983
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
	PlayerHand[index].Pos.x = pos.x;
	PlayerHand[index].Pos.y = pos.y;
}
Card* Player::getCardPtr(int index)
{
	Card* ptr = &PlayerHand[index];
	return ptr;
}
bool Player::getPTurn()
{
	return isPlayerTurnAtk;
}
void Player::setPTurn(bool bol)
{
	isPlayerTurnAtk = bol;
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
				std::swap(PlayerHand[j], PlayerHand[(j + 1)]);
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------

Table::Table() 
{
	Card card;
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			cardsOnTable[i][j] = card; // This is meant to slap in the default card into all the table slots so that we can preform logic on it as the name of the card will be "" (we treat this as a null value)
		}
	}
}
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
DiscardedCards::DiscardedCards() {};
DiscardedCards::~DiscardedCards() {};

void DiscardedCards::addToPile(Card card)
{
	dCards.emplace_back(card);
}
//-------------------------------------------------------------------------------------------------------------
MainGame::MainGame() {}
MainGame::~MainGame() {}

int MainGame::getRound()
{
	return _round;
}
void MainGame::incramentRound()
{
	++_round;
}
void MainGame::setRound(const int num)
{
	_round = num;
}
//-------------------------------------------------------------------------------------------------------------
//worksassasas