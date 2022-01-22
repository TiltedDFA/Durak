#pragma once
#ifndef GAMEFUNCTIONS_HPP
#define GAMEFUNCTIONS_HPP
#include "SetupFunctions.hpp"

namespace c2 {// This namespace is for game functions
	
	inline const int  collision_percent_finder(int percentCertanty, std::shared_ptr<Card> card) {
	
		std::array<Vector2, 6>pos{};
		
		pos[0] = { 543.0, 457.0 };
		
		pos[1] = { 688.0, 457.0 };
		
		pos[2] = { 840.0, 457.0 };
		
		pos[3] = { 990.0, 457.0 };
		
		pos[4] = { 1143.0,457.0 };
		
		pos[5] = { 1300.0,457.0 };
		
		Rectangle rCard = { card->card_position.x, card->card_position.y, 120, 170 };
		
		for (int i = 0; i < 6; ++i) {
	
			Rectangle placeHB = { pos[i].x, pos[i].y, 120, 170 };
			
			if (CheckCollisionRecs(rCard, placeHB)) {				
		
				auto oSetArea = (placeHB.width - sqrt((card->card_position.x - placeHB.x) * (card->card_position.x - placeHB.x))) * (placeHB.height - sqrt((card->card_position.y - placeHB.y) * (card->card_position.y - placeHB.y)));
				
				auto percentOverlap = oSetArea / (placeHB.width * placeHB.height) * 100;
				
				if (static_cast<int>(percentOverlap > percentCertanty)) {
					
					return static_cast<int>(percentOverlap);
				}
			}
		}
		return 0;
	}

	inline bool can_attacker_attack(Table& table, std::shared_ptr<Card> card) {
		
		if (!card->is_card_face_up) 
			return false; 

		int l = 0;

		const std::array<std::array<std::shared_ptr<Card>, 2>, 6>cardsOnTable = table.getEntireTable();		
				
		for (const auto& i : cardsOnTable) 
			for (int j = 0; j < 2; ++j)
				if (i[j] != nullptr) { ++l; if (encrypt_data(i[j]->get_card_value()) == encrypt_data(card->get_card_value())) { return true; } }		

		if (!l)
			return true;

		return false;
	}	
	
	inline bool attacking_card_beats_card(const std::shared_ptr<Card>& card_one, const std::shared_ptr<Card>& card_two) {

		if (card_two == nullptr)
			return false;

		if (card_one != nullptr && card_two == nullptr || static_cast<card_suit>(encrypt_data(card_one->get_card_suit())) == Deck::master_suit &&
			static_cast<card_suit>(encrypt_data(card_two->get_card_suit())) != Deck::master_suit) // This code assumes that the only cards that will be passed to the function will be from the table
			return true;

		if (encrypt_data(card_one->get_card_suit()) == encrypt_data(card_two->get_card_suit()) && encrypt_data(card_one->get_card_value()) > encrypt_data(card_two->get_card_value()))
			return true; 

		return false;
	}
	
	inline std::pair<Vector2, int> find_colliding_placement(const std::shared_ptr<Card>& card) {

		std::array<Vector2, 6>pos{};

		pos[0] = { 543.0, 457.0 };

		pos[1] = { 688.0, 457.0 };

		pos[2] = { 840.0, 457.0 };

		pos[3] = { 990.0, 457.0 };

		pos[4] = { 1143.0,457.0 };

		pos[5] = { 1300.0,457.0 };

		const Rectangle rCard = { card->card_position.x, card->card_position.y, 120, 170 };

		for (int i = 0; i < 6; ++i) {
	
			const Rectangle box = { pos[i].x, pos[i].y, 120, 170 };
			
			if (CheckCollisionRecs(rCard, box))  
				return { pos[i], i }; 
		}

		return { { 0,0 }, 7 };
	}
	
	inline void hand_to_table(Player& player, Table& table, std::shared_ptr<Card> card, const int cardPile) {

		std::vector<std::shared_ptr<Card>> player_hand = player.getEntireHand();

		const auto posInHand = std::find(player_hand.begin(), player_hand.end(), card);

		if (posInHand != player_hand.end()) {
	
			if (player.isPlyrAtk()) { table.addCardToTableAtk(std::move(*posInHand), cardPile); player_hand.erase(posInHand); }

			else { table.addCardToTableDef(std::move(*posInHand), cardPile); player_hand.erase(posInHand); card->inDefTablePile = true; }

			player.setEntireHand(player_hand);
		}

	}
	
