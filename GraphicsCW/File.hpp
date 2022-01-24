#pragma once

#include "Setup.hpp"

namespace c3 {// C3 will be for reading and writing to files (for settings)

	extern inline void setDeckSize(const int& deckSize, const int& currentMusicVal, const bool& pirivadnoy);

	extern inline int getDeckSize();

	extern inline void setMusicalNumber(const int& num, const int& currentDeckSize, const bool& pirivadnoy);

	extern inline int getMusicNumber();

	extern inline void set_pirivadnoy_state(const int& deckSize, const int& currentMusicVal, const bool& pirivadnoy);

	extern inline bool get_pirivadnoy_state();

}


