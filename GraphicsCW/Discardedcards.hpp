#pragma once


#include "Table.hpp"

class Discardediscarded_cards
{
	std::vector<std::shared_ptr<Card>>discarded_cards;
public:
	Discardediscarded_cards();
	~Discardediscarded_cards();
	void addToPile(std::shared_ptr<Card> card)noexcept;
};


