#include "Game.hpp"
namespace c2 {// This namespace is for game functions

	extern inline int  collision_percent_finder(int percentCertanty, std::shared_ptr<Card> card) { //This function is used to find the amount of overlap between the card and the placement box

		std::array<Vector2, 6>pos{};

		pos[0] = { 543.0, 457.0 };

		pos[1] = { 688.0, 457.0 };

		pos[2] = { 840.0, 457.0 };

		pos[3] = { 990.0, 457.0 };

		pos[4] = { 1143.0,457.0 };

		pos[5] = { 1300.0,457.0 };

		const Rectangle rCard = { card->card_position.x, card->card_position.y, 120, 170 };

		for (int i = 0; i < 6; ++i) {

			const Rectangle placeHB = { pos[i].x, pos[i].y, 120, 170 };

			if (CheckCollisionRecs(rCard, placeHB)) {

				const auto oSetArea = (placeHB.width - sqrt((card->card_position.x - placeHB.x) * (card->card_position.x - placeHB.x)))
					* (placeHB.height - sqrt((card->card_position.y - placeHB.y) * (card->card_position.y - placeHB.y)));

				const auto percentOverlap = oSetArea / (placeHB.width * placeHB.height) * 100;

				if (static_cast<int>(percentOverlap > static_cast<int>(percentCertanty))) {

					return static_cast<int>(percentOverlap);
				}
			}
		}
		return 0;
	}

	extern inline bool can_attacker_attack(Table& table, std::shared_ptr<Card> card) {

		if (!card->is_card_face_up)
			return false;

		int l = 0;

		const std::array<std::array<std::shared_ptr<Card>, 2>, 6>cardsOnTable = table.getEntireTable();

		for (const auto& i : cardsOnTable)
			for (int j = 0; j < 2; ++j)
				if (i[j] != nullptr) { ++l; if (encrypt_data(i[j]->get_card_value()) == encrypt_data(card->get_card_value())) { return true; } }

		if (!l)
			return true;

		return false;
	}

	extern inline bool card_beats_card_def(const std::shared_ptr<Card>& card_one, const std::shared_ptr<Card>& card_two) { //This function checks where card one is able to beat card two for the defender

		if (card_two == nullptr)
			return false;

		if (card_one != nullptr && card_two == nullptr || static_cast<card_suit>(encrypt_data(card_one->get_card_suit())) == Deck::master_suit &&
			static_cast<card_suit>(encrypt_data(card_two->get_card_suit())) != Deck::master_suit) // This code assumes that the only cards that will be passed to the function will be from the table
			return true;

		if (encrypt_data(card_one->get_card_suit()) == encrypt_data(card_two->get_card_suit()) && encrypt_data(card_one->get_card_value()) > encrypt_data(card_two->get_card_value()))
			return true;

		return false;
	}

	extern inline std::pair<Vector2, int> find_colliding_placement(const std::shared_ptr<Card>& card) { // This function finds the placement box number that the card is currently touching

		std::array<Vector2, 6>pos{};

		pos[0] = { 543.0, 457.0 };

		pos[1] = { 688.0, 457.0 };

		pos[2] = { 840.0, 457.0 };

		pos[3] = { 990.0, 457.0 };

		pos[4] = { 1143.0,457.0 };

		pos[5] = { 1300.0,457.0 };

		const Rectangle rCard = { card->card_position.x, card->card_position.y, 120, 170 };

		for (int i = 0; i < 6; ++i) {

			const Rectangle box = { pos[i].x, pos[i].y, 120, 170 };

			if (CheckCollisionRecs(rCard, box))
				return { pos[i], i };
		}

		return { { 0,0 }, 7 };
	}

	void hand_to_table(Player& player, Table& table,const std::shared_ptr<Card>& card_to_play, const int& cardPile) {
		//places a card from a hand to the table

		std::vector<std::shared_ptr<Card>> player_hand = player.getEntireHand();

		const auto posInHand = 
			std::find(player_hand.begin(), player_hand.end(), card_to_play);

		if (posInHand != player_hand.end()) {
		
			if (table.getCardFromTableAtk(cardPile) == nullptr)
			{
				table.addCardToTableAtk(std::move(*posInHand), cardPile);
				player_hand.erase(posInHand);
			}

			else
			{
				table.addCardToTableDef(std::move(*posInHand), cardPile);
				player_hand.erase(posInHand); card_to_play->inDefTablePile = true;
			}

			player.setEntireHand(player_hand);
		}
	}

