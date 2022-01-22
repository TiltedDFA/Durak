#include "Class.hpp"

//-------------------------------------------------------------------------------------------------------------

Card::Card()
	: Suit(1), Value(2) //This is a member initilizer list (it needs to be written in order for the vars)
{
}
Card::~Card() {}
std::string Card::suitToString(const card_suit& suit)
{
	switch (suit)
	{
	case card_suit::SPADES:
		return "Spades";
	case card_suit::HEARTS:
		return "Hearts";
	case card_suit::DIAMONDS:
		return "Diamonds";
	case card_suit::CLUBS:
		return "Clubs";
	default:
		break;
	}
	throw std::runtime_error("Unexpected Error with Suit display");
}
std::string Card::valueToString(const card_value& value)
{
	switch (value)
	{
	case card_value::JACK:
		return "Jack";
	case card_value::QUEEN:
		return "Queen";
	case card_value::KING:
		return "King";
	case card_value::ACE:
		return "Ace";
	default:
		break;
	}
	throw std::runtime_error("Unexpected Error with Value display");;
}
void Card::displayCardWithValueText(const std::shared_ptr<Card>& card)
{
	const std::string cValStr = encrypt_data(card->Value) > 10 ? card->valueToString(static_cast<card_value>(encrypt_data(card->Value))) : std::to_string(encrypt_data(card->Value));
	const std::string cSuitStr = card->suitToString(static_cast<card_suit>(encrypt_data(card->Suit)));
	DrawText(cValStr.c_str(), static_cast<int>((card->card_position.x + 10)), static_cast<int>((card->card_position.y + 65)), 20, BLACK);
	DrawText(cSuitStr.c_str(), static_cast<int>((card->card_position.x + 10)), static_cast<int>((card->card_position.y + 95)), 20, BLACK);

}
void Card::set_card_value(const int& value) {

	Value = value;
}
void Card::set_card_suit(const int& suit) {

	Suit = suit;
}
int Card::get_card_value()noexcept{

	return Value;
}
int Card::get_card_suit()noexcept{

	return Suit;
}

//-------------------------------------------------------------------------------------------------------------
Deck::Deck()
{		
}
Deck::Deck(const int deckSize){
	
	int startValue = 0;
	switch (deckSize)
	{
	case 36:
		startValue = 4;
		break;
	case 52:
		startValue = 0;
		break;
	default:
		throw std::runtime_error("Unexpected Deck size value");
		break;
	}
	for (int i = startValue; i < 13; ++i) //13 Represents the different values
	{
		for (int j = 0; j < 4; ++j) // 4 is for the four suits
		{
			std::shared_ptr<Card> C = std::make_shared<Card>(); //This declares a card pointer and allocates it to the heap
			C->set_card_value(encrypt_data(i + 2)); //This is to make up for the array indexing 
			C->set_card_suit(encrypt_data(j + 1)); // As is this 
			deck.emplace_back(C);
		}
	}
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(std::begin(deck), std::end(deck), rng);
}
Deck::~Deck(){
}

std::shared_ptr<Card> Deck::dealCard() {
	
	assert(deck.size());

	std::shared_ptr<Card> holder = deck[0];

	deck.erase(deck.begin());

	return holder;
}

const std::shared_ptr<Card>& Deck::getLastCard() noexcept { // This is the visibleCard
	assert(deck.size());
	return deck[deck.size()-1];
}

void Deck::setPosLastCard(const Vector2& pos) { // Visible Card

	deck[deck.size()-1]->card_position = pos;
}

void Deck::setPosTopCardDeck(const Vector2& pos) { //Top of deck (hidden)

	assert(deck.size() > 0);

	deck[(deck.size() - 2)]->card_position = pos;
}

const std::shared_ptr<Card>& Deck::getTopOfVisDeck() noexcept { //This is the top of the deck(hidden)

	assert(deck.size() > 0);

	return *(deck.end() - 2);
}

void Deck::setmaster_suit(card_suit suit){

	master_suit = suit;
}

int Deck::getDeckSize()noexcept{
	
	return static_cast<int>(deck.size());
}
//-------------------------------------------------------------------------------------------------------------
Player::Player()
{
}
Player::~Player()
{
}
void Player::addToplayer_hand(std::shared_ptr<Card> cardToAdd)
{
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
void Player::setPlyrAtk(bool bol)
{
	plyrAtk = bol;
}
std::vector<std::shared_ptr<Card>> Player::getEntireHand() noexcept {

	return player_hand;
}
void Player::setEntireHand(std::vector<std::shared_ptr<Card>> hand)
{
	player_hand = hand;
}
void Player::set_hand_by_index(std::shared_ptr<Card> card, const int index)
{
	player_hand[index] = card;
}
void Player::set_player_winstate(bool has_won) noexcept {

	player_has_won = has_won;
}
const bool Player::get_player_winstate() noexcept {

	return player_has_won;
}
//-------------------------------------------------------------------------------------------------------------
Table::Table()
{
}
Table::~Table()
{
}
void Table::addCardToTableAtk(std::shared_ptr<Card> card, const int pNum)
{
	cardsOnTable[pNum][0] = card;
}
void Table::addCardToTableDef(std::shared_ptr<Card> card, const int pNum)
{
	cardsOnTable[pNum][1] = card;
}
std::shared_ptr<Card> Table::getCardFromTableAtk(const int index) noexcept {

	return cardsOnTable[index][0];
}
std::shared_ptr<Card> Table::getCardFromTableDef(const int index) noexcept {

	return cardsOnTable[index][1];
}
std::array<std::array<std::shared_ptr<Card>, 2>, 6>& Table::getEntireTable() noexcept {

	return cardsOnTable;
}
void Table::setEntireTable(std::array<std::array<std::shared_ptr<Card>, 2>, 6> table)
{
	cardsOnTable = table;
}
const int Table::get_amount_of_card_in_table() noexcept {

	int count = 0;
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 2; ++j)
			if (cardsOnTable[i][j] != nullptr)
				++count;
				
	return 	count;
}
//-------------------------------------------------------------------------------------------------------------
Discardediscarded_cards::Discardediscarded_cards() {};
Discardediscarded_cards::~Discardediscarded_cards() {};

void Discardediscarded_cards::addToPile(std::shared_ptr<Card> card) noexcept {

	discarded_cards.emplace_back(card);
}
//-------------------------------------------------------------------------------------------------------------
MainGame::MainGame() {}
MainGame::~MainGame() {}

int MainGame::getRound() noexcept {
	return _round;
}
void MainGame::incramentRound()
{
	++_round;
}
void MainGame::setRound(const int num)
{
	_round = num;
}
void MainGame::switchPTurn()
{
	pTurn = (pTurn) ? 0 : 1;
	cardsPlayedThisPass = 0;
}
void MainGame::setPTurn(int player)
{
	pTurn = player;
}
const unsigned short int MainGame::getCardsPlayed() noexcept {

	return cardsPlayedThisPass;
}
void MainGame::setCardsPlayed(unsigned short int played)
{
	cardsPlayedThisPass = played;
}
void MainGame::resetCardsPlayed()
{
	cardsPlayedThisPass = 0;
}
void MainGame::incramentCardsPlayed()
{
	++cardsPlayedThisPass;
}
const int MainGame::getPTurn() noexcept {

	return pTurn;
}
//-------------------------------------------------------------------------------------------------------------