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

	bool can_defend(Player& player, const std::shared_ptr<Card>& card_to_defend)
	{
		for(int i = 0; i < player.get_hand_size(); ++i)
		{
			if(static_cast<card_suit>(encrypt_data(player.from_hand_by_index(i)->get_card_suit())) ==
				Deck::master_suit &&
				static_cast<card_suit>(encrypt_data(card_to_defend->get_card_suit())) !=
				Deck::master_suit)
			{
				return true;
			}
			if (encrypt_data(player.from_hand_by_index(i)->get_card_suit()) == encrypt_data(card_to_defend->get_card_suit()))				
			{
				if(encrypt_data(player.from_hand_by_index(i)->get_card_value()) > encrypt_data(card_to_defend->get_card_value()))
				{
					return true;
				}
			}				
		}
		return false;
	}

	void attack(Table& table, Deck& deck, MainGame& mg, Discardediscarded_cards& bPile, std::vector<std::shared_ptr<Card>>& cardsVisible, std::array<Player, 2>& players) {

		if (table.get_num_cards_in_atk_table()) {

			const int lowest_val = players[0].find_lowest_card(encrypt_data(table.getCardFromTableAtk(table.find_card_in_atk())->get_card_suit()));

			if (lowest_val == 99) {

				c2::end_attack(deck, mg, bPile, table, cardsVisible, players);

				return;
			}

			players[0].from_hand_by_index(lowest_val)->canBeTouched = false;

			c2::hand_to_table(players[0], table, players[0].from_hand_by_index(lowest_val), table.find_empty_pile_atk());

			mg.incramentCardsPlayed();

		} else {

			const int lowest_val = players[0].find_lowest_card(0);

			players[0].from_hand_by_index(lowest_val)->canBeTouched = false;

			c2::hand_to_table(players[0], table, players[0].from_hand_by_index(lowest_val), table.find_empty_pile_atk());

			mg.incramentCardsPlayed();
		}
	}

	void defend(std::array<Player, 2>& players, Table& table,MainGame& mg, std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck) {

		while (table.get_num_cards_in_atk_table() != table.get_num_cards_in_defender_table()) {

			//check if pirivadnoy works
			if (find_card_to_defend(table) == 6) { //if no card to defend->pass

				mg.switchPTurn();

				return;
			}
			if(can_defend(players[0], table.getCardFromTableAtk(table.find_empty_pile_atk()))) {
				
			}
			else
			{
				c2::takeDefender(players, cardsVisible, deck, table, mg);
			}
		}
		mg.switchPTurn();
	}


}
