#pragma once
#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "raylib.h"
#include "Class.hpp"
#include <string>
#include <vector>
#include <cmath>
void DisplayMenu()
{
}
namespace c0 // c0 namespace function set up or do something update something
{	
	void setPosCard(Table& table, Deck deck /*std::vector<Vector2>& cPos*/)
	{ 
		float x = 600;
		float y = 75;
		for (int i = 0; i < 6; ++i)
		{			
			table.addCardToTableAtk(deck.removeTopCard(), i);			
			table.setCardPosAtk(i, { (x + 125 * i),y });
		}
		y = 840;
		for (int i = 0; i < 6; ++i)
		{			
			table.addCardToTableDef(deck.removeTopCard(), i);
			table.setCardPosDef((i),{(x+125*i),y});
		}
	}
	
}
namespace c1 //C1 namespace functions draw
{
	void cTable(Table table, Texture2D& cBack, Texture2D& cBlank, int& cardsOnScreen) // (Xpos, Ypos, AmountOfCards, Cardtext)
	{
		for (int i = 0; i < 6; ++i)
		{
			Card card = table.getCardFromTableAtk(i);
			if (card.faceUp) // this is not being hit 
			{
				DrawTexture(cBlank, (int)card.xPos, (int)card.yPos, WHITE);
			}
			else if (!card.faceUp)
			{
				DrawTexture(cBack, (int)card.xPos, (int)card.yPos, WHITE);
			}
			//*char val = &(char)(int)card.Value;
			//DrawText(val.c_str(), card.xPos);
			//++cardsOnScreen;
		}
		for (int i = 0; i < 6; ++i)
		{
			Card card = table.getCardFromTableDef(i);
			if (card.faceUp)
			{
				DrawTexture(cBlank, (int)card.xPos, (int)card.yPos, WHITE);
			}
			else if (!card.faceUp)
			{
				DrawTexture(cBack, (int)card.xPos, (int)card.yPos, WHITE);
			}
			//++cardsOnScreen;
		}
	}
}
namespace c2
{
	bool placeHBC(int percentCertanty, Card card)
	{
		std::array<Vector2, 6>pos = { (457,543), (457, 688), (457,840), (457,990), (457,1143), (457,1300)};
		Rectangle rCard = {card.xPos, card.yPos, 120, 170};
		for (int i = 0; i < 6; ++i)
		{
			Rectangle placeHB = { pos[i].x, pos[i].y, 120, 170 };			
			if (CheckCollisionRecs(rCard, placeHB))
			{
				auto xOSet = rCard.width -  sqrt((card.xPos - placeHB.x) * (card.xPos - placeHB.x));
				auto yOSet = rCard.height - sqrt((card.yPos - placeHB.y) * (card.yPos - placeHB.y));
				auto oSetArea = xOSet * yOSet;
				auto area = rCard.width * rCard.height;
				auto percentOverlap = ((oSetArea / area) * 100);
				if (percentOverlap > percentCertanty)
				{
					return true;
				}
			}
		}
		return false;
	}
}
#endif // !DISPLAY_HPP