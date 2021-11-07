#pragma once
#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <array>
#include <vector>
#include "raylib.h"

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

	float xPos{};
	float yPos{};
	bool faceUp = false;
	bool held = false;

	cardSuit Suit{};
	cardValue Value{};
	std::string Name{};
};
//-------------------------------------------------------------------------------------------------------------
class Deck
{
private:
	std::vector<Card> _Deck;
	inline static cardSuit masterSuit;
public:
	Deck();
	~Deck();

	void addToDeck(Card card);
	Card dealCard();
	void printDeck();

	Card lookAtTopCard();
	Card removeTopCard();

	static cardSuit getMasterSuit();
};
//-------------------------------------------------------------------------------------------------------------
class Player
{
private:
	std::string PlayerName;
	std::vector<Card> PlayerHand;
public:
	Player();
	~Player();
	Card getPlayerHand(int index);
	void setPlayerHand(int index, Card input);
	void addNeededCardsToPlayerHand(Deck deck);
	void addToPlayerHand(Card card);
	void eraseIndexHand(int index);
	void sortHand();

	std::string getPlayerName();
	void setPlayerName(std::string input);
};
//-------------------------------------------------------------------------------------------------------------
class Table
{
private:
	std::array<std::array<Card, 2>, 6>cardsOnTable;
	short int movesThisTurnAtk = 0;
public:
	void addCardToTableAtk(Card card, int pNum);
	void addCardToTableDef(Card card, int cardPile);
	void displayCardsOnTable();
	void clearTable();

	Card getCardFromTableDef(int index);
	Card getCardFromTableAtk(int index);
	void setCardPosAtk(int index, Vector2 pos);
	void setCardPosDef(int index, Vector2 pos);
	Vector2 getCardPosAtk(int index);
	Vector2 getCardPosDef(int index);
	void flipCardAtk(int index, bool bol);
	void flipCardDef(int index, bool bol);
	void flipHoldStateAtk(int index, bool bol);
	void flipHoldStateDef(int index, bool bol);
	Card* getPtrCardAtk(int index);
	Card* getPtrCardDef(int index);

	void setMovesMadeThisRound(int played);
	int getMovesMadeThisRound();
	void resetMovesMade();
	Table();
	~Table();
};

#endif // !CLASS_HPP