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
	void displayEndButtons(Player& player,MainGame& mg, Texture2D& endLow, Texture2D& endMid, Texture2D& endHigh, Sound& fxButton, DiscardedCards& bPile, Table& table, std::vector<std::shared_ptr<Card>>& cardsVisible)
	{
		// 1733, 936
		int cardsPlayedThisRound = mg.getCardsPlayed();
	

		if (!(cardsPlayedThisRound > 0))// && !player.isPlyrAtk())
		{
			DrawTexture(endLow, 1733, 936, WHITE);
		}
		else
		{
			//if (player.isPlyrAtk())
			//{
				Vector2 mP = GetMousePosition();
				Rectangle buttonHitBox = { 1733, 936, 150, 75 };
					if (CheckCollisionPointRec(mP, buttonHitBox))
					{
						if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
						{
							c2::moveAllTableToBPile(bPile, table, cardsVisible);
							DrawTexture(endMid, 1733, 936, WHITE);
						}
						else
						{
							DrawTexture(endHigh, 1733, 936, WHITE);
						}
						if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { PlaySound(fxButton); }
					}
					else
					{
						DrawTexture(endLow, 1733, 936, WHITE);
					}
			//}
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
}
#endif // !DISPLAY_HPP