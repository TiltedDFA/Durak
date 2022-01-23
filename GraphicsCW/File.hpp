#pragma once

#include "Setup.hpp"

namespace c3 {// C3 will be for reading and writing to files (for settings)

	extern inline void setDeckSize(const int deckSize, const int currentMusicVal);

	extern inline int getDeckSize();

	extern inline void setMusicalNumber(const int num, const int currentDeckSize);

	extern inline int getMusicNumber();

}


