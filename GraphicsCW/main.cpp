#include "raylib.h"
#include "Display.hpp"
#include <iostream>
#include "Class.hpp"

int main()
{
	// Variables
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1920;
	const int screenHeight = 1050; // have to do this to fix the mouse ghosting issue
	Vector2 MousePointing = { 0.0f, 0.0f };

	InitWindow(screenWidth, screenHeight, "Durak");
	SetTargetFPS(120); // This is to test how to increase the responsiveness
	bool _TScreen = true;
	bool prePlayScreen = false; // To select the settings before a match begins
	Deck deck;
	//TODO code something that will get get a deck to display cards on the play screen
	//Collision Rectangle
	//---------------------------------------------------------------------------------------
	Rectangle btnCheckColl = { 772, 509, 287, 105 };
	//Texture Initilization
	//---------------------------------------------------------------------------------------
	Texture2D blankCard = LoadTexture("170pixelBlank.png");
	Texture2D TitleScreen = LoadTexture("TitleScreen.png");
	Texture2D  _Table = LoadTexture("TableTwo.png");
	Texture2D CardBacking = LoadTexture("170CardBacking.png");
	//--------------------------------------------------------------------------------------
	// Main game loop

	//Code something that constructs cards based of the Card class

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
			DisplayBackOfCards(600, 75, 6, CardBacking);
			DisplayBackOfCards(600, 840, 6, blankCard);
			DrawCircleV(GetMousePosition(), 10, WHITE);
			EndDrawing();
			//Look into making ur own textures from the blank pixel && from the text to be atop of it
			// side note, x.pos of text will be blankCard.x/2,  same for Y. 
		}
		else if (_TScreen)
		{
			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(TitleScreen, 0, 0, WHITE);
			DrawCircleV(GetMousePosition(), 10, WHITE);
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
	CloseWindow();// Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	system("pause>0");
	return 0;
}