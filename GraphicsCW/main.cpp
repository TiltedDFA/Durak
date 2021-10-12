#include "raylib.h"
#include "Display.hpp"
#include <iostream>
#include "Class.hpp"

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	Vector2 MousePointing = { 0.0f, 0.0f };

	InitWindow(screenWidth, screenHeight, "Durak");
	SetTargetFPS(60);

	bool _TScreen = true;
	Deck deck;

	Rectangle btnCheckColl = { 772, 509, 287, 105 };
	Texture2D TitleScreen = LoadTexture("TitleScreen.png");
	Texture2D  _Table = LoadTexture("TableTwo.png");
	Texture2D CardBacking = LoadTexture("170CardBacking.png");
	
	//--------------------------------------------------------------------------------------
	// Main game loop	

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{	
		MousePointing = GetMousePosition();
		if (!_TScreen) // Not true?
		{
			//DisplayBackOfCards(600, 75, 6, CardBacking);
			//DisplayBackOfCards(600, 840, 6, CardBacking);
			//DrawText(TextFormat("Master suit is: %d", ((int)deck.getMasterSuit())), 200, 120, 20, WHITE);
		}
		else
		{
			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(TitleScreen, 0, 0, WHITE);
			EndDrawing();
			if (CheckCollisionPointRec(MousePointing, btnCheckColl))
			{
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				{
					BeginDrawing();
					DisplayBackOfCards(600, 75, 6, CardBacking);
					EndDrawing();
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
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	system("pause>0");
	return 0;
}
