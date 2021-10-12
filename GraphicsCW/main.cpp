#include "raylib.h"
#include "Display.hpp"
#include <iostream>
#include "Class.hpp"

int main(void)
{
	// Variables
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1920;
	const int screenHeight = 1080;
	Vector2 MousePointing = { 0.0f, 0.0f };

	InitWindow(screenWidth, screenHeight, "Durak");
	SetTargetFPS(60);

	bool _TScreen = true; 
	bool prePlayScreen = false; // To select the settings before a match begins
	Deck deck;


	//Collision Rectangles
	//---------------------------------------------------------------------------------------
	Rectangle btnCheckColl = { 772, 509, 287, 105 };

	//Texture Initilization 
	//---------------------------------------------------------------------------------------
	Texture2D TitleScreen = LoadTexture("TitleScreen.png");
	Texture2D  _Table = LoadTexture("TableTwo.png");
	Texture2D CardBacking = LoadTexture("170CardBacking.png");
	
	//--------------------------------------------------------------------------------------
	// Main game loop	

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{	
		MousePointing = GetMousePosition(); //Gets Mouse Pos. and saves it as a 2D co-ordinate

		if (prePlayScreen) // Not true?
		{
			//DisplayBackOfCards(600, 75, 6, CardBacking);
			//DisplayBackOfCards(600, 840, 6, CardBacking);
			//DrawText(TextFormat("Master suit is: %d", ((int)deck.getMasterSuit())), 200, 120, 20, WHITE);
			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(_Table, 0, 0, WHITE);
			EndDrawing();
		}
		else if (_TScreen)
		{
			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(TitleScreen, 0, 0, WHITE);
			EndDrawing();
			if (CheckCollisionPointRec(MousePointing, btnCheckColl))
			{
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				{
					// Do something with the button to make it nice
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
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	system("pause>0");
	return 0;
}
