#pragma once
#ifndef SETUPFUNCTIONS_HPP
#define SETUPFUNCTIONS_HPP
#include "Class.hpp"
namespace c1 {// Used to setup or maintain
			
	inline void addiscarded_cardsToVisibleVec(std::vector<std::shared_ptr<Card>>& cardsVisible, std::shared_ptr<Card> card) {
		
		cardsVisible.push_back(card);
	}
	
	inline void removeCardFromVisibleVect(std::vector<std::shared_ptr<Card>>& cardsVisible, std::shared_ptr<Card> card) {

		assert(cardsVisible.size() > 0);

		auto positionOfCardToRemove = std::find(cardsVisible.begin(), cardsVisible.end(), card);

		if (positionOfCardToRemove != cardsVisible.end()) { cardsVisible.erase(positionOfCardToRemove); }
	}

	inline void init_player_hands(std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck, std::array<Player, 2>& players) {

		float x = 600;
		
		float y = 75;
		
		for (int i = 0; i < 6; ++i)	{

			std::shared_ptr<Card> card = deck.dealCard();

			//card->canBeTouched = false; Temp disabled until ai is made

			card->is_card_face_up = false;

			card->card_position = { (x + 125 * i),y };

			players[0].addToplayer_hand(card);

			cardsVisible.push_back(card);
		}
	
		y = 840;
		
		for (int i = 0; i < 6; ++i)	{

			std::shared_ptr<Card> card = deck.dealCard();

			card->card_position = { (x + 125 * i),y };

			players[1].addToplayer_hand(card);

			cardsVisible.push_back(card);
		}		

		deck.setPosLastCard({ 376, 503 });	
	}
	
	inline auto findStartingPlayer(std::array<Player, 2> players, Deck& deck)
	{
		
		card_value lowestVal[2] = { card_value::ACE, card_value::ACE };
		
		for (int i = 0; i < 2; ++i) {
	
			const auto hSize = players[i].get_hand_size();
			
			for (int j = 0; j < hSize; ++j) {
	
				if (players[i].from_hand_by_index(j)->Suit == Deck::master_suit && players[i].from_hand_by_index(j)->Value < lowestVal[i]) {
		
					lowestVal[i] = players[i].from_hand_by_index(j)->Value;
				}
			}
		}
		if (lowestVal[0] == card_value::ACE && lowestVal[1] == card_value::ACE){ // This is to randomise the starting player if neither has a master suit
		
			return rand() % 2 + 1;
		}
		if (lowestVal[0] > lowestVal[1]){
		
			return 1;
		}
		else { return 0; }
	}
	
	inline void lockCardsInHand(std::array<Player, 2>players, MainGame mg) {
	
		auto pTurn = mg.getPTurn();
		
		for (int i = 0; i < players[pTurn].get_hand_size(); ++i) {
		
			auto card = players[pTurn].from_hand_by_index(i);
			
			card->canBeTouched = true;
			
			players[pTurn].set_hand_by_index(card, i);
		}
		
		auto otherPlayer = (pTurn + 1) % 2;
	
		for (int i = 0; i < players[otherPlayer].get_hand_size(); ++i) {
		
			auto card = players[otherPlayer].from_hand_by_index(i);
	
			card->canBeTouched = false;
	
			players[otherPlayer].set_hand_by_index(card, i);
		}
	}
	
	inline void bringCardOneToTop(std::shared_ptr<Card> cardOne, std::shared_ptr<Card> cardTwo, std::vector<std::shared_ptr<Card>>& cardsVisible) {

		assert(cardsVisible.size() > 1);
	
		auto cOnePos = std::find(cardsVisible.begin(), cardsVisible.end(), cardOne);
	
		auto cTwoPos = std::find(cardsVisible.begin(), cardsVisible.end(), cardTwo);
	
		if (cOnePos < cTwoPos) { std::iter_swap(cOnePos, cTwoPos); }		
	}	
	
