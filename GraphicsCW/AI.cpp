#include "AI.hpp"

namespace c4
{
	int find_card_to_defend(Table& table) {

		for(int i = 0; i < 6; ++i) {

			if (table.getCardFromTableAtk(i) != nullptr && table.getCardFromTableDef(i) == nullptr)
				return i; // This will return the index of the attack pile that needs to be defended
		}
		return 6;
	}

	std::pair<bool, int> can_defend(Player& player, const std::shared_ptr<Card>& card_to_defend)
	{
		for(int i = 0; i < player.get_hand_size(); ++i)
		{
			if(static_cast<card_suit>(encrypt_data(player.from_hand_by_index(i)->get_card_suit())) ==
				Deck::master_suit &&
				static_cast<card_suit>(encrypt_data(card_to_defend->get_card_suit())) !=
				Deck::master_suit)
			{
				return std::make_pair(true, i);
			}
			if (encrypt_data(player.from_hand_by_index(i)->get_card_suit()) == encrypt_data(card_to_defend->get_card_suit()))				
			{
				if(encrypt_data(player.from_hand_by_index(i)->get_card_value()) > encrypt_data(card_to_defend->get_card_value()))
				{
					return std::make_pair(true, i);
				}
			}				
		}
		return std::make_pair(false, 6);
	}

	void attack(Table& table, Deck& deck, MainGame& mg, Discardediscarded_cards& bPile, std::vector<std::shared_ptr<Card>>& cardsVisible, std::array<Player, 2>& players) {

		std::array<Vector2, 6>pos{};

		pos[0] = { 543.0, 457.0 };

		pos[1] = { 688.0, 457.0 };

		pos[2] = { 840.0, 457.0 };

		pos[3] = { 990.0, 457.0 };

		pos[4] = { 1143.0,457.0 };

		pos[5] = { 1300.0,457.0 };

		if (table.get_num_cards_in_atk_table()) { //if number of cards in the attack pile <= 1 then, else;

			const int lowest_val = players[0].find_lowest_card(encrypt_data(table.getCardFromTableAtk(table.find_card_in_atk())->get_card_suit()));

			if (lowest_val == 99) {

				c2::end_attack(deck, mg, bPile, table, cardsVisible, players);

				return;
			}

			players[0].from_hand_by_index(lowest_val)->card_position = pos[table.find_empty_pile_atk()];

			players[0].from_hand_by_index(lowest_val)->canBeTouched = false;

			c2::hand_to_table(players[0], table, players[0].from_hand_by_index(lowest_val), table.find_empty_pile_atk());

			mg.incramentCardsPlayed();

		} else {

			const int lowest_val = players[0].find_lowest_card(0);

			players[0].from_hand_by_index(lowest_val)->canBeTouched = false;

			c2::hand_to_table(players[0], table, players[0].from_hand_by_index(lowest_val), table.find_empty_pile_atk());

			mg.incramentCardsPlayed();

			mg.switchPTurn();
		}
	}

	void defend(std::array<Player, 2>& players, Table& table,MainGame& mg, std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck) {

		std::array<Vector2, 6>pos{};

		pos[0] = { 543.0, 457.0 };

		pos[1] = { 688.0, 457.0 };

		pos[2] = { 840.0, 457.0 };

		pos[3] = { 990.0, 457.0 };

		pos[4] = { 1143.0,457.0 };

		pos[5] = { 1300.0,457.0 };

		while (table.get_num_cards_in_atk_table() != table.get_num_cards_in_defender_table()) {

			int position_of_card_to_defend = find_card_to_defend(table);
			//check if pirivadnoy works
			std::pair<bool, int> result = can_defend(players[0],table.getCardFromTableAtk(position_of_card_to_defend));
			
			if(result.first) {

				assert(position_of_card_to_defend != 6);

				assert(result.second != 6);

				players[0].from_hand_by_index(result.second)->card_position = pos[position_of_card_to_defend];

				players[0].from_hand_by_index(result.second)->card_position = Vector2Add(players[0].from_hand_by_index(result.second)->card_position, {40,40});

				players[0].from_hand_by_index(result.second)->canBeTouched = false;

				c2::hand_to_table(players[mg.getPTurn()], table, players[0].from_hand_by_index(result.second), position_of_card_to_defend);

				c1::bringCardOneToTop(players[0].from_hand_by_index(result.second), table.getCardFromTableAtk(position_of_card_to_defend), cardsVisible);
			}
			else {

				c2::takeDefender(players, cardsVisible, deck, table, mg);
				
				return;
			}
		}
		mg.switchPTurn();
	}
}
