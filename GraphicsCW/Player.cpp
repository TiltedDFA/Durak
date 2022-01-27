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
std::shared_ptr<Card> Player::from_hand_by_index(const int index) noexcept {

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