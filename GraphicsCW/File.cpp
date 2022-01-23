#include "File.hpp"

namespace c3 {// C3 will be for reading and writing to files (for settings)

	extern inline void setDeckSize(const int deckSize, const int currentMusicVal) {

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

			save_file.close();
		}
	}

	extern inline int getDeckSize() {

		std::ifstream save_file(fileName, std::ios::in);

		if (!save_file) {

			setDeckSize(36, 1);

			return 36;
		}

		std::string size;

		save_file.seekg(std::ios::beg);

		std::getline(save_file, size);

		if (size == "36")
			return 36;

		if (size == "52")
			return 52;

		return 0;
	}

	extern inline void setMusicalNumber(const int num, const int currentDeckSize) {

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

	extern inline int getMusicNumber() {

		std::ifstream save_file(fileName, std::ios::in);

		if (!save_file) {

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
