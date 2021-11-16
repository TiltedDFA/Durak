#include "Class.hpp"

//-------------------------------------------------------------------------------------------------------------

Card::Card() { Suit = cardSuit::CLUBS; Value = cardValue::TWO; }
Card::~Card() {}
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
Deck::Deck()
{
	std::array<std::string, 4> suit = { "Spades", "Hearts", "Diamonds", "Clubs" };
	std::array<std::string, 13> value = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };

	for (int i = 0; i < value.size(); ++i)
	{
		for (int j = 0; j < suit.size(); ++j)
		{
			std::shared_ptr<Card> C = std::make_shared<Card>();
			C->Value = static_cast<cardValue>(i + 1); //This is to make up for the array indexing 
			C->Suit = static_cast<cardSuit>(j + 1); // As is this 
			C->Name = value[i] + " of " + suit[j];
			deck.emplace_back(C);
		}
	}
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(std::begin(deck), std::end(deck), rng);
}

Deck::~Deck()
{
}
std::shared_ptr<Card> Deck::dealCard()
{
	auto holder = deck[0];
	deck.erase(deck.begin());
	return holder;
}
cardSuit Deck::getMasterSuit()
{
	return masterSuit;
}
void Deck::setMasterSuit(cardSuit suit)
{
	masterSuit = suit;
}
void Deck::setVisibleCard(std::shared_ptr<Card> card)
{
	visibleCard = card;
}
void Deck::displayVisisbleCard(Texture2D& visiCardTexture)
{
	DrawTextureEx(visiCardTexture, visibleCard->cardPosition, 90.0, 1.0, WHITE);
}
std::shared_ptr<Card> Deck::getVisibleCard()
{
	return visibleCard;
}
std::pair<std::shared_ptr<Card>, std::shared_ptr<Card>> Deck::getTopOfDeck()
{
	return topOfDeck;
}
void Deck::setTopOfDeck(std::pair<std::shared_ptr<Card>, std::shared_ptr<Card>> pair)
{
	topOfDeck = pair;
}
//-------------------------------------------------------------------------------------------------------------
Player::Player()
{
}
Player::~Player()
{
}
void Player::addToPlayerHand(std::shared_ptr<Card> cardToAdd)
{
	playerHand.push_back(cardToAdd);
}
std::shared_ptr<Card> Player::getPlayerHandIndex(const int index)
{
	return playerHand[index];
}
std::size_t Player::getPlayerHandSize()
{
	return playerHand.size();
}
void Player::addNeededCardToPlayerHand(Deck& deck)
{
	while (playerHand.size() < 6)
	{
		playerHand.push_back(deck.dealCard());
	}
}
bool Player::isPlyrAtk()
{
	return plyrAtk;
}
void Player::setPlyrAtk(bool bol)
{
	plyrAtk = bol;
}
std::vector<std::shared_ptr<Card>> Player::getEntireHand()
{
	return playerHand;
}
void Player::setEntireHand(std::vector<std::shared_ptr<Card>> hand)
{
	playerHand = hand;
}
//-------------------------------------------------------------------------------------------------------------
Table::Table()
{
}

Table::~Table()
{
}
void Table::addCardToTableAtk(std::shared_ptr<Card> card, const int pNum)
{
	cardsOnTable[pNum][0] = card;
}
void Table::addCardToTableDef(std::shared_ptr<Card> card, const int pNum)
{
	cardsOnTable[pNum][1] = card;
}
std::shared_ptr<Card> Table::getCardFromTableAtk(const int index)
{
	return cardsOnTable[index][0];
}
std::shared_ptr<Card> Table::getCardFromTableDef(const int index)
{
	return cardsOnTable[index][1];
}
std::array<std::array<std::shared_ptr<Card>, 2>, 6> Table::getEntireTable()
{
	return cardsOnTable;
}
//-------------------------------------------------------------------------------------------------------------
DiscardedCards::DiscardedCards() {};
DiscardedCards::~DiscardedCards() {};

void DiscardedCards::addToPile(std::shared_ptr<Card> card)
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
void MainGame::switchAtkPlr()
{
	plrAtk = (plrAtk + 1) % 2;
}
void MainGame::setPlrAtk(int player)
{
	plrAtk = player;
}
//-------------------------------------------------------------------------------------------------------------