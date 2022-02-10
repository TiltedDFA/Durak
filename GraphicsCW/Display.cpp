#include "Display.hpp"
namespace c0 {//This is used to display

	void cTable(std::vector<std::shared_ptr<Card>>cardsVisible, Texture2D& cBack, Texture2D& cBlank) {

		for (const auto& i : cardsVisible) {

			if (i->is_card_face_up) {

				DrawTexture(cBlank, static_cast<int>(i->card_position.x), static_cast<int>(i->card_position.y), WHITE);

				i->displayCardWithValueText(i);
			}
			else if (!i->is_card_face_up) {

				DrawTexture(cBack, static_cast<int>(i->card_position.x), static_cast<int>(i->card_position.y), WHITE);
			}
		}
	}

	void displayPassButtons(std::array<Player, 2>& players, Table& table, MainGame& mg, Texture2D& passLow, Texture2D& passMid, Texture2D& passHigh, Sound& fxButton) {
		// 1520, 936
		//CheckCollisionPointRec
		const int cardsPlayedThisRound = mg.getCardsPlayed();

		assert(cardsPlayedThisRound > -1);

		if (players[mg.getPTurn()].isPlyrAtk() && cardsPlayedThisRound || !players[mg.getPTurn()].isPlyrAtk() && c2::defend_can_pass(table)) {

			Vector2 mP = GetMousePosition();

			Rectangle buttonHitBox = { 1520, 936, 150, 75 };

			if (CheckCollisionPointRec(mP, buttonHitBox)) {

				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

					DrawTexture(passMid, 1520, 936, WHITE);
				}
				else {

					DrawTexture(passHigh, 1520, 936, WHITE);
				}

				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					PlaySound(fxButton); mg.switchPTurn();
				}
			}
			else {

				DrawTexture(passLow, 1520, 936, WHITE);
			}
		}
		else {

			DrawTexture(passLow, 1520, 936, WHITE);
		}

	}

	void displayEndButtons(std::array<Player, 2>& players, MainGame& mg, Texture2D& endLow, Texture2D& endMid, Texture2D& endHigh, Sound& fxButton, Discardediscarded_cards& bPile, Table& table, std::vector<std::shared_ptr<Card>>& cardsVisible, Deck& deck) {
		// 1733, 936				
		Vector2 mP = GetMousePosition();

		Rectangle buttonHitBox = { 1733, 936, 150, 75 };

		if (CheckCollisionPointRec(mP, buttonHitBox) && c2::can_end_attack(table)) {

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

				c2::end_attack(deck, mg, bPile, table, cardsVisible, players);

				DrawTexture(endMid, 1733, 936, WHITE);
			}
			else {

				DrawTexture(endHigh, 1733, 936, WHITE);
			}
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

				PlaySound(fxButton);
			}
		}
		else {

			DrawTexture(endLow, 1733, 936, WHITE);
		}
	}

	void displayTakeButtons(Deck& deck, std::vector<std::shared_ptr<Card>>& cardsVisible, std::array<Player, 2>& players, MainGame& mg, Table& table, Texture2D& takeHigh, Texture2D& takeMid, Texture2D& takeLow) {
		//Either something incorrectly writes to this or the system isn't right since 
		Vector2 mP = GetMousePosition();

		Rectangle buttonHitBox = { 1733, 936, 150, 75 };

		if (CheckCollisionPointRec(mP, buttonHitBox)) {

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT && !c2::can_end_attack(table))) {

				c2::takeDefender(players, cardsVisible, deck, table, mg);

				DrawTexture(takeMid, 1733, 936, WHITE);
			}
			else {

				DrawTexture(takeHigh, 1733, 936, WHITE);
			}
			//if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {}
		}
		else {

			DrawTexture(takeLow, 1733, 936, WHITE);
		}

	}

	void displayPlayerState(Texture2D& atkHigh, Texture2D& atkLow, Texture2D& defHigh, Texture2D& defLow, bool atkState) {
		//Atk pos is: 1658. 42
		//Def pos is: 1507.44
		if (atkState) {

			DrawTexture(atkHigh, 1658, 42, WHITE);

			DrawTexture(defLow, 1507, 44, WHITE);
		}
		else {

			DrawTexture(atkLow, 1658, 42, WHITE);

			DrawTexture(defHigh, 1507, 44, WHITE);
		}
	}

	void displayWhosTurnItIs(MainGame& mg) {

		auto turn = mg.getPTurn();
		if (turn) {

			DrawRectangle(1658, 102, 100, 20, WHITE);
		}
		else if (!turn) {

			DrawRectangle(1507, 102, 100, 20, WHITE);
		}
	}

	void displayDeckSizeButtons(Rectangle& thirty, Rectangle& fifty, const bool& thirtySelected, const int& currentMusicSize, const bool& pirivadnoy) {

		Vector2 mP = GetMousePosition();

		const std::string threeSix = "36";

		const std::string fiveTwo = "52";

		if (CheckCollisionPointRec(mP, thirty)) {

			DrawRectangleRec(thirty, (thirtySelected) ? ORANGE : SKYBLUE);// The thirty selected bool is used to see find what the current deckSize is

			DrawRectangleRec(fifty, (thirtySelected) ? BLUE : RED);

			DrawText(threeSix.c_str(), static_cast<int>(thirty.x + (thirty.width / 2) - 35), static_cast<int>(thirty.y + (thirty.height / 2) - 25), 60, WHITE);

			DrawText(fiveTwo.c_str(), static_cast<int>(fifty.x + (fifty.width / 2) - 35), static_cast<int>(fifty.y + (fifty.height / 2) - 25), 60, WHITE);

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

				c3::setDeckSize(36, currentMusicSize, pirivadnoy);
			}
		}
		else if (CheckCollisionPointRec(mP, fifty)) {

			DrawRectangleRec(fifty, (thirtySelected) ? SKYBLUE : ORANGE);

			DrawRectangleRec(thirty, (thirtySelected) ? RED : BLUE);

			DrawText(threeSix.c_str(), static_cast<int>(thirty.x + (thirty.width / 2) - 35), static_cast<int>(thirty.y + (thirty.height / 2) - 25), 60, WHITE);

			DrawText(fiveTwo.c_str(), static_cast<int>(fifty.x + (fifty.width / 2) - 35), static_cast<int>(fifty.y + (fifty.height / 2) - 25), 60, WHITE);

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

				c3::setDeckSize(52, currentMusicSize, pirivadnoy);
			}
		}
		else {

			DrawRectangleRec(thirty, (thirtySelected) ? RED : BLUE);

			DrawRectangleRec(fifty, (thirtySelected) ? BLUE : RED);

			DrawText(threeSix.c_str(), static_cast<int>(thirty.x + (thirty.width / 2) - 35), static_cast<int>(thirty.y + (thirty.height / 2) - 25), 60, WHITE);

			DrawText(fiveTwo.c_str(), static_cast<int>(fifty.x + (fifty.width / 2) - 35), static_cast<int>(fifty.y + (fifty.height / 2) - 25), 60, WHITE);
		}
	}

	void displayTextForMusicButtons(const std::string& msg, const int x, const int y) {

		DrawText(msg.c_str(), x, y, 20, WHITE);
	}

	void displayMusicButtons(const Rectangle& noMusic, const Rectangle& jazzMusic, const Rectangle& lofiMusic, const Rectangle& electroSwingMusic, const  Music& JazzMusic, const Music& LofiMusic, const  Music& eSwingMusic, const int& selection, const int& deckSize, int& currentMusicNum, const bool& pirivadnoy) {

		const std::string nM = "No Music";

		const std::string jM = "Jazz Music";

		const std::string lM = "LoFi Music";

		const std::string eM = "Electro Swing Music";

		const Vector2 mP = GetMousePosition();

		if (CheckCollisionPointRec(mP, noMusic)) {

			DrawRectangleRec(noMusic, (selection == 1) ? ORANGE : SKYBLUE);

			DrawRectangleRec(jazzMusic, (selection == 2) ? RED : BLUE);

			DrawRectangleRec(lofiMusic, (selection == 3) ? RED : BLUE);

			DrawRectangleRec(electroSwingMusic, (selection == 4) ? RED : BLUE);

			displayTextForMusicButtons(nM, static_cast<int>(noMusic.x + (noMusic.width / 2) - 35), static_cast<int>(noMusic.y + (noMusic.height / 2) - 25));

			displayTextForMusicButtons(jM, static_cast<int>(jazzMusic.x + (jazzMusic.width / 2) - 35), static_cast<int>(jazzMusic.y + (jazzMusic.height / 2) - 25));

			displayTextForMusicButtons(lM, static_cast<int>(lofiMusic.x + (lofiMusic.width / 2) - 35), static_cast<int>(lofiMusic.y + (lofiMusic.height / 2) - 25));

			displayTextForMusicButtons(eM, static_cast<int>(electroSwingMusic.x + (electroSwingMusic.width / 2) - 100), static_cast<int>(electroSwingMusic.y + (electroSwingMusic.height / 2) - 25));

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !(selection == 1)) {

				c3::setMusicalNumber(1, deckSize, pirivadnoy);

				currentMusicNum = 1;

				c2::play_music(1, JazzMusic, LofiMusic, eSwingMusic);
			}
		}
		else if (CheckCollisionPointRec(mP, jazzMusic)) {

			DrawRectangleRec(noMusic, (selection == 1) ? RED : BLUE);

			DrawRectangleRec(jazzMusic, (selection == 2) ? ORANGE : SKYBLUE);

			DrawRectangleRec(lofiMusic, (selection == 3) ? RED : BLUE);

			DrawRectangleRec(electroSwingMusic, (selection == 4) ? RED : BLUE);

			displayTextForMusicButtons(nM, static_cast<int>(noMusic.x + (noMusic.width / 2) - 35), static_cast<int>(noMusic.y + (noMusic.height / 2) - 25));

			displayTextForMusicButtons(jM, static_cast<int>(jazzMusic.x + (jazzMusic.width / 2) - 35), static_cast<int>(jazzMusic.y + (jazzMusic.height / 2) - 25));

			displayTextForMusicButtons(lM, static_cast<int>(lofiMusic.x + (lofiMusic.width / 2) - 35), static_cast<int>(lofiMusic.y + (lofiMusic.height / 2) - 25));

			displayTextForMusicButtons(eM, static_cast<int>(electroSwingMusic.x + (electroSwingMusic.width / 2) - 100), static_cast<int>(electroSwingMusic.y + (electroSwingMusic.height / 2) - 25));

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !(selection == 2)) {

				c3::setMusicalNumber(2, deckSize, pirivadnoy);

				currentMusicNum = 2;

				c2::play_music(2, JazzMusic, LofiMusic, eSwingMusic);
			}
		}
		else if (CheckCollisionPointRec(mP, lofiMusic)) {

			DrawRectangleRec(noMusic, (selection == 1) ? RED : BLUE);			

			DrawRectangleRec(jazzMusic, (selection == 2) ? RED : BLUE);

			DrawRectangleRec(lofiMusic, (selection == 3) ? ORANGE : SKYBLUE);

			DrawRectangleRec(electroSwingMusic, (selection == 4) ? RED : BLUE);

			displayTextForMusicButtons(nM, static_cast<int>(noMusic.x + (noMusic.width / 2) - 35), static_cast<int>(noMusic.y + (noMusic.height / 2) - 25));

			displayTextForMusicButtons(jM, static_cast<int>(jazzMusic.x + (jazzMusic.width / 2) - 35), static_cast<int>(jazzMusic.y + (jazzMusic.height / 2) - 25));

			displayTextForMusicButtons(lM, static_cast<int>(lofiMusic.x + (lofiMusic.width / 2) - 35), static_cast<int>(lofiMusic.y + (lofiMusic.height / 2) - 25));

			displayTextForMusicButtons(eM, static_cast<int>(electroSwingMusic.x + (electroSwingMusic.width / 2) - 100), static_cast<int>(electroSwingMusic.y + (electroSwingMusic.height / 2) - 25));

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !(selection == 3)) {

				c3::setMusicalNumber(3, deckSize, pirivadnoy);

				currentMusicNum = 3;

				c2::play_music(3, JazzMusic, LofiMusic, eSwingMusic);
			}
		}
		else if (CheckCollisionPointRec(mP, electroSwingMusic)) {

			DrawRectangleRec(noMusic, (selection == 1) ? RED : BLUE);

			DrawRectangleRec(jazzMusic, (selection == 2) ? RED : BLUE);

			DrawRectangleRec(lofiMusic, (selection == 3) ? RED : BLUE);

			DrawRectangleRec(electroSwingMusic, (selection == 4) ? ORANGE : SKYBLUE);

			displayTextForMusicButtons(nM, static_cast<int>(noMusic.x + (noMusic.width / 2) - 35), static_cast<int>(noMusic.y + (noMusic.height / 2) - 25));

			displayTextForMusicButtons(jM, static_cast<int>(jazzMusic.x + (jazzMusic.width / 2) - 35), static_cast<int>(jazzMusic.y + (jazzMusic.height / 2) - 25));

			displayTextForMusicButtons(lM, static_cast<int>(lofiMusic.x + (lofiMusic.width / 2) - 35), static_cast<int>(lofiMusic.y + (lofiMusic.height / 2) - 25));

			displayTextForMusicButtons(eM, static_cast<int>(electroSwingMusic.x + (electroSwingMusic.width / 2) - 100), static_cast<int>(electroSwingMusic.y + (electroSwingMusic.height / 2) - 25));

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !(selection == 4)) {

				c3::setMusicalNumber(4, deckSize, pirivadnoy);

				currentMusicNum = 4;

				c2::play_music(4, JazzMusic, LofiMusic, eSwingMusic);
			}
		}
		else {

			DrawRectangleRec(noMusic, (selection == 1) ? RED : BLUE);

			DrawRectangleRec(jazzMusic, (selection == 2) ? RED : BLUE);

			DrawRectangleRec(lofiMusic, (selection == 3) ? RED : BLUE);

			DrawRectangleRec(electroSwingMusic, (selection == 4) ? RED : BLUE);

			displayTextForMusicButtons(nM, static_cast<int>(noMusic.x + (noMusic.width / 2) - 35), static_cast<int>(noMusic.y + (noMusic.height / 2) - 25));

			displayTextForMusicButtons(jM, static_cast<int>(jazzMusic.x + (jazzMusic.width / 2) - 35), static_cast<int>(jazzMusic.y + (jazzMusic.height / 2) - 25));

			displayTextForMusicButtons(lM, static_cast<int>(lofiMusic.x + (lofiMusic.width / 2) - 35), static_cast<int>(lofiMusic.y + (lofiMusic.height / 2) - 25));

			displayTextForMusicButtons(eM, static_cast<int>(electroSwingMusic.x + (electroSwingMusic.width / 2) - 100), static_cast<int>(electroSwingMusic.y + (electroSwingMusic.height / 2) - 25));

		}
	}

	void displaySpecialCards(Deck& deck, Texture2D& backOfCard, Texture2D& blankCard) {

		const std::shared_ptr<Card> deckCard = deck.getTopOfVisDeck();

		if (deck.getDeckSize() > 0) {

			const std::shared_ptr<Card> visibleCard = deck.getLastCard();

			DrawTextureEx(blankCard, visibleCard->card_position, 90.0f, 1.0f, WHITE);

			std::string cValStr = (encrypt_data(visibleCard->get_card_value()) > 10) ? visibleCard->valueToString(static_cast<card_value>(encrypt_data(visibleCard->get_card_value()))) : std::to_string(encrypt_data(visibleCard->get_card_value()));

			std::string cSuitStr = visibleCard->suitToString(static_cast<card_suit>(encrypt_data(visibleCard->get_card_suit())));

			DrawText(cValStr.c_str(), static_cast<int>((visibleCard->card_position.x - 105)), static_cast<int>((visibleCard->card_position.y + 20)), 30, BLACK);

			DrawText(cSuitStr.c_str(), static_cast<int>((visibleCard->card_position.x - 105)), static_cast<int>((visibleCard->card_position.y + 65)), 25, BLACK);
		}

		DrawTexture(backOfCard, static_cast<int>(deckCard->card_position.x), static_cast<int>(deckCard->card_position.y), WHITE);
	}	

	void display_pirivadnoy_buttons(const int& musical_number, const int& deck_size, bool& pirivadnoy) {

		const Vector2 mouse_position = GetMousePosition();

		const std::string text_no = "No";

		const std::string text_yes = "Yes";

		const Rectangle left_button = { 549,591,400,86 };

		const Rectangle right_button = { 963,590,400,86 };

		if (CheckCollisionPointRec(mouse_position, left_button)) {

			DrawRectangleRec(left_button, pirivadnoy ? ORANGE : SKYBLUE);

			DrawRectangleRec(right_button, pirivadnoy ? BLUE : RED);

			DrawText(text_yes.c_str(), static_cast<int>(left_button.x + left_button.width / 2 - 35), static_cast<int>(left_button.y + left_button.height / 2 - 35), 60, WHITE);

			DrawText(text_no.c_str(), static_cast<int>(right_button.x + right_button.width / 2 - 35), static_cast<int>(right_button.y + right_button.height / 2 - 35), 60, WHITE);

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

				c3::set_pirivadnoy_state(deck_size, musical_number, true);
				pirivadnoy = true;
			}
		}

		else if (CheckCollisionPointRec(mouse_position, right_button)) {

			DrawRectangleRec(right_button, pirivadnoy ? SKYBLUE : ORANGE);

			DrawRectangleRec(left_button, pirivadnoy ? RED : BLUE);

			DrawText(text_yes.c_str(), static_cast<int>(left_button.x + left_button.width / 2 - 35), static_cast<int>(left_button.y + left_button.height / 2 - 35), 60, WHITE);

			DrawText(text_no.c_str(), static_cast<int>(right_button.x + right_button.width / 2 - 35), static_cast<int>(right_button.y + right_button.height / 2 - 35), 60, WHITE);

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

				pirivadnoy = false;

				c3::set_pirivadnoy_state(deck_size, musical_number, false);				
			}
		}

		else {

			DrawRectangleRec(right_button, pirivadnoy ? BLUE : RED);

			DrawRectangleRec(left_button, pirivadnoy ? RED : BLUE);

			DrawText(text_yes.c_str(), static_cast<int>(left_button.x + left_button.width / 2 - 35), static_cast<int>(left_button.y + left_button.height / 2 - 35), 60, WHITE);

			DrawText(text_no.c_str(), static_cast<int>(right_button.x + right_button.width / 2 - 35), static_cast<int>(right_button.y + right_button.height / 2 - 35), 60, WHITE);
		}
	}
}