	extern inline void discard_table(Discardediscarded_cards& bPile, Table& table, std::vector<std::shared_ptr<Card>>& cardsVisible) { //empties table

		std::array<std::array<std::shared_ptr<Card>, 2>, 6>cardsOnTable = table.getEntireTable();

		for (int i = 0; i < 6; ++i) {

			for (int j = 0; j < 2; ++j) {

				if (cardsOnTable[i][j] != nullptr) {

					auto posInCV = std::find(cardsVisible.begin(), cardsVisible.end(), cardsOnTable[i][j]);

					if (posInCV != cardsVisible.end()) { cardsVisible.erase(posInCV); }

					bPile.addToPile(std::move(cardsOnTable[i][j]));
				}
			}
		}
		table.setEntireTable(cardsOnTable);
	}

	extern inline bool defend_can_pass(Table& table) { // checks whether the defender is able to pass

		const std::array<std::array<std::shared_ptr<Card>, 2>, 6> cardsOnTable = table.getEntireTable();

		std::pair<int, int> cardsPlayed;

		for (auto& i : cardsOnTable) {

			if (i[0] != nullptr)  
				++cardsPlayed.first; 

			if (i[1] != nullptr) 
				++cardsPlayed.second; 
		}

		if (!cardsPlayed.first)
			return false;

		if (cardsPlayed.first == cardsPlayed.second)
			return true;

		return false;
	}

	extern inline void switch_player_state(std::array<Player, 2>& players) {

		players[0].setPlyrAtk(!players[0].isPlyrAtk()); players[1].setPlyrAtk(!players[1].isPlyrAtk());
	}

	extern inline bool can_end_attack(Table& table) {

		if (table.get_num_cards_in_atk_table())
			return true;		
		return false;
	}

	extern inline void table_to_hand(Player& player, Table& table) { //moves all card on table to a player's hand

		std::array<std::array<std::shared_ptr<Card>, 2>, 6> cTable = table.getEntireTable();

		Vector2 takenCardPos = { 0, 150 };

		for (int i = 0; i < 6; ++i) {

			for (int j = 0; j < 2; ++j) {

				if (cTable[i][j] != nullptr) {

					takenCardPos.x = (75.0f * i);

					cTable[i][j]->card_position = takenCardPos;

					cTable[i][j]->canBeTouched = true;

					player.addToplayer_hand(std::move(cTable[i][j]));

					cTable[i][j] = nullptr;
				}
			}
		}

		table.setEntireTable(cTable);
	}

	extern inline int check_for_winner(Deck& deck, std::array<Player, 2>& players, Table& table) {

		for (int i = 0; i < 2; ++i) {

			if (deck.getDeckSize() == 0 && players[i].get_hand_size() == 0 && table.get_amount_of_card_in_table() == 0) {
				return i;
			}
		}
		return 2;
	}

	extern inline void play_music(const int music_number, const  Music& JazzMusic, const Music& LofiMusic, const  Music& eSwingMusic) {

		switch (music_number) {

		case 2:

			PlayMusicStream(JazzMusic);

			break;

		case 3:

			PlayMusicStream(LofiMusic);

			break;

		case 4:

			PlayMusicStream(eSwingMusic);

			break;

		default:

			break;
		}
	}

	extern inline void continuePlayingMusic(const int music_number, Music& JazzMusic, Music& LofiMusic, Music& eSwingMusic) {

		switch (music_number) {

		case 2:

			UpdateMusicStream(JazzMusic);

			break;

		case 3:

			UpdateMusicStream(LofiMusic);

			break;

		case 4:

			UpdateMusicStream(eSwingMusic);

			break;

		default:

			break;
		}
	}

	extern inline void end_attack(Deck& deck, MainGame& mg, Discardediscarded_cards& bPile, Table& table, std::vector<std::shared_ptr<Card>>& cardsVisible, std::array<Player, 2>& players) {

		discard_table(bPile, table, cardsVisible);

		c1::remove_table_from_visible_vector(table, cardsVisible);

		c1::add_need_cards_to_players(players, cardsVisible, deck);

		mg.switchPTurn();

		switch_player_state(players);
	}

	extern inline void takeDefender(std::array<Player, 2>& players, std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck, Table& table, MainGame& mg) {

		table_to_hand(players[mg.getPTurn()], table);

		c1::add_need_cards_to_players(players, cardsVisible, deck);

		mg.switchPTurn();
	}

	extern inline bool pirivadnoy_checker(Table& table, const std::shared_ptr<Card>& card) {
		// This function checks whether the defender is able to pirivadit

		if (table.get_num_cards_in_defender_table()) // if there's more than zero cards, this will return false
			return false;
		if (static_cast<card_value>(encrypt_data(card->get_card_value())) == 
			static_cast<card_value>(encrypt_data(table.getCardFromTableAtk(
				table.find_card_in_atk())->get_card_value()))
			&& table.get_num_cards_in_defender_table() == 0)
			return true;
		return false;
	}

	void privadi(MainGame& mg, std::array<Player, 2>& players) {

		c2::switch_player_state(players);
		mg.switchPTurn();
	}	
}