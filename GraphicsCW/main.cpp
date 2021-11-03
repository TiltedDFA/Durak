#include "raylib.h"
#include "raymath.h"
#include "Display.hpp"
#include <iostream>
#include "Class.hpp"
#include <vector>

int main()
{
	// Variables
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1920;
	const int screenHeight = 1050; // have to do this to fix the mouse ghosting issue
	InitWindow(screenWidth, screenHeight, "Durak");
	SetTargetFPS(120);
	//---------------------------------------------------------------------------------------
	Vector2 mP = { 0.0f, 0.0f };
	Vector2 dMP = { 0.0f, 0.0f };
	bool _TScreen = true;
	bool prePlayScreen = false;
	bool clickedOnCard = false;
	int amtOfCardsOnScreen = 0;
	Deck deck;
	Table table;
	//---------------------------------------------------------------------------------------
	Rectangle btnCheckColl = { 772, 509, 287, 105 };	
	//---------------------------------------------------------------------------------------
	Image appIcon = LoadImage("appIcon.png");
	SetWindowIcon(appIcon);
	Texture2D blankCard = LoadTexture("170pixelBlank.png");
	Texture2D TitleScreen = LoadTexture("TitleScreen.png");
	Texture2D  _Table = LoadTexture("TableTwo.png");
	Texture2D CardBacking = LoadTexture("170CardBacking.png");
	//--------------------------------------------------------------------------------------
	// Main game loop

	//Code something that moves the cards when the mouse moves them. The co-ordinates of the cards will be the mouse co-ordinates + the offset of where the mouse clicks the card
	c0::setPosCard(table, deck);
	while (!WindowShouldClose())
	{
		mP = GetMousePosition();
		
		if (prePlayScreen)
		{			
			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(_Table, 0, 0, WHITE);
			c0::DisplayBackOfCards(table, CardBacking, amtOfCardsOnScreen);		
			DrawCircleV(GetMousePosition(), 10, WHITE);
			EndDrawing();
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				for (int i = 0; i < 12; ++i)
				{
					
					Rectangle card;
					Card _card;
					if (i < 5) {
						card = { table.getCardFromTableAtk(i).xPos, table.getCardFromTableAtk(i).yPos, 120, 170 };
						_card = table.getCardFromTableAtk(i);
					}
					else
					{ //THE ERROR LIES BELOW THIS LINE 
						card = { table.getCardFromTableDef((i-5)).xPos, table.getCardFromTableDef((i-5)).yPos, 120, 170 };
						_card = table.getCardFromTableDef((i-5));
					}
					if (CheckCollisionPointRec(mP, card))
					{
						//if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
						//{
							dMP = GetMouseDelta();
							//Vector2Add(cPos[i],  GetMouseDelta());
							c0::mCard(_card, dMP);
							
							//cPos[i] = GetMousePosition() + (cPos[i] - GetMousePosition());
						//}
				    }
					
				}
			}
					
		}
		else if (_TScreen)
		{
			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(TitleScreen, 0, 0, WHITE);
			DrawCircleV(GetMousePosition(), 10, WHITE);
			EndDrawing();
			if (CheckCollisionPointRec(mP, btnCheckColl))
			{
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				{					
					prePlayScreen = true;
					_TScreen = false;
				}
			}
		}
		//----------------------------------------------------------------------------------
	}
	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(CardBacking);
	UnloadTexture(TitleScreen);
	UnloadTexture(_Table);
	CloseWindow();// Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	system("pause>0");
	return 0;
}