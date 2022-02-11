#pragma once

#include "Maingame.hpp"

namespace c1 {// Used to setup or maintain

	extern inline void addiscarded_cardsToVisibleVec(std::vector<std::shared_ptr<Card>>& cards_visible, std::shared_ptr<Card> card);

	extern inline void removeCardFromVisibleVect(std::vector<std::shared_ptr<Card>>& cards_visible, std::shared_ptr<Card> card);

	extern inline void init_player_hands(std::vector<std::shared_ptr<Card>>& cards_visible, Deck& deck, std::array<Player, 2>& players);

	extern inline int findStartingPlayer(std::array<Player, 2> players);

	extern inline void lockCardsInHand(std::array<Player, 2>players, MainGame mg);

	extern inline void bringCardOneToTop(const std::shared_ptr<Card>& cardOne, const std::shared_ptr<Card>& cardTwo, std::vector<std::shared_ptr<Card>>& cards_visible);

	extern inline void remove_table_from_visible_vector(Table& table, std::vector<std::shared_ptr<Card>>& cards_visible);

	extern inline bool deck_has_enough_cards_left(Deck& deck, const int numOfCardsNeeded);

	extern inline void add_need_cards_to_players(std::array<Player, 2>& players, std::vector<std::shared_ptr<Card>>& cards_visible, Deck& deck);
}
