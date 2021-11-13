#pragma once
#ifndef CLASS_HPP
#define CLASS_HPP
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include <utility>
#include "raylib.h"
#include "raymath.h"

enum class cardSuit
{
	SPADES = 1,
	HEARTS,
	DIAMONDS,
	CLUBS,
};
//-------------------------------------------------------------------------------------------------------------
enum class cardValue
{
	TWO = 2,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
};
//-------------------------------------------------------------------------------------------------------------
class Card
{
public:
	Card();
	~Card();	

	Vector2 cardPosition = {0,0};
	bool cardIsFaceUp = true;
	bool cardIsHeld = false;
	bool canBeTouched = true;

	cardSuit Suit{};
	cardValue Value{};
	std::string Name = "";
	std::string suitToString(cardSuit);
};
//-------------------------------------------------------------------------------------------------------------
class Deck
{
private:
	std::vector<std::shared_ptr<Card>> deck;
	std::shared_ptr<Card> visibleCard;
	cardSuit masterSuit = cardSuit::CLUBS;
public:
	Deck();
	~Deck();
	std::shared_ptr<Card> dealCard();
	cardSuit getMasterSuit();
	void setMasterSuit(cardSuit suit);
	void setVisibleCard(std::shared_ptr<Card> card);
	std::shared_ptr<Card> getVisibleCard();
};
//-------------------------------------------------------------------------------------------------------------
class Player
{
private:
	std::vector<std::shared_ptr<Card>>playerHand;
	bool plyrAtk = false;
public:
	Player();
	~Player();
	void addToPlayerHand(std::shared_ptr<Card> cardToAdd);
	std::shared_ptr<Card> getPlayerHandIndex(const int index);
	std::size_t getPlayerHandSize();
	void addNeededCardToPlayerHand(Deck& deck);	
};
//-------------------------------------------------------------------------------------------------------------
class Table
{
private:
	std::array<std::array<std::shared_ptr<Card>, 2>, 6>cardsOnTable;
public:
	Table();
	~Table();
	void addCardToTableAtk(std::shared_ptr<Card> card, const int pNum);
	void addCardToTableDef(std::shared_ptr<Card> card, const int pNum);
	std::shared_ptr<Card> getCardFromTableAtk(const int index);
	std::shared_ptr<Card> getCardFromTableDef(const int index);	
};
//-------------------------------------------------------------------------------------------------------------
class DiscardedCards
{
private:
	std::vector<std::shared_ptr<Card>>dCards;
public:
	DiscardedCards();
	~DiscardedCards();

	void addToPile(std::shared_ptr<Card> card);
};
//-------------------------------------------------------------------------------------------------------------
class MainGame
{
private:
	unsigned int plrAtk = 0;
	unsigned int _round = 0;
public:
	int getRound();
	void switchAtkPlr();
	void incramentRound();
	void setRound(const int num);
	void setPlrAtk(int player);
	MainGame();
	~MainGame();
};
//-------------------------------------------------------------------------------------------------------------

#endif // !CLASS_HPP