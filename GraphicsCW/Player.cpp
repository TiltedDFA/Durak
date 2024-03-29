#include "Player.hpp"
Player::Player()
{
}
Player::~Player()
{
}
void Player::addToplayer_hand(const std::shared_ptr<Card>& cardToAdd) {

	player_hand.push_back(cardToAdd);
}
std::shared_ptr<Card> Player::from_hand_by_index(const int index) {

	return player_hand[index];
}
std::size_t Player::get_hand_size() noexcept {

	return player_hand.size();
}
bool Player::isPlyrAtk() noexcept {

	return plyrAtk;
}
void Player::setPlyrAtk(bool bol) {

	plyrAtk = bol;
}
std::vector<std::shared_ptr<Card>> Player::getEntireHand() noexcept {

	return player_hand;
}
void Player::setEntireHand(std::vector<std::shared_ptr<Card>> hand) {

	player_hand = hand;
}
void Player::set_hand_by_index(std::shared_ptr<Card> card, const int index) {

	player_hand[index] = card;
}
void Player::set_player_winstate(bool has_won) noexcept {

	player_has_won = has_won;
}
const bool Player::get_player_winstate() noexcept {

	return player_has_won;
}
int Player::find_lowest_card(const int& card_suit_value)
{
	int lowest_value = 15;

	int count = 0;

	int lowest_val_positon = 99;

	if (!(card_suit_value && card_suit_value < 5)) //if card_suit_val == 0 then code below doesn't run else it does 
	{
		for (const auto& i : player_hand)
		{
			if (encrypt_data(i->get_card_value()) < lowest_value)
			{
				lowest_value = encrypt_data(i->get_card_value());
				lowest_val_positon = count;
			}
			++count;			
		}
		return lowest_val_positon;
	}

	for(const auto& i : player_hand)
	{
		if (encrypt_data(i->get_card_value()) < lowest_value && encrypt_data(i->get_card_suit()) == card_suit_value)
		{
			lowest_value = encrypt_data(i->get_card_value());
			lowest_val_positon = count;
		}
		++count;
	}
	return lowest_val_positon;
}