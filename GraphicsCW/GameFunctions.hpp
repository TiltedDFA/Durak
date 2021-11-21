#pragma once
#ifndef GAMEFUNCTIONS_HPP
#define GAMEFUNCTIONS_HPP
#include "SetupFunctions.hpp"

namespace c2
{
	int  placeHBC(int percentCertanty, std::shared_ptr<Card> card)
	{
		std::array<Vector2, 6>pos;
		pos[0] = { 543.0, 457.0 };
		pos[1] = { 688.0, 457.0 };
		pos[2] = { 840.0, 457.0 };
		pos[3] = { 990.0, 457.0 };
		pos[4] = { 1143.0,457.0 };
		pos[5] = { 1300.0,457.0 };
		Rectangle rCard = { card->cardPosition.x, card->cardPosition.y, 120, 170 };
		for (int i = 0; i < 6; ++i)
		{
			Rectangle placeHB = { pos[i].x, pos[i].y, 120, 170 };
			if (CheckCollisionRecs(rCard, placeHB))
			{
				auto xOSet = placeHB.width - sqrt(((card->cardPosition.x - placeHB.x) * (card->cardPosition.x - placeHB.x)));
				auto yOSet = placeHB.height - sqrt(((card->cardPosition.y - placeHB.y) * (card->cardPosition.y - placeHB.y)));
				auto oSetArea = xOSet * yOSet;
				auto area = placeHB.width * placeHB.height;
				auto percentOverlap = ((oSetArea / area) * 100);
				if (static_cast<int>(percentOverlap > percentCertanty))
				{
					return static_cast<int>(percentOverlap);
				}
			}
		}
		return 0;
	}
	bool canCardBePlayed(Table& table, std::shared_ptr<Card> card) // This function checks if an attacking card can be played based on the cards in the table.
	{


		if (!card->cardIsFaceUp) { return false; }
		std::array<std::array<std::shared_ptr<Card>, 2>, 6>cardsOnTable = table.getEntireTable();
		//auto cardPosInTable = std::find(cardsOnTable.begin(), cardsOnTable.end(), card);
		//if (cardPosInTable != cardsOnTable.end()) { return false; }
		if (cardsOnTable[0][0] == nullptr && cardsOnTable[1][0] == nullptr && cardsOnTable[2][0] == nullptr && cardsOnTable[3][0] == nullptr && cardsOnTable[4][0] == nullptr && cardsOnTable[5][0] == nullptr)
		{
			if (cardsOnTable[0][1] == nullptr && cardsOnTable[1][1] == nullptr && cardsOnTable[2][1] == nullptr && cardsOnTable[3][1] == nullptr && cardsOnTable[4][1] == nullptr && cardsOnTable[5][1] == nullptr)
			{
				return true;
			}
		}
		for (const auto& i : cardsOnTable)
		{
			for (int j = 0; j < 2; ++j)
			{
				if (i[j] != nullptr) { if (i[j]->Value == card->Value) { return true; } }
			}
		}
		return false;
	}
	bool cardBeatsCard(const std::shared_ptr<Card> cardOne, const std::shared_ptr<Card> cardTwo, Deck deck)
	{
		if (cardTwo == nullptr) { return false; }// This code assumes that the only cards that will be passed to the function will be from the table
		cardSuit mS = deck.getMasterSuit();
		if (cardOne->Suit == mS && cardTwo->Suit != mS) { return true; }
		else if (cardOne->Suit == cardTwo->Suit && cardOne->Value > cardTwo->Value) { return true; }
		return false;
	}
	std::pair<Vector2, int> BoxColFinder(const std::shared_ptr<Card> card)
	{
		std::array<Vector2, 6>pos;
		pos[0] = { 543.0, 457.0 };
		pos[1] = { 688.0, 457.0 };
		pos[2] = { 840.0, 457.0 };
		pos[3] = { 990.0, 457.0 };
		pos[4] = { 1143.0,457.0 };
		pos[5] = { 1300.0,457.0 };
		Rectangle rCard = { card->cardPosition.x, card->cardPosition.y, 120, 170 };

		for (int i = 0; i < 6; ++i)
		{
			Rectangle box = { pos[i].x, pos[i].y, 120, 170 };
			if (CheckCollisionRecs(rCard, box)) { return { pos[i], i }; }
		}
		return { { 0,0 }, 7 };
	}
	void moveCardFromPlayerHandToTable(Player& player, Table& table, std::shared_ptr<Card> card, const int cardPile)
	{
		std::vector<std::shared_ptr<Card>> playerHand = player.getEntireHand();
		auto posInHand = std::find(playerHand.begin(), playerHand.end(), card);
		if (posInHand != playerHand.end())
		{
			if (player.isPlyrAtk()) { table.addCardToTableAtk(std::move(*posInHand), cardPile); playerHand.erase(posInHand); }

			else { table.addCardToTableDef(std::move(*posInHand), cardPile); playerHand.erase(posInHand); card->inDefTablePile = true; }

			player.setEntireHand(playerHand);
		}
	}
	void moveAllTableToBPile(DiscardedCards& bPile, Table& table, std::vector<std::shared_ptr<Card>>& cardsVisible)
	{
		std::array<std::array<std::shared_ptr<Card>, 2>, 6>cardsOnTable = table.getEntireTable();
		for (const auto& i : cardsOnTable)
		{
			for (int j = 0; j < 2; ++j)
			{				

				if (i[j] != nullptr)
				{ 
					auto posInCV = std::find(cardsVisible.begin(), cardsVisible.end(), i[j]);
					if (posInCV != cardsVisible.end()) { cardsVisible.erase(posInCV); }
					bPile.addToPile(std::move(i[j]));
				}
			}
		}

	}
	bool canPassDef(Table& table)
	{
		std::array<std::array<std::shared_ptr<Card>, 2>, 6> cardsOnTable = table.getEntireTable();
		std::pair<int, int> cardsPlayed;
		for (auto& i : cardsOnTable)
		{
			if (i[0] != nullptr) { ++cardsPlayed.first; }
			if (i[1] != nullptr) { ++cardsPlayed.second; }
		}
		if (cardsPlayed.first == cardsPlayed.second) { return true; }
		return false;
	}
	void switchPlayerStates(std::array<Player, 2>& players) 
	{
		players[0].setPlyrAtk(!players[0].isPlyrAtk()); players[1].setPlyrAtk(!players[1].isPlyrAtk()); 
	}
}
#endif // !GAMEFUNCTIONS_HPP
