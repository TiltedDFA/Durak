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
	Deck deck;
	Table table;
	DiscardedCards bPile;
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

	Texture2D AtkHigh = LoadTexture("AtkHigh.png");
	Texture2D AtkLow = LoadTexture("AtkLow.png");
	Texture2D DefHigh = LoadTexture("DefHigh.png");
	Texture2D DefLow = LoadTexture("DefLow.png");
	//--------------------------------------------------------------------------------------
	// Main game loop

	//Code something that moves the cards when the mouse moves them. The co-ordinates of the cards will be the mouse co-ordinates + the offset of where the mouse clicks the card
	c1::setUpPlayerHandPos(cardsVisible, deck, players);
	c1::setTopCards(deck);
	
	if (c1::findStartingPlayer(players, deck) == 0) { players[0].setPlyrAtk(true); mainGame.setPTurn(0); }
	else { players[1].setPlyrAtk(true); mainGame.setPTurn(1); }
	while (!WindowShouldClose())
	{
		mP = GetMousePosition();
		hC = false;
		if (prePlayScreen)
		{
			int round = mainGame.getRound();
			c1::lockCardsInHand(players, mainGame);
			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexture(progTable, 0, 0, WHITE);
			c0::displayPassButtons(players, table, mainGame, PassButtonLow, PassButtonMid, PassButtonHigh, fxButton);
			c0::displayEndButtons(players[1], mainGame, EndButtonLow, EndButtonMid, EndButtonHigh, fxButton, bPile, table, cardsVisible);
			c0::displayPlayerState(AtkHigh, AtkLow, DefHigh, DefLow, players[1].isPlyrAtk());
			//deck.displayDeck(blankCard, CardBacking);
			c0::cTable(cardsVisible, CardBacking, blankCard);
			deck.displayVisisbleCard(blankCard);
			c0::displayDeckExtraCards(deck, CardBacking, blankCard);
			c0::displayWhosTurnItIs(mainGame);
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
					if (!cardsVisible[i]->cardIsHeld && !cardsVisible[i]->inDefTablePile)
					{
						int overlap = c2::placeHBC(50, cardsVisible[i]);
						if (overlap >= 50)
						{
							auto box = c2::BoxColFinder(cardsVisible[i]);
							cardsVisible[i]->cardPosition = box.first;
							if (players[mainGame.getPTurn()].isPlyrAtk())// This checks if it's true
							{
								if (overlap == 100)
								{
									if (c2::canCardBePlayed(table, cardsVisible[i]))//players[0]
									{
										cardsVisible[i]->canBeTouched = false;
										c2::moveCardFromPlayerHandToTable(players[mainGame.getPTurn()], table, cardsVisible[i], box.second);
										mainGame.incramentCardsPlayed();
									}
									else// if (!c1::canCardBePlayed(table, cardsVisible[i]))
									{
										Vector2 resetPos = { box.first.x , (box.first.y + 250.0f) };
										cardsVisible[i]->cardPosition = resetPos;
									}
								}
							}
							else if (!players[mainGame.getPTurn()].isPlyrAtk())
							{
								if (mainGame.getCardsPlayed() > 0 && c2::cardBeatsCard(cardsVisible[i], table.getCardFromTableAtk(box.second), deck))
								{
									cardsVisible[i]->cardPosition = Vector2Add(cardsVisible[i]->cardPosition, { 40,40 });
									cardsVisible[i]->canBeTouched = false;
									c2::moveCardFromPlayerHandToTable(players[mainGame.getPTurn()], table, cardsVisible[i], box.second);
								}
								else
								{
									Vector2 resetPos = { box.first.x , (box.first.y + 250.0f) };
									cardsVisible[i]->cardPosition = resetPos;
								}
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
	UnloadTexture(blankCard);
	UnloadTexture(CardBacking);
	UnloadTexture(TitleScreen);
	UnloadTexture(_Table);
	UnloadTexture(progTable);
	UnloadTexture(PassButtonHigh);
	UnloadTexture(PassButtonMid);
	UnloadTexture(PassButtonLow);
	UnloadTexture(EndButtonHigh);
	UnloadTexture(EndButtonMid);
	UnloadTexture(EndButtonLow);
	UnloadTexture(AtkHigh);
	UnloadTexture(AtkLow);
	UnloadTexture(DefHigh);
	UnloadTexture(DefLow);
	CloseWindow();// Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	system("pause>0");
	return 0;
}