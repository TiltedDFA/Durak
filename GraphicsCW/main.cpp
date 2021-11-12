#include "Display.hpp"
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
	bool hC = false;
	int amtOfCardsOnScreen = 0;
	Deck deck;
	Table table;
	MainGame mainGame;
	std::array<Player, 2>players;
	std::vector<Card*>cardsVisible;
	//---------------------------------------------------------------------------------------
	Rectangle btnCheckColl = { 772, 509, 287, 105 };
	//---------------------------------------------------------------------------------------
	Image appIcon = LoadImage("appIcon.png");
	SetWindowIcon(appIcon);
	Texture2D blankCard = LoadTexture("170pixelBlank.png");
	Texture2D TitleScreen = LoadTexture("TitleScreen.png");
	Texture2D  _Table = LoadTexture("TableCardHole.png");
	Texture2D progTable = LoadTexture("TableCardInProg.png");
	Texture2D CardBacking = LoadTexture("170CardBacking.png");
	//--------------------------------------------------------------------------------------
	// Main game loop

	//Code something that moves the cards when the mouse moves them. The co-ordinates of the cards will be the mouse co-ordinates + the offset of where the mouse clicks the card
	c3::setPosCard(cardsVisible, players, deck);
	deck.setUpTwoDeckCards();
	//mainGame.setPlrAtk(c2::findStartingPlayer(players, deck)); This is facing a vector out of error error
	while (!WindowShouldClose())
	{
		mP = GetMousePosition();
		hC = false;
		if (prePlayScreen)
		{
			BeginDrawing();			
			ClearBackground(RAYWHITE);
			DrawTexture(progTable, 0, 0, WHITE);
			deck.displayDeck(blankCard, CardBacking);
			c1::cTable(cardsVisible, CardBacking, blankCard, amtOfCardsOnScreen);
			DrawCircleV(GetMousePosition(), 10, WHITE);
			//c1::rectangles();
			EndDrawing();	
				for (int i = 0; i < cardsVisible.size(); ++i)
				{					
					if (cardsVisible[i]->canBeTouched)
					{
						Rectangle card;
						card = { cardsVisible[i]->Pos.x, cardsVisible[i]->Pos.y, 120, 170 };
						Card _card = *cardsVisible.at(i);
						if (!hC)
						{
							if (CheckCollisionPointRec(mP, card) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
							{
								hC = true;
								cardsVisible[i]->faceUp = !cardsVisible[i]->faceUp; // this function changes the state of the card in the cardsVisible pointer vector
							}
							if (CheckCollisionPointRec(mP, card) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
							{
								hC = true;
								cardsVisible[i]->held = true;								
								Vector2 mD = GetMouseDelta();
								cardsVisible[i]->Pos.x = (cardsVisible[i]->Pos.x + mD.x);
								cardsVisible[i]->Pos.y = (cardsVisible[i]->Pos.y + mD.y);
							}
							if (!CheckCollisionPointRec(mP, card) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
							{
								cardsVisible[i]->held = false;
							}
						}
						if (!_card.held)
						{
							
							int overlap = c2::placeHBC(50, _card);
							if (overlap >= 50)
							{
								if (overlap == 100)
								{
									//This works as intended
									//Use to shift from hand to tables assuming that the conditions are met
								}
								Vector2 boxPos = c2::BoxColFinder((*cardsVisible[i]));
								cardsVisible[i]->Pos = boxPos;								
							}							
						}
					}
				}
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
					hC = false;
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