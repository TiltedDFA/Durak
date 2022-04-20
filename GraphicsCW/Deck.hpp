#pragma once

#include "Card.hpp"

class Deck
{
	std::vector<std::shared_ptr<Card>> deck;// The deck which is based on an std::shared_ptr system. The shared_ptrs are a type of smart pointers which delete the contents from the heap automatically	
	// This value detirmins how the game will be played and adds a lot of power to cards of the same suit. The value for this is derived from the visible card.	
public:
	inline static card_suit master_suit;
	Deck();//Change how deck works
	Deck(const int deckSize);
	~Deck();

	std::shared_ptr<Card> dealCard();

	const std::shared_ptr<Card>& getLastCard()noexcept;
	void setPosLastCard(const Vector2& pos);

	const std::shared_ptr<Card>& getTopOfVisDeck()noexcept;
	void setPosTopCardDeck(const Vector2& pos);

	void setmaster_suit(const card_suit& suit);

	int getDeckSize()noexcept;
};
