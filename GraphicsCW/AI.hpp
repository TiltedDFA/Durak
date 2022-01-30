#pragma once
#ifndef AI_HPP
#define AI_HPP

#include "Display.hpp"

namespace c4
{
	extern inline int find_card_to_defend(Table& table);

	extern inline std::pair<bool, int> can_defend(Player& player, const std::shared_ptr<Card>& card_to_defend);

	extern inline void attack(Table& table, Deck& deck, MainGame& mg, Discardediscarded_cards& bPile, std::vector<std::shared_ptr<Card>>& cardsVisible, std::array<Player, 2>& players);

	extern inline void defend(std::array<Player, 2>& players, Table& table, MainGame& mg, std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck);
}


#endif
