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

enum class card_suit //This sets up the card's suits
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

	Vector2 card_position = { 0,0 };
	bool is_card_face_up = true;
	bool cardIsHeld = false;
	bool canBeTouched = true;
	bool inDefTablePile = false;

	card_suit Suit{};
	cardValue Value{};	
	static std::string suitToString(const card_suit&); // A fucntion that converts the enumarated values to a string(Which can be used to display)
	static std::string valueToString(const cardValue&);
	void displayCardWithValueText(const std::shared_ptr<Card>& card);
};
//-------------------------------------------------------------------------------------------------------------
class Deck
{
private:
	std::vector<std::shared_ptr<Card>> deck;// The deck which is based on an std::shared_ptr system. The shared_ptrs are a type of smart pointers which delete the contents from the heap automatically	
	// This value detirmins how the game will be played and adds a lot of power to cards of the same suit. The value for this is derived from the visible card.	
public:
	inline static card_suit master_suit;
	Deck();//Change how deck works
	Deck(const int deckSize);
	~Deck(); 

	std::shared_ptr<Card> dealCard();

	const std::shared_ptr<Card>& getLastCard();
	void setPosLastCard(const Vector2& pos);

	const std::shared_ptr<Card>& getTopOfVisDeck();
	void setPosTopCardDeck(const Vector2& pos);

	void setmaster_suit(card_suit suit);	
		
	int getDeckSize();
};
//-------------------------------------------------------------------------------------------------------------
class Player
{
protected:
	bool player_has_won = false;
private:
	std::vector<std::shared_ptr<Card>>player_hand;
	bool plyrAtk = false;
public:
	Player();
	~Player();
	void addToplayer_hand(std::shared_ptr<Card> cardToAdd);
	std::shared_ptr<Card> getplayer_handIndex(const int index);
	std::size_t getplayer_handSize();
	bool isPlyrAtk();
	void setPlyrAtk(bool bol);
	std::vector<std::shared_ptr<Card>> getEntireHand();
	void setEntireHand(std::vector<std::shared_ptr<Card>> hand);
	void setplayer_handIndex(std::shared_ptr<Card> card, const int index);
	void set_player_winstate(bool has_won);
	const bool get_player_winstate();
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
	const int getNumCardsOnTable();
};
//-------------------------------------------------------------------------------------------------------------
class Discardediscarded_cards
{
private:
	std::vector<std::shared_ptr<Card>>discarded_cards;
public:
	Discardediscarded_cards();
	~Discardediscarded_cards();
	void addToPile(std::shared_ptr<Card> card);
};
//-------------------------------------------------------------------------------------------------------------
class MainGame
{
private:
	int  pTurn = 1;
	unsigned int _round = 0;
	unsigned short int cardsPlayedThisPass = 0;	
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