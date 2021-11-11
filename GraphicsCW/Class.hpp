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
	bool canBeTouched = true;

	cardSuit Suit{};
	cardValue Value{};
	std::string Name{};
	std::string suitToString(cardSuit);
};
//-------------------------------------------------------------------------------------------------------------
class Deck
{
private:
	Vector2 deckPos = { 153, 470 };
	std::vector<Card> _Deck;
	std::array<Card, 2>nextTwoDeckCards;
	inline static Card visibleCard;
	inline static cardSuit masterSuit;
public:
	Deck();
	~Deck();

	void addToDeck(Card card);
	Card dealCard();
	void printDeck();

	void setUpTwoDeckCards();
	Card getCardFromTwoCards(int index);
	Card removeCardFromTwoCards(int index);

	void displayDeck(Texture2D flippedCard, Texture2D backOfCard);

	void setVCard(Card card);
	Card getVCard();

	Card lookAtTopCard();
	Card removeTopCard();

	static cardSuit getMasterSuit();
};
//-------------------------------------------------------------------------------------------------------------
class Player
{
private:
	std::string PlayerName;
	std::array<Card, 20> PlayerHand;
public:
	Player();
	~Player();
	Card getCardFromPH(int index);

	void addNeededCardsToPlayerHand(Deck deck);
	void addToPlayerHand(int index, Card card);
	void clearIndexHand(int index);	
	void setCardPos(Vector2 pos, int index);
	Card* getCardPtr(int index);

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
	Card* getPtrCardAtk(int index);
	Card* getPtrCardDef(int index);
	void setMovesMadeThisRound(int played);
	int getMovesMadeThisRound();
	void resetMovesMade();
	Table();
	~Table();
};

#endif // !CLASS_HPP