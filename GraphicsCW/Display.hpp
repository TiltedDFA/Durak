#pragma once
#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "raylib.h"

void DisplayBackOfCards(int X_Pos, int Y_Pos, int CardsToDisplay, Texture2D & Card) // (Xpos, Ypos, AmountOfCards, Cardtext)
{
    for (int i = 0; i < CardsToDisplay; i++, X_Pos += 125)
    {
        DrawTexture(Card, X_Pos, Y_Pos, WHITE);        
    }
}

#endif // !DISPLAY_HPP
