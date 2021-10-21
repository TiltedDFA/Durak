#pragma once
#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <vector>

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

	std::string getPlayerName();
	void setPlayerName(std::string input);
};
//-------------------------------------------------------------------------------------------------------------
class Table
{
private:
	std::vector<std::array<Card, 2>>cardsOnTable;
	short int movesThisTurnAtk = 0;
public:
	void addCardToTableAtk(Card card);
	void addCardToTableDef(Card card, int cardPile);
	void displayCardsOnTable();
	void clearTable();

	void setMovesMadeThisRound(int played);
	int getMovesMadeThisRound();
	void resetMovesMade();
	Table();
	~Table();
};
#endif // !CLASS_HPP