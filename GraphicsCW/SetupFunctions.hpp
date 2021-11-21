#pragma once
#ifndef SETUPFUNCTIONS_HPP
#define SETUPFUNCTIONS_HPP
#include "Class.hpp"
namespace c1 // Used to setup or maintain
{
	void setTopCards(Deck& deck)
	{
		//376, 503
		std::pair<std::shared_ptr<Card>, std::shared_ptr<Card>> cPair;
		cPair.first = deck.dealCard();
		cPair.second = deck.dealCard();
		cPair.first->cardPosition = { 153, 470 };
		cPair.second->cardPosition = { 153, 470 };
		deck.setTopOfDeck(cPair);
	}
	void addCardsToVisibleVec(std::vector<std::shared_ptr<Card>>& cardsVisible, std::shared_ptr<Card> card)
	{
		cardsVisible.push_back(card);
	}
	void removeCardFromVisibleVect(std::vector<std::shared_ptr<Card>>& cardsVisible, std::shared_ptr<Card> card)
	{
		auto positionOfCardToRemove = std::find(cardsVisible.begin(), cardsVisible.end(), card);
		if (positionOfCardToRemove != cardsVisible.end()) { cardsVisible.erase(positionOfCardToRemove); }
	}
	void setUpPlayerHandPos(std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck, std::array<Player, 2>& players)
	{
		float x = 600;
		float y = 75;
		for (int i = 0; i < 6; ++i)
		{
			std::shared_ptr<Card> card = deck.dealCard();
			//card->canBeTouched = false; Temp disabled until ai is made
			card->cardIsFaceUp = false;
			card->cardPosition = { (x + 125 * i),y };
			players[0].addToPlayerHand(card);
			cardsVisible.push_back(card);
		}
		y = 840;
		for (int i = 0; i < 6; ++i)
		{
			std::shared_ptr<Card> card = deck.dealCard();
			card->cardPosition = { (x + 125 * i),y };
			players[1].addToPlayerHand(card);
			cardsVisible.push_back(card);
		}
		std::shared_ptr<Card> card = deck.dealCard();
		card->cardPosition = { 376, 503 };
		deck.setVisibleCard(card);
		deck.setMasterSuit(card->Suit);
	}
	int findStartingPlayer(std::array<Player, 2>players, Deck deck)
	{
		cardValue lowestVal[2] = { cardValue::ACE, cardValue::ACE };
		auto mS = deck.getMasterSuit();
		for (int i = 0; i < 2; ++i)
		{
			auto hSize = players[i].getPlayerHandSize();
			for (int j = 0; j < hSize; ++j)
			{
				if (players[i].getPlayerHandIndex(j)->Suit == mS && players[i].getPlayerHandIndex(j)->Value < lowestVal[i])
				{
					lowestVal[i] = players[i].getPlayerHandIndex(j)->Value;
				}
			}
		}
		if (lowestVal[0] > lowestVal[1])
		{
			return 1;
		}
		else { return 0; }
	}
	void lockCardsInHand(std::array<Player, 2>players, MainGame mg)
	{
		auto pTurn = mg.getPTurn();
		for (int i = 0; i < players[pTurn].getPlayerHandSize(); ++i)
		{
			auto card = players[pTurn].getPlayerHandIndex(i);
			card->canBeTouched = true;
			players[pTurn].setPlayerHandIndex(card, i);
		}
		auto otherPlayer = (pTurn + 1) % 2;
		for (int i = 0; i < players[otherPlayer].getPlayerHandSize(); ++i)
		{
			auto card = players[otherPlayer].getPlayerHandIndex(i);
			card->canBeTouched = false;
			players[otherPlayer].setPlayerHandIndex(card, i);
		}
	}
}

#endif // !SETUPFUNCTIONS_HPP