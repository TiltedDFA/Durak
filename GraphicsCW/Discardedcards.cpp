#include "Discardedcards.hpp"

Discardediscarded_cards::Discardediscarded_cards() {};
Discardediscarded_cards::~Discardediscarded_cards() {};

void Discardediscarded_cards::addToPile(std::shared_ptr<Card> card) noexcept {

	discarded_cards.emplace_back(card);
}