	inline void remove_table_from_visible_vector(Table& table, std::vector<std::shared_ptr<Card>>& cardsVisible) {
	
		assert(cardsVisible.size() >= table.get_amount_of_card_in_table());

		const std::array<std::array<std::shared_ptr<Card>, 2>, 6> _Table = table.getEntireTable();
		
		for (const auto& i : _Table) {
		
			for (int j = 0; j < 2; ++j)	{
			
				if (i[j] != nullptr) {

					auto posInCardsVisible = std::find(cardsVisible.begin(), cardsVisible.end(), i[j]);

					if (posInCardsVisible != cardsVisible.end()) 
						cardsVisible.erase(posInCardsVisible);					
				}
			}
		}
	}
			
	inline bool deck_has_enough_cards_left(Deck& deck, const int numOfCardsNeeded) {
		
		assert(deck.getDeckSize() > 0, numOfCardsNeeded > -1);

		int deckSize = deck.getDeckSize();
	
		if ((deckSize - numOfCardsNeeded) >= 0) 
			return true; 
	
		return false;
	}
	
	inline void add_need_cards_to_players(std::array<Player, 2>&players, std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck) {		
	
		for (int i = 0; i < 2; ++i) {
		
			const auto cardsNeeded = (6 - players[i].get_hand_size());
			
			if (deck.getDeckSize()) { // code below will not run if deckSize == 0;
			
				if (deck_has_enough_cards_left(deck, cardsNeeded) && static_cast<int>(players[i].get_hand_size()) < 6) {
				
					for (auto j = 0; j < cardsNeeded; ++j) {
					
						std::shared_ptr<Card>card = deck.dealCard();
						
						card->card_position.y = (i) ? 850.0f : 0.0f;
						
						card->card_position.x = static_cast<float>(120 * j);
						
						players[i].addToplayer_hand(card);
						
						cardsVisible.push_back(card);
					}
				}
			}
		}
	}	
}
namespace c3  {// C3 will be for reading and writing to files (for settings)

	inline void setDeckSize(const int deckSize, const int currentMusicVal) {
	
		std::ofstream save_file(fileName, std::ios::out); // This creates the file		
		if (save_file) {
	
			switch (deckSize) {
			
			case 36:
			
				save_file << "36";
				
				break;
			
			case 52:
		
				save_file << "52";
				
				break;
		
			default:
		
				save_file << "0";
				
				break;
			}

			switch (currentMusicVal) {
		
			case 1:
			
				save_file << "\n1";
				
				break;
		
			case 2:
	
				save_file << "\n2";
			
				break;
		
			case 3:
		
				save_file << "\n3";
				
				break;
		
			case 4:
		
				save_file << "\n4";
			
				break;
			
			default:
		
				throw std::runtime_error("unexpected musical Value input");
			
				break;
			}
			
			save_file.close();
		}
	}		
	
	inline const int getDeckSize() {
		
		std::ifstream save_file(fileName, std::ios::in);
	
		if (!save_file)	{
	
			setDeckSize(36, 1);
	
			return 36;
		}
	
		std::string size;
		
		save_file.seekg(std::ios::beg);
		
		std::getline(save_file, size);
		
		if (size == "36")
			return 36;
	
		else if (size == "52")
			return 52;
		
		else return 0;
	}
	
	inline void setMusicalNumber(const int num, const int currentDeckSize) {
	
		std::ofstream save_file(fileName, std::ios::out);
		
		if (save_file) {
		
			save_file << currentDeckSize;
		
			switch (num) {
		
			case 1:
			
				save_file << "\n1";
				
				break;
		
			case 2:
				
				save_file << "\n2";
	
				break;

			case 3:
			
				save_file << "\n3";
			
				break;
	
			case 4:

				save_file << "\n4";
	
				break;
		
			default:
		
				throw std::runtime_error("Unexpected input Value experianced");
		
				break;
			}
		}
	}	
	
	inline const int getMusicNumber() {
		
		std::ifstream save_file(fileName, std::ios::in);
	
		if (!save_file)	{
		
			setDeckSize(36, 1);
	
			setMusicalNumber(1, 36);
	
			return 1;
		}
		
		std::string num;
	
		std::getline(save_file, num);

		std::getline(save_file, num);

		if (num == "1")
			return 1;

		else if (num == "2")
			return 2;

		else if (num == "3")
			return 3;

		else if (num == "4")
			return 4;
		
		else
			throw std::runtime_error("Unexpected Value read");
	}
} 
#endif // !SETUPFUNCTIONS_HPP
