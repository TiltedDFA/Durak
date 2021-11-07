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
	std::vector<Card*>cardsVisible;
	//---------------------------------------------------------------------------------------
	Rectangle btnCheckColl = { 772, 509, 287, 105 };
	//---------------------------------------------------------------------------------------
	Image appIcon = LoadImage("appIcon.png");
	SetWindowIcon(appIcon);
	Texture2D blankCard = LoadTexture("170pixelBlank.png");
	Texture2D TitleScreen = LoadTexture("TitleScreen.png");
	Texture2D  _Table = LoadTexture("TableCardHole.png");
	Texture2D CardBacking = LoadTexture("170CardBacking.png");
	//--------------------------------------------------------------------------------------
	// Main game loop

	//Code something that moves the cards when the mouse moves them. The co-ordinates of the cards will be the mouse co-ordinates + the offset of where the mouse clicks the card
	c3::setPosCard(cardsVisible, table, deck);
	while (!WindowShouldClose())
	{
		mP = GetMousePosition();
		bool hC = false;
		if (prePlayScreen)
		{
			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(_Table, 0, 0, WHITE);
			c1::cTable(table, CardBacking, blankCard, amtOfCardsOnScreen);
			DrawCircleV(GetMousePosition(), 10, WHITE);
			//c1::rectangles();
			EndDrawing();
			
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{

				for (int i = 0; i < 12; ++i)
				{

					Rectangle card;
					Card _card;
					Card* temp = &_card;
					if (i <= 5)
					{
						card = { table.getCardFromTableAtk(i).xPos, table.getCardFromTableAtk(i).yPos, 120, 170 };
						_card = table.getCardFromTableAtk(i);
					}
					else
					{
						card = { table.getCardFromTableDef((i - 6)).xPos, table.getCardFromTableDef((i - 6)).yPos, 120, 170 };
						_card = table.getCardFromTableDef((i - 6));
					}

					if (hC)
					{

					}
					else if (!hC)
					{
						if (CheckCollisionPointRec(mP, card) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
						{			
							hC = true;
							if (i <= 5)
							{
								table.flipCardAtk(i, ((_card.faceUp) ? false : true)); // this function inverse whether they're face up or down
							}
							else if (i >= 6)
							{
								table.flipCardDef((i - 6), ((_card.faceUp) ? false : true));
							}
							_card.faceUp = (_card.faceUp) ? false : true; // this function inverse whether they're face up or down
						}
						if (CheckCollisionPointRec(mP, card) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
						{				
							hC = true;
							if (i <= 5)
							{
								table.flipHoldStateAtk(i, true);
								Vector2 currentPos = table.getCardPosAtk(i);
								table.setCardPosAtk(i, Vector2Add(currentPos, GetMouseDelta()));
							}
							else if (i >= 6)
							{
								table.flipHoldStateDef((i - 6), true);
								Vector2 currentPos = table.getCardPosDef((i - 6));
								table.setCardPosDef((i - 6), Vector2Add(currentPos, GetMouseDelta()));
							}

						}
						if (!CheckCollisionPointRec(mP, card))
						{
							if (i <= 5)
							{
								table.flipHoldStateAtk(i, false);
							}
							else if (i >= 6)
							{
								
								table.flipHoldStateDef((i - 6), false);								
							}							
						}
						if (!_card.held)
						{
							if (c2::placeHBC(50, _card))
							{
								Vector2 boxPos = c2::BoxColFinder(_card);
								if (i <= 5)
								{
									table.setCardPosAtk(i, boxPos);
								}
								else if (i >= 6)
								{
									table.setCardPosDef((i - 6), boxPos);
								}
							}
						}
					}
				}
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					hC = false;
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