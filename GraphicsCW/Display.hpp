#pragma once
#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "GameFunctions.hpp"
namespace c0 //This is used to display
{	
	void cTable(std::vector<std::shared_ptr<Card>>cardsVisible, Texture2D& cBack, Texture2D& cBlank) // (Xpos, Ypos, AmountOfCards, Cardtext)
	{
		for (const auto& i : cardsVisible)
		{
			if (i->cardIsFaceUp)
			{
				DrawTexture(cBlank, static_cast<int>(i->cardPosition.x), static_cast<int>(i->cardPosition.y), WHITE);
				i->displayCardWithValueText(i);
			}
			else if (!i->cardIsFaceUp)
			{
				DrawTexture(cBack, static_cast<int>(i->cardPosition.x), static_cast<int>(i->cardPosition.y), WHITE);
			}

		}
	}
	void displayDeckExtraCards(Deck& deck, Texture2D& backOfCard, Texture2D& frontOfCard)
	{
		auto vCard = deck.getVisibleCard();
		auto topCards = deck.getTopOfDeck();
		//Still need to display visible card
		DrawTexture(backOfCard, static_cast<int>(topCards.first->cardPosition.x), static_cast<int>(topCards.first->cardPosition.y), WHITE);
		DrawTexture(backOfCard, static_cast<int>(topCards.second->cardPosition.x), static_cast<int>(topCards.second->cardPosition.y), WHITE);
	}
	void displayPassButtons(std::array<Player, 2>& players, Table& table, MainGame& mg, Texture2D& passLow, Texture2D& passMid, Texture2D& passHigh, Sound& fxButton)
	{
		// 1520, 936
		//CheckCollisionPointRec
		int cardsPlayedThisRound = mg.getCardsPlayed();		
		if (players[mg.getPTurn()].isPlyrAtk() && cardsPlayedThisRound || !players[mg.getPTurn()].isPlyrAtk() && c2::canPassDef(table))
		{
			Vector2 mP = GetMousePosition();
			Rectangle buttonHitBox = { 1520, 936, 150, 75 };
			if (CheckCollisionPointRec(mP, buttonHitBox))
			{
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				{
					DrawTexture(passMid, 1520, 936, WHITE);
				}
				else
				{
					DrawTexture(passHigh, 1520, 936, WHITE);
				}
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { PlaySound(fxButton); mg.switchPTurn(); }
			}
			else
			{
				DrawTexture(passLow, 1520, 936, WHITE);
			}
		}
		else
		{
			DrawTexture(passLow, 1520, 936, WHITE);
		}
		
	}
	void displayEndButtons(std::array<Player, 2>& players,MainGame& mg, Texture2D& endLow, Texture2D& endMid, Texture2D& endHigh, Sound& fxButton, DiscardedCards& bPile, Table& table, std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck)
	{
		// 1733, 936				
		Vector2 mP = GetMousePosition();
		Rectangle buttonHitBox = { 1733, 936, 150, 75 };
		if (CheckCollisionPointRec(mP, buttonHitBox) && c2::canEndAtk(table))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				c2::moveAllTableToBPile(bPile, table, cardsVisible); //This moves all the cards on the table to the discarded pile 
				DrawTexture(endMid, 1733, 936, WHITE);
				c1::addNeededCardsToPlayerHands(players, cardsVisible, deck);	
				mg.switchPTurn();
				c2::switchPlayerStates(players);
			}
			else
			{
				DrawTexture(endHigh, 1733, 936, WHITE);
			}
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{ 
				PlaySound(fxButton); 
			}
		}
		else
		{
			DrawTexture(endLow, 1733, 936, WHITE);
		}		
	}
	void displayTakeButtons(Deck& deck, std::vector<std::shared_ptr<Card>>& cardsVisible,std::array<Player, 2>& players, MainGame& mg, Table& table, Texture2D& takeHigh, Texture2D& takeMid, Texture2D& takeLow)
	{
		//Either something incorrectly writes to this or the system isn't right since 
		Vector2 mP = GetMousePosition();
		Rectangle buttonHitBox = { 1733, 936, 150, 75 };
		if (CheckCollisionPointRec(mP, buttonHitBox))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT && !c2::canEndAtk(table)))
			{
				c2::moveAllTableToPlayerHand(players[mg.getPTurn()], table);
				c1::addNeededCardsToPlayerHands(players, cardsVisible, deck);
				DrawTexture(takeMid, 1733, 936, WHITE);	
				mg.switchPTurn();
			}
			else
			{
				DrawTexture(takeHigh, 1733, 936, WHITE);
			}
			
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {}
		}
		else
		{
			DrawTexture(takeLow, 1733, 936, WHITE);
		}

	}
	void displayPlayerState(Texture2D& atkHigh, Texture2D& atkLow, Texture2D& defHigh, Texture2D& defLow, bool atkState)
	{
		//Atk pos is: 1658. 42
		//Def pos is: 1507.44
		if (atkState)
		{
			DrawTexture(atkHigh, 1658, 42, WHITE);
			DrawTexture(defLow, 1507, 44, WHITE);
		}
		else
		{
			DrawTexture(atkLow, 1658, 42, WHITE);
			DrawTexture(defHigh, 1507, 44, WHITE);
		}
	}
	void displayWhosTurnItIs(MainGame& mg)
	{
		auto turn = mg.getPTurn();
		if (turn) // turn is either 1 or 0 which represents true or false (kinda)
		{
			DrawRectangle(1658, 102, 100, 20, WHITE);
		}
		else if (!turn)
		{
			DrawRectangle(1507, 102, 100, 20, WHITE);
		}
	}
	void displayDeckSizeButtons(Rectangle& thirty, Rectangle& fifty, const bool& thirtySelected)
	{
		Vector2 mP = GetMousePosition();
		std::string threeSix = "36";
		std::string fiveTwo = "52";
		if (CheckCollisionPointRec(mP, thirty))
		{
			DrawRectangleRec(thirty, (thirtySelected) ? ORANGE : SKYBLUE);// The thirty selected bool is used to see find what the current deckSize is
			DrawRectangleRec(fifty, (thirtySelected) ? BLUE : RED);
			DrawText(threeSix.c_str(), static_cast<int>(thirty.x + (thirty.width / 2) - 35), static_cast<int>(thirty.y + (thirty.height / 2) - 25), 60, WHITE);
			DrawText(fiveTwo.c_str(), static_cast<int>(fifty.x + (fifty.width / 2) - 35), static_cast<int>(fifty.y + (fifty.height / 2) - 25), 60, WHITE);
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				c3::setDeckSize(36);
			}
		}
		else if (CheckCollisionPointRec(mP, fifty))
		{			
			
			DrawRectangleRec(fifty, (thirtySelected) ? SKYBLUE : ORANGE);
			DrawRectangleRec(thirty, (thirtySelected) ? RED : BLUE);
			DrawText(threeSix.c_str(), static_cast<int>(thirty.x + (thirty.width / 2) - 35), static_cast<int>(thirty.y + (thirty.height / 2) - 25), 60, WHITE);
			DrawText(fiveTwo.c_str(), static_cast<int>(fifty.x + (fifty.width / 2) - 35), static_cast<int>(fifty.y + (fifty.height / 2) - 25), 60, WHITE);
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				c3::setDeckSize(52);
			}
		}
		else
		{
			DrawRectangleRec(thirty, (thirtySelected) ? RED : BLUE);
			DrawRectangleRec(fifty, (thirtySelected) ? BLUE : RED);
			DrawText(threeSix.c_str(), static_cast<int>(thirty.x + (thirty.width / 2)-35), static_cast<int>(thirty.y + (thirty.height / 2)-25), 60, WHITE);
			DrawText(fiveTwo.c_str(), static_cast<int>(fifty.x + (fifty.width / 2)-35), static_cast<int>(fifty.y + (fifty.height / 2)-25), 60, WHITE);
		}
	}
}
#endif // !DISPLAY_HPP