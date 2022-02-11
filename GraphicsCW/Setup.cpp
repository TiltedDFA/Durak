#include "Setup.hpp"

namespace c1 {// Used to setup or maintain

	extern inline void addiscarded_cardsToVisibleVec(std::vector<std::shared_ptr<Card>>& cards_visible, std::shared_ptr<Card> card) {

		cards_visible.push_back(card);
	}

	extern inline void removeCardFromVisibleVect(std::vector<std::shared_ptr<Card>>& cards_visible, std::shared_ptr<Card> card) {

		assert(cards_visible.size() > 0);

		const auto positionOfCardToRemove = std::find(cards_visible.begin(), cards_visible.end(), card);

		if (positionOfCardToRemove != cards_visible.end())
			cards_visible.erase(positionOfCardToRemove);
	}

	extern inline void init_player_hands(std::vector<std::shared_ptr<Card>>& cards_visible, Deck& deck, std::array<Player, 2>& players) {

		constexpr float x = 600;

		float y = 75;

		for (int i = 0; i < 6; ++i) {

			std::shared_ptr<Card> card = deck.dealCard();

			//card->canBeTouched = false; Temp disabled until ai is made

			card->is_card_face_up = true;

			card->card_position = { (x + 125.0f * static_cast<float>(i)),y };

			players[0].addToplayer_hand(card);

			cards_visible.push_back(card);
		}

		y = 840;

		for (int i = 0; i < 6; ++i) {

			std::shared_ptr<Card> card = deck.dealCard();

			card->card_position = { (x + 125.0f * static_cast<float>(i)),y };

			players[1].addToplayer_hand(card);

			cards_visible.push_back(card);
		}

		deck.setPosLastCard({ 376, 503 });
	}

	extern inline int findStartingPlayer(std::array<Player, 2> players)
	{

		card_value lowestVal[2] = { card_value::ACE, card_value::ACE };

		for (int i = 0; i < 2; ++i) {

			for (int j = 0; j < players[i].get_hand_size(); ++j) {

				if (static_cast<card_suit>(encrypt_data(players[i].from_hand_by_index(j)->get_card_suit())) == Deck::master_suit &&
					static_cast<card_value>(encrypt_data(players[i].from_hand_by_index(j)->get_card_value())) < lowestVal[i])
				{

					lowestVal[i] = static_cast<card_value>(encrypt_data(players[i].from_hand_by_index(j)->get_card_value()));
				}
			}
		}
		if (lowestVal[0] == card_value::ACE && lowestVal[1] == card_value::ACE) { // This is to randomise the starting player if neither has a master suit

			return rand() % 2 + 1;
		}
		if (lowestVal[0] > lowestVal[1]) {

			return 1;
		}

		return 0;
	}

	extern inline void lockCardsInHand(std::array<Player, 2>players, MainGame mg) {

		const auto pTurn = mg.getPTurn();

		for (int i = 0; i < players[pTurn].get_hand_size(); ++i) {

			const auto card = players[pTurn].from_hand_by_index(i);

			card->canBeTouched = true;

			players[pTurn].set_hand_by_index(card, i);
		}

		const auto otherPlayer = (pTurn + 1) % 2;

		for (int i = 0; i < players[otherPlayer].get_hand_size(); ++i) {

			const auto card = players[otherPlayer].from_hand_by_index(i);

			card->canBeTouched = false;

			players[otherPlayer].set_hand_by_index(card, i);
		}
	}

	extern inline void bringCardOneToTop(const std::shared_ptr<Card>& cardOne, const std::shared_ptr<Card>& cardTwo, std::vector<std::shared_ptr<Card>>& cards_visible) {

		assert(cards_visible.size() > 1);

		const auto cOnePos = std::find(cards_visible.begin(), cards_visible.end(), cardOne);

		const auto cTwoPos = std::find(cards_visible.begin(), cards_visible.end(), cardTwo);

		if (cOnePos > cTwoPos) { std::iter_swap(cOnePos, cTwoPos); } // if c_one_pos is further (greater) in the cards_visible array (which would 
	}

	extern inline void remove_table_from_visible_vector(Table& table, std::vector<std::shared_ptr<Card>>& cards_visible) {

		assert(cards_visible.size() >= table.get_amount_of_card_in_table());

		const std::array<std::array<std::shared_ptr<Card>, 2>, 6> _table = table.getEntireTable();

		for (const auto& i : _table) {

			for (int j = 0; j < 2; ++j) {

				if (i[j] != nullptr) {

					auto posInCardsVisible = std::find(cards_visible.begin(), cards_visible.end(), i[j]);

					if (posInCardsVisible != cards_visible.end())
						cards_visible.erase(posInCardsVisible);
				}
			}
		}
	}

	extern inline bool deck_has_enough_cards_left(Deck& deck, const int numOfCardsNeeded) {

		const int deckSize = deck.getDeckSize();

		if (deckSize - numOfCardsNeeded >= 0)
			return true;

		return false;
	}

	extern inline void add_need_cards_to_players(std::array<Player, 2>& players, std::vector<std::shared_ptr<Card>>& cards_visible, Deck& deck) {

		for (int i = 0; i < 2; ++i) {

			const auto cardsNeeded = (6 - players[i].get_hand_size());

			if (deck.getDeckSize()) { // code below will not run if deckSize == 0;

				if (deck_has_enough_cards_left(deck, static_cast<int>(cardsNeeded)) && static_cast<int>(players[i].get_hand_size()) < 6) {

					for (auto j = 0; j < cardsNeeded; ++j) {

						std::shared_ptr<Card>card = deck.dealCard();

						card->card_position.y = i ? 850.0f : 0.0f;

						card->card_position.x = static_cast<float>(120 * j);

						players[i].addToplayer_hand(card);

						cards_visible.push_back(card);
					}
				}
			}
		}
	}

}

