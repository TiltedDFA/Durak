#include "Deck.hpp"

Deck::Deck()
{
}
Deck::Deck(const int deckSize) {

	int startValue = 0;
	switch (deckSize)
	{
	case 36:
		startValue = 4;
		break;
	case 52:
		startValue = 0;
		break;
	default:
		throw std::runtime_error("Unexpected Deck size value");
		break;
	}
	for (int i = startValue; i < 13; ++i) //13 Represents the different values
	{
		for (int j = 0; j < 4; ++j) // 4 is for the four suits
		{
			std::shared_ptr<Card> C = std::make_shared<Card>(); //This declares a card pointer and allocates it to the heap
			C->set_card_value(encrypt_data(i + 2)); //This is to make up for the array indexing 
			C->set_card_suit(encrypt_data(j + 1)); // As is this 
			deck.emplace_back(C);
		}
	}
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(std::begin(deck), std::end(deck), rng);
}

Deck::~Deck() {
}

std::shared_ptr<Card> Deck::dealCard() {

	assert(deck.size());

	std::shared_ptr<Card> holder = deck[0];

	deck.erase(deck.begin());

	return holder;
}

const std::shared_ptr<Card>& Deck::getLastCard() noexcept { // This is the visibleCard
	assert(deck.size());
	return deck[deck.size() - 1];
}

void Deck::setPosLastCard(const Vector2& pos) { // Visible Card

	deck[deck.size() - 1]->card_position = pos;
}

void Deck::setPosTopCardDeck(const Vector2& pos) { //Top of deck (hidden)

	assert(deck.size() > 0);

	deck[(deck.size() - 2)]->card_position = pos;
}

const std::shared_ptr<Card>& Deck::getTopOfVisDeck() noexcept { //This is the top of the deck(hidden)

	assert(deck.size() > 0);

	return *(deck.end() - 2);
}

void Deck::setmaster_suit(const card_suit& suit) {

	master_suit = suit;
}

int Deck::getDeckSize()noexcept {

	return static_cast<int>(deck.size());
}