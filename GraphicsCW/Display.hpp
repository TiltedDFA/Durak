#pragma once
#include "Game.hpp"
namespace c0 {//This is used to display

	extern inline void cTable(std::vector<std::shared_ptr<Card>>cardsVisible, Texture2D& cBack, Texture2D& cBlank);
	
	extern inline void displayPassButtons(std::array<Player, 2>& players, Table& table, MainGame& mg, Texture2D& passLow, Texture2D& passMid, Texture2D& passHigh, Sound& fxButton);
	
	extern inline void displayEndButtons(std::array<Player, 2>& players, MainGame& mg, Texture2D& endLow, Texture2D& endMid, Texture2D& endHigh, Sound& fxButton, Discardediscarded_cards& bPile, Table& table, std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck);
	
	extern inline void displayTakeButtons(Deck& deck, std::vector<std::shared_ptr<Card>>& cardsVisible, std::array<Player, 2>& players, MainGame& mg, Table& table, Texture2D& takeHigh, Texture2D& takeMid, Texture2D& takeLow);
	
	extern inline void displayPlayerState(Texture2D& atkHigh, Texture2D& atkLow, Texture2D& defHigh, Texture2D& defLow, bool atkState);
	
	extern inline void displayWhosTurnItIs(MainGame& mg);
	
	extern inline void displayDeckSizeButtons(Rectangle& thirty, Rectangle& fifty, const bool& thirtySelected, const int& currentMusicSize);
	
	extern inline void displayTextForMusicButtons(const std::string& msg, const int x, const int y);
	
	extern inline void displayMusicButtons(Rectangle& noMusic, Rectangle& jazzMusic, Rectangle& lofiMusic, Rectangle& electroSwingMusic, Music& JazzMusic, Music& LofiMusic, Music& eSwingMusic, const int& selection, const int& deckSize, int& currentMusicNum);

	extern inline void displaySpecialCards(Deck& deck, Texture2D& backOfCard, Texture2D& blankCard);
}
