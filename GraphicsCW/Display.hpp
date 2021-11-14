#pragma once
#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "Class.hpp"

namespace c0 // c0 will be the setting up / maintaing function
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
	void addCardsToVisibleVec(std::vector<std::shared_ptr<Card>>&cardsVisible, std::shared_ptr<Card> card)
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
			card->canBeTouched = false;
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
}
namespace c1 // This namespace does something e.g. finding the starting player
{
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
	bool canCardBePlayed(Table table, std::shared_ptr<Card> card) // This function checks if an attacking card can be played based on the cards in the table.
	{
		std::array<std::array<std::shared_ptr<Card>, 2>, 6>cardsOnTable = table.getEntireTable();
		if (cardsOnTable[0][0] == nullptr && cardsOnTable[1][0] == nullptr && cardsOnTable[2][0] == nullptr && cardsOnTable[3][0] == nullptr && cardsOnTable[4][0] == nullptr && cardsOnTable[5][0] == nullptr)
		{
			return true;
		}
		if (cardsOnTable[0][0]->Value == card->Value || cardsOnTable[1][0]->Value == card->Value || cardsOnTable[2][0]->Value == card->Value || cardsOnTable[3][0]->Value == card->Value || cardsOnTable[4][0]->Value == card->Value || cardsOnTable[5][0]->Value == card->Value)
		{
			return true;
		}
		return false;
	}
	bool cardBeatsCard(const std::shared_ptr<Card> cardOne, const std::shared_ptr<Card> cardTwo, Deck deck)
	{
		cardSuit mS = deck.getMasterSuit();
		if (cardOne->Suit == mS && cardTwo->Suit != mS) { return true; }
		else { return false; }
		if (cardOne->Suit == cardTwo->Suit && cardOne->Value > cardTwo->Value) { return true; }
		else { return false; }
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
		return { { 0,0 }, 7};
	}
	void moveCardFromPlayerHandToTable(Player& player, Table& table, std::shared_ptr<Card> card, const int cardPile)
	{
		std::vector<std::shared_ptr<Card>> playerHand = player.getEntireHand();
		auto posInHand = std::find(playerHand.begin(), playerHand.end(), card);
		if (posInHand != playerHand.end())
		{
			if (player.isPlyrAtk()) { table.addCardToTableAtk(std::move(*posInHand), cardPile); }
			else { table.addCardToTableDef(std::move(*posInHand), cardPile); }
		}	
	}
}
namespace c2 // This namespace is used to display 
{
	void cTable(std::vector<std::shared_ptr<Card>>cardsVisible, Texture2D& cBack, Texture2D& cBlank, int& cardsOnScreen) // (Xpos, Ypos, AmountOfCards, Cardtext)
	{
		for (auto i = 0; i < cardsVisible.size(); ++i)
		{
			if (cardsVisible[i]->cardIsFaceUp)
			{
				DrawTexture(cBlank, static_cast<int>(cardsVisible[i]->cardPosition.x), static_cast<int>(cardsVisible[i]->cardPosition.y), WHITE);
			}
			else if (!cardsVisible[i]->cardIsFaceUp)
			{
				DrawTexture(cBack, static_cast<int>(cardsVisible[i]->cardPosition.x), static_cast<int>(cardsVisible[i]->cardPosition.y), WHITE);
			}
		}
	}
	void displayDeckExtraCards(Deck& deck, Texture2D& backOfCard, Texture2D& frontOfCard)
	{
		auto vCard = deck.getVisibleCard();
		auto topCards = deck.getTopOfDeck();
		//Still need to display visible card
		DrawTexture(backOfCard, static_cast<int>(topCards.first->cardPosition.x), static_cast<int>(topCards.first->cardPosition.y), WHITE);
		DrawTexture(backOfCard, static_cast<int>(topCards.second->cardPosition.x), static_cast<int>(topCards.second->cardPosition.y), WHITE);
	}
}
namespace c3 // This will be used to preform game functions
{

}
#endif // !DISPLAY_HPP