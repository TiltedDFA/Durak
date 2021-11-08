#pragma once
#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "raylib.h"
#include "Class.hpp"
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
void DisplayMenu()
{
}
namespace c1 //C1 namespace functions draw
{
	void cTable(std::vector<Card*>cardsVisible, Texture2D& cBack, Texture2D& cBlank, int& cardsOnScreen) // (Xpos, Ypos, AmountOfCards, Cardtext)
	{
		for (auto i = 0; i < cardsVisible.size(); ++i)
		{
			if (cardsVisible[i]->faceUp)
			{
				DrawTexture(cBlank, cardsVisible[i]->xPos, cardsVisible[i]->yPos, WHITE);
			}
			else if (!cardsVisible[i]->faceUp)
			{
				DrawTexture(cBack, cardsVisible[i]->xPos, cardsVisible[i]->yPos, WHITE);
			}
		}
	}
	void rectangles()
	{
		std::array<Vector2, 6>pos;
		pos[0] = { 543.0, 457.0 };
		pos[1] = { 688.0, 457.0 };
		pos[2] = { 840.0, 457.0 };
		pos[3] = { 990.0, 457.0 };
		pos[4] = { 1143.0,457.0 };
		pos[5] = { 1300.0,457.0 };
		for (int i = 0; i < pos.size(); ++i)
		{
			DrawRectangle((int)pos[i].x, (int)pos[i].y, 120, 170, WHITE);
			//DrawRectangle(457.0, 543.0, 120, 170, WHITE);
		}
	}
}
namespace c2
{
	bool placeHBC(int percentCertanty, Card card)
	{
		std::array<Vector2, 6>pos;
		pos[0] = { 543.0, 457.0 };
		pos[1] = { 688.0, 457.0 };
		pos[2] = { 840.0, 457.0 };
		pos[3] = { 990.0, 457.0 };
		pos[4] = { 1143.0,457.0 };
		pos[5] = { 1300.0,457.0 };
		Rectangle rCard = {card.xPos, card.yPos, 120, 170};
		for (int i = 0; i < 6; ++i)
		{
			Rectangle placeHB = { pos[i].x, pos[i].y, 120, 170 };			
			if (CheckCollisionRecs(rCard, placeHB))
			{
				auto xOSet = placeHB.width -  sqrt(((card.xPos - placeHB.x) * (card.xPos - placeHB.x)));
				auto yOSet = placeHB.height - sqrt(((card.yPos - placeHB.y) * (card.yPos - placeHB.y)));
				auto oSetArea = xOSet * yOSet;
				auto area = placeHB.width * placeHB.height;
				auto percentOverlap = ((oSetArea / area) * 100);
				if ((int)percentOverlap > percentCertanty)
				{
					return true;
				}
			}
		}
		return false;
	}
	Vector2 BoxColFinder(Card card)
	{
		std::array<Vector2, 6>pos;
		pos[0] = { 543.0, 457.0 };
		pos[1] = { 688.0, 457.0 };
		pos[2] = { 840.0, 457.0 };
		pos[3] = { 990.0, 457.0 };
		pos[4] = { 1143.0,457.0 };
		pos[5] = { 1300.0,457.0 };
		Rectangle rCard = { card.xPos, card.yPos, 120, 170 };

		for (int i = 0; i < 6; ++i)	
		{
			Rectangle box = { pos[i].x, pos[i].y, 120, 170 };
			if (CheckCollisionRecs(rCard, box))
			{
				return pos[i];
			}
		}
		return { 0,0 };
	}	
	
	void addCardToPlay(std::vector<Card*> &cardPointers, Card* ptrToCard)
	{
		cardPointers.push_back(ptrToCard);
	}
	void removeCardFromPlay(std::vector<Card*>& cardPointers, Card* cardToAdd)
	{
		auto result = std::find(cardPointers.begin(), cardPointers.end(), cardToAdd); // If element matches the search, returns an iterator to the element. If no elements match then it returns an iterator to last iteam of the list
		if (result != cardPointers.end())
		{
			cardPointers.erase(result);
		}		
	}
	
}
namespace c3 // c3 namespace function set up or do something update something
{
	void setPosCard(std::vector<Card*> &cardsVisible, std::array<Player, 2>&player, Deck& deck /*std::vector<Vector2>& cPos*/)
	{
		float x = 600;
		float y = 75;
		for (int i = 0; i < 6; ++i)
		{
			Card card = deck.removeTopCard();
			player[0].addToPlayerHand(i, card);
			//table.setCardPosAtk(i, { (x + 125 * i),y });
			player[0].setCardPos({ (x + 125 * i),y }, i);
			Card* cPtr = player[0].getCardPtr(i);
			cardsVisible.push_back(cPtr);
		}
		y = 840;

		for (int i = 0; i < 6; ++i)
		{
			Card card = deck.removeTopCard();			
			player[1].addToPlayerHand(i, card);
			//table.setCardPosDef((i), { (x + 125 * i),y });
			player[1].setCardPos({ (x + 125 * i),y }, i);
			Card* cPtr = player[1].getCardPtr(i);
			cardsVisible.push_back(cPtr);
		}
	}

}
#endif // !DISPLAY_HPP