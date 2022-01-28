#include "AI.hpp"

namespace c4
{
	int attack(Player& player, Table& table)
	{
		int lowest_card_position = 99;

		if(table.get_num_cards_in_defender_table())
			lowest_card_position = player.find_lowest_card(0);
		else
		{
			
		}
		return 0;
	}

}
