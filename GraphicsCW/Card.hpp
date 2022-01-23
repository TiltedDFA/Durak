#pragma once
#include "Includes.hpp"
enum class card_suit //This sets up the card's suits
{
	SPADES = 1,
	HEARTS,
	DIAMONDS,
	CLUBS,
};
//-------------------------------------------------------------------------------------------------------------
enum class card_value // This sets up the card's values
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
	int Suit{};
	int Value{};
public:
	Card();
	~Card();

	Vector2 card_position = { 0,0 };
	bool is_card_face_up = true;
	bool cardIsHeld = false;
	bool canBeTouched = true;
	bool inDefTablePile = false;

	static std::string suitToString(const card_suit&); // A fucntion that converts the enumarated values to a string(Which can be used to display)
	static std::string valueToString(const card_value&);
	void displayCardWithValueText(const std::shared_ptr<Card>& card);

	void set_card_value(const int& value);
	void set_card_suit(const int& suit);

	int get_card_value()noexcept;
	int get_card_suit()noexcept;
};
