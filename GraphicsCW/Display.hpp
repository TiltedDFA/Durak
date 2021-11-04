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
	
	void mCard(Card& card, Vector2 mP)
	{
		/*
		Vector2 oSet = { (mP.x - cPos[i].x),(mP.y - cPos[i].y) };
		cPos[i].x = (mP.x + oSet.x);
		cPos[i].y = (mP.y + oSet.y);
		*/
		//Vector2Add(card.Pos, mP);
		float xOSet = mP.x - card.xPos;
		float yOSet = mP.y - card.yPos;

		float d = std::sqrt(xOSet * xOSet + yOSet * yOSet);
		if (d > 1)
		{
			card.xPos += xOSet * 1;
			card.yPos += yOSet * 1;
		}

	}
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
		
		/*
		int i;
		float x = 600;
		float y = 75;
		for (i=0;i<6;++i){cPos.push_back({(x+125*i),y});}
		y=840;
		for (i=0;i<6;++i){cPos.push_back({(x+125*i),y});}
		return cPos;
		*/
	}
	
}
namespace c1 //C1 namespace functions draw
{
	void card(Table table, Texture2D& cBack, Texture2D& cBlank, int& cardsOnScreen) // (Xpos, Ypos, AmountOfCards, Cardtext)
	{
		for (int i = 0; i < 6; ++i)
		{
			Card card = table.getCardFromTableAtk(i);
			if (card.faceUp)
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
			DrawTexture(cBack, (int)card.xPos, (int)card.yPos, WHITE);
			//++cardsOnScreen;
		}
	}
}
#endif // !DISPLAY_HPP