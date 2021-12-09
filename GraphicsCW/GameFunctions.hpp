#pragma once
#ifndef GAMEFUNCTIONS_HPP
#define GAMEFUNCTIONS_HPP
#include "SetupFunctions.hpp"

namespace c2
{
	int  placeHBC(int percentCertanty, std::shared_ptr<Card> card)
	{
		std::array<Vector2, 6>pos{};
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
				auto oSetArea = (placeHB.width - sqrt(((card->cardPosition.x - placeHB.x) * (card->cardPosition.x - placeHB.x)))) * (placeHB.height - sqrt(((card->cardPosition.y - placeHB.y) * (card->cardPosition.y - placeHB.y))));
				auto percentOverlap = ((oSetArea / (placeHB.width * placeHB.height)) * 100);
				if (static_cast<int>(percentOverlap > percentCertanty))// Converted to an int to force rounding
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
		const std::array<std::array<std::shared_ptr<Card>, 2>, 6>cardsOnTable = table.getEntireTable();		
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
		std::array<Vector2, 6>pos{};
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
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{				

				if (cardsOnTable[i][j] != nullptr)
				{
					auto posInCV = std::find(cardsVisible.begin(), cardsVisible.end(), cardsOnTable[i][j]);
					if (posInCV != cardsVisible.end()) { cardsVisible.erase(posInCV); }
					bPile.addToPile(std::move(cardsOnTable[i][j]));
				}
			}
		}
		table.setEntireTable(cardsOnTable);
	}
	bool canPassDef(Table& table)
	{
		const std::array<std::array<std::shared_ptr<Card>, 2>, 6> cardsOnTable = table.getEntireTable();
		std::pair<int, int> cardsPlayed;
		for (auto& i : cardsOnTable)
		{
			if (i[0] != nullptr) { ++cardsPlayed.first; }
			if (i[1] != nullptr) { ++cardsPlayed.second; }
		}
		if (!cardsPlayed.first) { return false; }
		else if (cardsPlayed.first == cardsPlayed.second) { return true; }
		return false;
	}
	void switchPlayerStates(std::array<Player, 2>& players) 
	{
		players[0].setPlyrAtk(!players[0].isPlyrAtk()); players[1].setPlyrAtk(!players[1].isPlyrAtk()); 
	}
	bool canEndAtk(Table& table) // use this to auto pass once defender defends
	{
		const std::array<std::array<std::shared_ptr<Card>, 2>, 6> cardsOnTable = table.getEntireTable();
		int completedValues = 0;
		for (const auto& i : cardsOnTable)
		{
			if (i[0] != nullptr && i[1] != nullptr) { ++completedValues; }
		}
		if (completedValues) { return true; }
		return false;
	}
	void moveAllTableToPlayerHand(Player& player, Table& table)
	{
		std::array<std::array<std::shared_ptr<Card>, 2>, 6> cTable = table.getEntireTable();
		Vector2 takenCardPos = { 0, 150 };		
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				if (cTable[i][j] != nullptr)
				{
					takenCardPos.x = (75.0f * i);
					cTable[i][j]->cardPosition = takenCardPos;
					cTable[i][j]->canBeTouched = true;
					player.addToPlayerHand(std::move(cTable[i][j]));
				}				
			}
		}
		table.setEntireTable(cTable);
	}
	void hasDefenderCoveredAllCards(Table& table)
	{

	}
	int checkIfPlayersWon(Deck& deck, std::array<Player, 2>& players)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (deck.getDeckSize() == 0 && players[i].getPlayerHandSize() == 0) //This checks if both deckSize and HandSize == 0;
			{
				return i;
			}
		}
		return 2;
	}	
	void playMusic(const int musicNum, Music& JazzMusic,Music& LofiMusic, Music& eSwingMusic)
	{
		switch (musicNum)
		{
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
	void continuePlayingMusic(const int musicNum, Music& JazzMusic, Music& LofiMusic, Music& eSwingMusic)
	{
		switch (musicNum)
		{
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
	
}
namespace c4 //This will be my finite state machine AI
{
constexpr auto ZeroValue = 0.0f;// These are all values that are declared here so they can be tweaked in order finetune the AI
constexpr auto MSValue = 20.0f;
constexpr auto sameSuitConst = 1.0f;

	const double findDefendingEval(std::shared_ptr<Card> cardUsedToDefend, std::shared_ptr<Card> cardToDefend, Deck& deck)
	{
		const cardSuit ms = deck.getMasterSuit();
		if (cardUsedToDefend->Suit != cardToDefend->Suit && cardUsedToDefend->Suit != ms) //Different suits and non ms 
		{
			return ZeroValue;
		}
		else if (cardUsedToDefend->Suit == cardToDefend->Suit && cardUsedToDefend->Value < cardToDefend->Value) //same suit lower value
		{
			return ZeroValue;
		}
		else if (cardUsedToDefend->Suit == ms && cardToDefend->Suit != ms)//Master suit vs non ms 
		{
			return (static_cast<float>(cardUsedToDefend->Value) + MSValue);
		}
		else if (cardUsedToDefend->Suit == cardToDefend->Suit && cardUsedToDefend->Value > cardToDefend->Value) //Same suit higher val
		{
			return (static_cast<float>(cardUsedToDefend->Value) - static_cast<float>(cardToDefend->Value));
		}
		return 9999999999999999999;
	}
	auto returnBestPlayerHandEval(const std::shared_ptr<Card>& card, Player& player, Deck& deck)
	{	
		std::vector<std::pair<double, std::vector<std::shared_ptr<Card>>::iterator>>evaluations;
		auto hand = player.getEntireHand();
		for (int i = 0; i < static_cast<int>(player.getPlayerHandSize()); ++i)
		{
			std::pair<double, std::vector<std::shared_ptr<Card>>::iterator>evalInfo;
			evalInfo.first = findDefendingEval(hand[i], card, deck);
			evalInfo.second = (hand.begin() + i);
			evaluations.push_back(evalInfo);
		}
		std::sort(evaluations.begin(), evaluations.end(), [](const std::pair<double, std::vector<std::shared_ptr<Card>>::iterator>& a, const std::pair<double, std::vector<std::shared_ptr<Card>>::iterator>& b)->bool { return (a.first < b.first); });
		
		for (int i = 0; i < static_cast<int>(evaluations.size()); ++i)
		{
			if (static_cast<int>(evaluations[i].first))
			{
				return evaluations[(i + 1)].second;
			}		
		}
		return hand.end();
	}
	auto defendACardBot(Table& table,Player& bot)
	{
		std::array<std::array<std::shared_ptr<Card>, 2>, 6>_t = table.getEntireTable();
		for(const auto& i : _t)
		{
			if (i[0] != nullptr && i[1] == nullptr)
			{
				//evaluations.push_back();
			}
		}
	}
	
	/*
	const double findDefendingEval(std::shared_ptr<Card> cardOne, std::shared_ptr<Card> cardTwo, Deck& deck)
	{
		const cardSuit ms = deck.getMasterSuit();
		if (cardOne->Suit != cardTwo->Suit && cardOne->Suit != ms) //Different suits and non ms 
		{
			return ZeroValue;
		}
		else if (cardOne->Suit == cardTwo->Suit && cardOne->Value < cardTwo->Value) //same suit lower value
		{
			return ZeroValue;
		}
		else if (cardOne->Suit == ms && cardTwo->Suit != ms)//Master suit vs non ms 
		{
			return (1 / (MSValue * static_cast<int>(cardOne->Value)));
		}
		else if (cardOne->Suit == cardTwo->Suit && cardOne->Value > cardTwo->Value) //Same suit higher val
		{
			return (1/(sameSuitConst*((static_cast<int>(cardOne->Value)
				- static_cast<int>(cardTwo->Value)))));
		}
	}
	*/
	/*
	std::vector<std::shared_ptr<Card>>::iterator evaluatePlayerHand(Player& bot, Table& table,Deck& deck)
	{
		auto handSize = bot.getPlayerHandSize();
		if (bot.isPlyrAtk())
		{

		}
		else if (!bot.isPlyrAtk())
		{
			std::vector<double>cardEvals;
			for (int i = 0; i < handSize; ++i)
			{
			//	cardEvals.push_back(findDefendingEval());
			}
		}
		//return std::vector<std::shared_ptr<Card>::;
	}
	*/
}
#endif // !GAMEFUNCTIONS_HPP
