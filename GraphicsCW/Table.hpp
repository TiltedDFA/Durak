#pragma once 

#include "Player.hpp"

class Table
{
	std::array<std::array<std::shared_ptr<Card>, 2>, 6>cardsOnTable;
public:
	Table();

	~Table();

	void addCardToTableAtk(std::shared_ptr<Card> card, const int pNum);

	void addCardToTableDef(std::shared_ptr<Card> card, const int pNum);

	std::shared_ptr<Card> getCardFromTableAtk(const int index)noexcept;

	std::shared_ptr<Card> getCardFromTableDef(const int index)noexcept;

	std::array<std::array<std::shared_ptr<Card>, 2>, 6>& getEntireTable()noexcept;

	void setEntireTable(std::array<std::array<std::shared_ptr<Card>, 2>, 6> table);

	const int get_amount_of_card_in_table()noexcept;

	int get_num_cards_in_defender_table();

	int get_num_cards_in_atk_table();

	int find_card_in_atk();

	int find_empty_pile_atk();
};