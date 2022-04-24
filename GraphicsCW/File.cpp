#include "File.hpp"

namespace c3 {// C3 will be for reading and writing to files (for settings)

	extern inline void setDeckSize(const int& deckSize, const int& currentMusicVal, const bool& pirivadnoy) {

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

				save_file << "\n1";
				break;
			}

			if (pirivadnoy)
				save_file << "\n1";

			else
				save_file << "\n0";			

			save_file.close();
		}
	}

	extern inline int getDeckSize() {

		std::ifstream save_file(fileName, std::ios::in);

		std::string size;

		try
		{
			save_file.seekg(std::ios::beg);

			std::getline(save_file, size);

			if (size == "")
				throw std::exception();

			if (size == "36")
				return 36;

			if (size == "52")
				return 52;
			throw std::exception();
		}
		catch (const std::exception&)
		{
			//throw std::runtime_error("Error opening or reading deck size");

			setDeckSize(36, 1, false);

			return 36;
		}
		

		

		return 0;
	}

	extern inline void setMusicalNumber(const int& num, const int& currentDeckSize, const bool& pirivadnoy) {

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
			}

			if(pirivadnoy)
				save_file << "\n1";

			else
				save_file << "\n0";
		}
	}

	extern inline int getMusicNumber() {

		std::ifstream save_file(fileName, std::ios::in);


		try
		{
			std::string num;

			std::getline(save_file, num);

			std::getline(save_file, num);

			if (num == "")
				throw std::exception();

			if (num == "1")
				return 1;

			if (num == "2")
				return 2;

			if (num == "3")
				return 3;

			if (num == "4")
				return 4;

			throw std::exception();
		}
		catch (const std::exception&)
		{
			//throw std::runtime_error("Error reading music number");

			setDeckSize(36, 1, false);

			return 1;
		}

		
	}

	extern inline void set_pirivadnoy_state(const int& deckSize, const int& currentMusicVal, const bool& pirivadnoy) {

		std::ofstream save_file(fileName, std::ios::out);

		if (save_file) {

			save_file << deckSize;

			save_file << "\n" << currentMusicVal;

			if (pirivadnoy)
				save_file << "\n1";
			else
				save_file << "\n0";
		}
	}

	extern inline bool get_pirivadnoy_state() {

		std::ifstream save_file(fileName, std::ios::in);

		try
		{
			std::string state;

			std::getline(save_file, state);

			std::getline(save_file, state);

			std::getline(save_file, state);

			if (state == "")
				throw std::exception();

			return state == "1" ? true : false;

			throw std::exception();
		}
		catch (const std::exception&)
		{
			//throw std::runtime_error("Error reading pirivadnoy state");

			setDeckSize(36, 1, false);

			return false;
		}
	}
}
