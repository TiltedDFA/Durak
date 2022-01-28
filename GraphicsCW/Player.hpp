#pragma once

#include "Deck.hpp"
class Player
{
protected:
	bool player_has_won = false;
private:
	std::vector<std::shared_ptr<Card>>player_hand;
	bool plyrAtk = false;
public:
	Player();
	~Player();
	void addToplayer_hand(const std::shared_ptr<Card>& cardToAdd);
	std::shared_ptr<Card> from_hand_by_index(const int index)noexcept;
	std::size_t get_hand_size()noexcept;
	bool isPlyrAtk() noexcept;
	void setPlyrAtk(bool bol);
	std::vector<std::shared_ptr<Card>> getEntireHand()noexcept;
	void setEntireHand(std::vector<std::shared_ptr<Card>> hand);
	void set_hand_by_index(std::shared_ptr<Card> card, const int index);
	void set_player_winstate(bool has_won)noexcept;
	const bool get_player_winstate()noexcept;
	int find_lowest_card(int val);
};
