#include "Table.hpp"

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
int Table::get_num_cards_in_defender_table() {

	int count = 0;

	for (const auto& i : cardsOnTable)
	{
		if (i[1] != nullptr)
			++count;
	}
	return count;
}
int Table::get_num_cards_in_atk_table() {

	int count = 0;

	for (const auto& i : cardsOnTable)
	{
		if (i[0] != nullptr)
			++count;
	}
	return count;
}
int Table::find_card_in_atk() {

	for (int i = 0; i < 6; ++i)
	{
		if (!(cardsOnTable[i][0] == nullptr))
			return i;
	}
	return 6;//if no free spots are found, it will return 6
}
int Table::find_empty_pile_atk()
{
	for (int i = 0; i < 6; ++i)
	{
		if (cardsOnTable[i][0] == nullptr)
			return i;
	}
	return 6;
}