	inline void discard_table(Discardediscarded_cards& bPile, Table& table, std::vector<std::shared_ptr<Card>>& cardsVisible) {
		
		std::array<std::array<std::shared_ptr<Card>, 2>, 6>cardsOnTable = table.getEntireTable();
		
		for (int i = 0; i < 6; ++i) {
		
			for (int j = 0; j < 2; ++j) {				

				if (cardsOnTable[i][j] != nullptr) {
					
					auto posInCV = std::find(cardsVisible.begin(), cardsVisible.end(), cardsOnTable[i][j]);
					
					if (posInCV != cardsVisible.end()) { cardsVisible.erase(posInCV); }
					
					bPile.addToPile(std::move(cardsOnTable[i][j]));
				}
			}
		}
		table.setEntireTable(cardsOnTable);
	}
	
	inline bool defend_can_pass(Table& table) {

		const std::array<std::array<std::shared_ptr<Card>, 2>, 6> cardsOnTable = table.getEntireTable();

		std::pair<int, int> cardsPlayed;

		for (auto& i : cardsOnTable) {
	
			if (i[0] != nullptr) { ++cardsPlayed.first; }
	
			if (i[1] != nullptr) { ++cardsPlayed.second; }
		}

		if (!cardsPlayed.first)  
			return false; 
	
		if (cardsPlayed.first == cardsPlayed.second) 
			return true; 
		
		return false;
	}
	
	inline void switch_player_state(std::array<Player, 2>& players) {
	
		players[0].setPlyrAtk(!players[0].isPlyrAtk()); players[1].setPlyrAtk(!players[1].isPlyrAtk()); 
	}
	
	inline bool can_end_attack(Table& table) {
	
		const std::array<std::array<std::shared_ptr<Card>, 2>, 6> cardsOnTable = table.getEntireTable();
		
		int completedValues = 0;
		
		for (const auto& i : cardsOnTable) {
	
			if (i[0] != nullptr && i[1] != nullptr) { ++completedValues; }
		}
	
		if (completedValues)  
			return true; 
		
		return false;
	}
	
	inline void table_to_hand(Player& player, Table& table) {
	
		std::array<std::array<std::shared_ptr<Card>, 2>, 6> cTable = table.getEntireTable();
		
		Vector2 takenCardPos = { 0, 150 };		
		
		for (int i = 0; i < 6; ++i) {
		
			for (int j = 0; j < 2; ++j) {
		
				if (cTable[i][j] != nullptr) {
				
					takenCardPos.x = (75.0f * i);
					
					cTable[i][j]->card_position = takenCardPos;
					
					cTable[i][j]->canBeTouched = true;
					
					player.addToplayer_hand(std::move(cTable[i][j]));
				}				
			}
		}

		table.setEntireTable(cTable);
	}
	
	inline int check_for_winner(Deck& deck, std::array<Player, 2>& players, Table& table) {		

		for (int i = 0; i < 2; ++i) {
		
			if (deck.getDeckSize() == 0 && players[i].get_hand_size() == 0 && table.get_amount_of_card_in_table() == 0) {
				return i;
			}
		}
		return 2;
	}	
	
	inline void play_music(const int music_number, Music& JazzMusic,Music& LofiMusic, Music& eSwingMusic) {
	
		switch (music_number) {
	
		case 2:
		
			PlayMusicStream(JazzMusic);
			
			break;
	
		case 3:
		
			PlayMusicStream(LofiMusic);
		
			break;
		
		case 4:
	
			PlayMusicStream(eSwingMusic);
			
			break;
		
		default:
	
			break;
		}		
	}
	
	inline void continuePlayingMusic(const int music_number, Music& JazzMusic, Music& LofiMusic, Music& eSwingMusic) {

		switch (music_number) {
	
		case 2:
		
			UpdateMusicStream(JazzMusic);
		
			break;
		
		case 3:
	
			UpdateMusicStream(LofiMusic);
		
			break;
		
		case 4:
	
			UpdateMusicStream(eSwingMusic);
		
			break;
		
		default:
	
			break;
		}
	}
	
