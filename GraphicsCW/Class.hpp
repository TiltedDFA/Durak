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
#include <fstream>
#include <iterator>
constexpr auto fileName = "SAVE.txt";// This globally declares the filename
constexpr auto screenWidth = 1920;// This globally declares screenwidth
constexpr auto screenHeight = 1050; // This globallydeclares the screenheight

enum class cardSuit //This sets up the card's suits
{
	SPADES = 1,
	HEARTS,
	DIAMONDS,
	CLUBS,
};
//-------------------------------------------------------------------------------------------------------------
enum class cardValue // This sets up the card's values
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
class Card // This is the card class, The majourity of the game is based around it
{
public:
	Card();
	~Card();

	Vector2 cardPosition = { 0,0 };
	bool cardIsFaceUp = true;
	bool cardIsHeld = false;
	bool canBeTouched = true;
	bool inDefTablePile = false;

	cardSuit Suit{};
	cardValue Value{};	
	std::string suitToString(const cardSuit&); // A fucntion that converts the enumarated values to a string(Which can be used to display)
	std::string valueToString(const cardValue&);
	void displayCardWithValueText(const std::shared_ptr<Card>& card);
};
//-------------------------------------------------------------------------------------------------------------
class Deck
{
private:
	std::vector<std::shared_ptr<Card>> deck;// The deck which is based on an std::shared_ptr system. The shared_ptrs are a type of smart pointers which delete the contents from the heap automatically
	std::shared_ptr<Card> visibleCard;// This is what stores the card that will be visible from the start of the game.
	std::pair<std::shared_ptr<Card>, std::shared_ptr<Card>>topOfDeck;
	// This value detirmins how the game will be played and adds a lot of power to cards of the same suit. The value for this is derived from the visible card.
	bool hasCardsRemaining = true;
public:
	inline static cardSuit masterSuit;
	Deck();
	Deck(const int deckSize);
	~Deck(); 
	std::shared_ptr<Card> dealCard();
	cardSuit getMasterSuit();
	void setMasterSuit(cardSuit suit);
	void setVisibleCard(std::shared_ptr<Card> card);
	void displayVisisbleCard(Texture2D& visiCardTexture);
	std::shared_ptr<Card> getVisibleCard();
	std::pair<std::shared_ptr<Card>, std::shared_ptr<Card>> getTopOfDeck();
	void setTopOfDeck(std::pair<std::shared_ptr<Card>, std::shared_ptr<Card>> pair);
	int getDeckSize();
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
	bool isPlyrAtk();
	void setPlyrAtk(bool bol);
	std::vector<std::shared_ptr<Card>> getEntireHand();
	void setEntireHand(std::vector<std::shared_ptr<Card>> hand);
	void setPlayerHandIndex(std::shared_ptr<Card> card, const int index);
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
	std::array<std::array<std::shared_ptr<Card>, 2>, 6>& getEntireTable();
	void setEntireTable(std::array<std::array<std::shared_ptr<Card>, 2>, 6> table);
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
	int  pTurn = 1;
	unsigned int _round = 0;
	unsigned short int cardsPlayedThisPass = 0;
	bool hasAtkPlayedCard = false;
public:
	int getRound();

	
	void incramentRound();
	void setRound(const int num);

	void setPTurn(const int player);
	void switchPTurn();
	const int getPTurn();

	const unsigned short int getCardsPlayed();
	void setCardsPlayed(const unsigned short int played);
	void resetCardsPlayed();
	void incramentCardsPlayed();

	MainGame();
	~MainGame();
};
//-------------------------------------------------------------------------------------------------------------

#endif // !CLASS_HPP