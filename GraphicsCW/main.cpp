/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

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
	InitWindow(screenWidth, screenHeight, "Durak");
	LoadNeededFiles();
	Deck deck;
	//--------------------------------------------------------------------------------------
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		//Doesn't work lol fix it (Issue is likely the LoadNeedeFiles())
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(TitleScreen, 0, 0, WHITE);
		//DisplayBackOfCards(600, 75, 6, CardBacking);
		//DisplayBackOfCards(600, 840, 6, CardBacking);
		//DrawText(TextFormat("Master suit is: %d", ((int)deck.getMasterSuit())), 200, 120, 20, WHITE);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(.Table);
	UnloadTexture(CardBacking);
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	system("pause>0");
	return 0;
}