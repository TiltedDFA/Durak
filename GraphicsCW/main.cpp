#include "Display.hpp"
int main()
{
	//--------------------------------------------------------------------------------------
	constexpr int screenWidth =  1920;// This declares screenwidth
	constexpr int screenHeight = 1050; // This declares the screenheight
	InitWindow(screenWidth, screenHeight, "Durak");//This initlizes the screen with the width and size 
	InitAudioDevice();// This initilizes the audio device
	SetTargetFPS(120);//This sets the target framerate
	//---------------------------------------------------------------------------------------
	Vector2 mP = {0.0f,0.0f}; //This is to store the mouse position 
	Vector2 dMP = { 0.0f, 0.0f }; //This is to store the delta of the position
	bool _TScreen = true; // This is to help the store which screen to display
	bool prePlayScreen = false; //This is also to help with the screen display system
	bool hC = false; //This variable is used primarily in the system that controlls the amnt of cards you pick up 	
	bool winScreen = false; //This is also for the system 
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

	Texture2D TakeButtonHigh = LoadTexture("TakeHigh.png");
	Texture2D TakeButtonMid = LoadTexture("TakeMid.png");
	Texture2D TakeButtonLow = LoadTexture("TakeLow.png");

	Texture2D AtkHigh = LoadTexture("AtkHigh.png");
	Texture2D AtkLow = LoadTexture("AtkLow.png");
	Texture2D DefHigh = LoadTexture("DefHigh.png");
	Texture2D DefLow = LoadTexture("DefLow.png");
	srand(time(NULL));
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
			if (players[mainGame.getPTurn()].isPlyrAtk()) { c0::displayEndButtons(players, mainGame, EndButtonLow, EndButtonMid, EndButtonHigh, fxButton, bPile, table, cardsVisible, deck); }
			else { c0::displayTakeButtons(deck, cardsVisible, players, mainGame, table, TakeButtonHigh, TakeButtonMid, TakeButtonLow); }			
			c0::displayPlayerState(AtkHigh, AtkLow, DefHigh, DefLow, players[1].isPlyrAtk());
			c0::cTable(cardsVisible, CardBacking, blankCard);
			deck.displayVisisbleCard(blankCard);
			c0::displayDeckExtraCards(deck, CardBacking, blankCard);
			c0::displayWhosTurnItIs(mainGame);
			DrawCircleV(GetMousePosition(), 10, WHITE);
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
								if (c2::cardBeatsCard(cardsVisible[i], table.getCardFromTableAtk(box.second), deck))
								{									
									cardsVisible[i]->cardPosition = Vector2Add(cardsVisible[i]->cardPosition, { 40,40 });
									cardsVisible[i]->canBeTouched = false;
									c2::moveCardFromPlayerHandToTable(players[mainGame.getPTurn()], table, cardsVisible[i], box.second);
									c1::bringCardOneToTop(cardsVisible[i], table.getCardFromTableAtk(box.second), cardsVisible);
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
		//---------------------------------------------------------------------------------
		else if (winScreen)
		{

		}
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
	UnloadTexture(TakeButtonHigh);
	UnloadTexture(TakeButtonMid);
	UnloadTexture(TakeButtonLow);
	CloseWindow();// Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	system("pause>0");
	return 0;
}