#include "Display.hpp"
int main()
{
	// Variables
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1920;
	const int screenHeight = 1050; // have to do this to fix the mouse ghosting issue
	InitWindow(screenWidth, screenHeight, "Durak");
	InitAudioDevice();
	SetTargetFPS(120);
	//---------------------------------------------------------------------------------------
	Vector2 mP = { 0.0f, 0.0f };
	Vector2 dMP = { 0.0f, 0.0f };
	bool _TScreen = true;
	bool prePlayScreen = false;
	bool clickedOnCard = false;
	bool hC = false;
	int cardsPlayedThisPass = 0;
	Deck deck;
	Table table;
	MainGame mainGame;
	std::array<Player, 2>players;
	std::vector<std::shared_ptr<Card>>cardsVisible;
	//---------------------------------------------------------------------------------------
	Rectangle btnCheckColl = { 772, 509, 287, 105 };
	//---------------------------------------------------------------------------------------
	Image appIcon = LoadImage("appIcon.png");
	SetWindowIcon(appIcon);
	Sound fxButton = LoadSound("buttonfx.wav");
	Texture2D blankCard = LoadTexture("170pixelBlank.png");
	Texture2D TitleScreen = LoadTexture("TitleScreen.png");
	Texture2D  _Table = LoadTexture("TableCardHole.png");
	Texture2D progTable = LoadTexture("TableWithButton.png");
	Texture2D CardBacking = LoadTexture("170CardBacking.png");

	Texture2D PassButtonHigh = LoadTexture("PassHigh.png");
	Texture2D PassButtonMid = LoadTexture("PassMid.png");
	Texture2D PassButtonLow = LoadTexture("PassLow.png");

	Texture2D EndButtonHigh = LoadTexture("EndHigh.png");
	Texture2D EndButtonMid = LoadTexture("EndMid.png");
	Texture2D EndButtonLow = LoadTexture("EndLow.png");

	//--------------------------------------------------------------------------------------
	// Main game loop

	//Code something that moves the cards when the mouse moves them. The co-ordinates of the cards will be the mouse co-ordinates + the offset of where the mouse clicks the card
	c0::setUpPlayerHandPos(cardsVisible, deck, players);
	c0::setTopCards(deck);
	if (c1::findStartingPlayer(players, deck) == 0) { players[0].setPlyrAtk(true); }
	else { players[1].setPlyrAtk(true); }
	//deck.setUpTwoDeckCards();
	//mainGame.setPlrAtk(c2::findStartingPlayer(players, deck)); This is facing a vector out of error error
	while (!WindowShouldClose())
	{
		mP = GetMousePosition();
		hC = false;
		if (prePlayScreen)
		{
			int round = mainGame.getRound();

			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(progTable, 0, 0, WHITE);
			c2::displayPassButtons(PassButtonLow, PassButtonMid, PassButtonHigh, fxButton, cardsPlayedThisPass);
			c2::displayEndButtons(EndButtonLow, EndButtonMid, EndButtonHigh, fxButton, cardsPlayedThisPass);
			//deck.displayDeck(blankCard, CardBacking);
			c2::cTable(cardsVisible, CardBacking, blankCard);
			deck.displayVisisbleCard(blankCard);
			c2::displayDeckExtraCards(deck, CardBacking, blankCard);			
			DrawCircleV(GetMousePosition(), 10, WHITE);
			//c1::rectangles();
			EndDrawing();
			for (int i = 0; i < cardsVisible.size(); ++i)
			{
				if (cardsVisible[i]->canBeTouched)
				{
					Rectangle card;
					card = { cardsVisible[i]->cardPosition.x, cardsVisible[i]->cardPosition.y, 120, 170 };
					if (!hC)
					{
						if (CheckCollisionPointRec(mP, card) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
						{
							hC = true;
							cardsVisible[i]->cardIsFaceUp = !cardsVisible[i]->cardIsFaceUp; // this function changes the state of the card in the cardsVisible pointer vector
						}
						if (CheckCollisionPointRec(mP, card) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
						{
							hC = true;
							cardsVisible[i]->cardIsHeld = true;
							Vector2 mD = GetMouseDelta();
							cardsVisible[i]->cardPosition.x = (cardsVisible[i]->cardPosition.x + mD.x);
							cardsVisible[i]->cardPosition.y = (cardsVisible[i]->cardPosition.y + mD.y);
						}
						if (!CheckCollisionPointRec(mP, card) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						{
							cardsVisible[i]->cardIsHeld = false;
						}
					}
					if (!cardsVisible[i]->cardIsHeld)
					{
						int overlap = c1::placeHBC(50, cardsVisible[i]);
						if (overlap >= 50)
						{
							auto box = c1::BoxColFinder(cardsVisible[i]);
							cardsVisible[i]->cardPosition = box.first;
							if (overlap == 100)
							{
								if (c1::canCardBePlayed(table, cardsVisible[i]))//players[0])
								{
									cardsVisible[i]->canBeTouched = false;
									c1::moveCardFromPlayerHandToTable(players[1], table, cardsVisible[i], box.second, cardsPlayedThisPass);
								}
								else if (!c1::canCardBePlayed(table, cardsVisible[i]))
								{
									Vector2 resetPos = { box.first.x , (box.first.y + 250.0f) };
									cardsVisible[i]->cardPosition = resetPos;
								}
								//This works as intended
								//Use to shift from hand to tables assuming that the conditions are met
								//Time to code this.
								// Push to table if the conditons are met. Treat the player as players[1]
							}							
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