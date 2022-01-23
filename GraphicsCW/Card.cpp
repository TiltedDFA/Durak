#include "Card.hpp"

Card::Card()
	: Suit(1), Value(2) //This is a member initilizer list (it needs to be written in order for the vars)
{
}
Card::~Card() {}

std::string Card::suitToString(const card_suit& suit)
{
	switch (suit)
	{
	case card_suit::SPADES:
		return "Spades";
	case card_suit::HEARTS:
		return "Hearts";
	case card_suit::DIAMONDS:
		return "Diamonds";
	case card_suit::CLUBS:
		return "Clubs";
	default:
		break;
	}
	throw std::runtime_error("Unexpected Error with Suit display");
}

std::string Card::valueToString(const card_value& value)
{
	switch (value)
	{
	case card_value::JACK:
		return "Jack";
	case card_value::QUEEN:
		return "Queen";
	case card_value::KING:
		return "King";
	case card_value::ACE:
		return "Ace";
	default:
		break;
	}
	throw std::runtime_error("Unexpected Error with Value display");;
}

void Card::displayCardWithValueText(const std::shared_ptr<Card>& card)
{
	const std::string cValStr = encrypt_data(card->Value) > 10 ? card->valueToString(static_cast<card_value>(encrypt_data(card->Value))) : std::to_string(encrypt_data(card->Value));
	const std::string cSuitStr = card->suitToString(static_cast<card_suit>(encrypt_data(card->Suit)));
	DrawText(cValStr.c_str(), static_cast<int>((card->card_position.x + 10)), static_cast<int>((card->card_position.y + 65)), 20, BLACK);
	DrawText(cSuitStr.c_str(), static_cast<int>((card->card_position.x + 10)), static_cast<int>((card->card_position.y + 95)), 20, BLACK);

}

void Card::set_card_value(const int& value) {

	Value = value;
}

void Card::set_card_suit(const int& suit) {

	Suit = suit;
}

int Card::get_card_value()noexcept {

	return Value;
}

int Card::get_card_suit()noexcept {

	return Suit;
}
