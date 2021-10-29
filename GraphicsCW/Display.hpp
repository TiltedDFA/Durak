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
namespace c0
{
	void DisplayBackOfCards(Table table, Texture2D& _Card, int& cardsOnScreen) // (Xpos, Ypos, AmountOfCards, Cardtext)
	{
		for (int i = 0; i < 6; ++i)
		{
			Card card = table.getCardFromTableAtk(i);
			DrawTexture(_Card, card.xPos, card.yPos, WHITE);
			++cardsOnScreen;
		}
		for (int i = 0; i < 6; ++i)
		{
			Card card = table.getCardFromTableDef(i);
			DrawTexture(_Card, card.xPos, card.yPos, WHITE);
			++cardsOnScreen;
		}
	}
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
			Card temp = deck.removeTopCard(); 
			table.addCardToTableAtk(temp, i);
			table.setCardPosAtk(i,{(x+125*i),y});
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

#endif // !DISPLAY_HPP