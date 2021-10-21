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
	void DisplayBackOfCards(int X_Pos, int Y_Pos, int CardsToDisplay, Texture2D& Card) // (Xpos, Ypos, AmountOfCards, Cardtext)
	{
		for (int i = 0; i < CardsToDisplay; ++i, X_Pos += 125)
		{
			DrawTexture(Card, X_Pos, Y_Pos, WHITE);
		}
	}
	void DisplayWordInMiddleOfTexture(int X_Pos, int Y_Pos, Texture2D& texture, std::string message)
	{
		const char msg[50] = message...;
		DrawTexture(texture, X_Pos, Y_Pos, WHITE);
		DrawText(message, )
			//time to raylib 
	}
}

#endif // !DISPLAY_HPP