	inline int findEmptyTablePile(Table& table) {
	
		std::array<std::array<std::shared_ptr<Card>, 2>, 6> _t = table.getEntireTable();
		
		int l = 0;
		
		for (const auto& i : _t) {
		
			if (i[0] == nullptr)
			{
				++l;
				break;				
			}			
		}
		return l;
	}
	
	inline void end_attack(Deck& deck, MainGame& mg, Discardediscarded_cards& bPile,Table& table, std::vector<std::shared_ptr<Card>>& cardsVisible, std::array<Player, 2>& players) {

		discard_table(bPile, table, cardsVisible);

		c1::remove_table_from_visible_vector(table, cardsVisible);

		c1::add_need_cards_to_players(players, cardsVisible, deck);

		mg.switchPTurn();

		switch_player_state(players);
	}

	inline void takeDefender(std::array<Player, 2>&players, std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck, Table& table, MainGame& mg) {

		table_to_hand(players[mg.getPTurn()], table);

		c1::add_need_cards_to_players(players, cardsVisible, deck);

		mg.switchPTurn();
	}
}

//namespace c4 { //This will be my finite state machine AI
/*
constexpr auto ZeroValue = 0.0f;// These are all values that are declared here so they can be tweaked in order finetune the AI

constexpr auto MSValue = 20.0f;

constexpr auto sameSuitConst = 1.0f;

    inline const double findDefendingEval(std::shared_ptr<Card> cardUsedToDefend, std::shared_ptr<Card> cardToDefend, Deck& deck) {
		
		const card_suit ms = Deck::master_suit;
		
		if (cardUsedToDefend->get_card_suit() != cardToDefend->get_card_suit() && cardUsedToDefend->get_card_suit() != ms) {  //Different suits and non ms 
		
			return ZeroValue;
		}
		if (cardUsedToDefend->get_card_suit() == cardToDefend->get_card_suit() && cardUsedToDefend->get_card_value() < cardToDefend->get_card_value()) { //same get_card_suit() lower get_card_value()
		
			return ZeroValue;
		}
		if (cardUsedToDefend->get_card_suit() == ms && cardToDefend->get_card_suit() != ms) {//Master suit vs non ms 
		
			return (static_cast<float>(cardUsedToDefend->get_card_value()) + MSValue);
		}
		if (cardUsedToDefend->get_card_suit() == cardToDefend->get_card_suit() && cardUsedToDefend->get_card_value() > cardToDefend->get_card_value()) {//Same get_card_suit() higher val
		
			return (static_cast<float>(cardUsedToDefend->get_card_value()) - static_cast<float>(cardToDefend->get_card_value()));
		}
		return 9999999999999999999;
	}	

	inline auto returnBestDefplayer_handEval(const std::shared_ptr<Card>& card, Player& player, Deck& deck) {
	
		std::vector<std::pair<double, std::vector<std::shared_ptr<Card>>::iterator>>evaluations;
		
		auto hand = player.getEntireHand();
		
		for (int i = 0; i < static_cast<int>(player.get_hand_size()); ++i) {
		
			std::pair<double, std::vector<std::shared_ptr<Card>>::iterator>evalInfo;
			
			evalInfo.first = findDefendingEval(hand[i], card, deck);
			
			evalInfo.second = (hand.begin() + i);
			
			evaluations.push_back(evalInfo);
		}
		std::sort(evaluations.begin(), evaluations.end(), [](const std::pair<double, std::vector<std::shared_ptr<Card>>::iterator>& a, const std::pair<double, std::vector<std::shared_ptr<Card>>::iterator>& b)->bool { return (a.first < b.first); });
		
		for (int i = 0; i < static_cast<int>(evaluations.size()); ++i) {
		
			if (static_cast<int>(evaluations[i].first)) {
		
				return evaluations[(i + 1)].second;
			}
		}
		return hand.end();
	}
	
	inline auto defendACardBot(Table& table,Player& bot, Deck& deck, MainGame& mg) {
	
		int j = 0; // Counts the index of the table
		
		int k = 0; // checks how many times it's been defended
		
		std::array<std::array<std::shared_ptr<Card>, 2>, 6>_t = table.getEntireTable();		
		
		std::array<Vector2, 6>pos{};
		
		pos[0] = { 543.0, 457.0 };
		
		pos[1] = { 688.0, 457.0 };
		
		pos[2] = { 840.0, 457.0 };
		
		pos[3] = { 990.0, 457.0 };
		
		pos[4] = { 1143.0,457.0 };
		
		pos[5] = { 1300.0,457.0 };
		
		for(auto& i : _t) {
	
			if (i[0] != nullptr && i[1] == nullptr) {
	
				auto returnVal = returnBestDefplayer_handEval(i[0],bot,deck);
				
				if (!(returnVal == bot.getEntireHand().end())) {
				
					i[0]->card_position = pos[j];
					
					//was not thinking properly here, why would i check if the table is empty when i need not do so for the defending function

					c2::hand_to_table(bot, table, std::move(i[0]), j);
										
					mg.incramentCardsPlayed();
					
					++k;
				}
				break;
			}
			++j;
		}
	}
	
	auto attack(Table&table, std::array<Player, 2>&players, Deck& deck, MainGame& mg, Discardediscarded_cards& bPile, std::vector<std::shared_ptr<Card>>&cardsVisible) {
	
		auto hand = players[0].getEntireHand();
		
		auto mS = Deck::master_suit; //The master suit
		
		std::sort(hand.begin(), hand.end(), [](std::shared_ptr<Card>a, std::shared_ptr<Card>b)->bool { return (a->get_card_value() < b->get_card_value());});
		
		for (int i = 0; i < players[0].get_hand_size(); ++i) {
	
			if (hand[i]->get_card_suit() != mS &&  c2::can_attacker_attack(table, hand[i])) {

				auto x = c2::findEmptyTablePile(table);

				if (!x) {

					c2::end_attack(deck, mg, bPile, table, cardsVisible, players);
				}
				else {

					c2::hand_to_table(players[0], table, hand[i], x);
				}
			}
			else if (c2::can_attacker_attack(table, hand[i])) {

				auto x = c2::findEmptyTablePile(table);

				if (!x) {

					c2::end_attack(deck, mg, bPile, table, cardsVisible, players);
				}
				else {

					c2::hand_to_table(players[0], table, hand[i], x);
				}
			}			
			else {

				c2::end_attack(deck, mg, bPile, table, cardsVisible, players);
			}
		}		
	}
	/*
		for (const auto& i : _t) {
			if (i[0] != nullptr) {
				valOnTable.push_back(i[0]->Value);
				if (i[1] != nullptr) {
					valOnTable.push_back(i[1]->Value);
				}
			}
		}
		std::sort(valOnTable.begin(), valOnTable.end());

		for (const auto& l : valOnTable) {
			for (const auto& i : hand) {
				if (i->Value == l)
				{
					break;
					break;
				}
			}
		}
		*/
		
	/*
	const double findDefendingEval(std::shared_ptr<Card> cardOne, std::shared_ptr<Card> cardTwo, Deck& deck)
	{
		const card_suit ms = deck.getmaster_suit();
		if (cardOne->Suit != cardTwo->Suit && cardOne->Suit != ms) //Different suits and non ms 
		{
			return ZeroValue;
		}
		else if (cardOne->Suit == cardTwo->Suit && cardOne->Value < cardTwo->Value) //same suit lower value
		{
			return ZeroValue;
		}
		else if (cardOne->Suit == ms && cardTwo->Suit != ms)//Master suit vs non ms 
		{
			return (1 / (MSValue * static_cast<int>(cardOne->Value)));
		}
		else if (cardOne->Suit == cardTwo->Suit && cardOne->Value > cardTwo->Value) //Same suit higher val
		{
			return (1/(sameSuitConst*((static_cast<int>(cardOne->Value)
				- static_cast<int>(cardTwo->Value)))));
		}
	}
	*/
	/*
	std::vector<std::shared_ptr<Card>>::iterator evaluateplayer_hand(Player& bot, Table& table,Deck& deck)
	{
		auto handSize = bot.get_hand_size();
		if (bot.isPlyrAtk())
		{

		}
		else if (!bot.isPlyrAtk())
		{
			std::vector<double>cardEvals;
			for (int i = 0; i < handSize; ++i)
			{
			//	cardEvals.push_back(findDefendingEval());
			}
		}
		//return std::vector<std::shared_ptr<Card>::;
	}
	*/
//}

namespace c4 {
	inline bool trump_suit_checker(std::shared_ptr<Card>&Card) {

		return (static_cast<card_suit>(encrypt_data(Card->get_card_suit())) == Deck::master_suit) ? true : false;
	}
	
}
#endif // !GAMEFUNCTIONS_HPP
