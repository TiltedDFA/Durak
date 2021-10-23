#pragma once
#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "raylib.h"
#include <string>
void DisplayMenu()
{
}
namespace c0
{
	void DisplayBackOfCards(int X_Pos, int Y_Pos, int CardsToDisplay, Texture2D& Card, int& cardsOnScreen) // (Xpos, Ypos, AmountOfCards, Cardtext)
	{
		for (int i = 0; i < CardsToDisplay; ++i, X_Pos += 125)
		{
			DrawTexture(Card, X_Pos, Y_Pos, WHITE);
			++cardsOnScreen;
		}
	}
	std::vector<Rectangle> makeRectOfCards(int cardsOnScreen)
	{
		std::vector<Rectangle>rectanglesOfCards;
		for (int i = 0; i < cardsOnScreen; ++i)
		{

		}
	}
}

#endif // !DISPLAY_HPP